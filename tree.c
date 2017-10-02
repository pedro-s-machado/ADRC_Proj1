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
	
	struct _twoBitNode *oo, *ol, *lo, *ll;

};


oneBitNode* PrefixTree(char* fileName){
    
    return NULL;
}

void PrintTable(oneBitNode* root){

}

int LookUp(oneBitNode* root, char* address){

    return 0;
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
