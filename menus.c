#include <stdio.h>

#include "option.h"
#include "input.h"

int add_word() {
    char word[WORD_BUFF_SIZE];

    int len = -1;
    while (len<0) {
        printf("Word: ");
        len = dict_getline(word, WORD_BUFF_SIZE);

        if(len<0)
            printf("dict_getline(): error %d\n", len);
    }
    

}

int main_menu() {
    enum {
        ADD = 1,
        DEL,
        DISP,
        EXIT
    };
    
    const char * main_menu_message = "\
Choose from the following functions:";
    
    const char* main_options[] = {
        "add",
        "delete",
        "display",
        "exit"
    }; 
   
    int choice = option_chooser(
        main_menu_message,
        main_options, 
        sizeof(main_options)/sizeof(char*));

    switch (choice) {
    case ADD:
        /* code */
        break;
    case DEL:
        /* code */
        break;
    case DISP:
        /* code */
        break;
    case EXIT:
        return 0;
    default:
        break;
    }

    return 1;
}