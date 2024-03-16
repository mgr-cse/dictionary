#include <stdio.h>

#include "option.h"
#include "input.h"
#include "fhandler.h"

int add_word() {
    char word[WORD_BUFF_SIZE];

    int len = -1;
    while (len<0) {
        printf("Word: ");
        len = dict_getline(word, WORD_BUFF_SIZE);

        if(len<0)
            printf("dict_getline(): error %d\n", len);
    }

    char def[DEF_BUFF_SIZE];
    len = -1;
    while (len<0) {
        printf("definition: ");
        len = dict_getline(def, DEF_BUFF_SIZE);

        if(len<0)
            printf("dict_getline(): error %d\n", len);
    }
    
    if(add_entry(word, def)) {
        printf("add_word(): Can't add a new entry \
in file\n");
        return 1;
    }
    
    return 0;
}

void del_word() {
    char word[WORD_BUFF_SIZE];

    int len = -1;
    while (len<0) {
        printf("Word: ");
        len = dict_getline(word, WORD_BUFF_SIZE);

        if(len<0)
            printf("dict_getline(): error %d\n", len);
    }

    del_entry(word);
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
        add_word();
        break;
    case DEL:
        del_word();
        break;
    case DISP:
        disp_entries();
        break;
    case EXIT:
        return 0;
    default:
        break;
    }

    return 1;
}