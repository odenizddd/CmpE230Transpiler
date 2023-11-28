#include "Map.h"

varMap vars;
nodeMap nodes;

int getVar(char* key) {
    for(int i = 0; i < vars.count; i++) {
        if(!strcmp(vars.keys[i], key)) {
            return vars.values[i];
        }
    }
    return 0;
}

void setVar(char* key, int value) {
    for(int i = 0; i < vars.count; i++) {
        if(!strcmp(vars.keys[i], key)) {
            vars.values[i] = value;
        }
    }
    vars.keys[vars.count] = key;
    vars.values[vars.count++] = value;
}

int existsVar(char* key) {
    for(int i = 0; i < vars.count; i++) {
        if(!strcmp(vars.keys[i], key)) {
            return 1;
        }
    }
    return 0;
}

char* getNode(ASTNode* key) {
    for(int i = 0; i < nodes.count; i++) {
        if(nodes.keys[i] == key) {
            return nodes.values[i];
        }
    }
    return NULL;
}

void setNode(ASTNode* key, char* value) {
    for(int i = 0; i < nodes.count; i++) {
        if(nodes.keys[i] == key) {
            nodes.values[i] = value;
        }
    }
    nodes.keys[nodes.count] = key;
    nodes.values[nodes.count++] = value;
}

int existsNode(ASTNode* key) {
    for(int i = 0; i < nodes.count; i++) {
        if(nodes.keys[i] == key) {
            return 1;
        }
    }
    return 0;
}