#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    CLS_LETTER = 0,
    CLS_DIGIT,
    CLS_DOT,
    CLS_SQUOTE,
    CLS_DQUOTE,
    CLS_BACKSLASH,
    CLS_EQUAL,
    CLS_GT,
    CLS_PLUS,
    CLS_STAR,
    CLS_HASH,
    CLS_DELIM,
    CLS_SPACE,
    CLS_NEWLINE,
    CLS_NUL,
    CLS_OTHER,
    NUM_CLASSES
};

static unsigned char class_of[256];

static void build_char_classes(void) {
    int i;
    for (i = 0; i < 256; i++) class_of[i] = CLS_OTHER;

    for (i = 'a'; i <= 'z'; i++) class_of[i] = CLS_LETTER;
    for (i = 'A'; i <= 'Z'; i++) class_of[i] = CLS_LETTER;
    class_of[(unsigned char)'_'] = CLS_LETTER;
    for (i = '0'; i <= '9'; i++) class_of[i] = CLS_DIGIT;

    class_of[(unsigned char)'.']  = CLS_DOT;
    class_of[(unsigned char)'\''] = CLS_SQUOTE;
    class_of[(unsigned char)'"']  = CLS_DQUOTE;
    class_of[(unsigned char)'\\'] = CLS_BACKSLASH;
    class_of[(unsigned char)'=']  = CLS_EQUAL;
    class_of[(unsigned char)'>']  = CLS_GT;
    class_of[(unsigned char)'+']  = CLS_PLUS;
    class_of[(unsigned char)'*']  = CLS_STAR;
    class_of[(unsigned char)'#']  = CLS_HASH;

    class_of[(unsigned char)';'] = CLS_DELIM;
    class_of[(unsigned char)','] = CLS_DELIM;
    class_of[(unsigned char)'('] = CLS_DELIM;
    class_of[(unsigned char)')'] = CLS_DELIM;
    class_of[(unsigned char)'{'] = CLS_DELIM;
    class_of[(unsigned char)'}'] = CLS_DELIM;

    class_of[(unsigned char)' ']  = CLS_SPACE;
    class_of[(unsigned char)'\t'] = CLS_SPACE;
    class_of[(unsigned char)'\r'] = CLS_SPACE;
    class_of[(unsigned char)'\n'] = CLS_NEWLINE;
    class_of[0]                   = CLS_NUL;
}

enum {
    S_START = 0,
    S_IDENT,
    S_INT, S_FLOAT_DOT, S_FLOAT,
    S_CHAR_OPEN, S_CHAR_ESC, S_CHAR_BODY, S_CHAR_DONE,
    S_STR_BODY, S_STR_ESC, S_STR_DONE,
    S_PREPROC,
    S_PLUS, S_INC,
    S_ASSIGN,
    S_GREATER,
    S_STAR,
    S_DELIM,
    S_WS,
    S_NEWLINE,
    NUM_STATES
};

#define NO_TRANS (-1)
static int trans[NUM_STATES][NUM_CLASSES];

static void loop_except(int from, int to, int a, int b) {
    int c;
    for (c = 0; c < NUM_CLASSES; c++) {
        if (c == CLS_NUL || c == CLS_NEWLINE || c == a || c == b) continue;
        trans[from][c] = to;
    }
}
static void set(int from, int cls, int to) { trans[from][cls] = to; }

static void build_transition_table(void) {
    int s, c;
    for (s = 0; s < NUM_STATES; s++)
        for (c = 0; c < NUM_CLASSES; c++)
            trans[s][c] = NO_TRANS;

    set(S_START, CLS_LETTER,  S_IDENT);
    set(S_START, CLS_DIGIT,   S_INT);
    set(S_START, CLS_SQUOTE,  S_CHAR_OPEN);
    set(S_START, CLS_DQUOTE,  S_STR_BODY);
    set(S_START, CLS_HASH,    S_PREPROC);
    set(S_START, CLS_PLUS,    S_PLUS);
    set(S_START, CLS_EQUAL,   S_ASSIGN);
    set(S_START, CLS_GT,      S_GREATER);
    set(S_START, CLS_STAR,    S_STAR);
    set(S_START, CLS_DELIM,   S_DELIM);
    set(S_START, CLS_SPACE,   S_WS);
    set(S_START, CLS_NEWLINE, S_NEWLINE);

    set(S_IDENT, CLS_LETTER, S_IDENT);
    set(S_IDENT, CLS_DIGIT,  S_IDENT);

    set(S_INT, CLS_DIGIT, S_INT);
    set(S_INT, CLS_DOT,   S_FLOAT_DOT);
    set(S_FLOAT_DOT, CLS_DIGIT, S_FLOAT);
    set(S_FLOAT, CLS_DIGIT, S_FLOAT);

    loop_except(S_CHAR_OPEN, S_CHAR_BODY, CLS_BACKSLASH, -1);
    set(S_CHAR_OPEN, CLS_BACKSLASH, S_CHAR_ESC);
    loop_except(S_CHAR_ESC, S_CHAR_BODY, -1, -1);
    set(S_CHAR_BODY, CLS_SQUOTE, S_CHAR_DONE);

    loop_except(S_STR_BODY, S_STR_BODY, CLS_BACKSLASH, CLS_DQUOTE);
    set(S_STR_BODY, CLS_BACKSLASH, S_STR_ESC);
    set(S_STR_BODY, CLS_DQUOTE, S_STR_DONE);
    loop_except(S_STR_ESC, S_STR_BODY, -1, -1);

    loop_except(S_PREPROC, S_PREPROC, -1, -1);

    set(S_PLUS, CLS_PLUS, S_INC);

    set(S_WS, CLS_SPACE, S_WS);
}

