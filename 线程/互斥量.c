#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *thread_start(void *p, int id)
{
    for (int i = 0; i < id; i++)
    {
        int j = 0;
    }
    pthread_mutex_lock(p);
    printf("%d\n", id);
    pthread_mutex_unlock(p);
}

int main(int argc, char *argv[])
{
    pthread_t tid1;
    pthread_t tid2;
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t *p = &lock;
    pthread_create(&tid1, NULL, thread_start(p, 20000), NULL);
    pthread_create(&tid2, NULL, thread_start(p, 1), NULL);
    sleep(1);
    return 0;
}