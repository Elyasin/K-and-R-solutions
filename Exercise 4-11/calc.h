#define NUMBER  '0' /* signal that a number was found */
#define SINUS   '~'
#define EXP     '\"'
#define POW     '^'
#define PRINT   '?'
#define DUPL    ':'
#define SWAP    '#'
#define CLEAR   '_'
#define SET_VAR '8' // capital characters set values
#define GET_VAR '9' // small characters read values

#define ALPHA   26

int getch(void);
int getop(char []);
void push(double);
double pop(void);
double top(void);
void swap(void);
void clear(void);
