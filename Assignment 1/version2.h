/*******************************************************
 * Assignment 1
 * Created by James Johnston
 * Computer Science 424 (Operating Systems)
 * version2.h
 * Version 2
********************************************************/
#ifndef VERSION2_H
#define VERSION2_H
#include "version.h"
#include <list>

// PCB structure for Version 2
struct PCB2 {
    int parent = PCB_STATUS::NOT_SET;
    int first_child = PCB_STATUS::NOT_SET;
    int younger_sibling = PCB_STATUS::NOT_SET;
    int older_sibling = PCB_STATUS::NOT_SET;
};

class version2 : public version {
private:
  PCB2 *pcb;
  int max;
public:
  void init(int n), create(int p), destroy(int p);

  version2() {}
  ~version2() {}

  void print(), create_root();
  int get_next();
  bool exists(int p);
};

#endif
