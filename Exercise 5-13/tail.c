#include <stdio.h>
#include <string.h>

#define MAXLINES 5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int maxlines);

int main(int argc, char** argv) {

    int n = 10; // default value for optional parameter
    int nlines;

    if (argc > 2)
        printf("Usage: tail [-n] where n is a number\n");
    else {

        if (argc == 2) 
            n = atoi(++argv[1]);
        if (n == 0) 
            n = 10;

        if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {

            int i;

            if (nlines <= n) {
                printf("nlines (%d) <= n (%d): print all lines\n", nlines, n);
                for (i = 0; i < nlines; i++)
                    printf("%s\n", lineptr[i]);
            } else {
                printf("nlines (%d) > n (%d): print last %d lines\n", nlines, n, n);
                for (i = nlines - n; i < nlines; i++)
                    printf("%s\n", lineptr[i]);
            }
        } else {
            printf("too many input lines\n");
            return 1;
        }
    }

    return 0;
}



#define MAXLEN 1000

int get_line(char line[], int maxline);
char *alloc(int);

int readlines(char *lineptr[], int maxlines) {

    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
        if (nlines >= MAXLINES || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }

    return nlines;

}

int get_line(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') s[i++] = c;
    s[i] = '\0';
    return i;
}



#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else
        return 0;
}

void afree(char *p) {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}
