#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_t tid;
int share_number = 0;

void *thread_start(void *p)
{
    share_number++;
    printf("%d\n", share_number); //打印数大于1表示出现了一致性问题
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&tid, NULL, thread_start, NULL);
    }
    sleep(1);
    return 0;
}