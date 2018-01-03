#include <stdlib.h>
#include "cmdie.h"

static Cmd* tree;

void cmdie_build() {
  
}

void cmdie_parse(int argc, char **argv) {
  
}

Cmd* cmdie_make_cmd() {
  Cmd* result = (Cmd*)malloc(sizeof(Cmd));
  result->parent = NULL;
  result->subs_count = 0;
  result->opts_count = 0;
  result->desc = NULL;
  return result;
}

Opt* cmdie_make_opt() {
  Opt* result = (Opt*)malloc(sizeof(Opt));
  result->names = NULL;
  result->namel = NULL;
  result->value = NULL;
  result->desc = NULL;
  return result;
}

Cmd* cmdie_add_cmd(Cmd* self) {
  self->subs[self->subs_count++] = cmdie_make_cmd();
  return self;
}
