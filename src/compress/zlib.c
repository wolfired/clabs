#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "zlib.h"

void zlib_create(ZLib* p_thiz) { 
    *p_thiz = malloc(sizeof(ZLib_));

}

void zlib_delete(ZLib* p_thiz) {
    if (NULL != (*p_thiz)->compressed_data) {
        free((*p_thiz)->compressed_data);
    }
    free(*p_thiz);
    *p_thiz = NULL;
}
