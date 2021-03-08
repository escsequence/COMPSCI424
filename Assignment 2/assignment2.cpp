/*******************************************************
 * Assignment 1
 * Created by James Johnston
 * Computer Science 424 (Operating Systems)
 * assignment1.cpp
 * This is the main method cpp file to run.
********************************************************/
#include <iostream>
#include "bounded_buffer.h"


int main() {

  std::cout << "##########################################" << std::endl;
  std::cout << "####            Assignment 2          ####" << std::endl;
  //std::cout << "####           PCB COMPARERER         ####" << std::endl;
  std::cout << "####    COMPSCI424 - James Johnston   ####" << std::endl;
  std::cout << "##########################################" << std::endl;
  std::cout << std::endl;

  // Initalize our array
  //init(PROCESS_ARRAY_SIZE);
  //std::cout << std::endl;

  bounded_buffer bb_main = bounded_buffer(20, 5, 5);
  bb_main.run();

  // Return 0 to end the program
  return 0;
}
