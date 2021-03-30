#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H
#include <vector>
#include <sstream>
#include <string>
#include <iterator>

namespace ba_command {
  enum command_action {
    CA_INVALID,
    CA_REQUEST,
    CA_RELEASE,
    CA_END
  };

  struct command {
    int i, j, k;
    command_action action;
  };

  template <typename Out>
  static void split (const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while(std::getline(iss, item, delim)) {
      *result++ = item;
    }
  }

  static std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
  }

  static command parse(std::string m) {
    command c;
    // default
    c.action = CA_INVALID;

    if (m == "end" || m == "END") {
      c.action = CA_END;
    } else {
      std::vector<std::string> parsed_elements = split(m, ' ');
      if (parsed_elements.size() > 0) {
        if (parsed_elements[0] == "request" || parsed_elements[0] == "REQUEST") {
          c.action = CA_REQUEST;
        } else if (parsed_elements[0] == "release" || parsed_elements[0] == "RELEASE") {
          c.action = CA_RELEASE;
        }
        if (c.action != CA_INVALID) {
          if (parsed_elements.size() > 5) {
            try {
              c.i = std::stoi(parsed_elements[1]);
              // Skipping 2
              c.j = std::stoi(parsed_elements[3]);
              // Skipping 4
              c.k = std::stoi(parsed_elements[5]);
            } catch (int e) {
              std::cout << "Error! The input data is corrupted (possibly did not contain numeric values)." << std::endl;
              std::cout << "Try this format: request 3 of 1 for 0" << std::endl;
              c.action = CA_INVALID;
            }
          } else {
            std::cout << "Error! The input data is corrupted (possibly did not contain numeric values)." << std::endl;
            std::cout << "Try this format: request 3 of 1 for 0" << std::endl;
          }
        }
      }
    }
    return c;
  }
}

#endif
