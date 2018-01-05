#ifndef V8HUB_HPP
#define V8HUB_HPP

#include "include/libplatform/libplatform.h"
#include "include/v8.h"

class V8Hub {
  public:
    V8Hub();
    ~V8Hub();
    void tryGetVM();

  private:
    std::unique_ptr<v8::Platform> _platform;
};

#endif