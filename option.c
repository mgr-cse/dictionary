#include <stdio.h>
#include <stdlib.h>

#include "input.h"

int option_chooser(
    const char* title,
    const char* options[],
    unsigned int len
)
{
    puts(title);
    putchar('\n');

    for(int i=0; i<len; i++)
        printf("\t%d) %s\n", i+1, options[i]);
    putchar('\n');
    
    int choice;
    int success = 0;
    
    while(!success) {
        printf("Enter your choice: ");
        
        int error_code;

        choice = opt_getnum(&error_code);

        if(error_code!=0) {
            continue;
        }

        if(choice < 1 || choice > len) {
            printf("Choice out of range.\n");
            continue;
        }

        success = 1;
    }

    return choice;
}