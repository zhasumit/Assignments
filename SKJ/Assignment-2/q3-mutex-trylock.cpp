#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


pthread_mutex_t resourceA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t resourceB = PTHREAD_MUTEX_INITIALIZER;


void *thread1(void *arg)
{
    while (1)
    {
        if (pthread_mutex_trylock(&resourceA) == 0)
        {
            printf("Thread 1: Acquired resource A\n");
            sleep(1);
            if (pthread_mutex_trylock(&resourceB) == 0)
            {
                printf("Thread 1: Acquired resource B\n");
                pthread_mutex_unlock(&resourceB);
                printf("Thread 1: Released resource B\n");
            }
            else
            {
                pthread_mutex_unlock(&resourceA);
                continue;
            }
            pthread_mutex_unlock(&resourceB);
            pthread_mutex_unlock(&resourceA);
        }
    }
    return NULL;
}


void *thread2(void *arg)
{
    while (1)
    {
        if (pthread_mutex_trylock(&resourceB) == 0)
        {
            printf("Thread 2: Acquired resource B\n");
            sleep(1);
            if (pthread_mutex_trylock(&resourceA) == 0)
            {
                printf("Thread 2: Acquired resource A\n");
                pthread_mutex_unlock(&resourceA);
                printf("Thread 2: Released resource A\n");
            }
            else
            {
                pthread_mutex_unlock(&resourceB);
                continue;
            }
            pthread_mutex_unlock(&resourceA);
            pthread_mutex_unlock(&resourceB);
        }
    }
    return NULL;
}


int main()
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
