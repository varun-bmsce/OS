#include <stdio.h>

struct Block {
    int block_no;
    int block_size;
    int is_free;
};

struct File {
    int file_no;
    int file_size;
};

void resetBlocks(struct Block blocks[], int n) {
    for (int i = 0; i < n; i++) {
        blocks[i].is_free = 1;
    }
}

void firstFit(struct Block blocks[], int n_blocks, struct File files[], int n_files) {
    printf("\nMemory Management Scheme - First Fit\n");
    printf("File_no :\tFile_size :\tBlock_no :\tBlock_size :\n");

    for (int i = 0; i < n_files; i++) {
        int allocated = 0;
        for (int j = 0; j < n_blocks; j++) {
            if (blocks[j].is_free && blocks[j].block_size >= files[i].file_size) {
                blocks[j].is_free = 0;
                printf("%d\t\t%d\t\t%d\t\t%d\n", files[i].file_no, files[i].file_size, blocks[j].block_no, blocks[j].block_size);
                allocated = 1;
                break;
            }
        }
        if (!allocated)
            printf("%d\t\t%d\t\t-\t\t-\n", files[i].file_no, files[i].file_size);
    }
}

void bestFit(struct Block blocks[], int n_blocks, struct File files[], int n_files) {
    printf("\nMemory Management Scheme - Best Fit\n");
    printf("File_no :\tFile_size :\tBlock_no :\tBlock_size :\n");

    for (int i = 0; i < n_files; i++) {
        int best = -1;
        for (int j = 0; j < n_blocks; j++) {
            if (blocks[j].is_free && blocks[j].block_size >= files[i].file_size) {
                if (best == -1 || blocks[j].block_size < blocks[best].block_size)
                    best = j;
            }
        }
        if (best != -1) {
            blocks[best].is_free = 0;
            printf("%d\t\t%d\t\t%d\t\t%d\n", files[i].file_no, files[i].file_size, blocks[best].block_no, blocks[best].block_size);
        } else {
            printf("%d\t\t%d\t\t-\t\t-\n", files[i].file_no, files[i].file_size);
        }
    }
}

void worstFit(struct Block blocks[], int n_blocks, struct File files[], int n_files) {
    printf("\nMemory Management Scheme - Worst Fit\n");
    printf("File_no :\tFile_size :\tBlock_no :\tBlock_size :\n");

    for (int i = 0; i < n_files; i++) {
        int worst = -1;
        for (int j = 0; j < n_blocks; j++) {
            if (blocks[j].is_free && blocks[j].block_size >= files[i].file_size) {
                if (worst == -1 || blocks[j].block_size > blocks[worst].block_size)
                    worst = j;
            }
        }
        if (worst != -1) {
            blocks[worst].is_free = 0;
            printf("%d\t\t%d\t\t%d\t\t%d\n", files[i].file_no, files[i].file_size, blocks[worst].block_no, blocks[worst].block_size);
        } else {
            printf("%d\t\t%d\t\t-\t\t-\n", files[i].file_no, files[i].file_size);
        }
    }
}

int main() {
    int n_blocks, n_files, choice;

    printf("Memory Management Scheme\n");
    printf("Enter the number of blocks: ");
    scanf("%d", &n_blocks);

    struct Block blocks[n_blocks];

    printf("Enter the size of the block:\n");
    for (int i = 0; i < n_blocks; i++) {
        blocks[i].block_no = i + 1;
        printf("Block %d: ", i + 1);
        scanf("%d", &blocks[i].block_size);
        blocks[i].is_free = 1;
    }

    printf("Enter the number of files: ");
    scanf("%d", &n_files);

    struct File files[n_files];
    printf("Enter the size of the file:\n");
    for (int i = 0; i < n_files; i++) {
        files[i].file_no = i + 1;
        printf("File %d: ", i + 1);
        scanf("%d", &files[i].file_size);
    }

    do {
        printf("\n1. Best Fit\n2. Worst Fit\n3. First Fit\n4. Exiting\nEnter your choice: ");
        scanf("%d", &choice);

        resetBlocks(blocks, n_blocks);

        switch (choice) {
            case 1: bestFit(blocks, n_blocks, files, n_files); break;
            case 2: worstFit(blocks, n_blocks, files, n_files); break;
            case 3: firstFit(blocks, n_blocks, files, n_files); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
