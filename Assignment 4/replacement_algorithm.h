#ifndef REPLACEMENT_ALGORITHM_H
#define REPLACEMENT_ALGORITHM_H
#include <iostream>
#include <stdio.h>
#include "ra.h"
#include "ra_fifo.h"
#include "ra_lru.h"
#include "ra_opt.h"
class ra_program {
  private:
    /**
     * Returns a random value.
     * Make sure to call srand(value) ahead of time!
     *
     * @param min Minimum starting value
     * @param max Maximum ending value
     * @return Random value
     */
    int random(int min, int max);

    /**
     * Returns an array of size provided, each value inside the array is random (min-max).
     * Make sure to call srand(value) ahead of time!
     *
     * ex: random_array(1, 2, 5) => {1, 1, 2, 2, 1}
     *
     * @param min Minimum starting value for each item
     * @param max Maximum ending value for each item
     * @return Array with random values
     */
    int* random_array(int min, int max, int size);

    /**
     * Converts an int array to a string.
     *
     * ex: int v[] = {1, 1, 2, 2, 1};
     * ex: int_array_to_string(v, 5) => "11221"
     *
     * @param arr Integer array to convert
     * @param size Size of the integer array to convert
     * @return String conversion of the integer array
     */
    std::string int_array_to_string(int arr[], int size);

  public:

    /**
     * Constructor for the program, calculates a random seed
     */
    ra_program() {
      srand(time(NULL));
    }

    /**
     * Runs the program.
     *
     * @return Return code for the program, if successful or not
     */
    int run();
};


#endif
