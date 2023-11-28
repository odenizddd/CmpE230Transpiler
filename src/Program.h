#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdio.h>
#include <stdlib.h>

#include "Lexer.h"
#include "Parser.h"

void transpile(char* input, char* output);
extern FILE* fileOut;

#endif