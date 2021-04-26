#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void error_exit(char *msg)
{
    printf("%s\n", msg);
    exit(1);
}

void handle(int sig)
{
    if (sig == SIGINT)
        printf("捕捉到了INT信号\n");
    else
        printf("捕捉到了未知信号%d\n", sig);
    exit(0);
}

int main(int argc, char *argv[])
{
    if (signal(SIGINT, handle) == SIG_ERR)
        error_exit("设置INT信号处理程序出错\n");
    while (1)
    {
        printf("\n");
    }
    exit(0);
}