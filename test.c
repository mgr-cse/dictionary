#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* f = fopen("dictionary.txt", "r+");
    char c = '0';
    while((c=fgetc(f))!=',');
    fputc('@', f);
    return 0;
}