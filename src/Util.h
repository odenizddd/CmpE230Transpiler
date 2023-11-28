#ifndef UTIL_H
#define UTIL_H

#include "Parser.h"
#include <stdlib.h>

int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int dvd(int a, int b);
int mod(int a, int b);
int and(int a, int b);
int or (int a, int b);
int lr (int a, int b);
int rr (int a, int b);
int ls (int a, int b);
int rs (int a, int b);
int not(int a, int b);
int xor(int a, int b);

void* op(ASTNode* node);
char* instruction(ASTNode* node);

#endif