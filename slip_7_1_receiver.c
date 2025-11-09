#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

int main() {
    char text[100];
    
    while(1) {
        int fd = open("/tmp/myfifo", O_RDONLY);
        read(fd, text, 100);
        close(fd);
        for(int i = 0; text[i]; i++)
            text[i] = toupper(text[i]);
        printf("Message received: %s\n", text);
        if(strcmp(text, "EXIT") == 0) break;
    }
    
    unlink("/tmp/myfifo");
    return 0;
}


