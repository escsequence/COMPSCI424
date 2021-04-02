#include "banker_algorithm.h"

void banker_algorithm::init() {
  // Load the configuration so we can set the n and m variables
  init_load_config();

  // Setup our array
  init_setup_array();

  // Parse the configuration data now
  init_parse_config();

  // Verify the data is valid
  if (!init_validate_config()) {
    std::cout << "!!!! Configuration/system is unsafe, please verify the configuration and re-run." << std::endl;
    config_valid = false;
    return;
  } else {
    config_valid = true;
  }

  // Print status
  std::cout << "#### Resources (m) = " << this->m << " | Processes (n) = " << this->n << std::endl;
  std::cout << std::endl;
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

  // Santize our array to be all DEFAULT_UNDEFINED_VALUE
  for (int in = 0; in < n; ++in) {
    for (int im = 0; im < m; ++im) {
      max[in][im] = DEFAULT_UNDEFINED_VALUE;
      allocation[in][im] = DEFAULT_UNDEFINED_VALUE;
      request[in][im] = DEFAULT_UNDEFINED_VALUE;
    }
  }

  for (int im = 0; im < m; ++im) {
    available[im] = DEFAULT_UNDEFINED_VALUE;
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
    ba::config_flag current_flag = ba::CF_INVALID;

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
          ba::config config_to_insert;
          config_to_insert.flag = current_flag;
          config_to_insert.value = new int[n];
          for (int i = 0; i < m; ++i) {
            config_to_insert.value[i] = std::stoi(parsed_elements[i]);
          }
          configuration.push_back(config_to_insert);
          //std::cout << "Added this data as a configuration for (flag = " << config_to_insert.flag << ")" << std::endl;
        } else {
          if (parsed_elements[0] == "Available") {
            current_flag = ba::CF_AVAILABLE;
            //std::cout << "FLAG SET TO AVALIABLE" << std::endl;
          } else if (parsed_elements[0] == "Max") {
            current_flag = ba::CF_MAX;
            //std::cout << "FLAG SET TO MAX" << std::endl;
          } else if (parsed_elements[0] == "Allocation") {
            current_flag = ba::CF_ALLOCATION;
            //std::cout << "FLAG SET TO ALLOCATION" << std::endl;
          } else if (parsed_elements[0] == "Requests" || parsed_elements[0] == "Request") {
            current_flag = ba::CF_REQUEST;
          }
          // Probably a keyword to define what we are looking for
        }
        // n and m are both set
      }
    }
    config_file.close();
  }
}

void banker_algorithm::init_parse_config() {
  // Loop through all the config stuff
  int mp = 0;
  int ap = 0;
  int rp = 0;
  for(ba::config c: configuration) {
    switch(c.flag) {
      case ba::CF_AVAILABLE:
        for (int i = 0; i < m; ++i) {
          this->available[i] = c.value[i];
        }
        break;
      case ba::CF_MAX:
        for (int i = 0; i < m; ++i) {
          this->max[mp][i] = c.value[i];
        }
        mp++;
        break;
      case ba::CF_ALLOCATION:
        for (int i = 0; i < m; ++i) {
          this->allocation[ap][i] = c.value[i];
        }
        ap++;
        break;
      case ba::CF_REQUEST:
        for (int i = 0; i < m; ++i) {
          this->request[rp][i] = c.value[i];
        }
        rp++;
        break;
    }
  }
}

bool banker_algorithm::init_validate_config() {

  // 1. Allocation <= Maximum
  for (int in = 0; in < n; ++in) {
    for (int im = 0; im < m; ++im) {
      if (allocation[in][im] > max[in][im]) {
        return false;
      }
    }
  }
  // 2. All of Allocation + Avaiable = Total


  return true;
}

bool banker_algorithm::valid(int &val) {
  return (val == DEFAULT_UNDEFINED_VALUE);
}

void banker_algorithm::print_status() {
  // Available
  std::cout << "Available = " << std::endl << "[";
  for (int im = 0; im < m; ++im) {
    if (im != m-1)
      std::cout << available[im] << ", ";
    else
    std::cout << available[im];

  }
  std::cout <<  "]" << std::endl;
  std::cout << std::endl;
  // Max
  std::cout << "Max = " << std::endl;
  for (int in = 0; in < n; ++in) {
      std::cout << "[";
      for (int im = 0; im < m; ++im) {
        std::string val = valid(max[in][im]) ? "~" : std::to_string(max[in][im]);
        if (im != m-1)
          std::cout << val << ", ";
        else
          std::cout << val;
      }
      std::cout << "]" << std::endl;
  }
  std::cout << std::endl;
  // Allocation
  std::cout << "Allocation = " << std::endl;
  for (int in = 0; in < n; ++in) {
      std::cout << "[";
      for (int im = 0; im < m; ++im) {
        std::string val =  valid(allocation[in][im]) ? "~" : std::to_string(allocation[in][im]);
        if (im != m-1)
          std::cout << val << ", ";
        else
        std::cout << val;
      }
      std::cout << "]" << std::endl;
  }
  std::cout << std::endl;
  // Request
  std::cout << "Request = " << std::endl;
  for (int in = 0; in < n; ++in) {
      std::cout << "[";
      for (int im = 0; im < m; ++im) {
        std::string val = valid(request[in][im]) ? "~" : std::to_string(request[in][im]);
        if (im != m-1)
          std::cout << val << ", ";
        else
        std::cout << val;
      }
      std::cout << "]" << std::endl;
  }
  std::cout << std::endl;
}

int banker_algorithm::run() {
  // Invalid configuration detected.
  if (!config_valid)
    return 1;

  switch(arg_handle.get_mode()) {
    case ba::BM_MANUAL:
      // Process inputs
      return run_manual();
    case ba::BM_AUTO:
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
    ba::command current = ba::parse(entry);

    // Identify what wer are trying to do..
    switch (current.action) {
      case ba::CA_REQUEST:
        break;
      case ba::CA_RELEASE:
        break;
      case ba::CA_END:
        manual_process_inputs = false;
        std::cout << "Program terminated." << std::endl;
        break;
      case ba::CA_STATUS:
        print_status();
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
