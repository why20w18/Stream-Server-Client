#ifndef __SSERVER_H__
#define __SSERVER_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "const.h"

#define SERVER_IP "127.0.0.1"



void argsCheckFill(int *argc , char **argv,unsigned int* argPort , int* argStream , char **argCh);
void deleteChanells(char **argCh);
void printServerInfo(const int argc,const unsigned int argPort ,const int argStream ,char **argCh);

//THREAD FONKSIYONLARI//
void* readerWriterThread(void *args);
void* clientSenderThread(void *args);


#endif //__SSERVER_H__