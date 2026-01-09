#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char input[100];
int i = 0;

void X();

void A() {
    if (input[i] == 'a') {
        i++;   // Consume 'a'
        X();   // Process 'X'
        if (input[i] == 'd') {
            i++;  // Consume 'd'
            return;
        } else {
            printf("Invalid String\n");
            exit(0);
        }
    } else {
        printf("Invalid String\n");
        exit(0);
    }
}

void X() {
    while ((input[i] == 'b' && input[i + 1] == 'b') ||
           (input[i] == 'b' && input[i + 1] == 'c')) {
        i += 2;  // Consume 'bb' or 'bc'
    }
    // Don't move `i` forward if 'd' is present, allow A() to process it
}

int main() {
    printf("Enter the string: ");
    scanf("%s", input);

    A();

    if (input[i] == '\0')
        printf("Valid String\n");
    else
        printf("Invalid String\n");

    return 0;
}

