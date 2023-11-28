#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define FILENAME "data.txt"
pthread_mutex_t fileMutex = PTHREAD_MUTEX_INITIALIZER;


void *readFromFile(void *arg)
{
    pthread_mutex_lock(&fileMutex);
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL){
        perror("Error opening file for reading");
        exit(1);
    }
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL){
        printf("Read: %s", buffer);
    }
    fclose(file);
    pthread_mutex_unlock(&fileMutex);
    return NULL;
}


void *writeToFile(void *arg)
{
    pthread_mutex_lock(&fileMutex);
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL){
        perror("Error opening file for writing");
        exit(1);
    }
    fprintf(file, "Hello from the write thread!\n");
    fclose(file);
    pthread_mutex_unlock(&fileMutex);
    return NULL;
}


void *updateFile(void *arg)
{
    pthread_mutex_lock(&fileMutex);
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL){
        perror("Error opening file for updating");
        exit(1);
    }
    fprintf(file, "Hello from the update thread!\n");
    fclose(file);
    pthread_mutex_unlock(&fileMutex);
    return NULL;
}


int main()
{
    pthread_t readThread, writeThread, updateThread;


    pthread_create(&readThread, NULL, readFromFile, NULL);
    pthread_create(&writeThread, NULL, writeToFile, NULL);
    pthread_create(&updateThread, NULL, updateFile, NULL);


    // Create a thread to continuously display the file contents in the terminal
    pthread_t displayThread;
    pthread_create(&displayThread, NULL, readFromFile, NULL);


    pthread_join(readThread, NULL);
    pthread_join(writeThread, NULL);
    pthread_join(updateThread, NULL);


    return 0;
}
