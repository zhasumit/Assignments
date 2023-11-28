#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t resourceA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t resourceB = PTHREAD_MUTEX_INITIALIZER;
void *thread1(void *arg)
{
    pthread_mutex_lock(&resourceA);
    printf("Thread 1: Acquired resource A\n");
    sleep(1);
    pthread_mutex_lock(&resourceB);
    printf("Thread 1: Acquired resource B\n");
    pthread_mutex_unlock(&resourceB);
    printf("Thread 1: Released resource B\n");
    pthread_mutex_unlock(&resourceA);
    printf("Thread 1: Released resource A\n");
    return NULL;
}


void *thread2(void *arg)
{
    pthread_mutex_lock(&resourceB);
    printf("Thread 2: Acquired resource B\n");
    sleep(1);
    pthread_mutex_lock(&resourceA);
    printf("Thread 2: Acquired resource A\n");
    pthread_mutex_unlock(&resourceA);
    printf("Thread 2: Released resource A\n");
    pthread_mutex_unlock(&resourceB);
    printf("Thread 2: Released resource B\n");
    return NULL;
}


int main(){
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
