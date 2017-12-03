#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

int main(int argc, char** argv) {

    FILE *fp1, *fp2;
    char line1[MAXLINE], line2[MAXLINE];
    char *filename1, *filename2;

    if (argc != 3) {
        printf("error: program must be called with two arguments\n");
        return 1;
    }


    filename1 = *++argv;
    filename2 = *++argv;
    if ((fp1 = fopen(filename1, "r")) == NULL) {
        fprintf(stderr, "can't open %s\n", filename1);
        return 1;
    }
    if ((fp2 = fopen(filename2, "r")) == NULL) {
        fprintf(stderr, "can't open %s\n", filename2);
        return 1;
    }

    while (fgets(line1, MAXLINE, fp1) != NULL &&
            fgets(line2, MAXLINE, fp2) != NULL) {
        if (strcmp(line1, line2) != 0) {
            printf("%s: %s", filename1, line1);
            printf("%s: %s", filename2, line2);
            break;
        }
    }

    return 0;
}

