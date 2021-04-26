#ifndef RA_FIFO_H
#define RA_FIFO_H
#include "ra.h"
namespace ra {
  class fifo_algorithm : protected algorithm {
    public:
      std::string run() {
        return "Test!";
      }
  };
}
#endif
