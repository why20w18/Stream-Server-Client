#ifndef __FILE_OPERATION_H__
#define __FILE_OPERATION_H__

#include "thread_op.h"
#include "const.h"

#include <stdio.h>
#include <stdlib.h>

FILE* fileFill(const char *filePath); //filePath ile dosya okumasi ve writeBuff func cagirmasi
void writeBuff(FILE *file,char image[IMAGE_COUNT_X][IMAGE_COUNT_Y]); //burada sadece kritik bolgeyi kitleyip buffa guvenli yazma yapilir 


#endif //__FILE_OPERATION_H__