#include "banker_algorithm.h"
std::mutex mtx;

/**
 * Random method to randomize junk.
 * Uses a distrubtion generator.
 */
int random(int min, int max) {
    thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

/**
 * Initalization of all the processes, called in the constructor.
 */
void banker_algorithm::init() {

  // Random seed
  srand(time(NULL));

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

/**
 * Loads the configuration file in our config object.
 */
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

/**
 * Parses the configuration data we loaded into our current_state.
 */
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

/**
 * Validates the configuration data loaded from the file.
 * @return bool If the configuration information is valid.
 */
bool banker_algorithm::init_validate_config() {
  return validate_state(this->current_state);
}

/**
 * Validates the state specified.
 * @param s A state of the bankers algorithm.
 * @return bool State is valid, allocation isn't greater than the maximum.
 */
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

/**
 * Determines whether the value passed in is a array data information (NOT DEFAULT_UNDEFINED_VALUE).
 * @param &val Values to analyze.
 * @return bool If the value is NOT DEFAULT_UNDEFINED_VALUE
 */
bool banker_algorithm::valid(int &val) {
  return (val != DEFAULT_UNDEFINED_VALUE);
}

/**
 * Prints the state spcified.
 * @param s A state to print out to the console.
 */
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

/**
 * Calls print_state on our current_state. (Prints our current state)
 */
void banker_algorithm::print_status() {
  print_state(current_state);
}

/**
 * Runs either manual or automatic mode, engages the bankers algorithm program.
 * @return int Return value for the main method, successful run for 0.
 */
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

/**
 * Our run method for the manual mode of operation.
 * @return int Return value for the main method, successful run for 0.
 */
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
        if (request(current_state, current.i, current.j, current.k)) {
          ba::log(ba::LF_REQUEST, arg_handle.get_mode(), current, true);
          //temp_state->aquire(current.i, current.j, current.k);
          if (current_state->requestr(current.i, current.j, current.k)) {
            current_state->aquire(current.i, current.j, current.k);
          } else {
            ba::log(ba::LF_REQUEST, arg_handle.get_mode(), current, false);
          }
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

/**
 * Engages the auto thread execution for the automatic mode.
 * @param int Current process/thread being run.
 */
void banker_algorithm::auto_thread_run(int thread_id) {
  int random_command_count = 3; // Amount of requests / releases
  int current_command_num = 0; // Current set of actions we are on

  // While there are less commands then we want
  while(current_command_num < random_command_count) {

    // Current command we are working on
    ba::command current_command;

    // Was the request generated?
    bool request_generated = false;

    // While the request hasn't been successfully generated yet.
    while(!request_generated) {

      // Lock the mutex
      mtx.lock();

      // Determine a random value for our action
      int j = random(0, current_state->m - 1);
      int k = thread_id;
      int i = random(0, current_state->available[j]);

      // Assign the values of our random values
      current_command.j = j;
      current_command.k = k;
      current_command.i = i;

      // Try to request
      if (request(current_state, i, j, k)) {
        // Went through, now try and assign it to our current state.
        if (current_state->requestr(current_command.i, current_command.j, current_command.k)) {
          current_state->aquire(current_command.i, current_command.j, current_command.k);
          ba::log(ba::LF_REQUEST, arg_handle.get_mode(), current_command, true, thread_id);
          request_generated = true;
          mtx.unlock();
        } else {
          // Error.
          ba::log(ba::LF_REQUEST, arg_handle.get_mode(), current_command, false, thread_id);
          int wait_before_retry = random(1000, 3000);
          //std::cout << "Thread " << thread_id << " - Sleeping for " << wait_before_retry << std::endl;
          mtx.unlock();
          std::this_thread::sleep_for(std::chrono::milliseconds(wait_before_retry));
        }
      } else {
        ba::log(ba::LF_REQUEST, arg_handle.get_mode(), current_command, false, thread_id);
        int wait_before_retry = random(1000, 3000);
        //std::cout << "Thread " << thread_id << " - Sleeping for " << wait_before_retry << std::endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(wait_before_retry));
      }
    }

    mtx.lock();
    int wait_before_release = random(1000, 3000);
    mtx.unlock();

    std::this_thread::sleep_for(std::chrono::milliseconds(wait_before_release));


    mtx.lock();
    if (valid_release(current_state, current_command.i, current_command.j, current_command.k)) {
      // Yep, so now release it.
      current_state->release(current_command.i, current_command.j, current_command.k);
      ba::log(ba::LF_RELEASE, arg_handle.get_mode(), current_command, true, thread_id);
    } else {
      ba::log(ba::LF_RELEASE, arg_handle.get_mode(), current_command, false, thread_id);
    }
    mtx.unlock();

    // Increment current command value
    current_command_num++;
  }
}

/**
 * Our run method for the automatic mode of operation.
 * @return int Return value for the main method, successful run for 0.
 */
int banker_algorithm::run_auto() {
  // Yet to be developed.
  int process_count = current_state->n;
  std::thread process_thread[process_count];
  //
  for (int i = 0; i < process_count; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    process_thread[i] = std::thread(&banker_algorithm::auto_thread_run, this, i);
  }

  for (int i = 0; i < process_count; ++i) {
    process_thread[i].join();
  }

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
    if (!marked[in] && dl_available(state, in)) {

      // Mark the process
      marked[in] = true;

      // Loop through our resources and change the availability based on the allocations
      for (int im = 0; im < state->m; ++im)
        state->available[im] += state->allocation[in][im];

      // Push the process back to our safe vector
      safe.push_back(in);

      // Call the same function
      dl_safe(marked, state, safe);

      // Pop the safe vector
      safe.pop_back();

      // Now mark it as not safe
      marked[in] = false;

      // Loop through our resources and change the availability based on the allocations
      for (int im = 0; im < state->m; ++im)
        state->available[im] -= state->allocation[in][im];
    }
  }

  // Check to see if we have an safe paths
  if (safe.size() == this->m) {

    // If so, then our deadlock tmp total gets incrementedd
    dl_tmp_total++;

  }
}

bool banker_algorithm::deadlock_detect(ba::state *state) {
  // Create a vector of safe processes
  std::vector<int> safe;

  // Set our tmp total to 0
  this->dl_tmp_total = 0;

  // Create a bool array
  bool marked[state->n];
  memset(marked, false, sizeof(marked));

  // Run our function to check if the deadload is safe
  dl_safe(marked, state, safe);

  // Return if there are still 0 safe paths
  return dl_tmp_total == 0;
}

bool banker_algorithm::request(ba::state *s, int i, int j, int k) {
  // We mirror our state into a temporary state
  ba::state *tmp = new ba::state(*current_state);

  if (tmp->requestr(i, j, k)) {
    tmp->aquire(i, j, k);
    return !deadlock_detect(tmp);
  }
  return false;
}

/**
 * If the data passed in is a valid release
 * @param *s The state to find a deadlock in.
 * @param i Resource Amount.
 * @param j Resource id.
 * @param k Process id.
 * @return bool If the values are within the allocation data.
 */
bool banker_algorithm::valid_release(ba::state *s, int i, int j, int k) {
  return ((i <= s->allocation[k][j]) && (i >= 0));
}
