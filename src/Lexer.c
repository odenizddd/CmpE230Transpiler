#include "Lexer.h"

TokenVector tokens = {.count = 0};

char* whoami(TokenType type) {
    char* type_string = (char*) malloc(16 * sizeof(char));
    if(type == PLUS) {
        strcpy(type_string, "PLUS");
    }else if(type == STAR) {
        strcpy(type_string, "STAR");
    }else if(type == MINUS) {
        strcpy(type_string, "MINUS");
    }else if(type == DIV) {
        strcpy(type_string, "DIV");
    }else if(type == MODULUS) {
        strcpy(type_string, "MODULUS");
    }else if(type == AND) {
        strcpy(type_string, "AND");
    }else if(type == OR) {
        strcpy(type_string, "OR");
    }else if(type == LEFT_PAREN) {
        strcpy(type_string, "LEFT_PAREN");
    }else if(type == RIGHT_PAREN) {
        strcpy(type_string, "RIGHT_PAREN");
    }else if(type == COMMA) {
        strcpy(type_string, "COMMA");
    }else if(type == ASSIGN) {
        strcpy(type_string, "ASSIGN");
    }else if(type == LEFT_SHIFT) {
        strcpy(type_string, "LEFT_SHIFT");
    }else if(type == RIGHT_SHIFT) {
        strcpy(type_string, "RIGHT_SHIFT");
    }else if(type == LEFT_ROT) {
        strcpy(type_string, "LEFT_ROT");
    }else if(type == RIGHT_ROT) {
        strcpy(type_string, "RIGHT_ROT");
    }else if(type == XOR) {
        strcpy(type_string, "XOR");
    }else if(type == NOT) {
        strcpy(type_string, "NOT");
    }else if(type == VARIABLE) {
        strcpy(type_string, "VARIABLE");
    }else if(type == LITERAL) {
        strcpy(type_string, "LITERAL");
    }else {}
    return type_string;
}

Token* newToken(TokenType type, char text[]) {
    Token* token = (Token*) malloc(sizeof(Token));
    token->type = type;
    token->text = (char*) malloc(strlen(text));
    memcpy(token->text, text, strlen(text));
    return token;
}

static void _printToken(Token* token) {
    printf("Type: %s Text: %s\n", whoami(token->type), token->text);
}

void _pushToken(TokenVector* tokens, Token* token) {
    tokens->data[tokens->count++] = *token;
}
void _printTokens(TokenVector* tokens) {
    for(int i = 0; i < tokens->count; i++) {
        _printToken(&tokens->data[i]);
    }
}

void pushToken(Token* token) {
    _pushToken(&tokens, token);
}
void printTokens() {
    _printTokens(&tokens);
}

void tokenize(char* source) {
    //stash errors with error(lineNo)
    size_t size = strlen(source);
    for(int i = 0; i < size; i++) {
        char c = source[i];
        if(c == '+') {
            pushToken(newToken(PLUS, "+"));
        }else if(c == '*') {
            pushToken(newToken(STAR, "*"));
        }else if(c == '-') {
            pushToken(newToken(MINUS, "-"));
        }else if(c == '/') {
            pushToken(newToken(DIV, "/"));
        }else if(c == '%') {
            pushToken(newToken(MODULUS, "%"));
        }else if(c == '&') {
            pushToken(newToken(AND, "&"));
        }else if(c == '|') {
            pushToken(newToken(OR, "|"));
        }else if(c == '(') {
             pushToken(newToken(LEFT_PAREN, "("));
        }else if(c == ')') {
            pushToken(newToken(RIGHT_PAREN, ")"));
        }else if(c == ',') {
            pushToken(newToken(COMMA, ","));
        }else if(c == '=') {
            pushToken(newToken(ASSIGN, "="));
        }else if(isdigit(c)) {
            int end = i;
            while(isdigit(source[end])) {end++;}
            if(isalpha(source[end--])) {error(lineNo);}
            //extract substring
            char* text = (char*) malloc((end - i + 2) * sizeof(char));
            strncpy(text, source + i, end - i + 1);
            pushToken(newToken(LITERAL, text));
            i = end;
        }else if(isalpha(c)) {
            int end = i;
            while(isalpha(source[end])) {end++;}
            if(isdigit(source[end--])) {error(lineNo);}
            //extract substring
            char* text = (char*) malloc((end - i + 2) * sizeof(char));
            strncpy(text, source + i, end - i + 1);
            TokenType type;
            if(strcmp(text, "xor") == 0) {
                type = XOR;
            }else if(strcmp(text, "not") == 0) {
                type = NOT;
            }else if(strcmp(text, "ls") == 0) {
                type = LEFT_SHIFT;
            }else if(strcmp(text, "rs") == 0) {
                type = RIGHT_SHIFT;
            }else if(strcmp(text, "lr") == 0) {
                type = LEFT_ROT;
            }else if(strcmp(text, "rr") == 0) {
                type = RIGHT_ROT;
            }else {
                type = VARIABLE;
            }
            pushToken(newToken(type, text));
            //classify
            i = end;
        }else if(isspace(c)) {

        }else {
            error(lineNo);
        }
    }
}