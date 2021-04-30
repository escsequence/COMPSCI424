/*******************************************************
 * Assignment 4
 * Created by James Johnston
 * Computer Science 424 (Operating Systems)
 * assignment4.cpp
 * This is the main method cpp file to run for the assignment.
********************************************************/
#include "replacement_algorithm.h"

int main(int argc, char** argv) {
  std::cout << "##########################################" << std::endl;
  std::cout << "####            Assignment 4          ####" << std::endl;
  std::cout << "####    COMPSCI424 - James Johnston   ####" << std::endl;
  std::cout << "##########################################" << std::endl;

  // Create an instance of the program
  ra_program prg;

  // Return the program return value
  return prg.run();
}
