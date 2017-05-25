/* 
 * File:   main.c
 * Author: elyasin
 *
 * Created on July 30, 2015, 9:00 AM
 */

#include <stdio.h>
#include <stdlib.h>

#define P   0 // Program
#define PC  1 // Program - Comment
#define S   2 // String
#define E   3 // Escape  (in Strings)
#define CS  4 // Comment (simple)
#define CM  5 // Comment (multiple lines)
#define CMP 6 // Comment (multiple lines) - Program
#define C   7 // Character
#define E2  8 // Escape (in Characters)

void update_transition(char c);
void countParens(char c);

//global STATE; start in state P
int STATE = P;

//counter for braces, brackets, parentheses
int braces = 0;
int brackets = 0;
int parentheses = 0;

//for unblanced symbols like )(
int BRACES_UNB = 0;
int BRACKETS_UNB = 0;
int PARENTHESES_UNB = 0;


int main(int argc, char** argv) {

    int c;

    while ((c = getchar()) != EOF) {
        update_transition(c);
    }

    if (braces != 0 || BRACES_UNB == 1) 
        puts("Unbalanced braces");
    if (brackets != 0 || BRACKETS_UNB == 1) 
        puts("Unbalanced brackets");
    if (parentheses != 0 || PARENTHESES_UNB == 1) 
        puts("Unbalanced parentheses");
    if (STATE != P && STATE != CS) 
        puts("Unbalanced quotes (double, single)");

    if (braces + brackets + parentheses == 0 
            && (BRACES_UNB + BRACKETS_UNB + PARENTHESES_UNB == 0) 
            && (STATE == P || STATE == CS)) 
        puts("All good");

    return 0;
}

void update_transition(char c) {

    if (STATE == P) {
        if (c == '/') {
            STATE = PC;
            return;
        }
        if (c == '"') {
            STATE = S;
            return;
        }
        if (c == '\'') {
            STATE = C;
            return;
        }
        countParens(c);
        return;
    } else if (STATE == PC) {
        if (c != '/' && c != '*') {
            STATE = P;
            countParens(c);
            return;
        }
        if (c == '/') STATE = CS;
        if (c == '*') STATE = CM;
        return;
    } else if (STATE == CS) {
        if (c == '\n') STATE = P;
        return;
    } else if (STATE == CM) {
        if (c == '*') STATE = CMP;
        return;
    } else if (STATE == CMP) {
        if (c == '/') STATE = P;
        if (c != '/' && c != '*') STATE = CM;
        return;
    } else if (STATE == S) {
        if (c == '"') STATE = P;
        if (c == '\\') STATE = E;
        return;
    } else if (STATE == E) {
        STATE = S;
        return;
    } else if (STATE == C) {
        if (c == '\'') STATE = P;
        if (c == '\\') STATE = E2;
        return;
    } else if (STATE == E2) {
        STATE = C;
        return;
    }

}

void countParens(char c) {
    if (c == '(') parentheses++;
    if (c == ')') parentheses--;
    if (c == '[') brackets++;
    if (c == ']') brackets--;
    if (c == '{') braces++;
    if (c == '}') braces--;
    if (parentheses < 0)
        PARENTHESES_UNB = 1; 
    if (brackets < 0)
        BRACKETS_UNB = 1;
    if (braces < 0)
        BRACES_UNB = 1;
}
