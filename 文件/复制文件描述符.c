#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd, fd2;
    int error;
    const char *pathname = "temp.txt";
    const char *text = "ok\n";
    char buff[4096];

    fd = openat(AT_FDCWD, pathname, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        printf("打开文件失败\n"), exit(1);
    fd2 = dup(fd);
    if (fd2 == -1)
        printf("复制文件描述符失败\n"), exit(1);
    printf("%s", text);
    if (pwrite(fd, text, sizeof(text), 0) == -1)
        printf("写入文件失败\n"), exit(1);
    if (read(fd2, buff, sizeof(text)) == -1)
        printf("读取文件失败\n"), exit(1);
    printf("%s", buff);
    unlink(pathname);
    close(fd);
    close(fd2);
    exit(0);
}