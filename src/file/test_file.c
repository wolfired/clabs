#include "file/file.h"

int main(int argc, char** argv) {
    clabsFile file;
    clabsFileInit(&file);

    clabsFileOpen(&file, "../src/file/test_file.c");

    printf("%d\n", clabsFileSize(&file));

    clabsFileClose(&file);

    return 0;
}
