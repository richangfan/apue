#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void error_exit(char *msg)
{
    printf("%s\n", msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int fd[2];
    const char *s = "hello";
    char buf[1024];

    if (pipe(fd) != 0)
        error_exit("创建pipe出错");
    write(fd[1], s, sizeof(s));
    read(fd[0], &buf, sizeof(s));
    printf("%s\n", buf);
    exit(0);
}