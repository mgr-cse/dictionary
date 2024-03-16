#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

#define DICT_FILE_NAME "dictionary.txt"

static FILE* dict_file;

static ENTRIES entries = NULL;
static int entries_len;

int get_word(FILE* fptr, char word[], int max_len, char delim) {
    int i = 0;
    while(i<max_len) {
        char c = fgetc(fptr);
        if(c=='\\') c = fgetc(fptr);
        else if(c==delim) break;

        word[i] = c;
        i++;
    }

    if(i==max_len) {
        printf("get_word(): overflow\n");
        word[max_len-1] = '\0';
        return -1;
    }

    word[i] = '\0';
    return 0;

}

int read_file(){
    int ret_code = 0;

    FILE* fptr = fopen(DICT_FILE_NAME, "r");
    
    if(fptr == NULL) {
        printf("read_file(): faild to find "\
DICT_FILE_NAME" Trying to create a new one.\n");
    
        fptr = fopen(DICT_FILE_NAME, "w+");
    }

    if(fptr == NULL) {
        printf("read_file(): still can not \
open a file, exiting...\n");
        return -1;
    }

    // count lines
    entries_len = 0;
    char c;
    while((c=fgetc(fptr))!=EOF){
        if(c=='\n') entries_len++;
    }

    entries = (ENTRIES)malloc(entries_len*sizeof(ENTRY));
    if(!entries) {
        printf("read_file() Failed to allocate memory \
for reading the file\n");
        return -1;
    }

    // parse entries
    rewind(fptr);
    for(int i=0; i<entries_len; i++) {
        int err = get_word(fptr, entries[i].word, WORD_BUFF_SIZE, ',');
        if(err) {
            ret_code = -1;
            goto READ_FILE_CLOSE;
        }
        err = get_word(fptr, entries[i].def, DEF_BUFF_SIZE, '\n');
        if(err) {
            ret_code = -1;
            goto READ_FILE_CLOSE;
        }
        entries[i].del = 0;
    }

READ_FILE_CLOSE:
    int err = fclose(fptr);
    if(err) return -1;
    return ret_code;
    
}

int put_word(FILE* fptr, char word[]) {
    for(int i=0; word[i]!='\0'; i++) {
        if(word[i]==',' || word[i]=='\\')
            fputc('\\', fptr);
        fputc(word[i], fptr);
    }
    return 0;
}

int write_back_entries() {
    FILE* fptr = fopen(DICT_FILE_NAME, "w");
    if(fptr==NULL) {
        printf("write_back() can not open file\n");
        return -1;
    }
    
    for(int i=0; i<entries_len; i++) {
        if(entries[i].del==1) continue;

        put_word(fptr, entries[i].word);
        fputc(',', fptr);
        put_word(fptr, entries[i].def);
        fputc('\n', fptr);
    }

    int err = fclose(fptr);
    if(err) {
        printf("write_back_entries(): can not close file\n");
        return -1;
    }
    return 0;
}

int add_entry(char word[], char def[]) {
    for(int i=0; i<entries_len; i++) {
        if(strcmp(word, entries[i].word)==0) {
            printf("Word already exists!\n");
            return -1;
        }
    }

    entries_len++;
    entries = (ENTRIES)realloc(entries, entries_len*sizeof(ENTRY));
    if(entries==NULL) {
        printf("add_entry(): realloc failed\n");
        return -1;
    }
    
    strcpy(entries[entries_len - 1].word, word);
    strcpy(entries[entries_len - 1].def, def);
    entries[entries_len - 1].del = 0;

    write_back_entries();
    
    return 0;
}

void del_entry(char word[]) {
    for(int i=0; i<entries_len; i++)
        if(strcmp(word, entries[i].word)==0) {
            entries[i].del = 1;
            break;
        }
}


void disp_entries() {
    for(int i=0; i<entries_len; i++) {
        if(entries[i].del==1) continue;
        
        for(int j=0; entries[i].word[j]!='\0'; j++)
            putchar(entries[i].word[j]);
        putchar(':');
        putchar(' ');

        for(int j=0; entries[i].def[j]!='\0'; j++)
            putchar(entries[i].def[j]);
        putchar('\n');
    }
}

void close_file() {
    write_back_entries();
    free(entries);
}