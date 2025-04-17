#include <stdio.h>
#include <stdbool.h>

#define P 5
#define R 3

void deadlockDetection(int allocation[P][R], int request[P][R], int available[R]) {
    int work[R];
    bool finish[P] = {false};
    bool deadlock = false;


    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }


    int count = 0;
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canProceed = true;
                for (int j = 0; j < R; j++) {
                    if (request[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }


                if (canProceed) {
                    for (int j = 0; j < R; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    printf("Process P%d is finished.\n", i);
                    found = true;
                    count++;
                }
            }
        }

        if (!found) {
            break;
        }
    }

    for (int i = 0; i < P; i++) {
        if (!finish[i]) {
            deadlock = true;
            printf("Process P%d is in deadlock.\n", i);
        }
    }

    if (!deadlock) {
        printf("No deadlock detected. All processes can complete.\n");
    } else {
        printf("Deadlock detected.\n");
    }
}

int main() {
    int allocation[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int request[P][R] = {
        {0, 0, 0},
        {2, 0, 2},
        {0, 0, 0},
        {1, 0, 0},
        {0, 0, 2}
    };

    int available[R] = {0, 0, 0};

    deadlockDetection(allocation, request, available);

    return 0;
}
