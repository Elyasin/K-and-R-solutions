#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAX_WORD_COUNT 100

#define NOISEWORDS_SIZE   (sizeof noisewords / sizeof noisewords[0])

// words in noisewords must be ordered lexicographically

char *noisewords[] = {
    "a", "an", "and", "are", "at", "be", "by", "can", "did", "do", "done", 
    "for", "from", "have", "he", "her", "his", "if", "in", "into", "is", "it", 
    "its", "many", "must", "no", "none", "not", "of", "off", "on", "or",  
    "our", "ours", "so", "such", "that", "the", "them", "they", "their", 
    "this", "to", "too", "us", "was", "we", "were", "what", "who", "with", 
    "without"
};

struct tnode {
    char *word;
    int lines[MAX_WORD_COUNT];
    int index;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
int binsearch(char *, char * noisewords[], int);

int LINE_NUMBER = 1;

/* word frequency count */
main() {

    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if (binsearch(word, noisewords, NOISEWORDS_SIZE) == -1)
                root = addtree(root, word);
    treeprint(root);

    return 0;
}

struct tnode *talloc(void);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {

    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup(w);
        p->lines[p->index++] = LINE_NUMBER;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        if (p->lines[p->index - 1] != LINE_NUMBER)
            p->lines[p->index++] = LINE_NUMBER;
    } else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);

    return p;
}

/* treeprint: in-order print of tree */
void treeprint(struct tnode *p) {

    int i;

    if (p != NULL) {
        treeprint(p->left);
        printf("%s - ", p->word);
        for (i = 0; i < p->index; i++)
            printf("%d, ", p->lines[i]);
        printf("\n");
        treeprint(p->right);
    }
}

int binsearch(char *word, char *noisewords[], int n) {

    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        // use strcasecmp from string.h - case-insensitive comparison 
        if ((cond = strcasecmp(word, noisewords[mid])) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }

    return -1;
}

int getword(char *word, int lim) {

    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()) && c != '\n')
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        if (c == '\n')
            LINE_NUMBER++;
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* talloc: make a node */
struct tnode *talloc(void) {
    struct tnode *p = (struct tnode *) malloc(sizeof (struct tnode));
    p->index = 0;
    return p;
}
