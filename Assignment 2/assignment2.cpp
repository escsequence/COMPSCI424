/*******************************************************
 * Assignment 2
 * Created by James Johnston
 * Computer Science 424 (Operating Systems)
 * assignment2.cpp
 * This is the main method cpp file to run.
********************************************************/
#include <iostream>
#include "bounded_buffer_mutex.h"
const bool DEBUG_PRINT = true; // Turn this off for less verbose data logged

int main() {

  std::cout << "##########################################" << std::endl;
  std::cout << "####            Assignment 2          ####" << std::endl;
  std::cout << "####           BOUNDED BUFFER         ####" << std::endl;
  std::cout << "####    COMPSCI424 - James Johnston   ####" << std::endl;
  std::cout << "##########################################" << std::endl;
  std::cout << std::endl;

  // Create our bounded buffer object (bounded_buffer.h)
  bounded_buffer bb_main = bounded_buffer(20, 5, 5, DEBUG_PRINT);

  // Run the assignment
  bb_main.run();

  // Return 0 to end the program
  return 0;
}
