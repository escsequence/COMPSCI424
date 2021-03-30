/*******************************************************
 * Assignment 3
 * Created by James Johnston
 * Computer Science 424 (Operating Systems)
 * assignment3.cpp
 * This is the main method cpp file to run for the assignment.
********************************************************/
#include <iostream>
#include "banker_algorithm.h"

const bool VERBOSE_PRINTING = true; // Turn this off for less verbose data logged

int main(int argc, char** argv) {
  std::cout << "##########################################" << std::endl;
  std::cout << "####            Assignment 3          ####" << std::endl;
  std::cout << "####      THE BANKER'S ALGORITHM      ####" << std::endl;
  std::cout << "####    COMPSCI424 - James Johnston   ####" << std::endl;
  std::cout << "##########################################" << std::endl;
  //std::cout << std::endl;

  // Accept the argument data into our arg object
  arg arg_handle = arg(argc, argv);

  // Output the mode
  std::cout << "#### Mode = " << arg_handle.get_mode_str() << std::endl;
  std::cout << "#### File = " << arg_handle.get_file() << std::endl;
  std::cout << std::endl;

  if (arg_handle.verify_mode_and_file()) {
    // Run the program
    banker_algorithm ba = banker_algorithm(arg_handle, 1000, 2000);
    return ba.run();
  } else {
    // Print out some help in-case the user is having difficulty running the program.
    std::cout << "The mode and/or file are either not provided or invalid." << std::endl;
    std::cout << "Please re-run the application with 2 arguments." << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "Mode needs to be either \'auto\' or \'manual\'." << std::endl;
    std::cout << "File can be anything but blank." << std::endl;
    std::cout << "Command: ./program mode file" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "Example: ./a.out manual test2.txt" << std::endl << std::endl;
  }

  // Return 0 to end the program
  return 0;
}
