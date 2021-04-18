#include "../common.h"
#include <fcntl.h>
#include <sys/stat.h>

void print_file_type(int mode);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("未输入文件路径\n");
        error_exit();
    }
    int fd = open(argv[1], O_EXCL);
    if (fd < 0)
        printf("打开文件失败\n"), error_exit();
    struct stat buf;
    if (fstat(fd, &buf) != 0)
        printf("fstat\n"), error_exit();
    printf("所属用户是%d\n", buf.st_uid);
    printf("所属用户组是%d\n", buf.st_gid);
    printf("文件体积是%ld字节\n", buf.st_size);
    printf("访问时间是%ld\n", buf.st_atim.tv_sec);
    printf("修改时间是%ld\n", buf.st_mtim.tv_sec);
    printf("状态更改时间是%ld\n", buf.st_ctim.tv_sec);
    printf("硬链接数是%ld\n", buf.st_nlink);
    printf("八进制文件权限是%o\n", buf.st_mode);
    print_file_type(buf.st_mode);
    printf("%ld\n", buf.st_blksize);
    printf("%ld\n", buf.st_dev);
    printf("%ld\n", buf.st_rdev);
    printf("%ld\n", buf.st_ino);
    printf("%ld\n", buf.st_mtim.tv_nsec);
    printf("%ld\n", buf.st_ctim.tv_nsec);
    printf("%ld\n", buf.st_atim.tv_nsec);
    exit(0);
}

void error_exit()
{
    switch (errno)
    {
    case EACCES:
        printf("Search permission is denied for one of the directories in the path prefix of pathname.\n");
        break;

    case EBADF:
        printf("fd is not a valid open file descriptor.\n");
        printf("dirfd is not a valid file descriptor.\n");
        break;

    case EFAULT:
        printf("Bad address.\n");
        break;

    case ELOOP:
        printf("Too many symbolic links encountered while traversing the path.\n");
        break;

    case ENAMETOOLONG:
        printf("pathname is too long.\n");
        break;

    case ENOENT:
        printf("A component of pathname does not exist or is a dangling symbolic link.\n");
        printf("fstatat error: pathname is an empty string and AT_EMPTY_PATH was not specified in flags.\n");
        break;

    case ENOMEM:
        printf("Out of memory (i.e., kernel memory).\n");
        break;

    case ENOTDIR:
        printf("A component of the path prefix of pathname is not a directory.\n");
        printf("fstatat error: pathname is relative and dirfd is a file descriptor referring to a file other than a directory.\n");
        break;

    case EOVERFLOW:
        printf("pathname or fd refers to a file whose size, inode number, or number of blocks cannot be represented in, respectively, the types off_t, ino_t, or blkcnt_t.  This error can occur when, for example, an application compiled on a 32-bit platform without -D_FILE_OFFSET_BITS=64 calls stat() on a file whose size exceeds (1<<31)-1 bytes.\n");
        break;

    case EINVAL:
        printf("Invalid flag specified in flags.\n");
        break;

    default:
        break;
    }
    exit(1);
}

void print_file_type(int mode)
{
    char *ft;
    if (S_ISREG(mode))
    {
        ft = "regular";
    }
    else if (S_ISDIR(mode))
    {
        ft = "directory";
    }
    else if (S_ISBLK(mode))
    {
        ft = "block";
    }
    else if (S_ISCHR(mode))
    {
        ft = "character";
    }
    else if (S_ISFIFO(mode))
    {
        ft = "FIFO";
    }
    else if (S_ISSOCK(mode))
    {
        ft = "socket";
    }
    else if (S_ISLNK(mode))
    {
        ft = "link";
    }
    else
    {
        ft = "未知类型";
    }
    printf("文件类型是%s\n", ft);
    if (S_ISUID & mode)
        printf("保存设置用户ID\n");
    else
        printf("不保存设置用户ID\n");
    if (S_ISGID & mode)
        printf("保存设置组ID\n");
    else
        printf("不保存设置组ID\n");
    return;
}