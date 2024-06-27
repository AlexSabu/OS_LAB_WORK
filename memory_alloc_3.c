//using linked list

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Memory {
    int size;
    bool is_alloc;
    struct Memory *next;
};

struct Memory* create_block(struct Memory *memory, int block_size) {
    struct Memory *new = (struct Memory*)malloc(sizeof(struct Memory));
    new->size = block_size;
    new->is_alloc = false;
    new->next = NULL;
    if (memory == NULL) {
        memory = new;
    } else {
        struct Memory *current = memory;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new;
    }
    return memory;
}

void FirstFit(struct Memory *memory, int process[], int num) {
    for (int i = 0; i < num; i++) {
        int flag = 0;
        int size = process[i];
        struct Memory *current = memory;
        while (current != NULL) {
            if (!current->is_alloc && current->size >= size) {
                flag = 1;
                current->is_alloc = true;
                int remaining = current->size - size;
                printf("process size %d allocated at block size %d. remaining: %d\n", process[i], current->size, remaining);
                if (remaining > 0) {
                    struct Memory *new = (struct Memory*)malloc(sizeof(struct Memory));
                    new->size = remaining;
                    new->is_alloc = false;
                    new->next = current->next;
                    current->size = size;
                    current->next = new;
                }
                break;
            }
            current = current->next;
        }
        if (flag == 0) {
            printf("process size %d cannot be allocated\n", process[i]);
        }
    }
}

void BestFit(struct Memory *memory, int process[], int num) {
    for (int i = 0; i < num; i++) {
        int size = process[i];
        struct Memory *current = memory;
        struct Memory *best = NULL;
        while (current != NULL) {
            if (!current->is_alloc && current->size >= size) {
                if (best == NULL || current->size < best->size) {
                    best = current;
                }
            }
            current = current->next;
        }
        if (best != NULL) {
            best->is_alloc = true;
            int remaining = best->size - size;
            printf("process size %d allocated at block size %d. remaining: %d\n", process[i], best->size, remaining);
            if (remaining > 0) {
                struct Memory *new = (struct Memory*)malloc(sizeof(struct Memory));
                new->size = remaining;
                new->is_alloc = false;
                new->next = best->next;
                best->size = size;
                best->next = new;
            }
        } else {
            printf("process size %d cannot be allocated\n", process[i]);
        }
    }
}

void WorstFit(struct Memory *memory, int process[], int num) {
    for (int i = 0; i < num; i++) {
        int size = process[i];
        struct Memory *current = memory;
        struct Memory *worst = NULL;
        while (current != NULL) {
            if (!current->is_alloc && current->size >= size) {
                if (worst == NULL || current->size > worst->size) {
                    worst = current;
                }
            }
            current = current->next;
        }
        if (worst != NULL) {
            worst->is_alloc = true;
            int remaining = worst->size - size;
            printf("process size %d allocated at block size %d. remaining: %d\n", process[i], worst->size, remaining);
            if (remaining > 0) {
                struct Memory *new = (struct Memory*)malloc(sizeof(struct Memory));
                new->size = remaining;
                new->is_alloc = false;
                new->next = worst->next;
                worst->size = size;
                worst->next = new;
            }
        } else {
            printf("process size %d cannot be allocated\n", process[i]);
        }
    }
}

int main() {
    int num_blocks, block_size;

    struct Memory *memory = NULL;

    printf("input number of blocks: ");
    scanf("%d", &num_blocks);
    printf("input block sizes:\n");
    for (int i = 0; i < num_blocks; i++) {
        scanf("%d", &block_size);
        memory = create_block(memory, block_size);
    }
    int process[] = {200, 300, 100, 50, 150, 500};
    printf("\nFirst Fit Allocation:\n");
    FirstFit(memory, process, 6);

    // Reset memory for Best Fit and Worst Fit
    memory = NULL;
    for (int i = 0; i < num_blocks; i++) {
        scanf("%d", &block_size);
        memory = create_block(memory, block_size);
    }
    printf("\nBest Fit Allocation:\n");
    BestFit(memory, process, 6);

    // Reset memory for Worst Fit
    memory = NULL;
    for (int i = 0; i < num_blocks; i++) {
        scanf("%d", &block_size);
        memory = create_block(memory, block_size);
    }
    printf("\nWorst Fit Allocation:\n");
    WorstFit(memory, process, 6);

    return 0;
}
