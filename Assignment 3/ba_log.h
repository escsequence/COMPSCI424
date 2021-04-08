#ifndef BA_LOG_H
#define BA_LOG_H
#include "ba_mode.h"
#include "ba_command.h"

namespace ba {
  enum log_flag {
    LF_RAW,
    LF_REQUEST,
    LF_RELEASE
  };

  static void log(log_flag flag, mode m, command cmd, bool success, int process = -1) {
    if (m == BM_AUTO) {
      std::cout << "[Thread " << process << "]: ";
    }
    switch (flag) {
      case LF_REQUEST:
        std::cout << "Process " << cmd.k << " requests " << cmd.i << " of resource " << cmd.j << ": ";

        if (success)
          std::cout << "accepted";
        else
          std::cout << "denied";

        std::cout << std::endl;

        break;
      case LF_RELEASE:
        std::cout << "Process " << cmd.k << " releases " << cmd.i << " of resource " << cmd.j << ": ";

        if (success)
          std::cout << "accepted";
        else
          std::cout << "denied";

        std::cout << std::endl;

        break;


    }
  }
}
#endif
