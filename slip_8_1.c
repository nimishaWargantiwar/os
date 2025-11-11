#include <stdio.h>
#include <stdlib.h>

void sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (a[j] > a[j+1]) {
                int t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
        }
    }
}

void cscan(int head, int req[], int n, int max) {
    int total = 0, seq[20], k = 0, prev = head;
    sort(req, n);

    // Step 1: Move right (towards higher requests)
    for (int i = 0; i < n; i++) {
        if (req[i] >= head) {
            seq[k++] = req[i];
        }
    }

    // Step 2: Move to the maximum cylinder if not already included
    if (seq[k-1] != max) {
        seq[k++] = max;
    }

     seq[k++] = 0;

    // Step 3: Wrap around to smaller requests
    for (int i = 0; i < n; i++) {
        if (req[i] < head) {
            seq[k++] = req[i];
        }
    }

    // Step 4: Calculate total head movement
   
    for (int i = 0; i < k; i++) {
        total += abs(seq[i] - prev);
        prev = seq[i];
    }

    // Step 5: Print sequence and stats
    printf("\nC-SCAN sequence: ");
    for (int i = 0; i < k; i++) {
        printf("%d ", seq[i]);
    }

    printf("\nTotal head movement: %d", total);
    printf("\nAverage seek distance: %.2f\n", (float) total / n);
}

void clook(int head, int req[], int n) {
    int total = 0, seq[20], k = 0, prev = head;
    sort(req, n);

    // Move right (towards higher requests)
    for (int i = 0; i < n; i++) {
        if (req[i] >= head) {
            seq[k++] = req[i];
        }
    }

    // Then jump to the smallest request
    for (int i = 0; i < n; i++) {
        if (req[i] < head) {
            seq[k++] = req[i];
        }
    }

    // Calculate total movement
    for (int i = 0; i < k; i++) {
        total += abs(seq[i] - prev);
        prev = seq[i];
    }

    printf("\nC-LOOK sequence: ");
    for (int i = 0; i < k; i++) {
        printf("%d ", seq[i]);
    }

    printf("\nTotal head movement: %d", total);
    printf("\nAverage seek distance: %.2f\n", (float) total / n);
}

int main() {
    int req[] = {10, 229, 39, 400, 18, 145, 120, 480, 20, 250};
    int n = 10;
    int head = 85, max = 499;

    printf("Current head: %d\nRequests: ", head);
    for (int i = 0; i < n; i++) {
        printf("%d ", req[i]);
    }

    cscan(head, req, n, max);
    clook(head, req, n);

    return 0;
}
