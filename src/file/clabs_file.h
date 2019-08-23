#ifndef CLABS_FILE_H
#define CLABS_FILE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    FILE* _pointer;
} clabsFile;

clabsFile* clabsFileNew();

void clabsFileInit(clabsFile* file);

void clabsFileOpen(clabsFile* file, char* file_name);

long clabsFileSize(clabsFile* file);

void clabsFileClose(clabsFile* file);

#endif
