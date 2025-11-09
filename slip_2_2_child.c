#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n = argc - 1;
    int a[n];

    for(int i = 0; i < n; i++)
        a[i] = atoi(argv[i + 1]);

    int key, low = 0, high = n - 1, mid, found = 0;
    printf("Enter element to search: ");
    scanf("%d", &key);

    while(low <= high) {
        mid = (low + high) / 2;
        if(a[mid] == key) {
            found = 1;
            break;
        } else if(a[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    if(found)
        printf("Element %d found at position %d\n", key, mid + 1);
    else
        printf("Element not found\n");

    return 0;
}
