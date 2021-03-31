#ifndef BANKER_ALGORITHM_H
#define BANKER_ALGORITHM_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
#include "arg.h"
#include "command_parser.h"

class banker_algorithm {
private:
  // This value is the default value our array items are set to
  const int DEFAULT_UNDEFINED_VALUE = INT_MIN;

  // Arrays
  int* available;
  int** max;
  int** allocation;
  int** request;

  // n and m are stored for use to define the array sizes
  int n, m;

  // Argument package handler that holds the argument values
  arg arg_handle;

  // Configuration array of configuration entries from the file
  std::vector<ba_config::config> configuration;

  void init(), init_load_config(), init_parse_config(), init_setup_array();
  void reload_config();

  int run_auto(), run_manual();

  void print_status();

  bool valid(int &val);

  // Manual
  bool manual_process_inputs;

  // Auto
public:
  banker_algorithm(arg a) {
    // Arguments passed in from the main method
    this->arg_handle = a;

    // Set up the vector for the configuration
    configuration = std::vector<ba_config::config>();

    // Run the initialize command
    this->init();

  }

  // Remove our access to these resources
  ~banker_algorithm() {
    for (int i = 0 ; i < n; ++i) {
        delete[] max[i];
        delete[] allocation[i];
        delete[] request[i];
      }
      delete[] available;
      delete[] max;
      delete[] allocation;
      delete[] request;
  }

  int run();
};
#endif
