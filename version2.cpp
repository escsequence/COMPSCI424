/*******************************************************
 * Assignment 1
 * Created by James Johnston
 * Computer Science 424 (Operating Systems)
 * version2.cpp
 * This is the second version of the PCB, this should be faster and it does not use linked lists
********************************************************/
#include "version2.h"

void version2::init(int n) {

  // Reset the clock for logging
  clock_reset();

  // Initalize our PCB memory allocation
  pcb = new PCB2[n];

  // Create the root PCB object
  create_root();

  // Keep track of our maximum amount of memory slots
  max = n;

  // Log information about the version
  clock_print("Version 2\t Initalization");
}

void version2::create_root() {
  // Create a new PCB object
  PCB2 root = PCB2();
  root.parent = PCB_STATUS::ROOT;
  root.first_child = PCB_STATUS::NOT_SET;
  root.younger_sibling = PCB_STATUS::NOT_SET;
  root.older_sibling = PCB_STATUS::NOT_SET;

  // Place it in memory
  pcb[0] = root;
}

/**
 * Returns the next value q
 */
int version2::get_next() {
  for (int i = 0; i < max; ++i) {
    if (pcb[i].parent == PCB_STATUS::NOT_SET)
      return i;
  }
  return PCB_STATUS::ROOT;
}

void version2::create(int p) {

  // Create our new PCB object
  PCB2 new_pcb = PCB2();
  // Assign the parent
  new_pcb.parent = p;

  // No first child or younger sibling because this is thw newest
  new_pcb.first_child = PCB_STATUS::NOT_SET;
  new_pcb.younger_sibling = PCB_STATUS::NOT_SET;

  // Get the next q memory location
  int q = get_next();

  // Check to see if the first child has been assigned
  if (pcb[p].first_child == PCB_STATUS::NOT_SET) {

    // No first child exists for this element, no need to append a older/younger situation
    new_pcb.older_sibling = PCB_STATUS::NOT_SET;

    // The first child is this one.
    pcb[p].first_child = q;

  } else {
    // A child exists
    // We get the first child pos
    int first_child = pcb[p].first_child;

    // Create a pointer so we can get the youngest
    PCB2 *newest_child = &pcb[first_child];

    // Create a pos tracker
    int newest_pos = first_child;

    // Loop through until we find the youngest
    while(newest_child->younger_sibling != PCB_STATUS::NOT_SET) {
      newest_pos = newest_child->younger_sibling;
      newest_child = &pcb[newest_pos];
    }

    // Set the younger sibling to us
    newest_child->younger_sibling = q;

    // Set the new PCB older to the old "youngest"
    new_pcb.older_sibling = newest_pos;
  }

  pcb[q] = new_pcb;
}

bool version2::exists(int p) {
  return pcb[p].parent != PCB_STATUS::NOT_SET;
}

void version2::destroy(int p) {
  if (exists(p)) {
    // PCB2 *top = pcb[p];
    int older_sibling = pcb[p].older_sibling;
    int younger_sibling = pcb[p].younger_sibling;
    int parent = pcb[p].parent;
    int first_child = pcb[p].first_child;


    // There are children, do stuff with the child nodes
    while(pcb[p].first_child != PCB_STATUS::NOT_SET) {
      destroy(pcb[p].first_child);
    }

    if (parent != PCB_STATUS::NOT_SET) {
      // Parent exists
      if (pcb[parent].first_child == p) {
        if (younger_sibling != PCB_STATUS::NOT_SET) {
          // Item is the first child, there should be no older sibling that exists for this one
          pcb[parent].first_child = younger_sibling;
          pcb[younger_sibling].older_sibling = PCB_STATUS::NOT_SET;
        } else {
          pcb[parent].first_child = PCB_STATUS::NOT_SET;
          // Just delete the first child of the parent since there are no other siblings
        }
      } else {
        // Could be in the middle or oldest?
        if (older_sibling != PCB_STATUS::NOT_SET && younger_sibling != PCB_STATUS::NOT_SET) {
          // somewhere in the middle
          pcb[older_sibling].younger_sibling = younger_sibling;
          pcb[younger_sibling].older_sibling = older_sibling;
        } else {
          // The oldest one
          pcb[younger_sibling].older_sibling = PCB_STATUS::NOT_SET;
        }
      }
    }
    pcb[p] = PCB2();
  }
}

void version2::print() {
  int pcb_count = 0;

  for (int i = 0; i < max; ++i) {
    if (pcb[i].parent != PCB_STATUS::NOT_SET) {
      pcb_count++;
      int older_sibling = pcb[i].older_sibling;
      int younger_sibling = pcb[i].younger_sibling;
      int parent = pcb[i].parent;
      int first_child = pcb[i].first_child;

      std::cout << std::endl << std::endl << "[" << i << "] => (";
      if (older_sibling != PCB_STATUS::NOT_SET)
        std::cout << "os = " << older_sibling << ", ";
      else
        std::cout << "os = NONE, ";

      if (younger_sibling != PCB_STATUS::NOT_SET)
        std::cout << "ys = " << younger_sibling << ", ";
      else
        std::cout << "ys = NONE, ";

      if (parent != PCB_STATUS::ROOT)
        std::cout << "p = " << parent << ", ";
      else
        std::cout << "p = ROOT, ";

      if (first_child != PCB_STATUS::NOT_SET)
        std::cout << "fc = " << first_child << " ";
      else
        std::cout << "fc = NONE ";

      std::cout << ")";
    }
  }

  if (pcb_count < 1) {
    std::cout << std::endl << "Empty PCB array." << std::endl;
  }

  std::cout << std::endl;
}
