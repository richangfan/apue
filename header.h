#include <stdio.h>
#include <stdlib.h>

void error_exit(const char *message)
{
    printf("%s\n", message);
    exit(1);
}