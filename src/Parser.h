#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "Map.h"
#include <string.h>
#include "Program.h"

typedef enum {
    PRIMARY = 0,
    FACTOR = 1,
    TERM = 2,
    BITWISE_AND = 3,
    BITWISE_OR = 4, 
    ASSIGNMENT = 5
} ASTType;

char* whatkind(ASTType type);

struct ASTNode{
    ASTType asttype;
    struct ASTNode* left;
    struct ASTNode* right;
    TokenType tokentype;
};
typedef struct ASTNode ASTNode;

ASTNode* newASTNode(ASTType type);

ASTNode* expression();
ASTNode* assignment();
ASTNode* bitwiseor();
ASTNode* bitwiseand();
ASTNode* term();
ASTNode* factor();
ASTNode* primary();
void show(ASTNode* node);
void printNode(ASTNode* node);
int eval(ASTNode* node);
void reset();

extern char* IR;
extern int nodeNo;

#endif