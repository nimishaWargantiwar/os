#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ---------------- FIFO ----------------
int fifo(int p[], int n, int f) 
{
    int fr[f];
    int i, j;
    int pos = 0;
    int faults = 0;

    for (i = 0; i < f; i++) 
    {
        fr[i] = -1;
    }

    for (i = 0; i < n; i++) 
    {
        int hit = 0;
        for (j = 0; j < f; j++) 
        {
            if (fr[j] == p[i]) 
            {
                hit = 1;
            }
        }
        if (hit == 0) 
        {
            fr[pos] = p[i];
            pos = (pos + 1) % f;
            faults++;
        }
        printf("%d\t", p[i]);
        for (j = 0; j < f; j++) 
            if (fr[j] != -1) printf("%d ", fr[j]); 
            else printf("- ");
        printf("\t%s\n", hit ? "Hit" : "Miss");
    }

    return faults;
}

// ---------------- LRU ----------------
int lru(int p[], int n, int f) 
{
    int fr[f];
    int last[f];
    int i, j;
    int faults = 0;

    for (i = 0; i < f; i++) 
    {
        fr[i] = -1;
        last[i] = -1;
    }

    for (i = 0; i < n; i++) 
    {
        int hit = 0;
        for (j = 0; j < f; j++) 
        {
            if (fr[j] == p[i]) 
            {
                hit = 1;
                last[j] = i;
                break;
            }
        }

        if (hit == 0) 
        {
            int l = 0;
            for (j = 1; j < f; j++) 
            {
                if (last[j] < last[l]) 
                {
                    l = j;
                }
            }
            fr[l] = p[i];
            last[l] = i;
            faults++;
        }
    }

    return faults;
}

// ---------------- Optimal ----------------
int optimal(int p[], int n, int f) 
{
    int fr[f];
    int i, j;
    int faults = 0;

    for (i = 0; i < f; i++) 
    {
        fr[i] = -1;
    }

    for (i = 0; i < n; i++) 
    {
        int hit = 0;
        int idx = 0;
        int far = -1;

        
        for (j = 0; j < f; j++) 
        {
            if (fr[j] == p[i]) 
            {
                hit = 1;
                break;
            }
        }

        if (hit == 0) 
        {
            for (j = 0; j < f; j++) 
            {
                if (fr[j] == -1) 
                {
                    idx = j;
                    break;
                }

                int k;
                for (k = i + 1; k < n; k++) 
                {
                    if (fr[j] == p[k]) 
                    {
                        break;
                    }
                }

                if (k > far) 
                {
                    far = k;
                    idx = j;
                }
            }

            fr[idx] = p[i];
            faults++;
        }
    }

    return faults;
}

// ---------------- Main ----------------
int main() 
{
    // int pages[50]={1,2,3,4,2,1,5,6,2,1,2,3,7,6,3,2,1,2,3,6};
    int pages[50];
    int n = 20;
    int f, choice;

    srand(time(NULL));

    printf("Random page reference string of size %d:\n", n);
    for (int i = 0; i < n; i++) 
    {
        pages[i] = rand() % 10;
        printf("%d,", pages[i]);
    }
    printf("\n\n");

    printf("Menu:\n");
    printf("1. FIFO\n");
    printf("2. LRU\n");
    printf("3. Optimal\n");
    printf("4. Compare FIFO, LRU, Optimal for 3 & 4 frames\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= 3) 
    {
        printf("Enter number of frames: ");
        scanf("%d", &f);

        if (choice == 1) 
        {
            printf("FIFO page faults = %d\n", fifo(pages, n, f));
        }
        else if (choice == 2) 
        {
            printf("LRU page faults = %d\n", lru(pages, n, f));
        }
        else if (choice == 3) 
        {
            printf("Optimal page faults = %d\n", optimal(pages, n, f));
        }
    } 
    else if (choice == 4) 
    {
        for (f = 3; f <= 4; f++) 
        {
            printf("Frames = %d: FIFO = %d, LRU = %d, Optimal = %d\n", 
                    f, fifo(pages, n, f), lru(pages, n, f), optimal(pages, n, f));
        }
    } 
    else 
    {
        printf("Invalid choice!\n");
    }

    return 0;
}
