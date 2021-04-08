/**
 * ba - (Bankers Algorithm)
 * ba_log.h
 * Author: James Johnston
 *
 * Contains a function and a flag (log_flag) to help log information from the
 * actions completed by the user or the automated randomized system.
 */
#ifndef BA_LOG_H
#define BA_LOG_H
#include "ba_mode.h"
#include "ba_command.h"
namespace ba {
  /**
   * log_flag enumerator
   *
   * LF_REQUEST - Indicates a request type of action that needs to be logged.
   * LF_RELEASE - Indicates a release type of action that needs to be logged.
   */
  enum log_flag {
    LF_REQUEST,
    LF_RELEASE
  };

  /**
   * Logs information about a request or release
   *
   * @param flag (ba::log_flag) Flag of the type of logging.
   * @param m (ba::mode) Mode that we are in, if auto then display what thread is being used.
   * @param cmd (ba::command) Command that holds our values of the action processed.
   * @param success (bool) If the action was successful or not (displays a "failed" or "succeeded").
   * @param process (int) Defaults to -1, this indicates the thread being run, so we know what thread is displaying the message.
   */
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
