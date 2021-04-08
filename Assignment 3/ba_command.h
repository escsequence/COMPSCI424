/**
 * ba - (Bankers Algorithm)
 * ba_command.h
 * Author: James Johnston
 *
 * Structure of each command for manual mode of this program.
 */
#ifndef BA_COMMAND_H
#define BA_COMMAND_H
namespace ba {
  /**
   * command_action enumerator
   *
   * CA_INVALID - Invalid action entry.
   * CA_REQUEST - Request action.
   * CA_RELEASE - Release action.
   * CA_END - Ending action, we end the program.
   * CA_STATUS - Custom entry, we output the status of our array.
   */
  enum command_action {
    CA_INVALID,
    CA_REQUEST,
    CA_RELEASE,
    CA_END,
    CA_STATUS
  };

  /**
   * command structure
   *
   * int values are stored from the command as: i of j for k
   */
  struct command {
    int i, j, k; // Values of the standardized i of j for k.
    command_action action; // Action the user wants to perform
  };

  /**
   * Parses a string a user enters into a valid command.
   *
   * @param m raw string to parse (style = i of j for k for basic request and release)
   * @return ba::command command the user wants to process.
   */
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
            std::cout << "Error! The input data is not completed (possibly missing some parameters?)." << std::endl;
            std::cout << "Try this format: request 3 of 1 for 0" << std::endl;
          }
        } else {
          // Extra commands
          if (m == "status" || m == "STATUS") {
            c.action = CA_STATUS;
          }
        }
      }
    }
    return c;
  }
}
#endif
