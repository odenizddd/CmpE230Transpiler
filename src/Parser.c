#include "Parser.h"
#include "Util.h"

static int i = 0;
char* IR;
int nodeNo = 1;

char* whatkind(ASTType type) {
    char* mykind = (char*) malloc(16 * sizeof(char));
    if(type == PRIMARY) {
        strcpy(mykind, "PRIMARY");
    }else if(type == FACTOR) {
        strcpy(mykind, "FACTOR");
    }else if(type == TERM) {
        strcpy(mykind, "TERM");
    }else if(type == ASSIGNMENT) {
        strcpy(mykind, "ASSIGNMENT");
    }else {}
    return mykind;
}

ASTNode* newASTNode(ASTType type) {
    ASTNode* node = (ASTNode*) malloc(sizeof(ASTNode));
    node->asttype = type;
    return node;
}

ASTNode* expression() {
    return assignment();
}

ASTNode* assignment() {
    ASTNode* left = bitwiseor();
    if(i < tokens.count && tokens.data[i].type == ASSIGN) {
        i++;
        if(left->asttype == PRIMARY //&& left->tokentype == VARIABLE
        ) {
            ASTNode* right = assignment();
            ASTNode* assignment = newASTNode(ASSIGNMENT);
            assignment->left = left;
            assignment->right = right;
            assignment->tokentype = ASSIGN;
            return assignment;
        }else {
            error(lineNo);
        }
    }
    return left;
}

ASTNode* bitwiseor() {
    ASTNode* node = bitwiseand();
    Token token = tokens.data[i];
    while(i < tokens.count && (
        token.type == OR
    )) {
        i++;
        ASTNode* right = bitwiseand();
        ASTNode* left = newASTNode(BITWISE_OR);
        left->left = node;
        left->right = right;
        left->tokentype = token.type;
        node = left;
        token = tokens.data[i];
    }
    return node;
}

ASTNode* bitwiseand() {
    ASTNode* node = term();
    Token token = tokens.data[i];
    while(i < tokens.count && (
        token.type == AND
    )) {
        i++;
        ASTNode* right = term();
        ASTNode* left = newASTNode(BITWISE_AND);
        left->left = node;
        left->right = right;
        left->tokentype = token.type;
        node = left;
        token = tokens.data[i];
    }
    return node;
}

ASTNode* term() {
    ASTNode* node = factor();
    Token token = tokens.data[i];
    while(i < tokens.count && (
        token.type == PLUS ||
        token.type == MINUS
    )) {
        i++;
        ASTNode* right = factor();
        ASTNode* left = newASTNode(TERM);
        left->left = node;
        left->right = right;
        left->tokentype = token.type;
        node = left;
        token = tokens.data[i];
    }
    return node;
}

ASTNode* factor() {
    ASTNode* node = primary();
    Token token = tokens.data[i];
    while(i < tokens.count && (
        token.type == STAR ||
        token.type == DIV ||
        token.type == MODULUS
    )) {
        i++;
        ASTNode* right = primary();
        ASTNode* left = newASTNode(FACTOR);
        left->left = node;
        left->right = right;
        left->tokentype = token.type;
        node = left;
        token = tokens.data[i];
    }
    return node;
}

ASTNode* primary() {
    //TODO: implement checks when a token is consumed via i++
    if(i >= tokens.count) return NULL;
    Token token = tokens.data[i];
    //printf("I am: %s", token.text);
    ASTNode* primary = newASTNode(PRIMARY);
    primary->tokentype = token.type;
    if(token.type == LITERAL) {
        primary->left = (ASTNode*)token.text;
    }else if(token.type == VARIABLE) {
        primary->left = (ASTNode*)token.text;
    }else if(token.type == LEFT_PAREN) {
        i++;
        primary = expression();
        if(tokens.data[i].type != RIGHT_PAREN) {
            error(lineNo);
        }
    }else if(token.type == XOR ||
             token.type == LEFT_SHIFT ||
             token.type == RIGHT_SHIFT ||
             token.type == LEFT_ROT ||
             token.type == RIGHT_ROT
             ) {
        i++;
        if(tokens.data[i].type != LEFT_PAREN) {
            error(lineNo);
        }
        i++;
        primary->left = expression();
        //show(primary->left);
        if(tokens.data[i].type != COMMA) {
            error(lineNo);
        }
        i++;
        primary->right = expression();
        if(tokens.data[i].type != RIGHT_PAREN) {
            error(lineNo);
        }
        //printNode(primary->right);
    }else if(token.type == NOT) {
        i++;
        if(tokens.data[i].type != LEFT_PAREN) {
            error(lineNo);
        }
        i++;
        primary->left = expression();
        if(tokens.data[i].type != RIGHT_PAREN) {
            error(lineNo);
        }
        //printNode(primary->left);
        //printf("\n");
    }else {
        error(lineNo); 
        //return primary;
        }
    i++;
    return primary;
}

void show(ASTNode* node) {
    if(node->asttype == PRIMARY) {
        if(node->tokentype == LITERAL || node->tokentype == VARIABLE ) {
            printf("Primary with value: %s\n", (char*)node->left);
        }else if(node->tokentype == NOT) {
            printf("Primary with value: %s\n", (char*)node->left->left);
        }else {
            printf("Primary with type: %s", whoami(node->tokentype));
            show(node->left);
            show(node->right);
        }
    }else if(node->asttype == FACTOR) {
        printf("Factor left: %s op: %s right: %s\n", whatkind(node->left->asttype), whoami(node->tokentype), whatkind(node->right->asttype));
        show(node->left);
        show(node->right);
    }else if(node->asttype == TERM) {
        printf("Term left: %s op: %s right: %s\n", whatkind(node->left->asttype), whoami(node->tokentype), whatkind(node->right->asttype));
        show(node->left);
        show(node->right);
    }else if(node->asttype == ASSIGNMENT) {
        printf("Assignment left: %s op: %s right: %s\n", whatkind(node->left->asttype), whoami(node->tokentype), whatkind(node->right->asttype));
        show(node->left);
        show(node->right);
    }else {}
}

