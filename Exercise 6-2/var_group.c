#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

#define NKEYS   (sizeof keytab / sizeof keytab[0])

// keywords must be ordered lexicographically

struct key {
    char *word;
    int count;
} keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "do", 0,
    "double", 0,
    "else", 0,
    "enum", 0,
    "extern", 0,
    "float", 0,
    "for", 0,
    "goto", 0,
    "if", 0,
    "int", 0,
    "long", 0,
    "register", 0,
    "return", 0,
    "short", 0,
    "signed", 0,
    "sizeof", 0,
    "static", 0,
    "struct", 0,
    "switch", 0,
    "typedef", 0,
    "union", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
struct key *binsearch(char *, struct key *, int);

int PREFIX_COUNT = 6;

/* word frequency count */
main(int argc, char *argv[]) {

    struct tnode *root;
    char word[MAXWORD];

    // Read parameter from command line
    if (argc == 2) {
        PREFIX_COUNT = atoi(argv[1]);
        if (PREFIX_COUNT <= 0) {
            PREFIX_COUNT = 6;
        }
    }

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if ( (isalpha(word[0]) || word[0] == '_') && strlen(word) >= PREFIX_COUNT )
            if (binsearch(word, keytab, NKEYS) == NULL)
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
        p->word = strndup(w, PREFIX_COUNT);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strncmp(w, p->word, PREFIX_COUNT)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);

    return p;
}

/* treeprint: in-order print of tree */
void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

/* talloc: make a node */
struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof (struct tnode));
}

struct key *binsearch(char *word, struct key *tab, int n) {

    int cond;
    struct key* low = &tab[0];
    struct key* high = &tab[n];
    struct key* mid;

    while (low < high) {
        mid = low + (high - low) / 2;
        if ((cond = strcmp(word, mid->word)) < 0)
            high = mid;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }

    return NULL;
}

int getword(char *word, int lim) {

    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    //Consume string constants
    if (c == '\"') {
        for (; --lim > 0; w++)
            if ((*w = getch()) == '\"')
                break;
        *++w = '\0';
        return word[0];
    }
    //Consume comments
    if (c == '/') {
        c = getch();
        //Single line comments
        if (c == '/') {
            for ((*w++ = c) && (--lim > 0); --lim > 0; w++)
                if ((*w = getch()) == '\n') {
                    *++w = '\0';
                    return word[0];
                }
        } else if (c == '*') {
            for ((*w++ = c) && (--lim > 0); --lim > 0; w++)
                if ((*w = getch()) == '/')
                    if (*(w - 1) == '*') {
                        *++w = '\0';
                        return word[0];
                    }
        } else {
            ungetch(c);
            *w = '\0';
            return '/';
        }
    }
    //Consume preprocessor control lines
    if (c == '#') {
        //Simple assumption: starts with '#' and ends with '\n'
        for (; --lim > 0; w++)
            if ((*w = getch()) == '\n')
                break;

    }
    if (!isalpha(c) && c != '_') {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch()) && *w != '_') {
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
