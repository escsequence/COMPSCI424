#include "banker_algorithm.h"

int banker_algorithm::run() {
  switch(arg_handle.get_mode()) {
    case BA_MANUAL:
      // Process inputs
      return run_manual();
    case BA_AUTO:
      // Run automatically
      return run_auto();
    default:
      // Something went wrong, this should not be triggered.
      return 1;
  }
}

int banker_algorithm::run_manual() {
  while(manual_process_inputs) {
    std::string entry;
    std::cout << "Command: ";
    getline(std::cin, entry);
    ba_command::command current = ba_command::parse(entry);
    switch (current.action) {
      case ba_command::CA_REQUEST:
        break;
      case ba_command::CA_RELEASE:
        break;
      case ba_command::CA_END:
        manual_process_inputs = false;
        std::cout << "Program terminated." << std::endl;
        break;
      default:
        std::cout << "Invalid input. Please either try \'request\', \'release\', or \'end\'" << std::endl;
    }
  }
  return 0;
}



int banker_algorithm::run_auto() {
  return 0;
}
