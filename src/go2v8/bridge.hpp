#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#ifdef __cplusplus

#include "V8Hub.hpp"

V8Hub v8hub;

#endif

#ifdef __cplusplus
extern "C" {
#endif

void startup();
void shutdown();
void create();

#ifdef __cplusplus
}
#endif

#endif
