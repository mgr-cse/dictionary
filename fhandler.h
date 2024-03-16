#ifndef FHANDLER_H
#define FHANDLER_H

int read_file(void);
void close_file(void);

int add_entry(char word[], char def[]);
void del_entry(char word[]);
void disp_entries(void);

#endif