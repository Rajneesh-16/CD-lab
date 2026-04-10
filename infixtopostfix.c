//Write a program to convert infix expression to postfix expression via means of SDT using C for the following grammar. E -> E+T | E-T | T //T -> T*F | T/F | F F -> (E) | -F | id


#include <stdio.h>
#include <ctype.h>
#include <string.h>

char input[100];
int pos = 0;

// Function declarations
void E();
void T();
void F();

// Match expected character
void match(char expected) {
    if (input[pos] == expected) {
        pos++;
    } else {
        printf("Error: unexpected symbol %c\n", input[pos]);
    }
}

// E → T { (+|-) T }
void E() {
    T();
    while (input[pos] == '+' || input[pos] == '-') {
        char op = input[pos];
        match(op);
        T();
        printf("%c", op);   // SDT action
    }
}

// T → F { (*|/) F }
void T() {
    F();
    while (input[pos] == '*' || input[pos] == '/') {
        char op = input[pos];
        match(op);
        F();
        printf("%c", op);   // SDT action
    }
}

// F → (E) | -F | id
void F() {
    if (input[pos] == '(') {
        match('(');
        E();
        match(')');
    }
    else if (input[pos] == '-') {   // unary minus
        match('-');
        F();
        printf("~");   // use ~ for unary minus
    }
    else if (isalnum(input[pos])) {   // id
        printf("%c", input[pos]);
        pos++;
    }
    else {
        printf("Error: invalid character %c\n", input[pos]);
    }
}

int main() {
    printf("Enter infix expression: ");
    scanf("%s", input);

    printf("Postfix expression: ");
    E();

    printf("\n");
    return 0;
}