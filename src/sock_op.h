#ifndef __SOCKET_OPERATION_H__
#define __SOCKET_OPERATION_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "const.h"



void setServerConfig(int *fileDescriptor,struct sockaddr_in *serverConfig,
    const char* serverIpAddr,unsigned int serverPort,
    SSERVER_PARAMS ipv4_ipv6 , SSERVER_PARAMS tcp_udp,SSERVER_PARAMS autoMountSocket,SSERVER_PARAMS debug_yes_no);


void setClientConfig(int *fileDescriptor,struct sockaddr_in *clientConfig,const char* connectIpAddr,
    unsigned int connectPort,SSERVER_PARAMS ipv4_ipv6 , SSERVER_PARAMS tcp_udp,SSERVER_PARAMS debug_yes_no);

const char* toStrIpAddr(struct sockaddr_in *serverConfig);

#endif //__SOCKET_OPERATION_H__