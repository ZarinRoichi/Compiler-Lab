#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char input[100];
int i = 0;

void Factor();
void Term();
void Exp();
void Asgn_Stat();

void Factor() {
    if (input[i] == '(') {
        i++;
        Exp();
        if (input[i] == ')') {
            i++;
            return;
        } else {
            printf("Invalid Expression: Missing closing parenthesis\n");
            exit(0);
        }
    } else if (isalpha(input[i]) || isdigit(input[i])) {
        i++;
        return;
    }
    printf("Invalid Expression: Unexpected character '%c'\n", input[i]);
    exit(0);
}

void Term() {
    Factor();
    while (input[i] == '*' || input[i] == '/') {
        i++;
        Factor();
    }
}

void Exp() {
    Term();
    while (input[i] == '+' || input[i] == '-') {
        i++;
        Term();
    }
}

// Function to handle assignment statements: id = exp
void Asgn_Stat() {
    if (isalpha(input[i])) {  // Identifier (id) should start with a letter
        i++;
        if (input[i] == '=') {
            i++;  // Move past '='
            Exp();  // Parse the expression after '='
        } else {
            printf("Error: Expected '=' after identifier\n");
            exit(0);
        }
    } else {
        printf("Error: Invalid assignment statement\n");
        exit(0);
    }
}

int main() {
    printf("Enter the statement to parse: ");
    fgets(input, sizeof(input), stdin);

    // Remove newline from input if present
    input[strcspn(input, "\n")] = '\0';

    Asgn_Stat();  // Start parsing

    if (input[i] == '\0')
        printf("Parsing successful! Statement is valid.\n");
    else
        printf("Invalid Statement: Unexpected characters after parsing\n");

    return 0;
}
