#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int err;
FILE *fp;

void error_exit(char *msg)
{
    printf("%s\n", msg);
    exit(1);
}

void test_putc(const char *pathname, const char *s)
{
    int len;
    fp = fopen(pathname, "w+");
    if (fp == NULL)
        error_exit("打开出错");
    len = strlen(s);
    for (int i = 0; i < len; i++)
    {
        if (fputc((unsigned int)s[i], fp) == EOF)
        {
            if (feof(fp) != 0)
                printf("文件结束\n");
            if ((err = ferror(fp)) != 0)
                printf("输入出错：%d\n", err);
            exit(1);
        }
    }
    if (fclose(fp) != 0)
        error_exit("关闭出错");
}

void test_getc(const char *pathname)
{
    int c;
    fp = fopen(pathname, "r");
    if (fp == NULL)
        error_exit("打开出错");
    while ((c = fgetc(fp)) != EOF)
    {
        printf("%c", (unsigned char)c);
    }
    printf("\n");
    if ((err = ferror(fp)) != 0)
    {
        printf("输出出错：%d\n", err);
        exit(1);
    }
    if (fclose(fp) != 0)
        error_exit("关闭出错");
}

int main(int argc, char *argv[])
{
    const char *pathname = "temp";
    test_putc(pathname, "hello, world!");
    test_getc(pathname);
    if (unlink(pathname) != 0)
        error_exit("删除出错");
    exit(0);
}