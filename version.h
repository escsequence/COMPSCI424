/*******************************************************
 * Assignment 1
 * Created by James Johnston
 * Computer Science 424 (Operating Systems)
 * version.h
 * This is an interface for version objects. This class takes the structure for how
 * a version should operate.
********************************************************/
#ifndef VERSION_H
#define VERSION_H
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <iomanip>

// The PCB statuses are defined so we know if an element is at the "root" or does not exist
enum PCB_STATUS {
  NOT_SET = -2,
  ROOT = -1
};

class version {
protected:
  clock_t t;
public:

  // Resets the clock (should be done before a test is done)
  void clock_reset() {
    t = clock();
  }

  // Prints the time it took, does not reset the clock (this has to be done manually)
  void clock_print(std::string msg) {
    t = clock() - t;
    std::cout << std::fixed << std::showpoint;
    std::cout << msg << " took (" << std::setprecision(8) << ((float)t)/CLOCKS_PER_SEC << " seconds)" << std::endl;
  }

  // Our abstract functions that will need to be defined in our main classes
  virtual void init(int n) = 0;
  virtual void create(int p) = 0;
  virtual void destroy(int p) = 0;
  virtual void print() = 0;
  virtual bool exists(int p) = 0;
};
#endif
