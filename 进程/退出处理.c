#include <stdio.h>
#include <stdlib.h>

void error_exit(char *msg)
{
    printf("%s\n", msg);
    exit(1);
}

void handle(void)
{
    printf("OK\n");
}

int main(int argc, char *argv[])
{
    if (atexit(handle) != 0)
        error_exit("注册退出处理函数出错");
    exit(0);
}