// fibonacci_program.c

#include <stdio.h>

// Function to calculate Fibonacci series
void fibonacci(int n) {
    int first = 0, second = 1, next, i;

    printf("Fibonacci Series: ");
    for (i = 0; i < n; i++) {
        if (i <= 1)
            next = i;
        else {
            next = first + second;
            first = second;
            second = next;
        }
        printf("%d ", next);
    }
    printf("\n");
}

int main() {
    printf("Executing Fibonacci program...\n");
    fibonacci(10); // Example: Fibonacci series up to 10 numbers
    return 0;
}
