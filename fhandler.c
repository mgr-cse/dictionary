#include <stdio.h>
#include <stdlib.h>

#define DICT_FILE_NAME "dictionary.txt"

static FILE* dict_file;

int dict_file_init() {
    dict_file = fopen(DICT_FILE_NAME, "r+");

    if(dict_file==NULL){
        printf("dict_file_init(): trying to create a fresh file\n");

        dict_file = fopen(DICT_FILE_NAME, "w+");
        if(dict_file==NULL) {
            printf("dict_file_init(): error opening a file\n");
            return -1;
        }
    }
    return 0;
}

int dict_file_close() {
    if(dict_file!=NULL) {
        fclose(dict_file);
        return 0;
    }
    return -1;
}