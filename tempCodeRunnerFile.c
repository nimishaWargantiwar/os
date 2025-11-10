
int main() {
    int head = 185, n = 10, max = 499;
    int req[] = {20, 229, 39, 450, 18, 145, 120, 380, 20, 250};

    printf("Current Head: %d\nRequests: ", head);
    for (int i = 0; i < n; i++) printf("%d ", req[i]);

    scan(req, n, head, max);
    look(req, n, head);

    return 0;
}
