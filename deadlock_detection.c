// //deadlock detection program

#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int processes, resources;
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int request[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int finish[MAX_PROCESSES];
int work[MAX_RESOURCES];
int safe_sequence[MAX_PROCESSES];
int num_safe_processes = 0;

void initialize() {
    // Initialize finish array
    for (int i = 0; i < processes; ++i) {
        finish[i] = 0;
    }
}

int safety_check() {
    // Initialize work array
    for (int i = 0; i < resources; ++i) {
        work[i] = available[i];
    }

    int finished;
    do {
        finished = 1;
        for (int i = 0; i < processes; ++i) {
            if (finish[i] == 0) {
                int possible = 1;
                for (int j = 0; j < resources; ++j) {
                    if (request[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }
                if (possible) {
                    // Try allocating resources temporarily
                    for (int j = 0; j < resources; ++j) {
                        work[j] += allocation[i][j];
                    }
                    // Check if deadlock occurs
                    int deadlock = 0;
                    for (int j = 0; j < resources; ++j) {
                        if (work[j] < available[j]) {
                            deadlock = 1;
                            break;
                        }
                    }
                    // If no deadlock, mark process as finished
                    if (!deadlock) {
                        safe_sequence[num_safe_processes++] = i;
                        finish[i] = 1;
                        finished = 0;
                    }
                    // Undo temporary allocation
                    for (int j = 0; j < resources; ++j) {
                        work[j] -= allocation[i][j];
                    }
                }
            }
        }
    } while (!finished);

    // Check if all processes finished
    for (int i = 0; i < processes; ++i) {
        if (finish[i] == 0) {
            return 0; // Deadlock detected
        }
    }
    return 1; // No deadlock detected
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < processes; ++i) {
        for (int j = 0; j < resources; ++j) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the request matrix:\n");
    for (int i = 0; i < processes; ++i) {
        for (int j = 0; j < resources; ++j) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("Enter the available resources: ");
    for (int i = 0; i < resources; ++i) {
        scanf("%d", &available[i]);
    }

    initialize();

    if (safety_check()) {
        printf("No deadlock detected.\n");
        printf("Safe sequence: ");
        for (int i = 0; i < num_safe_processes; ++i) {
            printf("%d ", safe_sequence[i]);
        }
        printf("\n");
    } else {
        printf("Deadlock detected.\n");
    }

    return 0;
}
