#ifndef MAP_H
#define MAP_H

#include <string.h>
#include <stdlib.h>

#include "Lexer.h"
#include "Parser.h"

typedef struct ASTNode ASTNode;

typedef struct {
    char* keys[1024];
    int values[1024];
    int count;
} varMap;

int getVar(char* key);
void setVar(char* key, int value);
int existsVar(char* key);

typedef struct {
    ASTNode* keys[1024];
    char* values[1024];
    int count;
} nodeMap;

char* getNode(ASTNode* key);
void setNode(ASTNode* key, char* value);
int existsNode(ASTNode* key);

#endif