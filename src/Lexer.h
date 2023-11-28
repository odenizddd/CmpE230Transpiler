#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Error.h"

typedef enum {
    PLUS,
    STAR,
    MINUS,
    DIV,
    MODULUS,
    AND,
    OR,
    LEFT_PAREN,
    RIGHT_PAREN,
    COMMA,
    ASSIGN,
    LEFT_SHIFT,
    RIGHT_SHIFT,
    LEFT_ROT,
    RIGHT_ROT,
    XOR,
    NOT,
    VARIABLE,
    LITERAL
} TokenType;

char* whoami(TokenType myType);

typedef struct {
    TokenType type;
    char* text;
} Token;

Token* newToken(TokenType type, char text[]);

typedef struct {
    Token data[128];
    int count;
} TokenVector;

void pushToken(Token* token);
void printTokens();

void tokenize(char* source);

extern int lineNo;
extern TokenVector tokens;

#endif