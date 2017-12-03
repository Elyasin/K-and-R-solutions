#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGE_LINES 30
#define MAXLINE 1000

void print_file(char *);

int main(int argc, char** argv) {

    if (argc == 1) {
        printf("No files specified\n");
        return 1;
    }

    while (--argc > 0) {
        print_file(*++argv);
    }

    return 0;
}

void print_file(char *file) {
    FILE *fp;
    char line[MAXLINE];
    int lineno = 0;
    int page = 1;

    if ((fp = fopen(file, "r")) == NULL) {
        printf("%s: error opening file\n", file);
        return;
    }

    printf("----------New file----------\n");
    printf("Title: %s\n\n", file);

    while (fgets(line, MAXLINE, fp) != NULL) {
        if (lineno % MAX_PAGE_LINES == 0) {
            printf("Page %d\n", page);
            page++;
        }
        printf("%s", line);
        lineno++;
    }

    if (ferror(fp)) {
        fprintf(stderr, "%s: error in file\n", file);
    }

    fclose(fp);

}

