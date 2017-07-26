#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101

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

int main(int argc, char** argv) {

    printf("hash(\"IN\") == 18? : %d\n", hash("IN") == 18);
    struct nlist *p = lookup("IN");
    printf("lookup(\"IN\") == NULL? : %d\n", p == NULL);
    p = install("IN", "TEXT");
    printf("install(\"IN\", \"TEXT\") == NULL? : %d\n", p == NULL);
    p = lookup("IN");
    printf("lookup(\"IN\" == NULL? : %d\n", p == NULL);
    undef(p->name);
    printf("undef(\"IN\")\n");
    p = lookup("IN");
    printf("lookup(\"IN\") == NULL? : %d\n", p == NULL);

    return 0;
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
