#include "file.h"

clabsFile* clabsFileNew() {
    clabsFile* file = malloc(sizeof(clabsFile));

    if(NULL == file){
        return NULL;
    }

    clabsFileInit(file);

    return file;
}

void clabsFileInit(clabsFile* file){
    file->_pointer = NULL;
}

void clabsFileOpen(clabsFile* file, char* file_name){
    if(NULL != file->_pointer){
        return;
    }

    FILE* f = fopen(file_name, "r");

    if(NULL == f){
        return;
    }

    file->_pointer = f;
}

long clabsFileSize(clabsFile* file){
    if(NULL == file->_pointer){
        return 0;
    }

    fseek(file->_pointer, 0, SEEK_END);
    return ftell(file->_pointer);
}

void clabsFileClose(clabsFile* file){
    if(NULL == file->_pointer){
        return;
    }

    fclose(file->_pointer);
    file->_pointer = NULL;
}
