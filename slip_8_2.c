#include <stdio.h>
#include <stdlib.h>


void sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (a[j] > a[j+1]) {
                int t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
}

void scan(int req[], int n, int head, int max) {
    int seq[50], k = 0, total = 0, i, prev = head;

    sort(req, n);

    // Find position of head
    for (i = 0; i < n && req[i] < head; i++);

    // Move right → to higher requests
    for (int j = i; j < n; j++) seq[k++] = req[j];

    // Go to end (max) and reverse direction
    seq[k++] = max;
    for (int j = i - 1; j >= 0; j--) seq[k++] = req[j];

    printf("\nSCAN order: ");
    for (int j = 0; j < k; j++) {
        total += abs(seq[j] - prev);
        prev = seq[j];
        printf("%d ", seq[j]);
    }

    printf("\nTotal head movement: %d", total);
    printf("\nAverage seek distance: %.2f\n", (float) total / n);
}

void look(int req[], int n, int head) {
    int seq[50], k = 0, total = 0, i, prev = head;

    sort(req, n);

    // Find position of head
    for (i = 0; i < n && req[i] < head; i++);

    // Move right then reverse
    for (int j = i; j < n; j++) seq[k++] = req[j];
    for (int j = i - 1; j >= 0; j--) seq[k++] = req[j];

    printf("\nLOOK order: ");
    for (int j = 0; j < k; j++) {
        total += abs(seq[j] - prev);
        prev = seq[j];
        printf("%d ", seq[j]);
    }

    printf("\nTotal head movement: %d", total);
    printf("\nAverage seek distance: %.2f\n", (float) total / n);
}

int main() {
    int req[] = {20, 229, 39, 450, 18, 145, 120, 380, 20, 250};
    int n = 10, head = 185, max = 499;

    scan(req, n, head, max);
    look(req, n, head);

    return 0;
}















// #include <stdio.h>
// #include <stdlib.h>

// #define MAX 50

// void sort(int a[], int n) {
//     for (int i = 0; i < n - 1; i++) {
//         for (int j = 0; j < n - i - 1; j++) {
//             if (a[j] > a[j + 1]) {
//                 int t = a[j];
//                 a[j] = a[j + 1];
//                 a[j + 1] = t;
//             }
//         }
//     }
// }

// void scan(int req[], int n, int head, int max) {
//     int total = 0, seq[MAX], k = 0, i;

//     sort(req, n);

//     for (i = 0; i < n && req[i] < head; i++);

//     for (int j = i; j < n; j++)
//         seq[k++] = req[j];

//     if (seq[k - 1] != max)
//         seq[k++] = max;

//     for (int j = i - 1; j >= 0; j--)
//         seq[k++] = req[j];

//     printf("SCAN sequence: ");
//     for (int j = 0, prev = head; j < k; j++) {
//         total += abs(seq[j] - prev);
//         prev = seq[j];
//         if (seq[j] != max)
//             printf("%d ", seq[j]);
//     }

//     printf("\nTotal head movement: %d", total);
//     printf("\nAverage seek distance: %.2f\n\n", (float) total / n);
// }

// void look(int req[], int n, int head) {
//     int total = 0, seq[MAX], k = 0, i;

//     sort(req, n);

//     for (i = 0; i < n && req[i] < head; i++);

//     for (int j = i; j < n; j++)
//         seq[k++] = req[j];

//     for (int j = i - 1; j >= 0; j--)
//         seq[k++] = req[j];

//     printf("LOOK sequence: ");
//     for (int j = 0, prev = head; j < k; j++) {
//         total += abs(seq[j] - prev);
//         prev = seq[j];
//         printf("%d ", seq[j]);
//     }

//     printf("\nTotal head movement: %d", total);
//     printf("\nAverage seek distance: %.2f\n", (float) total / n);
// }

// int main() {
//     int req[] = {20, 229, 39, 450, 18, 145, 120, 380, 20, 250};
//     int n = 10;
//     int head = 185;
//     int max = 499;

//     scan(req, n, head, max);
//     look(req, n, head);

//     return 0;
// }
