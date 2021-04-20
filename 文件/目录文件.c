#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>

void error_exit(char *msg)
{
    printf("%s\n", msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    const char *pathname = "tempdir";
    struct stat buf;
    int fd;
    DIR *dirp;
    struct dirent *dp;

    umask(0);
    fd = mkdir(pathname, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);
    if (fd < 0)
        error_exit("创建目录失败");
    if (close(fd) != 0)
        error_exit("关闭文件失败");
    dirp = opendir(pathname);
    if (dirp == NULL)
        error_exit("打开目录失败");
    while ((dp = readdir(dirp)) != NULL)
    {
        printf("————目录项开始————\n");
        printf("名称：%s\n", dp->d_name);
        printf("i节点：%ld\n", dp->d_ino);
        printf("长度：%d\n", dp->d_reclen);
        printf("类型：%d\n", dp->d_type);
        printf("————目录项结束————\n");
    }
    if (closedir(dirp) != 0)
        error_exit("关闭目录失败");
    fd = open(pathname, O_EXCL);
    if (fd < 0)
        error_exit("打开文件失败");
    if (fstat(fd, &buf) != 0)
        error_exit("fstat出错");
    printf("八进制文件权限是%o\n", buf.st_mode);
    printf("文件体积是%ld字节\n", buf.st_size);
    if (close(fd) != 0)
        error_exit("关闭文件失败");
    if (rmdir(pathname) != 0)
        error_exit("删除空目录失败");
    exit(0);
}