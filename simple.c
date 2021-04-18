#include <stdio.h>
#include <stdlib.h>

void error_exit(char *msg)
{
    printf("%s\n", msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    exit(0);
}