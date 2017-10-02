#ifndef tree_h
#define tree_h

typedef struct _oneBitNode oneBitNode;

typedef struct _twoBitNode twoBitNode;

oneBitNode* PrefixTree(char* fileName);

void PrintTable(oneBitNode* root);

int LookUp(oneBitNode* root, char* address);

oneBitNode* InsertPrefix(oneBitNode* root, char* prefix, int nextHop);

oneBitNode* DeletePrefix(oneBitNode* root, char* prefix);

twoBitNode* BinaryToTwoBit(oneBitNode* root);

void PrintTableEven(twoBitNode* root);

#endif

