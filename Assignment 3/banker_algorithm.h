#ifndef BANKER_ALGORITHM_H
#define BANKER_ALGORITHM_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
#include "arg.h"
#include "ba.h"

class banker_algorithm {
private:
  // This value is the default value our array items are set to
  const int DEFAULT_UNDEFINED_VALUE = INT_MIN;

  ba::state *current_state;
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

  void trigger_request(int i, int j, int k);
  void trigger_release(int i, int j, int k);

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
