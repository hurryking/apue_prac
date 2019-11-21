#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
 
int main(int argc, char *argv[])
{
    int fd, copyfd;
 
    fd = open("./log.txt", O_RDWR|O_CREAT);

    copyfd = dup(fd);
 
    char buf1[] = "hello ";
    char buf2[] = "world!";
 

    if (write(fd, buf1, 6) != 6) {
        printf("write error!");
    }
 
    printf("%d\n", (int)lseek(fd, 0, SEEK_CUR));
    printf("%d\n", (int)lseek(copyfd, 0, SEEK_CUR));
 
    if (write(copyfd, buf2, 6) != 6) {
        printf("write error!");
    }
 
    return 0;
}