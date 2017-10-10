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
    
    do {
        printf(" >");
        bufsize = 0; // have getline allocate a buffer for us
        getline(&line, &bufsize, stdin);
        if (line[0] == 'a') status = 0;
        
    } while (status);
    
    free(line);
    free(args);
    
    return 0;
}
