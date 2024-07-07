// sum_of_cubes_program.c

#include <stdio.h>

// Function to calculate sum of cubes of numbers
void sum_of_cubes(int n) {
    int sum = 0, i;
    for (i = 1; i <= n; i++) {
        sum += i * i * i;
    }
    printf("Sum of cubes of numbers up to %d: %d\n", n, sum);
}

int main() {
    printf("Executing Sum of Cubes program...\n");
    sum_of_cubes(5); // Example: Sum of cubes of numbers up to 5
    return 0;
}
