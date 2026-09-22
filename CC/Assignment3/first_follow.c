#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSYM 100
#define MAXLEN 20
#define MAXPROD 100
#define MAXRHS 20
#define MAXLINE 200

char symbols[MAXSYM][MAXLEN];
int numSymbols = 0;
int isNonTerminal[MAXSYM];

typedef struct {
    int lhs;
    int rhs[MAXRHS];
    int rhsLen;
} Production;

Production prod[MAXPROD];
int numProd = 0;

int firstSet[MAXSYM][MAXSYM];
int firstCount[MAXSYM];
int nullable[MAXSYM];

int followSet[MAXSYM][MAXSYM];
int followCount[MAXSYM];

int startSymbol = -1;
int dollarIndex = -1;

int getSymbolIndex(const char *name) {
    int i;
    for (i = 0; i < numSymbols; i++)
        if (strcmp(symbols[i], name) == 0) return i;
    strcpy(symbols[numSymbols], name);
    isNonTerminal[numSymbols] = 0;
    numSymbols++;
    return numSymbols - 1;
}

int addToSet(int set[MAXSYM][MAXSYM], int *count, int idx, int sym) {
    int i;
    for (i = 0; i < count[idx]; i++)
        if (set[idx][i] == sym) return 0;
    set[idx][count[idx]] = sym;
    count[idx]++;
    return 1;
}

void readProductionLine(char *line) {
    char *arrow = strstr(line, "->");
    if (!arrow) return;

    char lhsName[MAXLEN];
    sscanf(line, "%s", lhsName);
    int lhs = getSymbolIndex(lhsName);
    isNonTerminal[lhs] = 1;
    if (startSymbol == -1) startSymbol = lhs;

    char *rest = arrow + 2;
    char *altSave;
    char *alt = strtok_r(rest, "|", &altSave);
    while (alt) {
        Production p;
        p.lhs = lhs;
        p.rhsLen = 0;

        char altCopy[MAXLINE];
        strcpy(altCopy, alt);
        char *tokSave;
        char *tok = strtok_r(altCopy, " \t\r\n", &tokSave);
        while (tok) {
            if (strcmp(tok, "eps") != 0) {
                p.rhs[p.rhsLen] = getSymbolIndex(tok);
                p.rhsLen++;
            }
            tok = strtok_r(NULL, " \t\r\n", &tokSave);
        }

        prod[numProd] = p;
        numProd++;
        alt = strtok_r(NULL, "|", &altSave);
    }
}

void readGrammarInteractive(void) {
    int n, i;

    printf("Enter number of productions: ");
    scanf("%d", &n);
    getchar();

    printf("\nEnter productions in the form:\n");
    printf("E -> T Ex | eps\n");
    printf("Use eps for epsilon.\n");
    printf("Separate symbols using spaces.\n\n");

    for (i = 0; i < n; i++) {
        char line[MAXLINE];
        printf("Production %d: ", i + 1);
        fgets(line, MAXLINE, stdin);
        readProductionLine(line);
    }
}

void computeFirstSets(void) {
    int changed = 1;
    while (changed) {
        changed = 0;
        int p;
        for (p = 0; p < numProd; p++) {
            int lhs = prod[p].lhs;

            if (prod[p].rhsLen == 0) {
                if (!nullable[lhs]) { nullable[lhs] = 1; changed = 1; }
                continue;
            }

            int i;
            int allNullableSoFar = 1;
            for (i = 0; i < prod[p].rhsLen; i++) {
                int sym = prod[p].rhs[i];

                if (!isNonTerminal[sym]) {
                    if (addToSet(firstSet, firstCount, lhs, sym)) changed = 1;
                    allNullableSoFar = 0;
                    break;
                }

                int j;
                for (j = 0; j < firstCount[sym]; j++)
                    if (addToSet(firstSet, firstCount, lhs, firstSet[sym][j])) changed = 1;

                if (!nullable[sym]) { allNullableSoFar = 0; break; }
            }

            if (allNullableSoFar && !nullable[lhs]) { nullable[lhs] = 1; changed = 1; }
        }
    }
}

void firstOfSequence(int *seq, int len, int result[MAXSYM], int *resultCount, int *seqNullable) {
    *resultCount = 0;
    *seqNullable = 1;
    int i;
    for (i = 0; i < len; i++) {
        int sym = seq[i];

        if (!isNonTerminal[sym]) {
            int already = 0, k;
            for (k = 0; k < *resultCount; k++) if (result[k] == sym) already = 1;
            if (!already) result[(*resultCount)++] = sym;
            *seqNullable = 0;
            return;
        }

        int j;
        for (j = 0; j < firstCount[sym]; j++) {
            int t = firstSet[sym][j];
            int already = 0, k;
            for (k = 0; k < *resultCount; k++) if (result[k] == t) already = 1;
            if (!already) result[(*resultCount)++] = t;
        }

        if (!nullable[sym]) { *seqNullable = 0; return; }
    }
}

void computeFollowSets(void) {
    addToSet(followSet, followCount, startSymbol, dollarIndex);

    int changed = 1;
    while (changed) {
        changed = 0;
        int p;
        for (p = 0; p < numProd; p++) {
            int i;
            for (i = 0; i < prod[p].rhsLen; i++) {
                int sym = prod[p].rhs[i];
                if (!isNonTerminal[sym]) continue;

                int rest[MAXSYM], restLen;
                int seqNullable;
                firstOfSequence(&prod[p].rhs[i + 1], prod[p].rhsLen - i - 1, rest, &restLen, &seqNullable);

                int j;
                for (j = 0; j < restLen; j++)
                    if (addToSet(followSet, followCount, sym, rest[j])) changed = 1;

                if (seqNullable) {
                    int k;
                    for (k = 0; k < followCount[prod[p].lhs]; k++)
                        if (addToSet(followSet, followCount, sym, followSet[prod[p].lhs][k])) changed = 1;
                }
            }
        }
    }
}

void printSets(void) {
    int i, j;
    printf("FIRST sets\n");
    for (i = 0; i < numSymbols; i++) {
        if (!isNonTerminal[i]) continue;
        printf("FIRST(%s) = { ", symbols[i]);
        for (j = 0; j < firstCount[i]; j++) {
            printf("%s", symbols[firstSet[i][j]]);
            if (j < firstCount[i] - 1 || nullable[i]) printf(", ");
        }
        if (nullable[i]) printf("eps");
        printf(" }\n");
    }

    printf("\nFOLLOW sets\n");
    for (i = 0; i < numSymbols; i++) {
        if (!isNonTerminal[i]) continue;
        printf("FOLLOW(%s) = { ", symbols[i]);
        for (j = 0; j < followCount[i]; j++) {
            printf("%s", symbols[followSet[i][j]]);
            if (j < followCount[i] - 1) printf(", ");
        }
        printf(" }\n");
    }
}

int main(void) {
    readGrammarInteractive();

    dollarIndex = getSymbolIndex("$");
    
    printf("\n");
    computeFirstSets();
    computeFollowSets();
    printSets();

    return 0;
}
