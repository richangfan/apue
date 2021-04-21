#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("进程ID：%d\n", getpid());
    printf("上级进程ID：%d\n", getppid());
    printf("实际用户ID：%d\n", getuid());
    printf("实际组ID：%d\n", getgid());
    printf("有效用户ID：%d\n", geteuid());
    printf("有效组ID：%d\n", getegid());
    exit(0);
}