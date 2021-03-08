#include "bounded_buffer.h"

/* Random function returns a random integer value */
int random(int min, int max) {
  return rand() % max + min;
}

int second_to_ms(int s) {
  return s*1000;
}

void bounded_buffer::init() {
  srand(time(NULL));
}

void print(std::string data, std::string thread) {
  std::cout << "[" << thread << " Thread]:\t" << data << std::endl;
}

void bounded_buffer::run() {
  // Get the main thread up and running
  std::thread main_thread(&bounded_buffer::main, this);
  main_thread.join();
}


// Main thread
void bounded_buffer::main() {
  print("Creating producer and consumer threads...", "Main");
  // Create a clock to keep track of time
  clock_t t = clock();

  std::thread producer_thread(&bounded_buffer::producer, this);
  std::thread consumer_thread(&bounded_buffer::consumer, this);

  producer_thread.join();
  consumer_thread.join();
  print("Threads have been terminated.", "Main");
}

void bounded_buffer::producer() {
  print("Started.", "Producer");
  int next_in = 0;
  // while (true)
  while(true) {
    //  get random number k1, between 1 and k
    int k1 = random(1, max_burst);
    print("Burst (k1) set to " + std::to_string(k1), "Producer");

    //  for i from 0 to k1
    for (int i = 0; i < k1; ++i) {

      // add 1 to buffer[(next_in + i) mod n]
      buffer[(next_in + i) % size]++;
      print("Buffer[" + std::to_string((next_in + i) % size) + "] = " + std::to_string(buffer[(next_in + i) % size]), "Producer");
    }

    //  next_in = (next_in + k1) mod n
    next_in = (next_in + k1) % size;

    //  get random number t1, between 0 and t
    int t1 = random(0, max_thread_sleep);
    //  sleep for t1 seconds
    print("Sleeping for " + std::to_string(t1) + " seconds.", "Producer");
    std::this_thread::sleep_for(std::chrono::milliseconds(second_to_ms(t1)));
  }

}

void bounded_buffer::consumer() {
  print("Started.", "Consumer");
  int next_out = 0;

  // while (true)
  while(true) {
    //    get random number t2, between 0 and t
    int t2 = random(0, max_thread_sleep);
    //    sleep for t2 seconds
    print("Sleeping for " + std::to_string(t2) + " seconds.", "Consumer");
    std::this_thread::sleep_for(std::chrono::milliseconds(second_to_ms(t2)));

    //    get random number k2, between 1 and k
    int k2 = random(1, max_burst);
    print("Burst (k2) set to " + std::to_string(k2), "Consumer");

    //    for i from 0 to k2
    for (int i = 0; i < k2; ++i) {
      // data = buffer[(next_out + i) mod n]
      int data = buffer[(next_out + i) % size];
      // if (data > 1) exit and report race condition
      print("Buffer[" + std::to_string((next_out + i) % size) + "] = " + std::to_string(buffer[(next_out+ i) % size]), "Consumer");

      if (data > 1) {
        print("!!! Data in buffer exceeds 1 !!!", "Consumer");
        return;
      } else {
        buffer[(next_out + i) % size] = 0;
      }


    }
    //    next_out = (next_out + k2) mod n
    next_out = (next_out + k2);
  }
}
