/*******************************************************
 * Assignment 1
 * Created by James Johnston
 * Computer Science 424 (Operating Systems)
 * assignment1.cpp
 * This is the main method cpp file to run.
********************************************************/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "version1.h"
#include "version2.h"
const int PROCESS_ARRAY_SIZE = 1000000; //Large size
version *v1, *v2; // Created an interface

/* Random function returns a random integer value */
int random(int min, int max) {
  return rand() % max + min;
}

/* Initalize our program */
void init(int n) {
  // Random number seed
  srand(time(NULL));

  // Create our two new versions of the PCB
  v1 = new version1();
  v2 = new version2();

  v1->init(n);
  v2->init(n);
}

void test0() {
  // Test to verify functionality
  std::cout << "[ ============ Test 0 ============ ]" << std::endl;
  std::cout << "| Verify results of the PCB types  |" << std::endl;
  std::cout << "| ---------- Version 1 ----------- |" << std::endl;
  std::cout << "cr[0] (first child of pcb[0]) ==> v1->create(0);" << std::endl;
  v1->create(0);
  std::cout << "cr[0] (second child of pcb[0]) ==> v1->create(0);" << std::endl;
  v1->create(0);
  std::cout << "cr[2] (first child of pcb[2]) ==> v1->create(2);" << std::endl;
  v1->create(2);
  std::cout << "cr[0] (third child of pcb[3]) ==> v1->create(0);" << std::endl;
  v1->create(0);

  std::cout << "Current status of PCBs for Version 1: ";
  v1->print();

  std::cout << std::endl << "de[0] (destroys all descendents of PCB[0]) ==> v1->destroy(0)" << std::endl;
  v1->destroy(0);

  std::cout << "Current status of PCBs for Version 1: " << std::endl;
  v1->print();

  std::cout << "| ---------- Version 2 ----------- |" << std::endl;
  std::cout << "cr[0] (first child of pcb[0]) ==> v2->create(0);" << std::endl;
  v2->create(0);
  std::cout << "cr[0] (second child of pcb[0]) ==> v2->create(0);" << std::endl;
  v2->create(0);
  std::cout << "cr[2] (first child of pcb[2]) ==> v2->create(2);" << std::endl;
  v2->create(2);
  std::cout << "cr[0] (third child of pcb[3]) ==> v2->create(0);" << std::endl;
  v2->create(0);

  std::cout << "Current status of PCBs for Version 2: ";
  v2->print();

  std::cout << std::endl << "de[0] (destroys all descendents of PCB[0]) ==> v2->destroy(0)" << std::endl;
  v2->destroy(0);

  std::cout << "Current status of PCBs for Version 2: " << std::endl;
  v2->print();
}


// Just create
void test1() {
  int amount_to_create = 25000;
  std::cout << "[ ============ Test 1 ============ ]" << std::endl;
  std::cout << "| Process creation time comparsion |" << std::endl;
  v1->clock_reset();
  for (int j = 0; j < amount_to_create; j++) {
    v1->create(j % 5);
  }
  v1->clock_print("Version 1\tTest 1");

  // Version 2
  v2->clock_reset();
  for (int j = 0; j < amount_to_create; j++) {
    v2->create(j % 5);
  }

  //v2->print();
  v2->clock_print("Version 2\tTest 1");
}

// Just destroy
void test2() {
  int amount_to_destroy = 10000;
  std::cout << std::endl;
  std::cout << "[ ============ Test 2 ============ ]" << std::endl;
  std::cout << "| Process deletion time comparsion |" << std::endl;
  v1->clock_reset();
  //v1->print();
  for (int j = amount_to_destroy; j >= 0; j--) {
    v1->destroy(j);
  }
  //v1->print();
  v1->clock_print("Version 1\tTest 2");

  // Version 2
  v2->clock_reset();
  //v2->print();
  for (int j = amount_to_destroy; j >= 0; j--) {
   v2->destroy(j);
  }
  //v2->print();
  v2->clock_print("Version 2\tTest 2");
}

// Mix and match
void test3() {
  int amount_to_create = 7500;
  std::cout << std::endl;
  std::cout << "[ ============ Test 3 ============ ]" << std::endl;
  std::cout << "| Mix and match time comparsion    |" << std::endl;
  v1->clock_reset();
  // Create 6 base PCB's
  v1->create(0);
  v1->create(1);
  v1->create(2);
  v1->create(3);
  v1->create(4);
  v1->create(5);

  // Loop through X amount of times and create random on either one of the nodes
  for (int j = 0; j < amount_to_create; j++) {
    v1->create(random(0, 5));
  }

  // Now delete half of them
  for (int j = amount_to_create; j <= amount_to_create / 2; j--) {
    v1->destroy(j);
  }

  // And create them again
  for (int j = amount_to_create / 2; j < amount_to_create*2; j++) {
    v1->create(random(0, 5));
  }

  // Destroy them all now
  for (int j = amount_to_create; j <= 0; j--) {
    v1->destroy(j);
  }
  v1->clock_print("Version 1\tTest 3");

  v2->clock_reset();
  // Create 6 base PCB's
  v2->create(0);
  v2->create(1);
  v2->create(2);
  v2->create(3);
  v2->create(4);
  v2->create(5);

  // Loop through X amount of times and create random on either one of the nodes
  for (int j = 0; j < amount_to_create; j++) {
    v2->create(random(0, 5));
  }

  // Now delete half of them
  for (int j = amount_to_create; j <= amount_to_create / 2; j--) {
    v2->destroy(j);
  }

  // And create them again
  for (int j = amount_to_create / 2; j < amount_to_create*2; j++) {
    v2->create(random(0, 5));
  }

  // Destroy them all now
  for (int j = amount_to_create; j <= 0; j--) {
    v2->destroy(j);
  }
  v2->clock_print("Version 2\tTest 3");
}

void run() {
  // Test0 is for verification of the data - for testing, run this by itseslf!!
  //test0();

  // Test 1 is for adding A TON of PCBs
  test1();

  // Test 2 is for removing a TON of PCBs
  test2();

  // Test 3 is for adding, deleting half-way, then removing all
  test3();
}


int main() {

  // Initalize our array
  init(PROCESS_ARRAY_SIZE);

  // Run the tests
  run();

  // Return 0 to end the program
  return 0;
}
