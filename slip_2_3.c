#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int prime(int n) {
    if (n < 2) {
        return 0;
    }

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }

    return 1;
}

int main(int c, char *v[]) {
    if (c != 2 || atoi(v[1]) <= 0) {
        printf("Enter positive number!\n");
        return 1;
    }

    if (fork() == 0) {
        int n = atoi(v[1]);
        int count = 0;
        int i = 2;

        printf("Child: First %d primes:\n", n);

        while (count < n) {
            if (prime(i)) {
                printf("%d ", i);
                count++;
            }
            i++;
        }

        printf("\n");
    } 
    else {
        wait(NULL);
        printf("Parent: Child done.\n");
    }

    return 0;
}
