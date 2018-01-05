#ifndef CMDIE_H
#define CMDIE_H

#define CMD_COUNT 32
#define OPT_COUNT 32

#include "clabs.h"

typedef struct _Cmd {
    struct _Cmd *parent;
    struct _Cmd *subs[CMD_COUNT];
    int subs_count;
    struct _Opt *opts[OPT_COUNT];
    int opts_count;
    char *desc;
} Cmd;

typedef struct _Opt {
    char *names;
    char *namel;
    char *value;
    char *desc;
} Opt;

void cmdie_build();
void cmdie_parse(int argc, char **argv);

Cmd *cmdie_make_cmd();
Opt *cmdie_make_opt();

Cmd *cmdie_add_cmd(Cmd *self);

#endif
