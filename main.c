//
//  main.c
//  ADRC_Assignment1
//
//  Created by Tobias Barblan on 02/10/17.
//  Copyright © 2017 Tobias Barblan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

int main(int argc, const char * argv[]) {
    
    printf(" ### ADRC 1° semestre 2017-1018 - Assignment 1 ### \n\n");
    printf("To list all possible commands, type help and press enter, \n\n");
    
    char *line = NULL;
    char **args = NULL;
    int status = 1;
    size_t bufsize = 0;

    oneBitNode * root = NULL;
    char testInsert[17] ="010";
    char testPrefix[17] = "001";
    
    do {
        printf(" >");
        bufsize = 0; // have getline allocate a buffer for us
        getline(&line, &bufsize, stdin);
        if (line[0] == 'q') status = 0;
        else if(line[0] == 'i') root = InsertPrefix(root, testInsert, 9);
        else if(line[0] == 'n') root = PrefixTree("PrefixTable.txt");
        else if(line[0] == 'p') printTree2(root);
        else if(line[0] == 'o') printTree(root, 0, -1);
        else if(line[0] == 'f') printf("Next Hop for %s is %d\n", testPrefix, LookUp1(root, testPrefix));
        else if(line[0] == 'd') root = DeletePrefix(root, testInsert);
        else if(line[0] == 't') PrintTable(root);

    } while (status);
    
    free(line);
    free(args);
    
    return 0;
}
