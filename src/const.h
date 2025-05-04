#ifndef __CONST_H__
#define __CONST_H__

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define IMAGE_COUNT_X 512  //sutun
#define IMAGE_COUNT_Y 512 //satir
#define NOT_SHARED 0
#define SHARED 1
#define PRIV
#define DEFAULT_BUFF_SIZE 3072

#define DEBUG_LOG(x) printf("[DEBUG-LOG] : %s\n",x)
#define PATH_LENGTH 100

#define BACKLOG_COUNT 10

#define THREAD_COUNT 3

#define true 1
#define false 0

#define MSG_CONNECTED_SUCCESS "STREAM SERVERA BAGLANIDINIZ !\n"
#define MSG_ERROR_CHANNEL "[STREAM-SERVER-ERROR] : LUTFEN 1-2-3 KANALLARINDAN BIRINI SECIN !\n"

typedef enum {
    YES = 1,
    NO = 0,
    IPV4 = AF_INET,
    IPV6 = AF_INET6,
    TCP = SOCK_STREAM,
    UDP = SOCK_DGRAM
}SSERVER_PARAMS;



//#define YES 1
//#define NO 0


#define MSG_ERROR_CH_ASCII \
" ██████╗ ███████╗ ██████╗███████╗██████╗ ███████╗██╗███████╗ \n" \
"██╔════╝ ██╔════╝██╔════╝██╔════╝██╔══██╗██╔════╝██║╚══███╔╝\n" \
"██║  ███╗█████╗  ██║     █████╗  ██████╔╝███████╗██║  ███╔╝ \n" \
"██║   ██║██╔══╝  ██║     ██╔══╝  ██╔══██╗╚════██║██║ ███╔╝  \n" \
"╚██████╔╝███████╗╚██████╗███████╗██║  ██║███████║██║███████╗ \n" \
" ╚═════╝ ╚══════╝ ╚═════╝╚══════╝╚═╝  ╚═╝╚══════╝╚═╝╚══════╝\n" \
"                                                            \n" \
"██╗  ██╗ █████╗ ███╗   ██╗ █████╗ ██╗                       \n" \
"██║ ██╔╝██╔══██╗████╗  ██║██╔══██╗██║                       \n" \
"█████╔╝ ███████║██╔██╗ ██║███████║██║                       \n" \
"██╔═██╗ ██╔══██║██║╚██╗██║██╔══██║██║                       \n" \
"██║  ██╗██║  ██║██║ ╚████║██║  ██║███████╗                  \n" \
"╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝                  \n" \
"                                                            \n" \
"███████╗███████╗ ██████╗████████╗██╗███╗   ██╗              \n" \
"██╔════╝██╔════╝██╔════╝╚══██╔══╝██║████╗  ██║              \n" \
"███████╗█████╗  ██║        ██║   ██║██╔██╗ ██║              \n" \
"╚════██║██╔══╝  ██║        ██║   ██║██║╚██╗██║              \n" \
"███████║███████╗╚██████╗   ██║   ██║██║ ╚████║              \n" \
"╚══════╝╚══════╝ ╚═════╝   ╚═╝   ╚═╝╚═╝  ╚═══╝              "



#endif 