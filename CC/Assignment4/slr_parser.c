#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSYM 100
#define MAXLEN 20
#define MAXPROD 100
#define MAXRHS 20
#define MAXLINE 200
#define MAXSTATES 300
#define MAXITEMS 200

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
int augStartSymbol = -1;
int augProdIndex = -1;
int dollarIndex = -1;

int symbolExists(const char *name) {
    int i;
    for (i = 0; i < numSymbols; i++)
        if (strcmp(symbols[i], name) == 0) return i;
    return -1;
}

int getSymbolIndex(const char *name) {
    int idx = symbolExists(name);
    if (idx != -1) return idx;
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
    printf("E -> E + T | T\n");
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

void computeFollowSets(int seedSymbol) {
    addToSet(followSet, followCount, seedSymbol, dollarIndex);

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

typedef struct {
    int prod;
    int dot;
} Item;

typedef struct {
    Item items[MAXITEMS];
    int count;
} ItemSet;

int itemEqual(Item a, Item b) {
    return a.prod == b.prod && a.dot == b.dot;
}

int addItem(ItemSet *s, Item it) {
    int i;
    for (i = 0; i < s->count; i++)
        if (itemEqual(s->items[i], it)) return 0;
    s->items[s->count] = it;
    s->count++;
    return 1;
}

void closureSet(ItemSet *I) {
    int changed = 1;
    while (changed) {
        changed = 0;
        int i;
        int n = I->count;
        for (i = 0; i < n; i++) {
            Item it = I->items[i];
            if (it.dot < prod[it.prod].rhsLen) {
                int sym = prod[it.prod].rhs[it.dot];
                if (isNonTerminal[sym]) {
                    int p;
                    for (p = 0; p < numProd; p++) {
                        if (prod[p].lhs == sym) {
                            Item ni;
                            ni.prod = p;
                            ni.dot = 0;
                            if (addItem(I, ni)) changed = 1;
                        }
                    }
                }
            }
        }
    }
}

int itemSetEqual(ItemSet *a, ItemSet *b) {
    if (a->count != b->count) return 0;
    int i;
    for (i = 0; i < a->count; i++) {
        int found = 0, j;
        for (j = 0; j < b->count; j++)
            if (itemEqual(a->items[i], b->items[j])) { found = 1; break; }
        if (!found) return 0;
    }
    return 1;
}

void gotoSet(ItemSet *I, int sym, ItemSet *J) {
    J->count = 0;
    int i;
    for (i = 0; i < I->count; i++) {
        Item it = I->items[i];
        if (it.dot < prod[it.prod].rhsLen && prod[it.prod].rhs[it.dot] == sym) {
            Item ni;
            ni.prod = it.prod;
            ni.dot = it.dot + 1;
            addItem(J, ni);
        }
    }
    closureSet(J);
}

ItemSet states[MAXSTATES];
int numStates = 0;
int delta[MAXSTATES][MAXSYM];

void buildCanonicalCollection(void) {
    int i, sym;
    for (i = 0; i < MAXSTATES; i++)
        for (sym = 0; sym < MAXSYM; sym++)
            delta[i][sym] = -1;

    ItemSet start;
    start.count = 0;
    Item startItem;
    startItem.prod = augProdIndex;
    startItem.dot = 0;
    addItem(&start, startItem);
    closureSet(&start);
    states[0] = start;
    numStates = 1;

    for (i = 0; i < numStates; i++) {
        for (sym = 0; sym < numSymbols; sym++) {
            if (delta[i][sym] != -1) continue;

            ItemSet J;
            gotoSet(&states[i], sym, &J);
            if (J.count == 0) continue;

            int found = -1, k;
            for (k = 0; k < numStates; k++)
                if (itemSetEqual(&states[k], &J)) { found = k; break; }

            if (found >= 0) {
                delta[i][sym] = found;
            } else {
                states[numStates] = J;
                delta[i][sym] = numStates;
                numStates++;
            }
        }
    }
}

typedef struct {
    char type;
    int value;
} ActionCell;

ActionCell actionTable[MAXSTATES][MAXSYM];
int conflictCount = 0;

void buildTables(void) {
    int i, sym;
    for (i = 0; i < numStates; i++)
        for (sym = 0; sym < MAXSYM; sym++)
            actionTable[i][sym].type = ' ';

    for (i = 0; i < numStates; i++) {
        int k;
        for (k = 0; k < states[i].count; k++) {
            Item it = states[i].items[k];
            Production p = prod[it.prod];

            if (it.dot < p.rhsLen) {
                int sym = p.rhs[it.dot];
                if (!isNonTerminal[sym]) {
                    int j = delta[i][sym];
                    if (j == -1) continue;
                    if (actionTable[i][sym].type != ' ' &&
                        !(actionTable[i][sym].type == 'S' && actionTable[i][sym].value == j)) {
                        printf("Conflict at state %d on symbol %s\n", i, symbols[sym]);
                        conflictCount++;
                    }
                    actionTable[i][sym].type = 'S';
                    actionTable[i][sym].value = j;
                }
            } else {
                if (it.prod == augProdIndex) {
                    if (actionTable[i][dollarIndex].type != ' ') {
                        printf("Conflict at state %d on symbol $\n", i);
                        conflictCount++;
                    }
                    actionTable[i][dollarIndex].type = 'A';
                    actionTable[i][dollarIndex].value = 0;
                } else {
                    int a;
                    for (a = 0; a < followCount[p.lhs]; a++) {
                        int sym = followSet[p.lhs][a];
                        if (actionTable[i][sym].type != ' ' &&
                            !(actionTable[i][sym].type == 'R' && actionTable[i][sym].value == it.prod)) {
                            printf("Conflict at state %d on symbol %s\n", i, symbols[sym]);
                            conflictCount++;
                        }
                        actionTable[i][sym].type = 'R';
                        actionTable[i][sym].value = it.prod;
                    }
                }
            }
        }
    }
}

void printProductionText(int p) {
    printf("%s ->", symbols[prod[p].lhs]);
    if (prod[p].rhsLen == 0) {
        printf(" eps");
    } else {
        int i;
        for (i = 0; i < prod[p].rhsLen; i++)
            printf(" %s", symbols[prod[p].rhs[i]]);
    }
}

void printItemText(Item it) {
    Production p = prod[it.prod];
    printf("%s ->", symbols[p.lhs]);
    int i;
    for (i = 0; i < p.rhsLen; i++) {
        if (i == it.dot) printf(" .");
        printf(" %s", symbols[p.rhs[i]]);
    }
    if (it.dot == p.rhsLen) printf(" .");
}

void printStates(void) {
    int i, k;
    for (i = 0; i < numStates; i++) {
        printf("State %d\n", i);
        for (k = 0; k < states[i].count; k++) {
            printf("  ");
            printItemText(states[i].items[k]);
            printf("\n");
        }
    }
}

void printActionGotoTables(void) {
    int termList[MAXSYM], termCount = 0;
    int ntList[MAXSYM], ntCount = 0;
    int i;

    for (i = 0; i < numSymbols; i++) {
        if (isNonTerminal[i]) {
            if (i != augStartSymbol) ntList[ntCount++] = i;
        } else {
            termList[termCount++] = i;
        }
    }

    printf("\nACTION table\n");
    printf("%-6s", "State");
    for (i = 0; i < termCount; i++) printf("%-8s", symbols[termList[i]]);
    printf("\n");

    int s;
    for (s = 0; s < numStates; s++) {
        printf("%-6d", s);
        for (i = 0; i < termCount; i++) {
            ActionCell c = actionTable[s][termList[i]];
            char buf[16];
            if (c.type == ' ') strcpy(buf, "");
            else if (c.type == 'A') strcpy(buf, "acc");
            else sprintf(buf, "%c%d", c.type, c.value);
            printf("%-8s", buf);
        }
        printf("\n");
    }

    printf("\nGOTO table\n");
    printf("%-6s", "State");
    for (i = 0; i < ntCount; i++) printf("%-8s", symbols[ntList[i]]);
    printf("\n");

    for (s = 0; s < numStates; s++) {
        printf("%-6d", s);
        for (i = 0; i < ntCount; i++) {
            int j = delta[s][ntList[i]];
            char buf[16];
            if (j == -1) strcpy(buf, "");
            else sprintf(buf, "%d", j);
            printf("%-8s", buf);
        }
        printf("\n");
    }
}

void parseInput(void) {
    char line[MAXLINE];
    printf("\nEnter input string to parse (space separated symbols): ");
    fgets(line, MAXLINE, stdin);

    int inputSyms[MAXLINE];
    int inputLen = 0;

    char lineCopy[MAXLINE];
    strcpy(lineCopy, line);
    char *save;
    char *tok = strtok_r(lineCopy, " \t\r\n", &save);
    while (tok) {
        int idx = symbolExists(tok);
        if (idx == -1 || isNonTerminal[idx]) {
            printf("Unknown terminal symbol: %s\n", tok);
            return;
        }
        inputSyms[inputLen++] = idx;
        tok = strtok_r(NULL, " \t\r\n", &save);
    }
    inputSyms[inputLen++] = dollarIndex;

    int stateStack[MAXLINE];
    int symStack[MAXLINE];
    int top = 0;
    stateStack[0] = 0;
    symStack[0] = -1;
    int ip = 0;

    printf("\n%-30s%-25s%s\n", "Stack", "Input", "Action");
    while (1) {
        int s = stateStack[top];
        int a = inputSyms[ip];
        ActionCell c = actionTable[s][a];

        char stackBuf[MAXLINE];
        stackBuf[0] = '\0';
        int si;
        for (si = 0; si <= top; si++) {
            if (symStack[si] != -1) {
                strcat(stackBuf, symbols[symStack[si]]);
                strcat(stackBuf, " ");
            }
            char numBuf[16];
            sprintf(numBuf, "%d ", stateStack[si]);
            strcat(stackBuf, numBuf);
        }

        char inputBuf[MAXLINE];
        inputBuf[0] = '\0';
        int ii;
        for (ii = ip; ii < inputLen; ii++) {
            strcat(inputBuf, symbols[inputSyms[ii]]);
            strcat(inputBuf, " ");
        }

        if (c.type == 'S') {
            printf("%-30s%-25sshift\n", stackBuf, inputBuf);
            top++;
            symStack[top] = a;
            stateStack[top] = c.value;
            ip++;
        } else if (c.type == 'R') {
            printf("%-30s%-25sreduce ", stackBuf, inputBuf);
            printProductionText(c.value);
            printf("\n");

            int popCount = prod[c.value].rhsLen;
            top -= popCount;
            int t = stateStack[top];
            top++;
            symStack[top] = prod[c.value].lhs;
            stateStack[top] = delta[t][prod[c.value].lhs];
        } else if (c.type == 'A') {
            printf("%-30s%-25saccept\n", stackBuf, inputBuf);
            printf("\nInput string is accepted by the grammar.\n");
            return;
        } else {
            printf("%-30s%-25serror\n", stackBuf, inputBuf);
            printf("\nSyntax error: no action for state %d on symbol %s\n", s, symbols[a]);
            return;
        }
    }
}

int main(void) {
    readGrammarInteractive();

    char augName[MAXLEN + 10];
    snprintf(augName, sizeof(augName), "%s'", symbols[startSymbol]);
    while (symbolExists(augName) != -1 && strlen(augName) < sizeof(augName) - 1)
        strcat(augName, "'");
    if (strlen(augName) > MAXLEN - 1) augName[MAXLEN - 1] = '\0';
    augStartSymbol = getSymbolIndex(augName);
    isNonTerminal[augStartSymbol] = 1;

    Production augProd;
    augProd.lhs = augStartSymbol;
    augProd.rhsLen = 1;
    augProd.rhs[0] = startSymbol;
    prod[numProd] = augProd;
    augProdIndex = numProd;
    numProd++;

    dollarIndex = getSymbolIndex("$");

    computeFirstSets();
    computeFollowSets(augStartSymbol);

    buildCanonicalCollection();
    buildTables();

    printf("\nLR(0) canonical collection\n");
    printStates();

    printActionGotoTables();

    if (conflictCount > 0)
        printf("\nGrammar is not SLR(1): %d conflict(s) found.\n", conflictCount);

    parseInput();

    return 0;
}
