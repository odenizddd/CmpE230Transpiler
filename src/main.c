#include <stdio.h>

#include "Program.h"
#include "Lexer.h"
#include "Map.h"

int main(int argc, char *argv[]) {

    transpile(argv[1], argv[2]);
    
    return 0;
}
