#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    mkfifo("/tmp/myfifo", 0666);
    char text[100];
    
    while(1) {
        printf("Message: ");
        fgets(text, 100, stdin);
        text[strcspn(text, "\n")] = 0;
        int fd = open("/tmp/myfifo", O_WRONLY);
        write(fd, text, sizeof(text));
        close(fd);
        if(strcmp(text, "exit") == 0) break;
    }
    return 0;
}





