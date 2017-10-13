#ifndef tree_h
#define tree_h

typedef struct _oneBitNode oneBitNode;

typedef struct _twoBitNode twoBitNode;

typedef struct _prefix Prefix;

// Tobias
oneBitNode* PrefixTree(char* );

struct _prefix *listing(struct _oneBitNode *ptr, int prefixDigits[16], struct _prefix *list);
void free_DFSlist(struct _prefix *list);

void PrintTable(oneBitNode* root);

// Pedro
int LookUp(oneBitNode* root, char* address);

oneBitNode* InsertPrefix(oneBitNode* root, char prefix[16], int nextHop);

oneBitNode* DeletePrefix(oneBitNode* root, char* prefix);

twoBitNode* BinaryToTwoBit(oneBitNode* , int );

void PrintTableEven(twoBitNode* root);

void printTree(oneBitNode *root, int depth, int s);

void printTree2(oneBitNode *root);

int LookUp1(oneBitNode* root, char* address);

#endif

