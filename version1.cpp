#include "version1.h"

void version1::init(int n) {
  // Reset the clock for logging
  clock_reset();

  // Create our new list of PCB array chunks
  pcb = new PCB[n];


  // Create the root PCB object
  PCB root = PCB();
  root.parent = 0;
  root.children = std::list<int>();
  pcb[0] = root;

  max = n;

  clock_print("Version 1\t Initalization");
}

/**
 * Returns the next value q
 */
int version1::get_next() {
  for (int i = 0; i < max; ++i) {
    if (pcb[i].parent == -1)
      return i;
  }
  return 0;
}

void version1::create(int p) {
  PCB new_pcb = PCB();

  int q = get_next();
  PCB current = pcb[p];

  new_pcb.parent = p;
  new_pcb.children = std::list<int>();

  pcb[q] = new_pcb;
  pcb[p].children.push_back(q);

  // Debug printing
  //std::cout << q << "->";
  //std::cout << p << std::endl;

}

bool version1::exists(int p) {
  return pcb[p].parent != -1;
}

void version1::destroy(int p) {
  pcb[p].parent = -1;
  for(int n : pcb[p].children) {
    destroy(n);
  }
  pcb[p].children.clear();
}

void version1::print() {
  for (int i = 0; i < max; ++i) {
    if (pcb[i].parent != -1 && !pcb[i].children.empty()) {
      std::cout << std::endl << std::endl << "[" << i << "] -> (";

      for(int n : pcb[i].children) {
        std::cout << n << ",";
      }

      std::cout << ")";
    }
  }
}
