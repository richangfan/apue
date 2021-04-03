#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *thread1(void *p)
{
    p = (void *)1;
    printf("线程1主动退出\n");
    return p;
}

void *thread2(void *p)
{
    p = (void *)2;
    printf("线程2主动退出\n");
    pthread_exit(p);
}

void *thread3(void *p)
{
    p = (void *)3;
    sleep(3);
    printf("线程3主动退出\n");
}

int main(int argc, char *argv[])
{
    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_create(&tid2, NULL, thread2, NULL);
    pthread_create(&tid3, NULL, thread3, NULL);
    pthread_cancel(tid3);
    void *p;
    pthread_join(tid1, &p);
    printf("线程1返回%p\n", p);
    pthread_join(tid2, &p);
    printf("线程2返回%p\n", p);
    pthread_join(tid3, &p);
    printf("线程3返回%p\n", p);
    if (p == PTHREAD_CANCELED)
    {
        printf("线程3被取消\n");
    }
    return 0;
}