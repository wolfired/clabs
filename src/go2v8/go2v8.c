#include "bridge.hpp"

#include "go2v8.h"

void v8_startup() { startup(); }

void v8_shutdown() { shutdown(); }

void vm_create() { create(); }
