#include <stdio.h>
#include "cmdie.h"

int main(int argc, char** argv) {
  cmdie_build();
  cmdie_parse(argc, argv);

  Cmd* c = cmdie_make_cmd();
  c->desc = "Hello";

  printf("%s\n", c->desc);

  return 0;
}
