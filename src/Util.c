#include "Util.h"

int add(int a, int b) {return a + b;}
int sub(int a, int b) {return a - b;}
int mul(int a, int b) {return a * b;}
int dvd(int a, int b) {if(b == 0) {error(lineNo);} return (int)(a / b);}
int mod(int a, int b) {return a % b;}
int and(int a, int b) {return a & b;}
int or (int a, int b) {return a | b;}
int lr (int a, int b) {return (a << b)|(a >> (32 - b));}
int rr (int a, int b) {return (a >> b)|(a << (32 - b));}
int ls (int a, int b) {return a << b;}
int rs (int a, int b) {return a >> b;}
int not(int a, int b) {return ~a;}
int xor(int a, int b) {return a ^ b;}

void* op(ASTNode* node) {
    if(node->tokentype == PLUS) {
        return add;
    }else if(node->tokentype == MINUS) {
        return sub;
    }else if(node->tokentype == STAR) {
        return mul;
    }else if(node->tokentype == DIV) {
        return dvd;
    }else if(node->tokentype == MODULUS) {
        return mod;
    }else if(node->tokentype == AND) {
        return and;
    }else if(node->tokentype == OR) {
        return or;
    }else if(node->tokentype == LEFT_ROT) {
        return lr;
    }else if(node->tokentype == RIGHT_ROT) {
        return rr;
    }else if(node->tokentype == LEFT_SHIFT) {
        return ls;
    }else if(node->tokentype == RIGHT_SHIFT) {
        return rs;
    }else if(node->tokentype == NOT) {
        return not;
    }else if(node->tokentype == XOR) {
        return xor;
    }else {return 0;}
}

char* instruction(ASTNode* node) {
    char* name = (char*) calloc(16, sizeof(char));
    if(node->tokentype == PLUS) {
        strcpy(name, "add");
    }else if(node->tokentype == MINUS) {
        strcpy(name, "sub");
    }else if(node->tokentype == STAR) {
        strcpy(name, "mul");
    }else if(node->tokentype == DIV) {
        strcpy(name, "udiv");
    }else if(node->tokentype == MODULUS) {
        strcpy(name, "urem");
    }else if(node->tokentype == AND) {
        strcpy(name, "and");
    }else if(node->tokentype == OR) {
        strcpy(name, "or");
    }else if(node->tokentype == LEFT_ROT) {
        strcpy(name, "udf");
    }else if(node->tokentype == RIGHT_ROT) {
        strcpy(name, "udf");
    }else if(node->tokentype == LEFT_SHIFT) {
        strcpy(name, "shr");
    }else if(node->tokentype == RIGHT_SHIFT) {
        strcpy(name, "shl");
    }else if(node->tokentype == NOT) {
        strcpy(name, "xor");
    }else if(node->tokentype == XOR) {
        strcpy(name, "xor");
    }else {return 0;}
    return name;
}