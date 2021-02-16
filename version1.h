#ifndef VERSION1_H
#define VERSION1_H
#include "version.h"
#include <list>

struct PCB {
    int parent = -1;
    std::list<int> children;
};

class version1 : public version {
private:
  PCB *pcb;
  int max;
public:
  void init(int n), create(int p), destroy(int p);

  version1() {

  }
  ~version1() {

  }

  void print();
  int get_next();
  bool exists(int p);
};

#endif
