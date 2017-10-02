#include <stdio.h>
#include <stdlib.h>
#include "tree.h"


struct _oneBitNode
{
	unsigned int nextHop;

	struct _oneBitNode *left, *right;

};


struct _twoBitNode
{
	unsigned int nextHop;
	
	struct _twoBitNode *oo, *ol, *lo, *ll;

};


struct _oneBitNode* PrefixTree(char* fileName){
    
    return NULL;
}

void PrintTable(struct _oneBitNode* root){

}

int LookUp(struct _oneBitNode* root, char* address){

    return 0;
}

struct _oneBitNode* InsertPrefix(struct _oneBitNode* root, char* prefix, int nextHop){
    return NULL;
}

struct _oneBitNode* DeletePrefix(struct _oneBitNode* root, char* prefix){
    return NULL;
}

struct _twoBitNode* BinaryToTwoBit(struct _oneBitNode* root){
    return NULL;
}

void PrintTableEven(struct _twoBitNode* root){

}
