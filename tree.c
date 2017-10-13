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

typedef struct _prefix
{
    char prefix[16];
    int nexthop;
    struct _prefix *next;
    
}Prefix;


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
    struct _oneBitNode *root = malloc(sizeof(struct _oneBitNode)), *ptr = NULL;
    char c;
    _Bool prefix_read = 0, nextHop_read = 0, file_read = 0;
    
    printf("Loading prefix table from \"%s\"\n", filename);
    file = fopen(filename, "r");
    if (file) {
        
        // Intitializing the root of the prefix tree
        root->nextHop = -1;
        root->o = NULL;
        root->l = NULL;
        ptr = root;
        
        do {
            
            while (!prefix_read) {
                c = fgetc(file);
                if (c == '0') {
                    if (ptr->o == NULL) {
                        ptr->o = malloc(sizeof(struct _oneBitNode));
                        ptr->o->nextHop = -1;
                        ptr->o->l = NULL;
                        ptr->o->o = NULL;
                    }
                    ptr = ptr->o;
                }
                else if (c == '1') {
                    if (ptr->l == NULL) {
                        ptr->l = malloc(sizeof(struct _oneBitNode));
                        ptr->l->nextHop = -1;
                        ptr->l->l = NULL;
                        ptr->l->o = NULL;
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
                    if (ptr->nextHop < 0)
                        ptr->nextHop = 0;
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

struct _prefix *listing(struct _oneBitNode *ptr, int *prefixDigits, struct _prefix *list, struct _oneBitNode *root) {
    int i, j, k;
    for (i = 0 ; i < 16 ; i++)
        if (prefixDigits[i] < 0)
            break; // We are at depth i in the tree
    if (ptr->nextHop >= 0) {
        // Found a prefix
        for (j = 0 ; j < 16 ; j++) {
            if (prefixDigits[j] == 1)
                list->prefix[j] = '1';
            else if (prefixDigits[j] == 0)
                list->prefix[j] = '0';
            else
                list->prefix[j] = '-';
        }
        list->nexthop = ptr->nextHop;
        list->next = malloc(sizeof(struct _prefix));
        for (k = 0 ; k < 16 ; k++)
            list->next->prefix[k] = '#';
        list->next->nexthop = -1;
        list->next->next = NULL;
        list = list->next;
    }
    if (ptr->o != NULL) {
        prefixDigits[i] = 0;
        for (k = i+1 ; k < 16 ; k++)
            prefixDigits[k] = -1;
        list = listing(ptr->o, prefixDigits, list, root);
    }
    if (ptr->l != NULL) {
        prefixDigits[i] = 1;
        for (k = i+1 ; k < 16 ; k++)
            prefixDigits[k] = -1;
        list = listing(ptr->l, prefixDigits, list, root);
    }
    return list;
    
}

void free_DFSlist(struct _prefix *list) {
    if (list->next != NULL)
        free_DFSlist(list->next);
    free(list);
}

void PrintTable(oneBitNode* root){
    
    int *prefixDigits = malloc(sizeof(int)*16);
    struct _prefix *list = malloc(sizeof(struct _prefix)), *ptr = NULL;
    for (int k = 0 ; k < 16 ; k++)
        list->prefix[k] = '-';
    list->nexthop = -1;
    list->next = NULL;
    for (int i = 0 ; i < 16 ; i++)
        prefixDigits[i] = -1;
    
    listing(root, prefixDigits, list, root);
    
    // Listing
    printf("Prefix\t\t\t\tNext Hop\n");
    ptr = list;
    while (ptr->next != NULL) {
        for (int i = 0 ; i < 16 ; i++)
            printf("%c", ptr->prefix[i]);
        printf("\t\t");
        printf("%d\n", ptr->nexthop);
        ptr = ptr->next;
    }
    
    // Freeing the memory used by the list of prefixes
    free_DFSlist(list);
}

int LookUp(oneBitNode* root, char* address){

    int hops[16], i = 0;
    for (i = 0 ; i < 16 ; i++) hops[i] = -1;
    
    oneBitNode* currentNode = root;
    oneBitNode* nextNode = NULL;
    
    for (int i = 0 ; i < 16 ; i++) {
        hops[i] = currentNode->nextHop;
        if (address[i] == 0 && currentNode->o != NULL)
            nextNode = currentNode->o;
        else if (address[i] == 1 && currentNode->l != NULL)
            nextNode = currentNode->l;
        else {
            printf("Not a correct address...\n");
            return -1;
        }
        if (nextNode != NULL)
            currentNode = nextNode;
        else
            break;
    }
    
    // Finished listing all possible next hops and storing them in array hops[]
    while (hops[i] < 0 && i > 0) i--;
    // and returning the one corresponding to the longest prefix for which there is a next hop in the table
    return hops[i];
    
}


int LookUp1(oneBitNode* root, char* address){

    int nextHop = -1;
    int depth = 0;
    int size;

    oneBitNode* currentNode = root;
    oneBitNode* nextNode = NULL;

    for(size=0;address[size]!='\0'; size++);

    while(currentNode != NULL && depth <= size){
        
        if(currentNode->nextHop != -1){
            nextHop = currentNode->nextHop;
        }

        if(address[depth] == '0'){
            nextNode = currentNode->o;
        
        }else if(address[depth] == '1'){
            nextNode = currentNode->l;

        }else{
            if(depth != size)
                printf("Address is not binary!(%c, %d)\n", address[depth], depth);
        }

        currentNode = nextNode;
        depth++;
    }

    return nextHop;
}
oneBitNode* InsertPrefix(oneBitNode* root, char prefix[17], int nextHop){
    
    //initializes the tree if doesn't exist
    if(root == NULL){
    
        root = malloc(sizeof(oneBitNode));
        root->o = NULL;
        root->l = NULL;
        root->nextHop = -1;
    }

    oneBitNode *currentNode = root;
    int depth = 0;
    int size;

    //finds size of the prefix
    for(size=0;prefix[size]!='\0'; size++); 

    //goes down the tree creating the path when doens't exist
    while(depth <= size-1){

        if(prefix[depth] == '0'){
            
            if(currentNode->o == NULL){
                
                currentNode->o = malloc(sizeof(oneBitNode));
                currentNode->o->o = NULL;
                currentNode->o->l = NULL;
                currentNode->o->nextHop = -1;
            }
            
            currentNode = currentNode->o;
        }
        else if(prefix[depth] == '1'){

            if(currentNode->l == NULL){
                
                currentNode->l = malloc(sizeof(oneBitNode));
                currentNode->l->o = NULL;
                currentNode->l->l = NULL;
                currentNode->l->nextHop = -1;
            }
            
            currentNode = currentNode->l;
        }
        else{
            printf("Address is not binary!(%c, %d)\n", prefix[depth], depth);
        }

        //printf("%d\n", depth);
        depth++;
    }

    //set's the next hop value
    currentNode->nextHop = nextHop;

    return root;
}


oneBitNode* DeletePrefix(oneBitNode* root, char* prefix){
    
    int depth = 0;
    int size;

    oneBitNode * currentNode = root;
    List * head = NULL;
    List * new;

    for(size=0;prefix[size]!='\0'; size++);

    while(currentNode != NULL && depth <= size){
    
        if(prefix[depth] == '0'){
            currentNode = currentNode->o;
        
        }else if(prefix[depth] == '1'){
            currentNode = currentNode->l;

        }else{
            if(depth != size)
                printf("Address is not binary!(%c, %d)\n", prefix[depth], depth);
        }

        depth++;
        new = malloc(sizeof(List));
        new->elem = currentNode;
        new->next = head;

        head = new;
    }

    //removes prefix next hop value
    currentNode->nextHop = -1;
    

    //removes unecessary node of the tree
    /*
    while((head != NULL) && (head->elem->nextHop == -1) && (head->elem->o == NULL) && (head->elem->l == NULL)){
        printf("%d\n", head->elem->nextHop);
        new = head;
        head = head->next;
        printf("\t%p\n", new->elem);
        free(new->elem);
        printf("\t%p\n", new->elem);
        free(new);
    }
    printf("%p %p\n", root->o, root->l);
    */
    return root;

}

twoBitNode* BinaryToTwoBit(oneBitNode* ptr, int parent_nextHop){
    if (ptr == NULL)
        return NULL;
    
    struct _twoBitNode *ptr2 = malloc(sizeof(struct _twoBitNode));
    if (ptr->nextHop < 0)
        ptr2->nextHop = parent_nextHop;
    else
        ptr2->nextHop = ptr->nextHop;
    ptr2->oo = NULL;
    ptr2->ol = NULL;
    ptr2->ll = NULL;
    ptr2->lo = NULL;
    
    if (ptr->o != NULL) {
        if (ptr->o->o != NULL)
            ptr2->oo = BinaryToTwoBit(ptr->o->o, ptr->o->nextHop);
        else {
            ptr2->oo = malloc(sizeof(struct _twoBitNode));
            ptr2->oo->nextHop = ptr->o->nextHop;
            ptr2->oo->oo = NULL;
            ptr2->oo->ol = NULL;
            ptr2->oo->lo = NULL;
            ptr2->oo->ll = NULL;
        }
        if (ptr->o->l != NULL)
            ptr2->ol = BinaryToTwoBit(ptr->o->l, ptr->o->nextHop);
        else {
            ptr2->ol = malloc(sizeof(struct _twoBitNode));
            ptr2->ol->nextHop = ptr->o->nextHop;
            ptr2->ol->oo = NULL;
            ptr2->ol->ol = NULL;
            ptr2->ol->lo = NULL;
            ptr2->ol->ll = NULL;
        }
    }
    if (ptr->l != NULL) {
        if (ptr->l->o != NULL)
            ptr2->lo = BinaryToTwoBit(ptr->l->o, ptr->l->nextHop);
        else {
            ptr2->lo = malloc(sizeof(struct _twoBitNode));
            ptr2->lo->nextHop = ptr->l->nextHop;
            ptr2->lo->oo = NULL;
            ptr2->lo->ol = NULL;
            ptr2->lo->lo = NULL;
            ptr2->lo->ll = NULL;
        }
        if (ptr->l->l != NULL)
            ptr2->ll = BinaryToTwoBit(ptr->l->l, ptr->l->nextHop);
        else {
            ptr2->ll = malloc(sizeof(struct _twoBitNode));
            ptr2->ll->nextHop = ptr->l->nextHop;
            ptr2->ll->oo = NULL;
            ptr2->ll->ol = NULL;
            ptr2->ll->lo = NULL;
            ptr2->ll->ll = NULL;
        }
    }
    
    return ptr2;
}

void PrintTableEven(twoBitNode* root){

}
