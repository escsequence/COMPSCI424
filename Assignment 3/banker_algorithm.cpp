#include "banker_algorithm.h"

void banker_algorithm::init() {
  // Load the configuration so we can set the n and m variables
  init_load_config();

  // Setup our array
  init_setup_array();

  // Parse the configuration data now
  init_parse_config();

  // Print status
  std::cout << "%%%% Configuration loaded | n = " << this->n << " | m = " << this->m << std::endl;
}

void banker_algorithm::init_parse_config() {
  // Loop through all the config stuff
  int mp = 0;
  int ma = 0;
  for(ba_config::config c: configuration) {
    switch(c.flag) {
      case ba_config::CF_AVAILABLE:
        for (int i = 0; i < m; ++i) {
          this->available[i] = c.value_array[i];
        }
        break;
      case ba_config::CF_MAX:
        for (int i = 0; i < m; ++i) {
          this->max[mp][i] = c.value_array[i];
        }
        mp++;
        break;
      case ba_config::CF_ALLOCATION:
        for (int i = 0; i < m; ++i) {
          this->max[ma][i] = c.value_array[i];
        }
        ma++;
        break;
    }
  }
}

void banker_algorithm::init_setup_array() {
  // We allocate our space for this variables
  available = new int[m];
  max = new int*[n];
  allocation = new int*[n];
  request = new int*[n];

  // Since max, allocation, and request are 2d arrays
  for (int i = 0; i < n; ++i) {
    max[i] = new int[m];
    allocation[i] = new int[m];
    request[i] = new int[m];
  }
}

void banker_algorithm::init_load_config() {
  std::ifstream config_file;
  std::string file_name = arg_handle.get_file();
  //std::cout << "Trying to read config file = " << file_name << std::endl;
  config_file.open(file_name);

  if (config_file.fail()) {
    std::cout << "!!! Error reading the config file !!!" << std::endl;
  } else {

    std::string line;
    bool n_set, m_set;
    ba_config::config_flag current_flag = ba_config::CF_INVALID;

    while(std::getline(config_file, line)) {
      std::vector<std::string> parsed_elements = split(line, ' ');
      // for(std::string ele : parsed_elements) {
      //   std::cout << "[e]: " << ele << std::endl;
      // }
      //std::cout << "size of the parsed elements: " << parsed_elements.size() << std::endl;

      if (!n_set || !m_set) {
        if (parsed_elements.size() == 2) {
          if (parsed_elements[1] == "processes") {
            int temp_n = std::stoi(parsed_elements[0]);
            this->n = temp_n;
            n_set = true;
          } else if (parsed_elements[1] == "resources") {
            int temp_m = std::stoi(parsed_elements[0]);
            this->m = temp_m;
            m_set = true;
          }
        }
      } else {
        if (parsed_elements.size() == m) {
          // This is most likely an entry
          ba_config::config config_to_insert;
          config_to_insert.flag = current_flag;
          config_to_insert.value_array = new int[n];
          for (int i = 0; i < m; ++i) {
            config_to_insert.value_array[i] = std::stoi(parsed_elements[i]);
          }
          configuration.push_back(config_to_insert);
          //std::cout << "Added this data as a configuration for (flag = " << config_to_insert.flag << ")" << std::endl;
        } else {
          if (parsed_elements[0] == "Available") {
            current_flag = ba_config::CF_AVAILABLE;
            //std::cout << "FLAG SET TO AVALIABLE" << std::endl;
          } else if (parsed_elements[0] == "Max") {
            current_flag = ba_config::CF_MAX;
            //std::cout << "FLAG SET TO MAX" << std::endl;
          } else if (parsed_elements[0] == "Allocation") {
            current_flag = ba_config::CF_ALLOCATION;
            //std::cout << "FLAG SET TO ALLOCATION" << std::endl;
          }
          // Probably a keyword to define what we are looking for
        }
        // n and m are both set
      }
    }
    config_file.close();
  }
}



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

  manual_process_inputs = true;

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
