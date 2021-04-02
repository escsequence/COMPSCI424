#ifndef BA_MODE_H
#define BA_MODE_H
#include <iostream>

namespace ba {
  /**
   * mode enumerator
   *
   * BM_INVALID - If input from the user does not match "manual" or "auto"
   * BM_MANUAL  - Used to run tests on the algorthim.
   * BM_AUTO    - Automatically runs the algorthim in a standard way.
   */
  enum mode {
    BM_INVALID = -1,
    BM_MANUAL,
    BM_AUTO
  };

  /**
   * Converts a string value to a mode enum.
   *
   * @param c Value that is parsed to find a mode.
   * @return BA_MODE value of the argument.
   */
  static mode str_to_mode(std::string c) {
    mode tmode = (c == "manual") ? BM_MANUAL : BM_INVALID;
    return (c == "auto") ? BM_AUTO : tmode;
  }
}

#endif
