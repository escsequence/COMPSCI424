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
enum ba_mode {
  BA_INVALID = -1,
  BA_MANUAL,
  BA_AUTO
};

/**
 * Converts a string value to a BA_MODE enum.
 *
 * @param c Value that is parsed to find a BA_MODE.
 * @return BA_MODE value of the argument.
 */
static ba_mode str_to_mode(std::string c) {
  ba_mode tmode = (c == "manual") ? BA_MANUAL : BA_INVALID;
  return (c == "auto") ? BA_AUTO : tmode;
}

#endif
