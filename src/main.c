#include <stdio.h>
#include <string.h>

#include "clabs.h"
#include "file.h"

int main(int argc, char** argv) {
    trace("This is a trace msg!\n");

    char* jscode = "console.log(\"Hello QJS!!\")";
    eval_source(argc, argv, jscode, strlen(jscode));

    clabsFile file;
    clabsFileInit(&file);

    clabsFileOpen(&file, "/home/link/workspace_git/clabs/src/main.c");

    printf("%d\n", clabsFileSize(&file));

    clabsFileClose(&file);

    return 0;
}
