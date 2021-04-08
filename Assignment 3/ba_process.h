#ifndef BA_PROCESS_H
#define BA_PROCESS_H
#include <thread>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <time.h>
#include <string>
#include <mutex>
#include <math.h>
#include <vector>

namespace ba {
  class process {
    private:
      ba::state *state;
      int count;
      void operate() {
        std::cout << "Do something.." << std::endl;
      }
    public:
      process(ba::state *s, int count) {
        this->state = s;
        this->count = count;
      }
  };
}

#endif
