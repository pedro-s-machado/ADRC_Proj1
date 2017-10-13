#ifndef tree_h
#define tree_h

typedef struct _oneBitNode oneBitNode;

typedef struct _twoBitNode twoBitNode;

// Tobias
oneBitNode* PrefixTree(char* );

void PrintTable(oneBitNode* root);

// Pedro
int LookUp(oneBitNode* root, char* address);

oneBitNode* InsertPrefix(oneBitNode* root, char prefix[16], int nextHop);

oneBitNode* DeletePrefix(oneBitNode* root, char* prefix);

twoBitNode* BinaryToTwoBit(oneBitNode* root);

void PrintTableEven(twoBitNode* root);

void printTree(oneBitNode *root, int depth, int s);

void printTree2(oneBitNode *root);

int LookUp1(oneBitNode* root, char* address);

#endif

