/*******************************************************
 * Assignment 1
 * Created by James Johnston
 * Computer Science 424 (Operating Systems)
 * version1.h
 * Version 1
********************************************************/
#ifndef VERSION1_H
#define VERSION1_H
#include "version.h"
#include <list>

// PCB structure for Version 1
struct PCB {
    int parent = PCB_STATUS::NOT_SET;
    std::list<int> children;
};

class version1 : public version {
private:
  // Array of PCB items
  PCB *pcb;

  // Maximum position, this is just "n" when we call init
  int max;
public:
  // Define our functions that
  void init(int n), create(int p), destroy(int p);

  version1() {}
  ~version1() {}

  void print(), create_root();
  int get_next();
  bool exists(int p);
};

#endif
