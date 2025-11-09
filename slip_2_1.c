#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void bubble(int a[], int n) {
    for(int i=0;i<n-1;i++) {
        for(int j=0;j<n-i-1;j++) {
            if(a[j] > a[j+1]) {
                int t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
        }
    }
}

void insertion(int a[], int n) {
    for(int i=1;i<n;i++) {
        int key = a[i], j = i - 1;
        while(j >= 0 && a[j] > key) {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = key;
    }
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    int a[n];
    printf("Enter %d elements:\n", n);
    for(int i=0;i<n;i++) scanf("%d", &a[i]);

    int pid = fork();

    if(pid == 0) {  // Child
        printf("\n--- CHILD PROCESS ---\nChild PID: %d | Parent PID: %d\n", getpid(), getppid());
        insertion(a, n);
        printf("Child (Insertion Sorted Array): ");
        for(int i=0;i<n;i++) printf("%d ", a[i]);
        printf("\n\n[Orphan Demo] Child sleeping 5 sec...\n");
        fflush(stdout);
        sleep(5);
        printf("After 5 sec, new Parent PID: %d (Orphan if PID=1)\n", getppid());
    } 
    else {  // Parent
        printf("\n--- PARENT PROCESS ---\nParent PID: %d | Child PID: %d\n", getpid(), pid);
        bubble(a, n);
        printf("Parent (Bubble Sorted Array): ");
        for(int i=0;i<n;i++) printf("%d ", a[i]);
        printf("\n\n[Zombie Demo] Parent sleeping 2 sec (child may finish first)...\n");
        fflush(stdout);
        sleep(2);

        // wait(NULL);  // Uncomment for NO zombie
        printf("\nParent: Child finished. (No zombie now)\nParent exiting...\n\n");
    }

    return 0;
}
