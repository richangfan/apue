#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void error_exit(char *msg)
{
    printf("%s\n", msg);
    exit(1);
}

void test_puts(const char *pathname, char *s)
{
    FILE *fp = fopen(pathname, "a+");
    if (fputs(s, fp) == EOF)
        error_exit("写入出错");
    if (fclose(fp) != 0)
        error_exit("关闭出错");
}

void test_gets(const char *pathname)
{
    char buf[1024];
    FILE *fp = fopen(pathname, "r");
    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        printf("%s", buf);
    }
    printf("\n");
    if (fclose(fp) != 0)
        error_exit("关闭出错");
}

int main(int argc, char *argv[])
{
    const char *pathname = "tmp";
    test_puts(pathname, "one\n");
    test_puts(pathname, "two\nthree");
    test_gets(pathname);
    if (unlink(pathname) != 0)
        error_exit("删除出错");
    exit(0);
}