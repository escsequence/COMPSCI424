#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "version1.h"
const int PROCESS_ARRAY_SIZE = 100000;
version *v1, *v2;


int random(int min, int max) {
  return rand() % max + min;
}

void init(int n) {
  // Random number seed
  srand(time(NULL));

  v1 = new version1();
  //v2 = new version1();

  v1->init(n);
  //v2->init(n);
}


// Just create
void test1() {
  int amount_to_create = 10000;
  std::cout << "[ ============ Test 1 ============ ]" << std::endl;
  std::cout << "[ Process creation time comparsion ]" << std::endl;
  v1->clock_reset();
  for (int j = 0; j < amount_to_create; j++) {
    v1->create(j % 3);
  }
  //v1->print();
  v1->clock_print("Version 1");
}

// Just destroy
void test2() {
  int amount_to_destroy = 10000;
  std::cout << std::endl;
  std::cout << "[ ============ Test 2 ============ ]" << std::endl;
  std::cout << "[ Process deletion time comparsion ]" << std::endl;
  v1->clock_reset();
  for (int j = amount_to_destroy; j > 1; j--) {
    v1->destroy(j * 2);
  }
  //v1->print();
  v1->clock_print("Version 2");
}

// Mix and match
void test3() {
  int amount_to_create = 50000;
  std::cout << std::endl;
  std::cout << "[ ============ Test 3 ============ ]" << std::endl;
  std::cout << "[ Process mix/match time comparsion ]" << std::endl;
  v1->clock_reset();
  for (int j = 0; j < amount_to_create; j++) {
    int create_num = random(0, 250);
    while(!v1->exists(create_num)) {
     create_num = random(0, 250);
    }
    v1->create(create_num);
  }
  //v1->print();
  v1->clock_print("Version 3");
}

void run() {
  test1();
  test2();
  test3();
}


int main() {
  init(PROCESS_ARRAY_SIZE);
  run();
  return 0;
}
