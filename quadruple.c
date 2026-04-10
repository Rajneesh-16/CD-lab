//Write a program to generate Quadruples(Three address code) for the given expression using c  for the following grammar. E -> E+E E -> E-E //E -> E*E E -> E/E E -> E%E E -> (E) E -> number E -> id


// The grammar is left recursive, so we convert it to:
// E → T E'
// E' → + T E' | - T E' | ε

// T → F T'
// T' → * F T' | / F T' | % F T' | ε

// F → (E) | number | id

//quadruple format
// (op, arg1, arg2, result)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char input[100];
int pos = 0;
int tempCount = 1;

// Quadruple structure
struct Quad {
    char op[5];
    char arg1[10];
    char arg2[10];
    char result[10];
} quad[100];

int quadIndex = 0;

// Create new temporary variable
char* newTemp() {
    char *temp = (char*)malloc(10);
    sprintf(temp, "t%d", tempCount++);
    return temp;
}

// Utility: create copy of string
char* copyStr(char *str) {
    char *res = (char*)malloc(20);
    strcpy(res, str);
    return res;
}

// Forward declarations
char* E();
char* T();
char* F();

// E → T { (+|-) T }
char* E() {
    char *left = T();

    while (input[pos] == '+' || input[pos] == '-') {
        char op[2];
        op[0] = input[pos++];
        op[1] = '\0';

        char *right = T();
        char *temp = newTemp();

        strcpy(quad[quadIndex].op, op);
        strcpy(quad[quadIndex].arg1, left);
        strcpy(quad[quadIndex].arg2, right);
        strcpy(quad[quadIndex].result, temp);
        quadIndex++;

        left = temp;
    }
    return left;
}

// T → F { (*|/|%) F }
char* T() {
    char *left = F();

    while (input[pos] == '*' || input[pos] == '/' || input[pos] == '%') {
        char op[2];
        op[0] = input[pos++];
        op[1] = '\0';

        char *right = F();
        char *temp = newTemp();

        strcpy(quad[quadIndex].op, op);
        strcpy(quad[quadIndex].arg1, left);
        strcpy(quad[quadIndex].arg2, right);
        strcpy(quad[quadIndex].result, temp);
        quadIndex++;

        left = temp;
    }
    return left;
}

// F → (E) | id | number
char* F() {
    if (input[pos] == '(') {
        pos++;
        char *val = E();
        if (input[pos] == ')') pos++;
        return val;
    }
    else if (isalnum(input[pos])) {
        char buffer[20];
        int i = 0;

        while (isalnum(input[pos])) {
            buffer[i++] = input[pos++];
        }
        buffer[i] = '\0';

        return copyStr(buffer);
    }
    else {
        printf("Error at position %d\n", pos);
        exit(1);
    }
}

// Main function
int main() {
    printf("Enter expression: ");
    scanf("%s", input);

    char *res = E();

    printf("\nQuadruples:\n");
    printf("Op\tArg1\tArg2\tResult\n");

    for (int i = 0; i < quadIndex; i++) {
        printf("%s\t%s\t%s\t%s\n",
               quad[i].op,
               quad[i].arg1,
               quad[i].arg2,
               quad[i].result);
    }

    printf("\nFinal Result stored in: %s\n", res);

    return 0;
}