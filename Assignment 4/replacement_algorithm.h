#ifndef REPLACEMENT_ALGORITHM_H
#define REPLACEMENT_ALGORITHM_H
#include <iostream>
#include <stdio.h>
#include "ra.h"
#include "ra_fifo.h"
#include "ra_lru.h"
class ra_program {
  private:
    // Randomization functionality
    int random(int min, int max);
    int* random_array(int min, int max, int size);
    std::string int_array_to_string(int arr[], int size);

  public:
    ra_program() {
      srand(time(NULL));
    }

    int run();
};


#endif
