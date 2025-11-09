#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int n, i, j, temp;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n];
    printf("Enter %d elements: ", n);
    for(i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // Bubble Sort
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    printf("Sorted array: ");
    for(i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    fflush(stdout);  // ensure print before fork()

    int pid = fork();

    if(pid == 0) {  // Child process
        char *args[20];
        static char nums[20][10];  // storage for converted numbers

        args[0] = "./child";  // child program name

        for(i = 0; i < n; i++) {
            sprintf(nums[i], "%d", a[i]);  // convert int -> string
            args[i + 1] = nums[i];
        }

        args[n + 1] = NULL;

       // printf("\nChild: Executing './child' with sorted array as arguments...\n");
        //fflush(stdout);

        execve("./child", args, NULL);

        perror("execve failed");
       // exit(1);
    } 
    else {  // Parent process
        wait(NULL);
        printf("\nParent: Child finished execution.\n");
    }

    return 0;
}
