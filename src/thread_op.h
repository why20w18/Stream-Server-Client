#ifndef __THREAD_OPERATION_H__
#define __THREAD_OPERATION_H__

#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#include "const.h"

typedef struct{
    char image[IMAGE_COUNT_X][IMAGE_COUNT_Y]; //goruntuyu tutacak ana array ->buffer<-
    sem_t empty; //bos bos alan sayisini tutar
    sem_t full; //dolu alan sayisini tutar
    pthread_mutex_t mutex; //buffer ortaktir erisimi ayarlar
}Buffer;


PRIV Buffer* createInitOneBuffer();
PRIV void deleteOneBuffer(Buffer *buff);
PRIV Buffer** createInitBuffers(const int argStream);

void deleteBuffers(Buffer** buffers,const int argStream);
void initBuffer(Buffer *buff);

void createThreadPoll(pthread_t *threadArr,const int threadCount,void* (*thread_func)(void*),void *arg,SSERVER_PARAMS autoinc_yesno);




#endif //__THREAD_OPERATION_H__
/*
    1-threadlerin baslatilmasi
    2-threadlerin silinmesi
    3-buffer erisimleri
    4-buffer yapisinin kurulmasi

*/