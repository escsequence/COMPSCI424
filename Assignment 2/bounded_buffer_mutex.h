#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H
#include <thread>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <time.h>
#include <string>
#include <mutex>
#include <math.h>

class bounded_buffer {
private:
  bool debug_print;
  int size, max_burst, max_thread_sleep;

  // Implementation of P and V functions
  int full, empty;
  int P(int s, std::string t);
  int V(int s);


  int *buffer;
  void init(), main(), producer(int time_limit), consumer(int time_limit);
  void print(std::string data, std::string thread, bool debug = false);
  clock_t time_elapsed;
  int stop_running_time;
  double current_time_elapsed();
public:
  void run();

  bounded_buffer(int n, int k, int t, bool debug = false) {
    debug_print = debug;

    size = n;
    max_burst = k;
    max_thread_sleep = t;

    // Initalize the buffer
    buffer = new int[size];

    full = 0;
    empty = size;
  }

  ~bounded_buffer() {
    delete buffer;
  }

};
#endif
