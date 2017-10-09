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

typedef struct List
{
    void *elem;
    struct List *next;

}List;


//Inserts elem in list after 'here' 
List* insertElem(List *here, void *elem){

    List *new = (List*)malloc(sizeof(List));
    
    if(new == NULL){
        printf("Error in memory allocation!\n");
        exit(1);
    }

    new->elem = elem;
    new->next == NULL;

    if(here != NULL){
        
        if(here->next != NULL){

            new->next = here->next;
        }

        here->next = new;
    }

    return new;
}

//Removes elem from list
List* removeElem(List* this){

    List *new = NULL;

    if(this != NULL){
    
        if(this->next != NULL){

            new = this->next;
        }

        free(this);
    }

    return new;
}

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

    oneBitNode* currentNode = root;
    List* top = insertElem(NULL, root);
    
    List* bottom = top;

    print("prefix \t nextHop")
    
    while(top != NULL){

        //address path needs to be stored in the list
        if(root->o != NULL){
            bottom = insertElem(root->o);
        }

        if(root->l != NULL){
            bottom = insertElem(root->l);
        }

        print();

    } 
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

        if(address[depth] == '0'){
            nextNode = currentNode->o;
        
        }else if(address[depth] == '1'){
            nextNode = currentNode->l;

        }else{
            printf("Address is not binary!\n");
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
