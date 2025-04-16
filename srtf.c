#include <stdio.h>

struct Process {
    int pid, at, bt, rt, ct, wt, tat;
};

void findSRTF(struct Process p[], int n) {
    int completed = 0, time = 0, min_idx;
    int min_rt = 1e9;
    int is_completed[100] = {0};
    
    while (completed != n) {
        min_rt = 1e9;
        min_idx = -1;
        
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !is_completed[i] && p[i].rt < min_rt) {
                min_rt = p[i].rt;
                min_idx = i;
            }
        }
        
        if (min_idx == -1) {
            time++;
            continue;
        }
        
        p[min_idx].rt--;
        time++;
        
        if (p[min_idx].rt == 0) {
            completed++;
            is_completed[min_idx] = 1;
            p[min_idx].ct = time;
            p[min_idx].tat = p[min_idx].ct - p[min_idx].at;
            p[min_idx].wt = p[min_idx].tat - p[min_idx].bt;
        }
    }
}

void printProcesses(struct Process p[], int n) {
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    struct Process p[n];
    
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
    }
    
    findSRTF(p, n);
    printProcesses(p, n);
    
    return 0;
}
