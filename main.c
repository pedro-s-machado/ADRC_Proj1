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
    printf("To list all possible commands, type h and press enter, \n\n");
    
    char *line = NULL;
    char *line2 = NULL;
    char **args = NULL;
    int status = 1;
    size_t bufsize = 0;

    oneBitNode *root = NULL;
    twoBitNode *root2 = NULL;
    
    do {
        printf("\n >");
        bufsize = 0; // have getline allocate a buffer for us
        getline(&line, &bufsize, stdin);
        
        if (line[0] == 'q'){
            status = 0;
        }
        else if(line[0] == 'i'){
            printf("Insert a Prefix(16 bit): >");
            bufsize = 0; // have getline allocate a buffer for us
            getline(&line, &bufsize, stdin);

            printf("Insert the NextHop(int): >");
            bufsize = 0; // have getline allocate a buffer for us
            getline(&line2, &bufsize, stdin);
            root = InsertPrefix(root, line, atoi(line2));
        } 
        else if(line[0] == 'o'){
            printf("Insert the name of the file: >");
            bufsize = 0; // have getline allocate a buffer for us
            scanf("%s", line);
            root = PrefixTree(line);
            getline(&line, &bufsize, stdin);
        }
        else if(line[0] == 'l'){
            printf("Insert the prefix(16 bit): >");
            scanf("%s", line);
            printf("Next Hop for %s is %d\n", line, LookUp1(root, line));   
            getline(&line, &bufsize, stdin);
        }
        else if(line[0] == 'd'){
            printf("Insert the prefix(16 bit): >");
            scanf("%s", line);
            root = DeletePrefix(root, line);
            getline(&line, &bufsize, stdin);
        }
        else if(line[0] == 'p'){
            PrintTable(root);
        }
        else if(line[0] == 'b'){
            root2 = BinaryToTwoBit(root, -1);
        }
        else if(line[0] == 'v'){
            PrintTableEven(root2);
        }else if(line[0] == 'h'){
            printf("o - PrefixTree\n");
            printf("p - PrintTable\n");
            printf("l - LookUp\n");
            printf("i - InsertPrefix\n");
            printf("d - DeletePrefix\n");
            printf("b - BinaryToTwoBit\n");
            printf("v - PrintTableEven\n");
            printf("h - Help\n");
            printf("q - Quit\n");
        }
        else{
            printf("Not a known command\n");
        }
    } while (status);
    
    free(line);
    free(args);
    
    return 0;
}