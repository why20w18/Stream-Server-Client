#include "sclient.h"


int clientFD;
struct sockaddr_in clientConfig;
char argIpAddr[32];
unsigned int argPort;
unsigned short argChannel;

int main(int argc , char* argv[]){
    
    argsClientCheckFill(&argc,argv,&argPort,argIpAddr,&argChannel);
    printClientInfo(argc,argChannel,argPort,argIpAddr);
    printf("[STREAM-CLIENT] : KANALDAN AYRILMAK ICIN => CTRL+Z\nKANALA BAGLANMAK ICIN => ENTER\n");
    getchar();
    setClientConfig(&clientFD,&clientConfig,argIpAddr,argPort,IPV4,TCP,YES);
    connectServer(argv,argIpAddr,argPort,argChannel);
    int i = -1;
    if(argChannel < 4 && argChannel > 0)
    while(true){
        char image[DEFAULT_BUFF_SIZE];
        memset(image,0,sizeof(DEFAULT_BUFF_SIZE));
        
        int recvBytes = recv(clientFD,image,sizeof(image),0);
        if(recvBytes == -1){
            perror("SERVERDAN ILK MESAJ ALINAMADI ! : ");
            exit(EXIT_FAILURE);
        }
        
        printf("%s\n",image);
    }
    else
    while(i++ < 1){
        char image[DEFAULT_BUFF_SIZE];
        memset(image,0,DEFAULT_BUFF_SIZE);
        int recvBytes = recv(clientFD,image,sizeof(image),0);
        
        printf("%s\n",image);
    }




    return 0x0;
}

void argsClientCheckFill(int *argc , char **argv,unsigned int* argPort , const char *argIpAddr , unsigned short *argChannel){
    //  ./sclient -a 127.0.0.1 -p 8080 -ch 1
     if(*argc == 7){
        for(int i = 1 ; i < *argc ; i++){
            if(strcmp("-a",argv[i]) == 0)
                strcpy(argIpAddr,argv[++i]);
           
            if(strcmp("-p",argv[i]) == 0)
                *argPort = atoi(argv[++i]);
            
            if(strcmp("-ch",argv[i]) == 0)
                *argChannel = atoi(argv[++i]);
        }    
    }
    else{
        fprintf(stderr,"GECERSIZ ARGUMAN SAYISI !\n\
KULLANIM ./sclient –a ip_addr –p port –ch channelNo");
            exit(EXIT_FAILURE);
    }
}

void printClientInfo(const int argc,const unsigned short argChNo ,const int argPort ,char *argIpAddr){
    printf("[CLIENT-INFO]\nARGUMAN SAYISI : %d\n",argc);
    printf("CONNECTED IP   : %s\n",argIpAddr);
    printf("PORT NUMARASI  : %d\n",argPort);
    printf("CONNECT CH     : %u\n\n",argChNo);
}


void connectServer(char **argv,const char* serverIpAddr , unsigned int serverPort , unsigned short channelNo){
    int connectStatus = connect(clientFD,(struct sockaddr *)&clientConfig,sizeof(struct sockaddr));
    if(connectStatus == -1){
        perror("CLIENT SERVERA BAGLANAMADI ! : ");
        exit(EXIT_FAILURE);
    }

    //ilk mesaji cekme
    char connectMSG[128];
    int recvBytes = recv(clientFD,connectMSG,sizeof(connectMSG),0);
    if(recvBytes == -1){
        perror("SERVERDAN ILK MESAJ ALINAMADI ! : ");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout,"[STREAM-SERVER-MSG] : %s\n",connectMSG);

    //sonu X ile bitirerek kanal bilgisini gönderme
    char sendCH[4];
    strcpy(sendCH,argv[6]);

    int sendedBytes = send(clientFD,sendCH,sizeof(sendCH),0);
    if(sendedBytes == -1){
        perror("KANAL BILGISI SERVERA ILETILEMEDI ! : ");
        exit(EXIT_FAILURE);
    }
}