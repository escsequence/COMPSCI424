#ifndef VERSION_H
#define VERSION_H
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <iomanip>

class version {
protected:
  clock_t t;
public:

  void clock_reset() {
    t = clock();
  }

  void clock_print(std::string msg) {
    t = clock() - t;
    std::cout << std::fixed << std::showpoint;
    std::cout << msg << " took (" << std::setprecision(8) << ((float)t)/CLOCKS_PER_SEC << " seconds)" << std::endl;
  }

  virtual void init(int n) = 0;
  virtual void create(int p) = 0;
  virtual void destroy(int p) = 0;
  virtual void print() = 0;
  virtual bool exists(int p) = 0;
};
#endif