typedef enum {
    TOK_NONE = -1,
    TOK_EOF,
    TOK_KEYWORD,
    TOK_IDENTIFIER,
    TOK_INTEGER,
    TOK_FLOAT,
    TOK_CHAR,
    TOK_STRING,
    TOK_PREPROCESSOR,
    TOK_OPERATOR,
    TOK_DELIMITER,
    TOK_INVALID,
    TOK_IGNORE,
    TOK_NEWLINE
} TokenType;

static int accept_type[NUM_STATES];

static void build_accept_table(void) {
    int s;
    for (s = 0; s < NUM_STATES; s++) accept_type[s] = TOK_NONE;

    accept_type[S_IDENT]     = TOK_IDENTIFIER;
    accept_type[S_INT]       = TOK_INTEGER;
    accept_type[S_FLOAT]     = TOK_FLOAT;
    accept_type[S_CHAR_DONE] = TOK_CHAR;
    accept_type[S_STR_DONE]  = TOK_STRING;
    accept_type[S_PREPROC]   = TOK_PREPROCESSOR;
    accept_type[S_PLUS]      = TOK_OPERATOR;
    accept_type[S_INC]       = TOK_OPERATOR;
    accept_type[S_ASSIGN]    = TOK_OPERATOR;
    accept_type[S_GREATER]   = TOK_OPERATOR;
    accept_type[S_STAR]      = TOK_OPERATOR;
    accept_type[S_DELIM]     = TOK_DELIMITER;
    accept_type[S_WS]        = TOK_IGNORE;
    accept_type[S_NEWLINE]   = TOK_NEWLINE;
}

static const char *type_name(TokenType t) {
    switch (t) {
        case TOK_KEYWORD:      return "KEYWORD";
        case TOK_IDENTIFIER:   return "IDENTIFIER";
        case TOK_INTEGER:      return "INTEGER";
        case TOK_FLOAT:        return "FLOAT";
        case TOK_CHAR:         return "CHAR";
        case TOK_STRING:       return "STRING";
        case TOK_PREPROCESSOR: return "PREPROCESSOR";
        case TOK_OPERATOR:     return "OPERATOR";
        case TOK_DELIMITER:    return "DELIMITER";
        case TOK_INVALID:      return "INVALID";
        default:               return "?";
    }
}

static const char *keywords[] = {
    "int", "float", "char", "if", "else", "while", "for", "return", "void"
};
#define NUM_KEYWORDS (int)(sizeof(keywords) / sizeof(keywords[0]))

static int is_keyword(const char *word) {
    int i;
    for (i = 0; i < NUM_KEYWORDS; i++)
        if (strcmp(word, keywords[i]) == 0) return 1;
    return 0;
}

typedef struct {
    TokenType   type;
    const char *text;
    int         length;
    int         line;
} Token;

static Token scan_token(const char *src, size_t *pos, int *line) {
    const char *start = src + *pos;
    int start_line = *line;
    int state = S_START;
    size_t cursor = *pos;

    int last_accept_state = -1;
    size_t last_accept_pos = *pos;

    for (;;) {
        unsigned char ch = (unsigned char)src[cursor];
        int cls = class_of[ch];
        int next = trans[state][cls];
        if (next == NO_TRANS) break;

        state = next;
        cursor++;

        if (accept_type[state] != TOK_NONE) {
            last_accept_state = state;
            last_accept_pos = cursor;
        }
    }

    Token tok;

    if (last_accept_state == -1) {
        if (src[*pos] == '\0') {
            tok.type = TOK_EOF; tok.text = start; tok.length = 0; tok.line = start_line;
            return tok;
        }
        tok.type = TOK_INVALID; tok.text = start; tok.length = 1; tok.line = start_line;
        (*pos)++;
        return tok;
    }

    tok.type   = accept_type[last_accept_state];
    tok.text   = start;
    tok.length = (int)(last_accept_pos - *pos);
    tok.line   = start_line;
    *pos       = last_accept_pos;

    if (tok.type == TOK_IDENTIFIER) {
        char buf[256];
        int n = tok.length < 255 ? tok.length : 255;
        memcpy(buf, tok.text, n);
        buf[n] = '\0';
        if (is_keyword(buf)) tok.type = TOK_KEYWORD;
    }

    return tok;
}

static char *read_file(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) { perror(path); exit(1); }
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = malloc(len + 1);
    fread(buf, 1, len, f);
    buf[len] = '\0';
    fclose(f);
    return buf;
}

static void print_token(Token tok) {
    if (tok.type == TOK_EOF) {
        printf("EOF\n");
        return;
    }
    printf("Line %2d: %-15s '%.*s'\n", tok.line, type_name(tok.type), tok.length, tok.text);
}

int main(int argc, char **argv) {
    build_char_classes();
    build_transition_table();
    build_accept_table();

    const char *path = argv[1];
    char *source = read_file(path);

    size_t pos = 0;
    int line = 1;

    for (;;) {
        Token tok = scan_token(source, &pos, &line);
        if (tok.type == TOK_NEWLINE) { line++; continue; }
        if (tok.type == TOK_IGNORE)  continue;

        print_token(tok);
        if (tok.type == TOK_EOF) break;
    }

    free(source);
    return 0;
}
