#include "sock_op.h"

void setServerConfig(int *fileDescriptor,struct sockaddr_in *serverConfig,const char* serverIpAddr,unsigned int serverPort,
    SSERVER_PARAMS ipv4_ipv6 , SSERVER_PARAMS tcp_udp,SSERVER_PARAMS autoMountSocket_yesno,SSERVER_PARAMS debug_yesno){
    
    int serverSocket = socket(ipv4_ipv6,tcp_udp,0);
    
    if(serverSocket == -1){
        perror("SERVER SOKETI ACILAMADI ! : ");
        exit(EXIT_FAILURE);
    }
    
    int yes_no = autoMountSocket_yesno;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes_no, sizeof(yes_no));

    serverConfig->sin_addr.s_addr = inet_addr(serverIpAddr);
    serverConfig->sin_family = ipv4_ipv6;
    serverConfig->sin_port = htons(serverPort);
    memset(&serverConfig->sin_zero,0,8);


    *fileDescriptor = serverSocket;
    int bindStatus = bind(*fileDescriptor, (struct sockaddr *)serverConfig, sizeof(struct sockaddr_in));

    if(bindStatus == -1){
        perror("SERVER SOKETI BIND EDILEMEDI ! : ");
        exit(EXIT_FAILURE);
    }

    if(debug_yesno){
        printf("SERVER SOKET FD : %d\n",*fileDescriptor);
        printf("SERVER PORT NO  : %d\n",serverPort);
        printf("SERVER IP ADRES : %s\n\n",serverIpAddr);    
    }
}


const char* toStrIpAddr(struct sockaddr_in *serverConfig){
    return inet_ntoa(serverConfig->sin_addr);
}

void setClientConfig(int *fileDescriptor,struct sockaddr_in *clientConfig,const char* connectIpAddr,unsigned int connectPort,
    SSERVER_PARAMS ipv4_ipv6 , SSERVER_PARAMS tcp_udp,SSERVER_PARAMS debug_yesno){
    int clientSocket = socket(ipv4_ipv6,tcp_udp,0);

    if(clientSocket == -1){
        perror("CLIENT SOKETI ACILAMADI ! : ");
        exit(EXIT_FAILURE);
    }


    clientConfig->sin_addr.s_addr = inet_addr(connectIpAddr);
    clientConfig->sin_family = ipv4_ipv6;
    clientConfig->sin_port = htons(connectPort);
    memset(&clientConfig->sin_zero,0,8);

    *fileDescriptor = clientSocket;


    if(debug_yesno){
        printf("CLIENT SOKET FD : %d\n",*fileDescriptor);
        printf("CLIENT CONNECT PORT NO  : %d\n",connectPort);
        printf("CLIENT CONNECT IP ADRES : %s\n\n",connectIpAddr);    
    }

}