#include "thread_op.h"

Buffer* createInitOneBuffer(){
    Buffer *buff = (Buffer*) malloc(sizeof(Buffer));
    initBuffer(buff);
    return buff;
}

void initBuffer(Buffer *buff){
    sem_init(&buff->empty,NOT_SHARED,IMAGE_COUNT_X);
    sem_init(&buff->full,NOT_SHARED,0);
    pthread_mutex_init(&buff->mutex,NULL);
}

void deleteOneBuffer(Buffer *buff){
    sem_destroy(&buff->empty);
    sem_destroy(&buff->full);
    pthread_mutex_destroy(&buff->mutex);
    free(buff);
}

Buffer** createInitBuffers(const int argStream){
    Buffer **buffs = (Buffer**) malloc(sizeof(Buffer*) * argStream);

    for(int i = 0 ; i < argStream ; i++)
        *(buffs+i) = createInitOneBuffer();
    
    return buffs;
}

void deleteBuffers(Buffer** buffs,const int argStream){
    for(int i = 0 ; i < argStream ; i++)
        deleteOneBuffer(*(buffs+i));
    free(buffs);

    DEBUG_LOG("DELETED ALL BUFFERS");
}

void createThreadPoll(pthread_t *threadArr,const int threadCount,void* (*thread_func)(void*),void *arg,SSERVER_PARAMS autoinc_yesno){
    if(autoinc_yesno){
        for(int i = 0 ; i < threadCount ; i++){
            int *tempArg = (int*) malloc(sizeof(int));
            *tempArg = i;
            pthread_create(&threadArr[i],NULL,thread_func,tempArg);
        }
    }
    else{
        for(int i = 0 ; i < threadCount ; i++){
            int *tempArg = (int*) malloc(sizeof(int));
            *tempArg = *(int*)arg;
            pthread_create(&threadArr[i],NULL,thread_func,tempArg);
        }
    }
}

