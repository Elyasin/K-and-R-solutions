#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

#define MAXWORD 100

enum {
    TEXT, DEFN, NAME
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

struct nlist { /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name; /* defined name */
    char *defn; /* replacement text */
};

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
void undef(char *);
int getword(char *, int);
int is_identifier(char *);

short STATE = TEXT;

int main(int argc, char** argv) {

    char word[MAXWORD];
    char name[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        if (STATE == NAME) {
            STATE = TEXT;
            install(name, word);
        }
        if (STATE == DEFN) {
            strcpy(name, word);
            if (is_identifier(name))
                STATE = NAME;
            else
                STATE = TEXT;
        }
        if (strcmp(word, "#define") == 0) {
            STATE = DEFN;
        }
    }

    // print out the hash table
    int i;
    printf("\n");
    for (i = 0; i < HASHSIZE; i++)
        if (hashtab[i] != NULL) {
            struct nlist *np;
            for (np = hashtab[i]; np != NULL; np = np->next)
                printf("%s - %s\n", np->name, np->defn);
        }


    return (EXIT_SUCCESS);
}

/* hash: form hash value from string s */
unsigned hash(char *s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s) {
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(np->name, s) == 0)
            return np; /* found */
    return NULL; /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char* defn) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *) malloc(sizeof (*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else /* already there */
        free((void *) np->defn); /* free previous defn */
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

/* undef: from s from hashtab */
void undef(char *s) {
    struct nlist *currentPtr, *previousPtr;

    for (previousPtr = NULL, currentPtr = hashtab[hash(s)];
            currentPtr != NULL;
            previousPtr = currentPtr, currentPtr = currentPtr->next) {

        if (strcmp(currentPtr->name, s) == 0) {
            if (previousPtr == NULL) /* first element */
                hashtab[hash(s)] = currentPtr->next;
            else /* element in the middle or at the end */
                previousPtr->next = currentPtr->next;
            /* free memory */
            free(currentPtr->name);
            free(currentPtr->defn);
            free(currentPtr);
            return;
        }
    }
}

/*
 * An identifier starts with '_' or an alphabetical character
 * followed by any sequence of '_' or alphanumerical character
 */
int is_identifier(char name[]) {
    char *p = name;

    if (!isalpha(*p) && *p != '_')
        return 0;

    while (*(++p))
        if (!isalnum(*p) && *p != '_')
            return 0;

    return 1;
}

int getword(char *word, int lim) {

    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()) && c != '\n')
        ;
    
    if (STATE == NAME) {
        *w++ = c;
        for (; --lim > 0 && !isspace(*w = getch()); w++)
            ;
        *w = '\0';
        return word[0];
    }
    
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c) && c != '#') {
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
