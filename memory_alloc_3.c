
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
    FirstFit(memory, process, 6);

    return 0;
}
