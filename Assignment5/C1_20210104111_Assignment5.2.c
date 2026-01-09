#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char input[100];
int i = 0;

void Factor();
void Term();
void Exp();

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

int main() {
    printf("Enter the arithmetic expression: ");
    fgets(input, sizeof(input), stdin);

    // Remove newline from input if present
    input[strcspn(input, "\n")] = '\0';

    Exp();

    if (input[i] == '\0')
        printf("Valid Expression\n");
    else
        printf("Invalid Expression: Unexpected characters after parsing\n");

    return 0;
}
