#include "file_op.h"

static int ch = 1;
FILE* fileFill(const char *filePath){
    if(filePath == NULL)
        printf("[SERVER-FILE-WARNING] (BOS VEYA YANLIS PATH) FILE_PATH: %s CHANNEL_%d\n",filePath,ch++);

    FILE *file = fopen(filePath,"r");
    

    return file;
}

void writeBuff(FILE *file,char image[IMAGE_COUNT_X][IMAGE_COUNT_Y]){
    for(int i = 0 ; i < IMAGE_COUNT_X ; i++){
        if(fgets(image[i],IMAGE_COUNT_Y,file) == NULL)
            rewind(file);   //dosya sonuysa tekrar basa cek imleci
        fgets(image[i],IMAGE_COUNT_Y,file);
    }
}