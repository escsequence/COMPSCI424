#ifndef BANKER_ALGORITHM_H
#define BANKER_ALGORITHM_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
#include <vector>
#include <cstring>
#include "arg.h"
#include "ba.h"

class banker_algorithm {
private:
  // This value is the default value our array items are set to
  const int DEFAULT_UNDEFINED_VALUE = INT_MIN;

  ba::state *current_state;
  ba::state *temp_state;
  int n, m;

  // Argument package handler that holds the argument values
  arg arg_handle;

  // Configuration array of configuration entries from the file
  std::vector<ba::config> configuration;

  void init(), init_setup_array();

  // Configuration
  void init_load_config(), init_parse_config();
  bool init_validate_config();
  bool config_valid;

  int run_auto(), run_manual();

  // State stuff
  bool validate_state(ba::state *s);
  void print_state(ba::state *s);

  void print_status();

  bool deadlock_detect(ba::state *state);
  void dl_safe(bool marked[], ba::state *state, std::vector<int> safe);
  bool dl_available(ba::state *state, int process);
  int dl_tmp_total;

  bool request(ba::state *s, int i, int j, int k);
  bool valid_release(ba::state *s, int i, int j, int k);

  bool valid(int &val);

  // Manual
  bool manual_process_inputs;

  // Auto
public:
  banker_algorithm(arg a) {
    // Arguments passed in from the main method
    this->arg_handle = a;

    // Set up the vector for the configuration
    configuration = std::vector<ba::config>();

    // Run the initialize command
    this->init();

  }

  int run();
};
#endif
