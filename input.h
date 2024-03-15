#ifndef INPUT_H
#define INPUT_H

#define OPT_DIGIT_BUFF 5
#define WORD_BUFF_SIZE 64
#define DEF_BUFF_SIZE 512

// error codes
#define BUFF_OVERFLOW 1
#define OPT_INVALID_NUM 2

int dict_clearbuf();
int dict_getline(char *restrict s, int len);
int opt_getnum(int *err_code);

#endif