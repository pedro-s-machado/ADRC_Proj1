#include <stdio.h>
#include <stdlib.h>


typedef struct _oneBitNode
{
	int nextHop;

	_oneBitNode *left, *right;

}oneBitNode;


typedef struct _twoBitNode
{
	int nextHop;
	
	_twoBitNode *oo, *ol, *lo, *ll;

}twoBitNode;


