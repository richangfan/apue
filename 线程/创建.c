#include <pthread.h>
#include <unistd.h>

void *start_thread(void *p)
{
    printf("子线程ID：%lu\n", (unsigned long)pthread_self());
    return p;
}

int main(int argc, char *argv[])
{
    pthread_t tid;
    int error;
    error = pthread_create(&tid, NULL, start_thread, NULL);
    if (error != 0)
        printf("创建线程出错"), exit(1);
    sleep(1);
    return 0;
}