#ifndef BANKER_ALGORITHM_H
#define BANKER_ALGORITHM_H
#include <iostream>
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

  int run_auto(), run_manual();

  // Manual
  bool manual_process_inputs;

  // Auto
public:
  banker_algorithm(arg a, int m, int n) {
    // Store these for de-allocation later
    this->n = n;
    this->m = m;

    // Arguments passed in from the main method
    this->arg_handle = a;

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
