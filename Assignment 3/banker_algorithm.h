#ifndef BANKER_ALGORITHM_H
#define BANKER_ALGORITHM_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "arg.h"
#include "command_parser.h"

class banker_algorithm {
private:
  int* available;
  int** max;
  int** allocation;
  int** request;
  int n, m;
  arg arg_handle;
  std::vector<ba_config::config> configuration;

  void init(), init_load_config(), init_parse_config(), init_setup_array();

  int run_auto(), run_manual();

  void print_status();

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
