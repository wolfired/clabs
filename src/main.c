#include <stdio.h>
#include <string.h>

#include "clabs.h"

int main(int argc, char **argv) {
    trace("This is a trace msg!\n");

    char* jscode = "console.log(\"Hello QJS!!\")";
    eval_source(argc, argv, jscode, strlen(jscode));

    return 0;
}
