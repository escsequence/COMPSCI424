#ifndef MODE_H
#define MODE_H
#include <iostream>

/**
 * BA_MODE enumerator
 *
 * INVALID - If input from the user does not match "manual" or "auto"
 * MANUAL  - Used to run tests on the algorthim.
 * AUTO    - Automatically runs the algorthim in a standard way.
 */
enum BA_MODE {
  INVALID = -1,
  MANUAL,
  AUTO
};

/**
 * Converts a string value to a BA_MODE enum.
 *
 * @param c Value that is parsed to find a BA_MODE.
 * @return BA_MODE value of the argument.
 */
static BA_MODE str_to_mode(std::string c) {
  BA_MODE tmode = (c == "manual") ? BA_MODE::MANUAL : BA_MODE::INVALID;
  return (c == "auto") ? BA_MODE::AUTO : tmode;
}

#endif
