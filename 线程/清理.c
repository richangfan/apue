#include "../header.h"
#include <pthread.h>
#include <unistd.h>

void cleanup(void *msg)
{
    printf("%s\n", (char *)msg);
}

void *start_thread(void *p)
{
    if (*(int *)p != 1)
    {
        pthread_cleanup_push(cleanup, "调用pthread_cancel执行清理程序");
        sleep(1);
        pthread_cleanup_pop(0);
    }
    pthread_cleanup_push(cleanup, "调用pthread_cleanup_pop执行清理程序");
    pthread_cleanup_pop(1);
    pthread_cleanup_push(cleanup, "调用pthread_exit执行清理程序");
    pthread_exit(NULL);
    pthread_cleanup_pop(0);
    printf("线程return\n");
}

/**
 * argc不等于1时调用pthread_cancel执行清理程序
 */
int main(int argc, char *argv[])
{
    pthread_t tid;
    int error;
    error = pthread_create(&tid, NULL, start_thread, (void *)&argc);
    if (error != 0)
        error_exit("创建线程出错");
    if (argc != 1)
    {
        error = pthread_cancel(tid);
        if (error != 0)
            error_exit("cancel出错");
    }
    error = pthread_join(tid, NULL);
    if (error != 0)
        error_exit("join出错");
    return 0;
}