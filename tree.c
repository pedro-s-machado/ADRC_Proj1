#include <stdio.h>
#include <stdlib.h>
#include "tree.h"


struct _oneBitNode
{
	unsigned int nextHop;
	struct _oneBitNode *o, *l; // o stands for a zero, l stands for a one

};


struct _twoBitNode
{
	unsigned int nextHop;
	struct _twoBitNode *oo, *ol, *lo, *ll; // oo stands for two zeroes, ol stands for zero-one, etc...

};


oneBitNode* PrefixTree(char* filename){
    printf("Loading prefix table from \"%s\"\n", filename);
    
    FILE* file;
    file = fopen(filename, "r");
    if (file) {
        
        
        fclose(file);
    }
    else {
        printf("Could not open file \"%s\"\n", filename);
    }
    
    return NULL;
}

void PrintTable(oneBitNode* root){

}

int LookUp(oneBitNode* root, char* address){

    int nextHop = -1;
    int depth = 0;

    oneBitNode* currentNode = root;
    oneBitNode* nextNode;

    while(currentNode != NULL){
        
        if(currentNode->nextHop != -1){
            nextHop = currentNode->nextHop;
        }

        if(address[0] == '0'){
            nextNode = currentNode->o;
        
        }else{
            nextNode = currentNode->l;

        }

        currentNode = nextNode;
        depth++;
    }

    return nextHop;
}

oneBitNode* InsertPrefix(oneBitNode* root, char* prefix, int nextHop){
    return NULL;
}

oneBitNode* DeletePrefix(oneBitNode* root, char* prefix){
    return NULL;
}

twoBitNode* BinaryToTwoBit(oneBitNode* root){
    return NULL;
}

void PrintTableEven(twoBitNode* root){

}
