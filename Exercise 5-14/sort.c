#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int reverse);

void q_sort(void *lineptr[], int left, int right,
        int (*comp)(void *, void *));
int numcmp(char *, char *);

main(int argc, char *argv[]) {

    int nlines;
    int numeric = 0;
    int reverse = 0;

    while (--argc > 0 && (*++argv)[0] == '-') {
        int c;
        while (c = *++argv[0])
            switch (c) {
                case 'n':
                    numeric = 1;
                    break;
                case 'r':
                    reverse = 1;
                    break;
                default:
                    printf("Illegal option: %c\n", c);
                    break;
            }
    }

    if (argc != 0)
        printf("Usage: sort -n -r\n");

    printf(numeric ? "Numerical  sort\n" : "Lexicographic sort\n");
    printf(reverse ? "Reverse  sort\n" : "Normal sort\n");


    if ((nlines = readlines(lineptr, MAXLINES)) > 0) {
        if (numeric)
            q_sort((void **) lineptr, 0, nlines - 1,
                    (int (*)(void *, void *)) numcmp);
        else
            q_sort((void **) lineptr, 0, nlines - 1,
                    (int (*)(void *, void *)) strcmp);
        writelines(lineptr, nlines, reverse);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

void q_sort(void *v[], int left, int right,
        int (*comp)(void *, void *)) {

    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0) 
            swap(v, ++last, i);
    swap(v, left, last);
    q_sort(v, left, last - 1, comp);
    q_sort(v, last + 1, right, comp);
}

int numcmp(char *s1, char *s2) {

    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void swap(void *v[], int i, int j) {

    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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

void writelines(char * lineptr[], int nlines, int reverse) {

    int i;

    if (reverse)
        for (i = nlines-1; i >= 0; i--)
            printf("%s\n", lineptr[i]);
    else
        for (i = 0; i < nlines; i++)
            printf("%s\n", lineptr[i]);
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
