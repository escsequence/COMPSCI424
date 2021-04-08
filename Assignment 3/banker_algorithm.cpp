#include "banker_algorithm.h"

void banker_algorithm::init() {

  // Load the configuration so we can set the n and m variables
  init_load_config();

  // Setup our state
  current_state = new ba::state(this->n, this->m);

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
          this->current_state->available[i] = c.value[i];
        }
        break;
      case ba::CF_MAX:
        for (int i = 0; i < m; ++i) {
          this->current_state->max[mp][i] = c.value[i];
        }
        mp++;
        break;
      case ba::CF_ALLOCATION:
        for (int i = 0; i < m; ++i) {
          this->current_state->allocation[ap][i] = c.value[i];
        }
        ap++;
        break;
      case ba::CF_REQUEST:
        for (int i = 0; i < m; ++i) {
          this->current_state->request[rp][i] = c.value[i];
        }
        rp++;
        break;
    }
  }
}

bool banker_algorithm::init_validate_config() {
  return validate_state(this->current_state);
}

bool banker_algorithm::validate_state(ba::state *s) {
  // 1. Allocation <= Maximum
  for (int in = 0; in < n; ++in) {
    for (int im = 0; im < m; ++im) {
      if (s->allocation[in][im] > s->max[in][im]) {
        return false;
      }
    }
  }
  // 2. All of Allocation + Avaiable = Total
  for (int rm = 0; rm < m; ++rm) {
    int alloc = 0;
    for (int in = 0; in < n; ++in) {
      for (int im = 0; im < m; ++im) {
        //if (s->allocation[in][im] > s->max[in][im]) {
          //return false;
        alloc += s->allocation[in][im];
      }
    }
    s->total[rm] = alloc + s->available[rm];
  }


  return true;
}

bool banker_algorithm::valid(int &val) {
  return (val != DEFAULT_UNDEFINED_VALUE);
}

void banker_algorithm::print_state(ba::state *s) {
  // Available
  std::cout << "Available = " << std::endl << "[";
  for (int im = 0; im < s->m; ++im) {
    if (im != m-1)
      std::cout << s->available[im] << ", ";
    else
    std::cout << s->available[im];

  }
  std::cout <<  "]" << std::endl;
  std::cout << std::endl;
  std::cout << "Total = " << std::endl << "[";
  for (int im = 0; im < s->m; ++im) {
    if (im != m-1)
      std::cout << s->total[im] << ", ";
    else
    std::cout << s->total[im];

  }
  std::cout <<  "]" << std::endl;
  std::cout << std::endl;
  // Max
  std::cout << "Max = " << std::endl;
  for (int in = 0; in < s->n; ++in) {
      std::cout << "[";
      for (int im = 0; im < s->m; ++im) {
        std::string val = valid(s->max[in][im]) ? std::to_string(s->max[in][im]) : "~";
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
  for (int in = 0; in < s->n; ++in) {
      std::cout << "[";
      for (int im = 0; im < s->m; ++im) {
        std::string val =  valid(s->allocation[in][im]) ? std::to_string(s->allocation[in][im]) : "~";
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
  for (int in = 0; in < s->n; ++in) {
      std::cout << "[";
      for (int im = 0; im < s->m; ++im) {
        std::string val = valid(s->request[in][im]) ? std::to_string(s->request[in][im]) : "~";
        if (im != m-1)
          std::cout << val << ", ";
        else
        std::cout << val;
      }
      std::cout << "]" << std::endl;
  }
  std::cout << std::endl;
  // Potential
  std::cout << "Potential = " << std::endl;
  for (int in = 0; in < s->n; ++in) {
      std::cout << "[";
      for (int im = 0; im < s->m; ++im) {
        int po_val = s->potential(in, im);
        std::string val = valid(po_val) ? std::to_string(po_val) : "~";
        if (im != m-1)
          std::cout << val << ", ";
        else
        std::cout << val;
      }
      std::cout << "]" << std::endl;
  }
  std::cout << std::endl;
}

void banker_algorithm::print_status() {
  print_state(current_state);
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
    //ba::state* tmp_state = NULL;
    switch (current.action) {
      case ba::CA_REQUEST:
        //tmp_state = request(current.i, current.j, current.k);

        if (request(current_state, current.i, current.j, current.k)) {
          ba::log(ba::LF_REQUEST, arg_handle.get_mode(), current, true);
          temp_state->aquire(current.i, current.j, current.k);
          current_state = temp_state;
        } else {
          ba::log(ba::LF_REQUEST, arg_handle.get_mode(), current, false);
        }
        break;
      case ba::CA_RELEASE:
        // Validate the data is okay to be releasedd
        if (valid_release(current_state, current.i, current.j, current.k)) {
          // Yep, so now release it.
          current_state->release(current.i, current.j, current.k);
          ba::log(ba::LF_RELEASE, arg_handle.get_mode(), current, true);
        } else {
          ba::log(ba::LF_RELEASE, arg_handle.get_mode(), current, false);
        }
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

bool banker_algorithm::dl_available(ba::state *state, int process) {
  bool fl = true;
  for (int i = 0; i < state->m; ++i) {
    //std::cout << "Potential[" << process << "][" << i << "] = " << state->potential(process, i) << std::endl;
    //std::cout << "Available[" << i << "] = " << state->available[i] << std::endl;
    fl = (state->potential(process, i) > state->available[i]) ? false : fl;
  }
  return fl;
}

void banker_algorithm::dl_safe(bool marked[], ba::state *state, std::vector<int> safe) {
  // Loop through all the processes
  for (int in = 0; in < state->n; ++in) {
    //std::cout << "marked[" << in << "] = " << marked[in] << std::endl;
    if (!marked[in] && dl_available(state, in)) {

      marked[in] = true;

      for (int im = 0; im < state->m; ++im)
        state->available[im] += state->allocation[in][im];

      safe.push_back(in);
      dl_safe(marked, state, safe);
      safe.pop_back();

      marked[in] = false;

      for (int im = 0; im < state->m; ++im)
        state->available[im] -= state->allocation[in][im];
    }
  }
  //std::cout << "Safe size = " << safe.size() << std::endl;
  if (safe.size() == this->m) {
    dl_tmp_total++;
  }

}



bool banker_algorithm::deadlock_detect(ba::state *state) {
  std::vector<int> safe;
  this->dl_tmp_total = 0;
  bool marked[state->n];
  memset(marked, false, sizeof(marked));
  dl_safe(marked, state, safe);
  //std::cout << "dl_tmp_total = " << dl_tmp_total << std::endl;
  return dl_tmp_total == 0;
}

bool banker_algorithm::request(ba::state *s, int i, int j, int k) {
  // We mirror our state into a temporary state
  temp_state = new ba::state(*current_state);

  if (temp_state->requestr(i, j, k)) {
    ba::state *tmp = new ba::state(*temp_state);
    tmp->aquire(i, j, k);
    return !deadlock_detect(tmp);
  }
  return false;
}

bool banker_algorithm::valid_release(ba::state *s, int i, int j, int k) {
  return ((i <= s->allocation[k][j]) && (i >= 0));
}
