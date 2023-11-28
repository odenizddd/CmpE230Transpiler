#include "Program.h"
#include "Parser.h"

int lineNo = 1;
FILE* fileOut;

void transpile(char* input, char* output) {
    FILE* fileIn;
    size_t len = 1024;
    char* line = (char*) malloc(len * sizeof(char));

    fileIn = fopen(input, "r");



    fileOut = fopen(output, "w");

    fputs("declare i32 @printf(i8*, ...)\n", fileOut);
    fprintf(fileOut, "@print.str = constant [4 x i8] c\"%cd\\0A\\00\"\n\n", 37);
    fputs("define i32 @main() {\n", fileOut);
    //IR = (char*) calloc(2048, sizeof(char));
    while(getline(&line, &len, fileIn) != -1) {
        //printf("content: %s", line);
        tokenize(line);
        memset(line, 0, len);
        //printTokens();
        if(safe(lineNo) && tokens.count > 0) {
            ASTNode* root = expression();
            //show(root);
            int result = 0;
            if(root && safe(lineNo)) {
                //show(root);
                result = eval(root);
            }
            if(safe(lineNo)) {
                printf("line: %d result: %d\n", lineNo, result);
                if(root->tokentype != ASSIGN) {
                    char* out = (char*) calloc(128, sizeof(char));
                    char* name = (char*) calloc(64, sizeof(char));
                    if(root->tokentype == LITERAL) {
                        name = (char*)root->left;
                    }else {
                        name = getNode(root);
                    }
                    sprintf(out, "\tcall i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %s )\n", name);
                    nodeNo++;
                    //strcat(IR, out);
                    fprintf(fileOut, "%s", out);
                }else {
                    char* name;
                    if(root->right->tokentype != LITERAL) {
                        name = getNode(root->right);
                    }else {
                        name = (char*) root->right->left;
                    }
                    char* out = (char*) calloc(128, sizeof(char));
                    sprintf(out, "\tstore i32 %s, i32* %c%s\n", name, 37, (char*) root->left->left);
                    //strcat(IR, out);
                    fprintf(fileOut, "%s", out);
                }
            }
        }
        tokens.count = 0;
        reset();
        lineNo++;
    }
    
    //fprintf(fileOut, "%s", IR);
    fputs("\tret i32 0\n", fileOut);
    fputs("}", fileOut);

    report();

    fclose(fileIn);
}