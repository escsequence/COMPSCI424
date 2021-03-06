#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H
#include <thread>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <time.h>
#include <string>

class bounded_buffer {
private:
  bool debug_print;
  int size, max_burst, max_thread_sleep;
  int *buffer;
  void init(), main(), producer(), consumer();
  void print(std::string data, std::string thread, bool debug = false);

public:
  void run();

  bounded_buffer(int n, int k, int t, bool debug = false) {
    debug_print = debug;

    size = n;
    max_burst = k;
    max_thread_sleep = t;

    // Initalize the buffer
    buffer = new int[size];
  }

  ~bounded_buffer() {
    delete buffer;
  }

};
#endif
