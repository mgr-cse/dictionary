#include <stdio.h>
#include <stdlib.h>

#include "input.h"

int dict_clearbuf() {
    while (getchar()!='\n');
}

int dict_getline(char *restrict s, int len)
{
    char c = '0';
    int scan_len = 0;
    
    while(scan_len < (len-1) && 
        (c=getchar()) != '\n')
    {
        s[scan_len] = c;
        scan_len++;
    }
    s[scan_len] = '\0';

    if(c!='\n' && scan_len==len-1) {
        dict_clearbuf();
        return -BUFF_OVERFLOW;
    }

    return scan_len;
}

int opt_getnum(int *err_code) {
    char buf[OPT_DIGIT_BUFF];
    int len = dict_getline(buf, OPT_DIGIT_BUFF);
    if(len<0) {
        printf("dict_getline() error: %d\n", len);
        *err_code = -OPT_INVALID_NUM;
        return 0;
    }
    
    for(int i=0; i<len; i++)
        if(buf[i]<'0' || buf[i]>'9') {
            printf("opt_getnum(): not a valid number\n");
            *err_code = -OPT_INVALID_NUM;
            return 0;
        }
    
    int num = atoi(buf);
    *err_code = 0;
    return num;
}