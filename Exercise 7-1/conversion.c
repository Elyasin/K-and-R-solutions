#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char** argv) {

    int c;

    //In Netbeans argv[0] is the program name

    if (argc < 2) {
        printf("No argument given (tolower or toupper)\n");
        return 1;
    } else if (strcmp(argv[1], "tolower") != 0 && strcmp(argv[1], "toupper") != 0) {
        printf("Argument must be either 'tolower' or 'toupper'\n");
        return 1;
    }
        
    if (!strcmp("tolower", argv[1]))
        while ((c = getchar()) != EOF)
            putchar(tolower(c));
    else if (!strcmp("toupper", argv[1]))
        while ((c = getchar()) != EOF)
            putchar(toupper(c));
    else
        printf("Argument must be 'tolwer' or 'toupper'\n");

    return 0;
}

