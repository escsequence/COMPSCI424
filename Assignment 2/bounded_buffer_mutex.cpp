#include "bounded_buffer_mutex.h"
std::mutex mtx; // Mutex to control the consumer and producer.

/* Random function returns a random integer value */
int random(int min, int max) {
  return rand() % max + min;
}

void bounded_buffer::init() {

  // Initalize the randomization srand function
  srand(time(NULL));
}

void bounded_buffer::print(std::string data, std::string thread, bool debug) {
  if ((debug_print == debug) || !debug)
    std::cout << "[" << thread << "   Thread]:\t" << data << std::endl;
}

double bounded_buffer::current_time_elapsed() {
  double k = double(clock() - time_elapsed)/CLOCKS_PER_SEC;
  return k;
}

void bounded_buffer::run() {
  // Get the main thread up and running
  std::thread main_thread(&bounded_buffer::main, this);
  main_thread.join();
}


// Main thread
void bounded_buffer::main() {

  stop_running_time = 20; // in seconds
  // Create a clock to keep track of time
  //time_elapsed = clock();
  print("Setting termination time of threads = " + std::to_string(stop_running_time) + " seconds.", "Main");


  print("Creating producer and consumer threads...", "Main");

  std::thread producer_thread(&bounded_buffer::producer, this, stop_running_time);
  std::thread consumer_thread(&bounded_buffer::consumer, this, stop_running_time);

  producer_thread.join();
  consumer_thread.join();

  print("Threads have been terminated.", "Main");
}

void bounded_buffer::producer(int time_limit) {
  print("Started.", "Producer");

  // Initalize our next_in variable for the producer
  int next_in = 0;

  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  while(true) {

    int seconds = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - begin).count();
    print("Current time thread alive = " + std::to_string(seconds) + " seconds", "Producer", true);

    if (seconds >= time_limit) {
      print("Terminating thread as it exceeds our time limit (" + std::to_string(time_limit) + ").", "Producer");
      return;
    }

    //std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - begin).count() << "[seconds]" << std::endl;

    //if (stop_running_time)
    mtx.lock();
    //  get random number k1, between 1 and k
    int k1 = random(1, max_burst);
    print("Burst (k1) set to " + std::to_string(k1), "Producer");

    //  for i from 0 to k1
    for (int i = 0; i < k1; ++i) {

      // add 1 to buffer[(next_in + i) mod n]
      buffer[(next_in + i) % size]++;
      print("Buffer[" + std::to_string((next_in + i) % size) + "] = " + std::to_string(buffer[(next_in + i) % size]), "Producer", true);
    }

    //  next_in = (next_in + k1) mod n
    next_in = (next_in + k1) % size;

    //  get random number t1, between 0 and t
    int t1 = random(0, max_thread_sleep);
    //  sleep for t1 seconds
    print("Sleeping for " + std::to_string(t1) + " seconds.", "Producer");
    mtx.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(t1));
  }

}

void bounded_buffer::consumer(int time_limit) {
  print("Started.", "Consumer");
  int next_out = 0;
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  // while (true)
  while(true) {
    int seconds = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - begin).count();
    print("Current time thread alive = " + std::to_string(seconds) + " seconds", "Consumer", true);

    if (seconds >= time_limit) {
      print("Terminating thread as it exceeds our time limit (" + std::to_string(time_limit) + ").", "Consumer");
      return;
    }

    //    get random number t2, between 0 and t
    int t2 = random(0, max_thread_sleep);
    //    sleep for t2 seconds
    print("Sleeping for " + std::to_string(t2) + " seconds.", "Consumer");
    std::this_thread::sleep_for(std::chrono::seconds(t2));
    mtx.lock();
    //    get random number k2, between 1 and k
    int k2 = random(1, max_burst);
    print("Burst (k2) set to " + std::to_string(k2), "Consumer");

    //    for i from 0 to k2
    for (int i = 0; i < k2; ++i) {
      // data = buffer[(next_out + i) mod n]
      int data = buffer[(next_out + i) % size];
      // if (data > 1) exit and report race condition
      print("Buffer[" + std::to_string((next_out + i) % size) + "] = " + std::to_string(buffer[(next_out+ i) % size]), "Consumer", true);

      if (data > 1) {
        print("!!! Data in buffer exceeds 1 !!!", "Consumer");
        mtx.unlock();
        return;
      } else {
        buffer[(next_out + i) % size] = 0;
      }

    }
    //    next_out = (next_out + k2) mod n
    next_out = (next_out + k2);
    mtx.unlock();
  }
}
