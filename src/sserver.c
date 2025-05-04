#include "sserver.h"
#include "sock_op.h"
#include "thread_op.h"
#include "file_op.h"

unsigned int argPort = 0;
int argStream = -1;
char* argCh[3];

struct sockaddr_in serverConfig;
int serverFD,clientFD;
socklen_t acceptSize = sizeof(struct sockaddr_in);
Buffer **buffs;

int main(int argc , char *argv[]){
    //argCh temizleme
    for (int i = 0; i < 3; i++) 
        argCh[i] = NULL;

    //ARGUMAN ISLEMLERI
    argsCheckFill(&argc,argv,&argPort,&argStream,argCh); //argumanlari kontrol edip doldurma
    printServerInfo(argc,argPort,argStream,argCh); //doldurulan argumanlarin debug islemi

    //BUFFER VE SYNC
    buffs = createInitBuffers(argStream); 
    pthread_t readWriteThreads[THREAD_COUNT];
    createThreadPoll(readWriteThreads,THREAD_COUNT,readerWriterThread,0,YES); 



    //SOKET ISLEMLERI
    setServerConfig(&serverFD,&serverConfig,SERVER_IP,argPort,IPV4,TCP,YES,true);
    int listenStatus = listen(serverFD,BACKLOG_COUNT);
    if(listenStatus == -1){
         perror("SERVER DINLEMEDE PROBLEM ! :");
         exit(EXIT_FAILURE);
    }
    printf("[SERVER-INFO-SOCKET] %s - %u ADRESINDE VE PORTUNDA DINLIYOR !\n",toStrIpAddr(&serverConfig),argPort);
    while(true){
        clientFD = accept(serverFD,(struct sockaddr*)&serverConfig,&acceptSize);
        send(clientFD,MSG_CONNECTED_SUCCESS,strlen(MSG_CONNECTED_SUCCESS),0);
        pthread_t clientNewThread;
        pthread_create(&clientNewThread,NULL,clientSenderThread,&clientFD);


    }


    deleteChanells(argCh);
    deleteBuffers(buffs,argStream);
    return 0x0;
}

void argsCheckFill(int *argc , char **argv,unsigned int* argPort , int* argStream , char **argCh){
    //–p port –s streams –ch1 videofile MIN 7 ARGUMAN
    if(*argc >= 7 && *argc <= 11){
        for(int i = 1 ; i < *argc ; i++){
            if(strcmp("-p",argv[i]) == 0)
                *argPort = atoi(argv[++i]);
            if(strcmp("-s",argv[i]) == 0 && atoi(argv[i+1]) <= 3){
                *argStream = atoi(argv[++i]);
                if(*argStream <= 0)
                    *argStream = 1;
            }
            if(strcmp("-ch1",argv[i]) == 0){
                //argCh[0] = (char*) malloc(sizeof(char) * PATH_LENGTH);
                //strcpy(argCh[0],argv[++i]);
                argCh[0] = strdup(argv[++i]); 
            }
            if(strcmp("-ch2",argv[i]) == 0){
                //argCh[1] = (char*) malloc(sizeof(char) * PATH_LENGTH);
                //strcpy(argCh[1],argv[++i]);
                argCh[1] = strdup(argv[++i]); 
            }
            if(strcmp("-ch3",argv[i]) == 0){
                //argCh[2] = (char*) malloc(sizeof(char) * PATH_LENGTH);
                //strcpy(argCh[2],argv[++i]);
                argCh[2] = strdup(argv[++i]);
            }
            
        }    
    }
    else{
        fprintf(stderr,"GECERSIZ ARGUMAN SAYISI !\n\
KULLANIM ./sserver –p port –s streams –ch1 videofile [–ch2 videofile] [–ch3 videofile]\n");
            exit(EXIT_FAILURE);
    }
}


void deleteChanells(char **argCh){
    free(argCh[0]);
    free(argCh[1]);
    free(argCh[2]);
    DEBUG_LOG("DELETED ALL CHANNELS");
}


void printServerInfo(const int argc,const unsigned int argPort ,const int argStream ,char** argCh){
    printf("[SERVER-INFO]\nARGUMAN SAYISI : %d\n",argc);
    printf("PORT NUMARASI  : %d\n",argPort);
    printf("STREAM SAYISI  : %d\n",argStream);
    printf("CH1            : %s\n",*argCh);
    printf("CH2            : %s\n",*(argCh+1));
    printf("CH3            : %s\n\n",*(argCh+2));
}


void* readerWriterThread(void *args){
    int *channel = (int*) malloc(sizeof(int));
    *channel = *(int*)args;
    free(args);

    FILE *file = fileFill(argCh[*channel]); //file dolduruldu 
    //printf("DEBUG: CHANNEL = %d - PATH = %s\n",*channel,argCh[*channel]);

    //KRITIK ERISIM//
    while(true){         //buff yazma islemi
        if(file == NULL) break;
        sem_wait(&buffs[*channel]->empty);
        pthread_mutex_lock(&buffs[*channel]->mutex);
        
            writeBuff(file,buffs[*channel]->image);
        
        pthread_mutex_unlock(&buffs[*channel]->mutex);
        sem_post(&buffs[*channel]->full);
    }
}


void* clientSenderThread(void *args){
    int clientFD_t = *(int*)args;
    printf("CLIENT_FD_THREAD : %d\n",clientFD_t);
    int corrCh = true;

    char recvChannelData[4];
    memset(recvChannelData,0,4);

    int receivedBytes = recv(clientFD_t,recvChannelData,4,0); //client kanal bilgisini teyit

   
    printf("RECV DATA CLIENT CONNECT CHANNEL : |%s|\n",recvChannelData);
    int channel = atoi(recvChannelData) -1;
    if(channel > 2 || channel < 0){
        int i = -1;
        while(i++ < 1)
        send(clientFD_t,MSG_ERROR_CH_ASCII,sizeof(MSG_ERROR_CH_ASCII),0);
        corrCh = false;
    }
    else 
    printf("CLIENT CONNECTED %d CHANNEL\n",channel+1);

    while(true && corrCh){
        sem_wait(&buffs[channel]->full);
        pthread_mutex_lock(&buffs[channel]->mutex);

        for (int i = 0; i < IMAGE_COUNT_X; i++)
            send(clientFD_t, buffs[channel]->image[i], strlen(buffs[channel]->image[i]), 0);

        pthread_mutex_unlock(&buffs[channel]->mutex);
        sem_post(&buffs[channel]->empty);

        usleep(500000);
    }

    close(clientFD_t);
    pthread_exit(NULL);

}