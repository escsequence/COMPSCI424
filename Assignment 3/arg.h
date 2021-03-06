/**
 * arg.h
 * Author: James Johnston
 *
 * Structure for holding the argument data passed in from the main method of the program.
 * Allows us to easily pass this information to other classes and objects.
 */
#ifndef ARG_H
#define ARG_H
#include "ba_mode.h"
class arg {
  private:
    // Count of the arguments.
    int c;

    // Values of the arguments stored as a double pointer char as from the main method.
    char **v;

    // Bankers algorthim mode from argument 2
    ba::mode m;

    // File name from argument 3
    std::string f;

  public:
    // Default constructor, takes in parameters from the main method
    arg(int argc, char** argv) {
      // Assign the c (count) and the v (values)
      c = argc;
      v = argv;

      // If the count is greater than 1 (meaning there is a single argument)
      if (c > 1) {
        // try and find a mode based on the string
        m = ba::str_to_mode(v[1]);
      }

      // If the count is greater than 2 (meaning there are two arguments)
      if (c > 2) {
        // Just assign it to the "f" variable since we are just storing a string.
        f = v[2];
      }
    }

    arg() {}

      /**
       * Returns the mode (string-ified version) for this argument object.
       *
       * @return string mode of the argument object, this should be the second parameter.
       */
      std::string get_mode_str() {
        switch(m) {
          case ba::BM_AUTO:
            return "auto";
          case ba::BM_MANUAL:
            return "manual";
          default:
            return "invalid";
        }
      }

      /**
       * Returns the mode for this argument object.
       *
       * @return mode of the argument object, this should be the second parameter.
       */
      ba::mode get_mode() {
        return m;
      }

      /**
       * Returns the file for this argument object.
       *
       * @return file of the argument object, this should be the third parameter.
       */
      std::string get_file() {
        return (f == "") ? "<No file name provided>" : f;
      }

      /**
       * Returns if the mode and the file are valid.
       *
       * @returns true if the mode is not invalid and file is not empty.
       */
      bool verify_mode_and_file() {
        return (f != "" && (m == ba::BM_AUTO || m == ba::BM_MANUAL));
      }
};
#endif
