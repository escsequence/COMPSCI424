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

  // We keep processing getting input values
  while(manual_process_inputs) {

    // Entry string from user
    std::string entry;

    // Formatting
    std::cout << "Command: ";

    // Get the line from the command
    getline(std::cin, entry);

    // Get the current command (parsing it from our static function)
    ba_command::command current = ba_command::parse(entry);

    // Identify what wer are trying to do..
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

  // Return control back to the original run
  return 0;
}



int banker_algorithm::run_auto() {
  // Yet to be developed.
  return 0;
}
