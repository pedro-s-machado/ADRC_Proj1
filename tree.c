#include <stdio.h>
#include <stdlib.h>


typedef struct _oneBitNode
{
    int nextHop;
	struct _oneBitNode *o, *l; // o stands for a zero, l stands for a one

}oneBitNode;


typedef struct _twoBitNode
{
	int nextHop;
	struct _twoBitNode *oo, *ol, *lo, *ll; // oo stands for two zeroes, ol stands for zero-one, etc...

}twoBitNode;

typedef struct List
{
    oneBitNode *elem;
    struct List *next;

}List;

typedef struct List1
{
    int a;
    int side;
    struct List1 *next;
}List1;


//Inserts elem in list after 'here' 
List* insertElem(List *here, void *elem){

    List *new = (List*)malloc(sizeof(List));
    
    if(new == NULL){
        printf("pError in memory allocation!\n");
        exit(1);
    }

    new->elem = elem;
    new->next = NULL;

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

//Inorder print of the tree
void printTree(oneBitNode *root, int depth, int s){

    int a = depth +1;
    if(root != NULL){

        printTree(root->o, a, 0);
        printf("nH = %d, depth = %d (side = %d)\n", root->nextHop, depth, s);
        printTree(root->l, a, 1);
        
    }
    return;

}


//BreathSearch print of the tree
void printTree2(oneBitNode *root){

    if(root == NULL) return;

    List * lista1 = malloc(sizeof(List));
    List *cu1 = lista1;
    List *aux= NULL;

    lista1->next = NULL;
    lista1->elem = root;

    List1 * lista2 = malloc(sizeof(List1));
    List1 *cu2 = lista2;
    List1 *aux2=NULL;

    lista2->next = NULL;
    lista2->a = 0;

    while(lista1 != NULL){

        if(lista1->elem->o != NULL){
            aux = malloc(sizeof(List));
            aux->elem = lista1->elem->o;
            aux->next = NULL;
            cu1->next = aux;
            cu1 = aux;

            aux2 = malloc(sizeof(List1));
            aux2->a = lista2->a +1;
            aux2->side = 0;
            aux2->next = NULL;
            cu2->next = aux2;
            cu2 = aux2;
        }

        if(lista1->elem->l != NULL){
            aux = malloc(sizeof(List));
            aux->elem = lista1->elem->l;
            aux->next = NULL;
            cu1->next = aux;
            cu1 = aux;

            aux2 = malloc(sizeof(List1));
            aux2->a = lista2->a +1;
            aux2->side = 1;
            aux2->next = NULL;
            cu2->next = aux2;
            cu2 = aux2;
        }

        printf("nH = %d - depth = %d (side = %d)\n", lista1->elem->nextHop, lista2->a, lista2->side);
        aux = lista1;
        lista1 = aux->next;
        aux2 = lista2;
        lista2 = aux2->next;

        free(aux);
        free(aux2);

    }
}


oneBitNode* PrefixTree(char* filename){
    
    FILE* file;
    oneBitNode *root = malloc(sizeof(struct _oneBitNode)), *ptr = NULL;
    char c;
    _Bool prefix_read = 0, nextHop_read = 0, file_read = 0;
    
    printf("Loading prefix table from \"%s\"\n", filename);
    file = fopen(filename, "r");
    if (file) {
        
        // Intitializing the root of the prefix tree
        // Destinations without known prefix are always have a Next Hop value of 1
        root->nextHop = -2;
        root->o = NULL;
        root->l = NULL;
        ptr = root;
        
        do {
            //getchar();

            while (!prefix_read) {
                
                c = fgetc(file);
                //printf("trip dad=%p o=%p l=%p\n",ptr, ptr->o, ptr->l);
                if (c == '0') {
                    if (ptr->o == NULL){
                        ptr->o = malloc(sizeof(struct _oneBitNode));
                        //printf("Novo0(%c) %p\n", c, ptr->o);
                        ptr->o->nextHop = -1;
                    }
                    ptr = ptr->o;
                }
                else if (c == '1') {
                    if (ptr->l == NULL){
                        //printf("Novo1(%c) %p\n",c, ptr->l);   
                        ptr->l = malloc(sizeof(struct _oneBitNode));
                        ptr->l->nextHop = -1;
                    }
                    ptr = ptr->l;
                }
                else if (c == '\t' || c == ' ') {
                    // Only tabulations and spaces should seperate the prefix and next hop values.
                    prefix_read = 1;
                }
                else {
                    printf("Prefix file corrupt, aborting...\n\n");
                    exit(-1);
                }
            }

            while (!nextHop_read) {
                c = fgetc(file);

                if (c >= '0' && c <= '9') {
                    if (ptr->nextHop < 0) ptr->nextHop = 0;
                    ptr->nextHop = 10*(ptr->nextHop) + atoi(&c);
                }
                else if (c == '\t' || c == ' ') {
                    // do nothing...
                }
                else if (c == '\n') {
                    nextHop_read = 1;
                }
                else if (c == EOF){
                    nextHop_read = 1;
                    file_read = 1;
                }
                else {
                    printf("Prefix file corrupt, aborting...\n\n");
                    // Free memory allocated for the tree...
                    exit(-1);
                }
            }
            
            prefix_read = 0;
            nextHop_read = 0;
            ptr = root;
            //printTree2(root);
            
        } while (!file_read);
        
        fclose(file);
        printf("Prefix file reading completed.\n");
    }
    else {
        printf("Could not open file \"%s\", aborting...\n\n", filename);
        free(root);
    }
    
    return root;
}


void PrintTable(oneBitNode* root){

    List* top = insertElem(NULL, root);
 
    List* bottom = top;

    printf("prefix \t nextHop");
    
    while(top != NULL){

        //address path needs to be stored in the list
        if(top->elem->o != NULL){
            bottom = insertElem(bottom, top->elem->o);
        }

        if(top->elem->l != NULL){
            bottom = insertElem(bottom, top->elem->l);
        }

        printf(" ");

    } 
}

int LookUp(oneBitNode* root, char* address){

    int nextHop = -1;
    int depth = 0;

    oneBitNode* currentNode = root;
    oneBitNode* nextNode = NULL;

    while(currentNode != NULL){
        //printf("depth = %d\n", depth);    
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
    
    oneBitNode *currentNode = root;
    int depth = 0;
    int size;

    for(size=0;prefix[size]!='\0'; size++);
    printf("Prefix Size (%d) \n", size);
    
    while(size-1 > depth){

        while(currentNode != NULL){
            
            if(prefix[depth] == '0'){
                currentNode = currentNode->o;
            }
            else if(prefix[depth] == '1'){
                currentNode = currentNode->l;
            }
            else{
                printf("Address is not binary!\n");
            }

            depth++;
        }

        if(depth == size-1){
            //if exist replace the nextHop value
            if(currentNode != NULL){
                currentNode->nextHop = nextHop;
            }
            //if doesn't exist create a new node
            else{
                
            }
        }
        else{

        }
    }
    return root;
}


oneBitNode* DeletePrefix(oneBitNode* root, char* prefix){
    return NULL;
}

twoBitNode* BinaryToTwoBit(oneBitNode* root){
    return NULL;
}

void PrintTableEven(twoBitNode* root){

}
