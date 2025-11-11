#include <stdio.h>

int n;
int pid[10], arrival[10], burst[10], waiting[10], turnaround[10];

void printTable() {
    printf("\nPID\tAT\tBT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               pid[i], arrival[i], burst[i], turnaround[i], waiting[i]);
    }
}


// ---------- FCFS (with sorting) ----------
void FCFS() {
    // Sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arrival[j] > arrival[j + 1]) {
                int t = arrival[j];
                arrival[j] = arrival[j + 1];
                arrival[j + 1] = t;

                t = burst[j];
                burst[j] = burst[j + 1];
                burst[j + 1] = t;

                t = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = t;
            }
        }
    }

    int time = 0;
    double tw = 0, tt = 0;

    printf("\nGantt chart: ");

    for (int i = 0; i < n; i++) {
        if (time < arrival[i]) {
            time = arrival[i];
        }

        printf("%d | P%d | ", time, pid[i]);
        waiting[i] = time - arrival[i];
        time += burst[i];
        turnaround[i] = waiting[i] + burst[i];
       // printf(" P%d ", pid[i]);
        tw += waiting[i];
        tt += turnaround[i];
    }
    printf("%d\n", time);
    printTable();
    printf("\nAverage WT=%.2f  Average TAT=%.2f\n", tw / n, tt / n);
}

// ---------- SJF Non-Preemptive ----------
void SJF_NP() {
    int done[10] = {0};
    int completed = 0;
    int time = 0;
    double tw = 0, tt = 0;

    printf("\nGantt chart: ");

    while (completed < n) {
        int idx = -1;
        int min = 9999;

        for (int i = 0; i < n; i++) {
            if (!done[i] && arrival[i] <= time && burst[i] < min) {
                min = burst[i];
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }



        printf("%d | P%d | ", time,pid[idx]);
        waiting[idx] = time - arrival[idx];
        time += burst[idx];
        turnaround[idx] = waiting[idx] + burst[idx];
        done[idx] = 1;
        completed++;
        tw += waiting[idx];
        tt += turnaround[idx];
    }

    printf("%d |",time);
    printTable();
    printf("\nAverage WT=%.2f  Average TAT=%.2f\n", tw / n, tt / n);
}
 //////////////
void SJF_P() {
    int rem[10];
    int completed = 0;
    int time = 0;
    int last = -1;

    for (int i = 0; i < n; i++) {
        rem[i] = burst[i];
    }

    double tw = 0, tt = 0;

    printf("\nGantt Chart: ");
    printf("%d", time);

    while (completed < n) {
        int idx = -1;
        int min = 9999;

        // Find process with shortest remaining time among arrived processes
        for (int i = 0; i < n; i++) {
            if (arrival[i] <= time && rem[i] > 0) {
                if (rem[i] < min || (rem[i] == min && arrival[i] < arrival[idx])) {
                    min = rem[i];
                    idx = i;
                }
            }
        }

        // If no process is ready, CPU is idle
        if (idx == -1) {
            time++;
            continue;
        }

        // Print process switch in Gantt chart
        if (last != idx) {
        if (last != -1) {
            printf(" | %d", time);  // Print end time of previous process
        }
        printf(" | P%d", pid[idx]);  // New process starts at current time
        last = idx;
    }

        rem[idx]--;
        time++;

        // If process finishes
        if (rem[idx] == 0) {
            turnaround[idx] = time - arrival[idx];
            waiting[idx] = turnaround[idx] - burst[idx];
            tt += turnaround[idx];
            tw += waiting[idx];
            completed++;
        }
    }
    printf(" | %d |\n", time);
    printTable();

    printf("\nAverage Waiting Time = %.2f", tw / n);
    printf("\nAverage Turnaround Time = %.2f\n", tt / n);
}

void RR() {
    int rem[10], completed = 0, time = 0, quantum = 2;
    double tw = 0, tt = 0;
    int queue[10], front = 0, rear = 0;
    int visited[10] = {0};

    for (int i = 0; i < n; i++)
        rem[i] = burst[i];

    printf("\nGantt Chart:\n%d", time);

    queue[rear++] = 0; // first process arrives at time 0
    visited[0] = 1;

    while (completed < n) {
        if (front == rear) { // no process in queue
            time++;
            for (int i = 0; i < n; i++) {
                if (arrival[i] <= time && rem[i] > 0 && !visited[i]) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        if (rem[idx] > quantum) {
            rem[idx] -= quantum;
            time += quantum;
            printf(" | P%d | %d", pid[idx], time);
        } else {
            time += rem[idx];
            rem[idx] = 0;
            printf(" | P%d | %d", pid[idx], time);
            completed++;
            turnaround[idx] = time - arrival[idx];
            waiting[idx] = turnaround[idx] - burst[idx];
            tw += waiting[idx];
            tt += turnaround[idx];
        }

        // enqueue newly arrived processes
        for (int i = 0; i < n; i++) {
            if (arrival[i] <= time && rem[i] > 0 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // if the current process still has time left, requeue it
        if (rem[idx] > 0)
            queue[rear++] = idx;
    }
    printTable();

    printf("\nAverage Waiting Time = %.2f", tw / n);
    printf("\nAverage Turnaround Time = %.2f\n", tt / n);
}
// ---------- Main ----------
int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Arrival & Burst for P%d: ", pid[i]);
        scanf("%d %d", &arrival[i], &burst[i]);
    }

    int ch;

    while (1) {
        printf("\n1.FCFS  2.SJF NP  3.SJF P  4.RR  5.Exit\nChoice: ");
        scanf("%d", &ch);

        if (ch == 1) {
            FCFS();
        } else if (ch == 2) {
            SJF_NP();
        } else if (ch == 3) {
            SJF_P();
        } else if (ch == 4) {
            RR();
        } else if (ch == 5) {
            break;
        } else {
            printf("Invalid choice\n");
        }
    }

    return 0;
}
