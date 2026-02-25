#include <stdio.h>

void listProcesses() {
    printf("Simulated Process List:\n");
    printf("PID\tProcess Name\n");
    printf("101\tProcess_A\n");
    printf("102\tProcess_B\n");
    printf("103\tProcess_C\n");
}

void getMemoryUsage() {
    printf("Simulated Memory Usage:\n");
    printf("Total Physical Memory: 8192 MB\n");
    printf("Used Physical Memory: 4096 MB\n");
}

void fcfs(int pid[], int bt[], int n) {
    int wt[n], tat[n];
    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];

    printf("\n--- FCFS Scheduling ---\n");
    printf("PID\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        printf("%d\t%d\t%d\t%d\n", pid[i], bt[i], wt[i], tat[i]);
    }
}

// SJF Scheduling
void sjf(int pid[], int bt[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (bt[i] > bt[j]) {
                int temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = pid[i]; pid[i] = pid[j]; pid[j] = temp;
            }
        }
    }

    int wt[n], tat[n];
    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];

    printf("\n--- SJF Scheduling ---\n");
    printf("PID\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        printf("%d\t%d\t%d\t%d\n", pid[i], bt[i], wt[i], tat[i]);
    }
}


void roundRobin(int pid[], int bt[], int n, int tq) {
    int rem_bt[n], wt[n], tat[n];
    for (int i = 0; i < n; i++) rem_bt[i] = bt[i];
    int t = 0;

    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = 0;
                if (rem_bt[i] > tq) {
                    t += tq;
                    rem_bt[i] -= tq;
                } else {
                    t += rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
        if (done) break;
    }

    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];

    printf("\n--- Round Robin Scheduling ---\n");
    printf("PID\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\n", pid[i], bt[i], wt[i], tat[i]);
}

void priorityScheduling(int pid[], int bt[], int pr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (pr[i] < pr[j]) {
                int temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = pid[i]; pid[i] = pid[j]; pid[j] = temp;
            }
        }
    }

    int wt[n], tat[n];
    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = wt[i - 1] + bt[i - 1];
    for (int i = 0; i < n; i++)
        tat[i] = wt[i] + bt[i];

    printf("\n--- Priority Scheduling ---\n");
    printf("PID\tBT\tPR\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\n", pid[i], bt[i], pr[i], wt[i], tat[i]);
}

int main() {
    int choice;
    while (1) {
        printf("\nCustom Task Manager\n");
        printf("1. List Processes\n2. Memory Usage\n3. Scheduling Algorithms\n4. Exit\n");
        scanf("%d", &choice);

        if (choice == 1) listProcesses();
        else if (choice == 2) getMemoryUsage();
        else if (choice == 3) {
            int n;
            printf("Enter number of processes: ");
            scanf("%d", &n);

            int pid[n], bt[n], pr[n];
            for (int i = 0; i < n; i++) {
                printf("Enter PID and Burst Time for process %d: ", i + 1);
                scanf("%d%d", &pid[i], &bt[i]);
            }

            char again;
            do {
               
                int temp_pid[n], temp_bt[n], temp_pr[n];
                for (int i = 0; i < n; i++) {
                    temp_pid[i] = pid[i];
                    temp_bt[i] = bt[i];
                    temp_pr[i] = pr[i];  
                }

                printf("\nSelect Scheduling Algorithm:\n");
                printf("1. FCFS\n2. SJF\n3. Round Robin\n4. Priority Scheduling\n");
                int algo_choice;
                scanf("%d", &algo_choice);

                if (algo_choice == 1)
                    fcfs(temp_pid, temp_bt, n);
                else if (algo_choice == 2)
                    sjf(temp_pid, temp_bt, n);
                else if (algo_choice == 3) {
                    int tq;
                    printf("Enter time quantum: ");
                    scanf("%d", &tq);
                    roundRobin(temp_pid, temp_bt, n, tq);
                } else if (algo_choice == 4) {
                    for (int i = 0; i < n; i++) {
                        printf("Enter Priority for process %d: ", i + 1);
                        scanf("%d", &temp_pr[i]);
                    }
                    priorityScheduling(temp_pid, temp_bt, temp_pr, n);
                } else {
                    printf("Invalid choice!\n");
                }

                printf("\nDo you want to try another scheduling algorithm? (y/n): ");
                scanf(" %c", &again);

            } while (again == 'y' || again == 'Y');
        }
        else break;
    }

    printf("Exiting Custom Task Manager Scheduler.\n");
    return 0;
}

