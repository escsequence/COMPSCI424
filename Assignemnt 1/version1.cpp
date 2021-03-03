/*******************************************************
 * Assignment 1
 * Created by James Johnston
 * Computer Science 424 (Operating Systems)
 * version1.cpp
 * Version 1 - This is the first design of the PCBs, uses a linked list.
********************************************************/
#include "version1.h"

void version1::init(int n) {

  // Reset the clock for logging
  clock_reset();

  // Initalize our PCB memory allocation
  pcb = new PCB[n];

  // Create the root PCB object
  create_root();

  // Keep track of our maximum amount of memory slots
  max = n;

  // Log information about the version
  clock_print("Version 1\t Initalization");
}

/**
 * We create a root object so we can insert PCB objects at the very top
 */
void version1::create_root() {

  /// New PCB object
  PCB root = PCB();

  // Parent is set to the root
  root.parent = PCB_STATUS::ROOT;

  // Empty children list
  root.children = std::list<int>();

  // Place it in memory
  pcb[0] = root;
}

/**
 * This function will try and find the next best avaliable memory location.
 * We just loop through the memory addresses and find the next one that is "open"
 */
int version1::get_next() {
  for (int i = 0; i < max; ++i) {
    if (pcb[i].parent == PCB_STATUS::NOT_SET)
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
  return pcb[p].parent != PCB_STATUS::NOT_SET;
}

void version1::destroy(int p) {
  pcb[p].parent = PCB_STATUS::NOT_SET;
  for(int n : pcb[p].children) {
    destroy(n);
  }
  pcb[p].children.clear();
}

void version1::print() {
  int pcb_count = 0;
  for (int i = 0; i < max; ++i) {
    if (pcb[i].parent != PCB_STATUS::NOT_SET) {
      pcb_count++;
      std::cout << std::endl << "[" << i << "] -> (";

      for(int n : pcb[i].children) {
        std::cout << n << ",";
      }

      std::cout << ")" << std::endl;
    }
  }
  if (pcb_count < 1) {
    std::cout << std::endl << "Empty PCB array." << std::endl;
  }
}
