#include <stdio.h>

int main() 
{
    int n, m;
    FILE *fp = fopen("state.txt", "r");
    if (!fp) 
    {
        printf("Error opening file!\n");
        return 1;
    }

    fscanf(fp, "%d %d", &n, &m);
    int alloc[10][10], max[10][10], need[10][10], avail[10];

    // --- Read Allocation matrix ---
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            fscanf(fp, "%d", &alloc[i][j]);
        }
    }

    // --- Read Max matrix ---
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            fscanf(fp, "%d", &max[i][j]);
        }
    }

    // --- Read Available vector ---
    for (int j = 0; j < m; j++) 
    {
        fscanf(fp, "%d", &avail[j]);
    }
    fclose(fp);

    // --- Calculate Need matrix ---
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            need[i][j] = max[i][j] - alloc[i][j];
            if (need[i][j] < 0) 
            {
                printf("Error: Invalid input! P%d has allocation > max for resource %d.\n", i, j);
                return 0;
            }
        }
    }

    // --- SAFETY CHECK ---
    int work[10], finish[10] = {0}, safe[10], count = 0;  //safe=answer

    for (int j = 0; j < m; j++) 
    {
        work[j] = avail[j];
    }

    while (count < n) 
    {
        int found = 0;

        for (int i = 0; i < n; i++) 
        {
            if (!finish[i]) 
            {
                int j;
                for (j = 0; j < m; j++) 
                {
                    if (need[i][j] > work[j]) 
                    {
                        break;
                    }
                }

                if (j == m) 
                {
                    for (int k = 0; k < m; k++) 
                    {
                        work[k] = work[k] + alloc[i][k];
                    }

                    safe[count] = i;
                    count++;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) 
        {
            break;
        }
    }

    if (count == n) 
    {
        printf("\nSystem is SAFE.\nSafe sequence: ");
        for (int i = 0; i < n; i++) 
        {
            printf("P%d ", safe[i]);
        }
        printf("\n");
    } 
    else 
    {
        printf("\nSystem is UNSAFE.\n");
    }


    // --- REQUEST PART (Only for 5.2) ---
    int p, req[10];
    printf("\nEnter process number & request vector:\nP = ");
    scanf("%d", &p);

    for (int j = 0; j < m; j++) 
    {
        scanf("%d", &req[j]);
    }

    int ok = 1;

    for (int j = 0; j < m; j++) 
    {
        if (req[j] > need[p][j] || req[j] > avail[j]) 
        {
            ok = 0;
        }
    }

    if (ok==0) 
    {
        printf("Request cannot be granted.\n");
        //return 0;
    }

    // --- Pretend allocation ---
    for (int j = 0; j < m; j++) 
    {
        avail[j] = avail[j] - req[j];
        alloc[p][j] = alloc[p][j] + req[j];
        need[p][j] = need[p][j] - req[j];
    }

    // --- Recheck safety after request ---
    for (int j = 0; j < m; j++) 
    {
        work[j] = avail[j];
    }

    for (int i = 0; i < n; i++) 
    {
        finish[i] = 0;
    }
    count = 0;

    while (count < n) 
    {
        int found = 0;

        for (int i = 0; i < n; i++) 
        {
            if (!finish[i]) 
            {
                int j;
                for (j = 0; j < m; j++) 
                {
                    if (need[i][j] > work[j]) 
                    {
                        break;
                    }
                }

                if (j == m) 
                {
                    for (int k = 0; k < m; k++) 
                    {
                        work[k] = work[k] + alloc[i][k];
                    }

                    safe[count] = i;
                    count++;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) 
        {
            break;
        }
    }

    if (count == n) 
    {
        printf("After request: SAFE state.\n");
    } 
    else 
    {
        printf("After request: UNSAFE state.\n");
    }

    return 0;
}
