#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int error;
    int fd;
    int offset;
    const char *pathname = "temp.txt";
    const char *text = "ok\n";
    char buff[4096];

    fd = openat(AT_FDCWD, pathname, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        printf("打开文件失败\n"), exit(1);
    error = write(fd, text, sizeof(text));
    if (error == -1)
        printf("写入文件失败\n"), exit(1);
    printf("写入%d字节\n", error);
    if (lseek(fd, 0, SEEK_SET) == -1)
        printf("设置文件偏移量失败\n"), exit(1);
    error = read(fd, buff, sizeof(text));
    if (error == -1)
        printf("读取文件失败\n"), exit(1);
    printf("读取%d字节\n", error);
    if (write(STDOUT_FILENO, buff, sizeof(text)) == -1)
        printf("写入标准输出文件失败\n"), exit(1);
    if (close(fd) == -1)
        printf("关闭文件失败\n"), exit(1);
    unlink(pathname);
    exit(0);
}