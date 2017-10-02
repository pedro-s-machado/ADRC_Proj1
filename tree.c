#include <stdio.h>
#include <stdlib.h>


struct _oneBitNode
{
	int nextHop;

	_oneBitNode *left, *right;

};


struct _twoBitNode
{
	int nextHop;
	
	_twoBitNode *oo, *ol, *lo, *ll;

};


_oneBitNode* PrefixTree(char* fileName){

}

void PrintTable(_oneBitNode* root){

}

int LookUp(_oneBitNode* root, char* address){

}

_oneBitNode* InsertPrefix(_oneBitNode* root, char* prefix, int nextHop){

}

_oneBitNode* DeletePrefix(_oneBitNode* root, char* prefix){

}

_twoBitNode* BinaryToTwoBit(_oneBitNode* root){

}

void PrintTableEven(_twoBitNode* root){

}