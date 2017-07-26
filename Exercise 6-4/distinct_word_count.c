#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

#define NOISEWORDS_SIZE   (sizeof stopwords / sizeof stopwords[0])

// words in noisewords must be ordered lexicographically

char *stopwords[] = {
    "a", "about", "above", "above", "across", "after", "afterwards", "again",
    "against", "all", "almost", "alone", "along", "already", "also", "although",
    "always", "am", "among", "amongst", "amoungst", "amount", "an", "and",
    "another", "any", "anyhow", "anyone", "anything", "anyway", "anywhere",
    "are", "around", "as", "at", "back", "be", "became", "because", "become",
    "becomes", "becoming", "been", "before", "beforehand", "behind", "being",
    "below", "beside", "besides", "between", "beyond", "bill", "both", "bottom",
    "but", "by", "call", "can", "cannot", "cant", "co", "con", "could",
    "couldnt", "cry", "de", "describe", "detail", "do", "done", "down", "due",
    "during", "each", "eg", "eight", "either", "eleven", "else", "elsewhere",
    "empty", "enough", "etc", "even", "ever", "every", "everyone", "everything",
    "everywhere", "except", "few", "fifteen", "fify", "fill", "find", "fire",
    "first", "five", "for", "former", "formerly", "forty", "found", "four",
    "from", "front", "full", "further", "get", "give", "go", "had", "has",
    "hasnt", "have", "he", "hence", "her", "here", "hereafter", "hereby",
    "herein", "hereupon", "hers", "herself", "him", "himself", "his", "how",
    "however", "hundred", "ie", "if", "in", "inc", "indeed", "interest", "into",
    "is", "it", "its", "itself", "keep", "last", "latter", "latterly", "least",
    "less", "ltd", "made", "many", "may", "me", "meanwhile", "might", "mill",
    "mine", "more", "moreover", "most", "mostly", "move", "much", "must", "my",
    "myself", "name", "namely", "neither", "never", "nevertheless", "next",
    "nine", "no", "nobody", "none", "noone", "nor", "not", "nothing", "now",
    "nowhere", "of", "off", "often", "on", "once", "one", "only", "onto", "or",
    "other", "others", "otherwise", "our", "ours", "ourselves", "out", "over",
    "own", "part", "per", "perhaps", "please", "put", "rather", "re", "same",
    "see", "seem", "seemed", "seeming", "seems", "serious", "several", "she",
    "should", "show", "side", "since", "sincere", "six", "sixty", "so", "some",
    "somehow", "someone", "something", "sometime", "sometimes", "somewhere",
    "still", "such", "system", "take", "ten", "than", "that", "the", "their",
    "them", "themselves", "then", "thence", "there", "thereafter", "thereby",
    "therefore", "therein", "thereupon", "these", "they", "thickv", "thin",
    "third", "this", "those", "though", "three", "through", "throughout",
    "thru", "thus", "to", "together", "too", "top", "toward", "towards",
    "twelve", "twenty", "two", "un", "under", "until", "up", "upon", "us",
    "very", "via", "was", "we", "well", "were", "what", "whatever", "when",
    "whence", "whenever", "where", "whereafter", "whereas", "whereby",
    "wherein", "whereupon", "wherever", "whether", "which", "while", "whither",
    "who", "whoever", "whole", "whom", "whose", "why", "will", "with", "within",
    "without", "would", "yet", "you", "your", "yours", "yourself", "yourselves",
    "the"
};

struct tnode {
    char *word;
    int frequency;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
int binsearch(char *, char * noisewords[], int);
int count_tree_elements(struct tnode*);
int copy_tree_to_array(struct tnode array[], int count, struct tnode *root);
int compare_tnode(const void*, const void*);

/* word frequency count */
main() {

    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if (binsearch(word, stopwords, NOISEWORDS_SIZE) == -1)
                root = addtree(root, word);

    // create array of appropriate size
    int tree_size = count_tree_elements(root);
    struct tnode tnode_array[tree_size];
    
    // copy struct tnodes into array
    copy_tree_to_array(tnode_array, 0, root);
    
    // qsort the array
    qsort(tnode_array, tree_size, sizeof (struct tnode), compare_tnode);
    
    // print the sorted array
    int i;
    for (i = 0; i < tree_size; i++)
        printf("%4d %s\n", tnode_array[i].frequency, tnode_array[i].word);

    return 0;
}

struct tnode *talloc(void);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {

    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup(w);
        p->frequency = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->frequency++;
    else if (cond < 0)
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
        printf("%4d %s\n", p->frequency, p->word);
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

int count_tree_elements(struct tnode *root) {
    int count = 1;
    if (root == NULL)
        return 0;

    count += count_tree_elements(root->left);
    count += count_tree_elements(root->right);
    return count;
}

int copy_tree_to_array(struct tnode array[], int count, struct tnode *root) {

    if (root == NULL)
        return count;

    array[count++] = *root;
    if (root->left != NULL)
        count = copy_tree_to_array(array, count, root->left);
    if (root->right != NULL)
        count = copy_tree_to_array(array, count, root->right);

    return count;
}

int compare_tnode(const void *elem1, const void *elem2) {
    return (((struct tnode*) elem2)->frequency 
            -
            ((struct tnode*) elem1)->frequency);
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
    return (struct tnode *) malloc(sizeof (struct tnode));
}