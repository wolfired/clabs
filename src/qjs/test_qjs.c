#include <string.h>

#include "qjs/clabs_qjs.h"

int main(int argc, char** argv) {
    char* jscode = "console.log(\"Hello QJS!!\")";
    eval_source(argc, argv, jscode, strlen(jscode));
    return 0;
}
