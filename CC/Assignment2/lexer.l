%{
#include <stdio.h>

typedef enum {
    TOK_KEYWORD,
    TOK_IDENTIFIER,
    TOK_INTEGER,
    TOK_FLOAT,
    TOK_CHAR,
    TOK_STRING,
    TOK_PREPROCESSOR,
    TOK_OPERATOR,
    TOK_DELIMITER,
    TOK_INVALID
} TokenType;

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
        default:                return "INVALID";
    }
}

static void emit(TokenType t) {
    printf("Line %2d: %-15s '%s'\n", yylineno, type_name(t), yytext);
}
%}

%option yylineno
%option noyywrap

KEYWORD (int|float|char|if|else|while|for|return|void)

%%
{KEYWORD}                                                     { emit(TOK_KEYWORD); }
[A-Za-z_][A-Za-z0-9_]*                                        { emit(TOK_IDENTIFIER); }
[0-9]+\.[0-9]+                                                { emit(TOK_FLOAT); }
[0-9]+                                                        { emit(TOK_INTEGER); }
\'([^\'\\]|\\.)\'                                             { emit(TOK_CHAR); }
\"([^\"\\]|\\.)*\"                                            { emit(TOK_STRING); }
#[^\n]*                                                       { emit(TOK_PREPROCESSOR); }
"//"[^\n]*                                                    { ; }
"/*"([^*]|\*+[^*/])*\*+"/"                                    { ; }
"++"|"--"|"+="|"-="|"*="|"/="|"%="|"=="|"!="|"<="|">="|"&&"|"||"|"<<"|">>"|"->" { emit(TOK_OPERATOR); }
[-+*/%=<>!&|^~.?:]                                            { emit(TOK_OPERATOR); }
[;,(){}\[\]]                                                  { emit(TOK_DELIMITER); }
[ \t\r]+                                                      { ; }
\n                                                             { ; }
.                                                              { emit(TOK_INVALID); }
%%

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (!f) { perror(argv[1]); return 1; }
        yyin = f;
    }
    yylex();
    printf("EOF\n");
    return 0;
}