void printNode(ASTNode* node) {
    if(node == NULL) {
        printf("Node is NULL");
    }else {
        if(node->left == NULL) {
            printf("Left child if node is null");
        }
        if(node->right == NULL) {
            printf("Right child of node is null");
        }
    }
}

int _lr(int a, int b) {
    //implement left rotation
    return 0;
}

int _rr(int a, int b) {
    //implement right rotation
    return 0;
}

int eval(ASTNode* node) {
    char* out = (char*) calloc(128, sizeof(char));
    int result;
    if(node->tokentype == PLUS ||
       node->tokentype == MINUS ||
       node->tokentype == STAR ||
       node->tokentype == DIV ||
       node->tokentype == MODULUS ||
       node->tokentype == AND ||
       node->tokentype == OR ||
       node->tokentype == LEFT_SHIFT ||
       node->tokentype == RIGHT_SHIFT ||
       node->tokentype == LEFT_ROT ||
       node->tokentype == RIGHT_ROT ||
       node->tokentype == XOR) {
        int (*func) (int, int);
        func = op(node);
        result = func(eval(node->left), eval(node->right));
        char* leftName;
        char* rightName;
        if(node->left->tokentype != LITERAL) {
            leftName = getNode(node->left);
        }else {
            leftName = (char*) node->left->left;
        }
        if(node->right->tokentype != LITERAL) {
            rightName = getNode(node->right);
        }else {
            rightName = (char*) node->right->left;
        }
        if(node->tokentype == LEFT_ROT) {
            sprintf(out, "\t%c%d = shl i32 %s, %s\n", 37, nodeNo++, leftName, rightName);
            //strcat(IR, out);
            fprintf(fileOut, "%s", out);
            sprintf(out, "\t%c%d = sub i32 %s, %s\n", 37, nodeNo++, "32", rightName);
            //strcat(IR, out);
            fprintf(fileOut, "%s", out);
            sprintf(out, "\t%c%d = ashr i32 %s, %c%d\n", 37, nodeNo, leftName, 37, nodeNo - 1); nodeNo++;
            //strcat(IR, out);
            fprintf(fileOut, "%s", out);
            sprintf(out, "\t%c%d = or i32 %c%d, %c%d\n", 37, nodeNo, 37, nodeNo-3, 37, nodeNo-1);
            //strcat(IR, out);
            fprintf(fileOut, "%s", out);
        }else if(node->tokentype == RIGHT_ROT) {
            sprintf(out, "\t%c%d = ashr i32 %s, %s\n", 37, nodeNo++, leftName, rightName);
            //strcat(IR, out);
            fprintf(fileOut, "%s", out);
            sprintf(out, "\t%c%d = sub i32 %s, %s\n", 37, nodeNo++, "32", rightName);
            //strcat(IR, out);
            fprintf(fileOut, "%s", out);
            sprintf(out, "\t%c%d = shl i32 %s, %c%d\n", 37, nodeNo, leftName, 37, nodeNo - 1); nodeNo++;
            //strcat(IR, out);
            fprintf(fileOut, "%s", out);
            sprintf(out, "\t%c%d = or i32 %c%d, %c%d\n", 37, nodeNo, 37, nodeNo-3, 37, nodeNo-1);
            //strcat(IR, out);
            fprintf(fileOut, "%s", out);
        }else {
            sprintf(out, "\t%c%d = %s i32 %s, %s\n", 37, nodeNo, instruction(node), leftName, rightName);
            //strcat(IR, out);
            fprintf(fileOut, "%s", out);
        }
    }else if(node->tokentype == NOT) {
        int (*func) (int, int);
        func = op(node);
        result = func(eval(node->left), 0);
        char* leftName;
        if(node->left->tokentype != LITERAL) {
            leftName = getNode(node->left);
        }else {
            leftName = (char*) node->left->left;
        }
        sprintf(out, "\t%c%d = %s i32 %s, %s\n", 37, nodeNo, instruction(node), leftName, "-1");
        //strcat(IR, out);
        fprintf(fileOut, "%s", out);
    }else if(node->tokentype == LITERAL){
        result = atoi((char*) node->left);
    }else if(node->tokentype == VARIABLE){
        if(!existsVar((char*) node->left)) {
            error(lineNo);
            return 0;
        }
        sprintf(out, "\t%c%d = load i32, i32* %c%s\n", 37, nodeNo, 37, (char*) node->left);
        //strcat(IR, out);
        fprintf(fileOut, "%s", out);
        result = getVar((char*) node->left);
    }else if(node->tokentype == ASSIGN){
        if(node->left->tokentype != VARIABLE) {error(lineNo);}//
        if(!existsVar((char*) node->left->left)) {
            sprintf(out, "\t%c%s = alloca i32\n", 37, (char*) node->left->left);
            //strcat(IR, out);
            fprintf(fileOut, "%s", out);
        }
        int right = eval(node->right);
        if(safe(lineNo)) {
            setVar((char*) node->left->left, right);
        }
        result = getVar((char*) node->left->left);
    }else {return 0;}
    if(node->tokentype != LITERAL && node->tokentype != ASSIGN) {
        char* name = (char*) calloc(16, sizeof(char));
        sprintf(name, "%c%d", 37, nodeNo++);
        setNode(node, name);
    }
    return result;
}

void reset() {
    i = 0;
}