// #include <stdio.h>
// #include <unistd.h>
// #include <sys/wait.h>

// int main() {
//     pid_t child1, child2;
//     int status;

//     child1 = fork();

//     if (child1 == 0) {
//         // First child process: Fibonacci program
//         printf("First child process (Fibonacci Program):\n");
//         execl("./system_call_child1", "system_call_child1", (char *)NULL);
//         perror("exec");
//         _exit(1); // Terminate child process in case of error
//     } else if (child1 > 0) {
//         // Parent process
//         child2 = fork();

//         if (child2 == 0) {
//             // Second child process: Sum of cubes program
//             printf("Second child process (Sum of Cubes Program):\n");
//             execl("./system_call_child2", "system_call_child1", (char *)NULL);
//             perror("exec");
//             _exit(1); // Terminate child process in case of error
//         } else if (child2 > 0) {
//             // Parent process
//             // Wait for both child processes to finish
//             waitpid(child1, &status, 0);
//             waitpid(child2, &status, 0);
//         } else {
//             perror("fork");
//             return 1;
//         }
//     } else {
//         perror("fork");
//         return 1;
//     }

//     return 0;
// }

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child1, child2;
    int status;

    // Fork the first child process (system_call_child1)
    child1 = fork();

    if (child1 < 0) {
        // Error handling if fork fails
        perror("fork");
        return 1;
    } else if (child1 == 0) {
        // Child process (system_call_child1)
        printf("First child process (Fibonacci Program):\n");
        execl("./system_call_child1", "system_call_child1", (char *)NULL);
        perror("exec");
        _exit(1); // Terminate child process in case of error
    } else {
        // Parent process

        // Wait for the first child process (system_call_child1) to complete
        waitpid(child1, &status, 0);

        // Now fork the second child process (system_call_child2)
        child2 = fork();

        if (child2 < 0) {
            // Error handling if fork fails
            perror("fork");
            return 1;
        } else if (child2 == 0) {
            // Child process (system_call_child2)
            printf("Second child process (Sum of Cubes Program):\n");
            execl("./system_call_child2", "system_call_child2", (char *)NULL);
            perror("exec");
            _exit(1); // Terminate child process in case of error
        } else {
            // Parent process
            // Wait for the second child process (system_call_child2) to complete
            waitpid(child2, &status, 0);
        }
    }

    return 0;
}


//exceution:

//  gcc -o system_call_parent system_call_parent.c
//  gcc -o system_call_child1 system_call_child1.c
//  gcc -o system_call_child2 system_call_child2.c
// ./system_call_parent