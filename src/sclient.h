#ifndef __SCLIENT_H__
#define __SCLIENT_H__

#include "sock_op.h"

void connectServer(char **argv,const char* serverIpAddr , unsigned int serverPort , unsigned short channelNo);
void argsClientCheckFill(int *argc , char **argv,unsigned int* argPort , const char *argIpAddr , unsigned short *argChannel);
void printClientInfo(const int argc,const unsigned short argChNo ,const int argPort ,char *argIpAddr);




#endif //__SCLIENT_H__