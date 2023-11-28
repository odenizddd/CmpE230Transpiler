#include "Error.h"

static int errors[256];
static int i = 0;

void error(int line) {
    if(safe(line)) {
         errors[i++] = line;
    }
}

void report() {
    for(int j = 0; j < i; j++) {
        printf("Error on line %d!\n", errors[j]);
    }
}

int safe(int lineNo) {
    for(int j = 0; j < i; j++) {
        if(errors[j] == lineNo) {
            return 0;
        }
    }
    return 1;
}