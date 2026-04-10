//Write a program to evaluate the given expression using Recursive decent Parser for the following grammar. E -> E + E E -> E-E E
// -> E*E E -> E/E E -> E%E E -> (E) E -> number E -> id. Use C Programming Language


//Solution: First do left recursion then write program

// E  → T E'
// E' → + T E' | - T E' | ε

// T  → F T'
// T' → * F T' | / F T' | % F T' | ε

// F  → (E) | number | id

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char input[100];
int pos = 0;

// Function declarations
int E();
int T();
int F();

// Match function
void match(char expected) {
    if (input[pos] == expected) {
        pos++;
    } else {
        printf("Error at position %d\n", pos);
        exit(1);
    }
}

// E → T { (+|-) T }
int E() {
    int val = T();
    
    while (input[pos] == '+' || input[pos] == '-') {
        char op = input[pos];
        match(op);
        int val2 = T();
        
        if (op == '+') val += val2;
        else val -= val2;
    }
    return val;
}

// T → F { (*|/|%) F }
int T() {
    int val = F();
    
    while (input[pos] == '*' || input[pos] == '/' || input[pos] == '%') {
        char op = input[pos];
        match(op);
        int val2 = F();
        
        if (op == '*') val *= val2;
        else if (op == '/') val /= val2;
        else val %= val2;
    }
    return val;
}

// F → (E) | number
int F() {
    int val = 0;
    
    if (input[pos] == '(') {
        match('(');
        val = E();
        match(')');
    }
    else if (isdigit(input[pos])) {
        while (isdigit(input[pos])) {
            val = val * 10 + (input[pos] - '0');
            pos++;
        }
    }
    else {
        printf("Error: invalid character %c\n", input[pos]);
        exit(1);
    }
    
    return val;
}

int main() {
    printf("Enter expression: ");
    scanf("%s", input);
    
    int result = E();
    
    printf("Result = %d\n", result);
    return 0;
}