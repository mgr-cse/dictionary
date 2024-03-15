#include <stdio.h>

#include "menus.h"
#include "fhandler.h"

#define DICT_VER "0.1"

int main(char argc, char* argv[]) {
    printf("Dictionary v"DICT_VER"\n");

    if(dict_file_init()!=0) {
        printf("Error opening dictionary file");
        return -1;
    }
    
    while(main_menu());

    dict_file_close();
    
    printf("Program exiting...\n");
    
    return 0;
}