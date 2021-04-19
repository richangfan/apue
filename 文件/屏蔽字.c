#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

void error_exit(char *msg)
{
    printf("%s\n", msg);
    exit(1);
}

void create_and_print(const char *pathname, const int mode)
{

    int fd = creat(pathname, mode);
    if (fd < 0)
        error_exit("创建文件失败");
    struct stat buf;
    if (fstat(fd, &buf) != 0)
        error_exit("fstat出错");
    printf("八进制文件权限是%o\n", buf.st_mode);
    if (unlink(pathname) != 0)
        error_exit("删除文件失败");
    close(fd);
}

int main(int argc, char *argv[])
{
    const char *pathname = "tmp";
    const int mode = S_IRUSR | S_IWGRP | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    create_and_print(pathname, mode);
    umask(0);
    create_and_print(pathname, mode);
    exit(0);
}