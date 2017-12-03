#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_COL 80

#define TAB_SIZE 8 //tab space on my system

int main(int argc, char** argv) {

    int c;
    short col = 0;

    if (argc < 2) {
        printf("No argument given\n");
        return 1;
    } else if (strcmp(argv[1], "hex") != 0 && strcmp(argv[1], "oct") != 0) {
        printf("Argument must be either 'hex' or 'oct'\n");
        return 1;
    }

    while ((c = getchar()) != EOF) {
        if (!isprint(c) && !iscntrl(c)) {
            if (strcmp(argv[1], "hex") == 0)
                printf("%#.2x", c);
            else
                printf("%#.3o", c);
            col += 4;
        } else {
            putchar(c);
            col++;
            if (col >= MAX_COL - TAB_SIZE)
                col = 0, putchar('\n');
            if (c == '\n')
                col = 0;
            if (c == '\t')
                col += TAB_SIZE;
        }
    }

    return 0;
}
