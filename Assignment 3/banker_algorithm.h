/**
 * ba - (Bankers Algorithm)
 * banker_algorithm.h
 * Author: James Johnston

 * This is the main container for the assignment 3. Holds the logic and
 * processing of inputs data and more for the algorithm.
 */
#ifndef BANKER_ALGORITHM_H
#define BANKER_ALGORITHM_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
#include <vector>
#include <cstring>
#include <chrono>
#include <thread>
#include <mutex>
#include "arg.h"
#include "ba.h"

class banker_algorithm {
private:
  // This value is the default value our array items are set to
  const int DEFAULT_UNDEFINED_VALUE = INT_MIN;

  // Current state (used mainly for manual run)
  ba::state *current_state;

  // Values of our process and resource count.
  int n, m;

  // Argument package handler that holds the argument values
  arg arg_handle;

  // Configuration array of configuration entries from the file
  std::vector<ba::config> configuration;

  /**
   * Initalization of all the processes, called in the constructor.
   */
  void init();

  /**
   * Loads the configuration file in our config object.
   */
  void init_load_config();

  /**
   * Parses the configuration data we loaded into our current_state.
   */
  void init_parse_config();

  /**
   * Validates the configuration data loaded from the file.
   * @return bool If the configuration information is valid.
   */
  bool init_validate_config();

  // Indicates our configuration validity.
  bool config_valid;

  /**
   * Our run method for the automatic mode of operation.
   * @return int Return value for the main method, successful run for 0.
   */
  int run_auto();

  /**
   * Our run method for the manual mode of operation.
   * @return int Return value for the main method, successful run for 0.
   */
  int run_manual();

  /**
   * Validates the state specified.
   * @param s A state of the bankers algorithm.
   * @return bool State is valid, allocation isn't greater than the maximum.
   */
  bool validate_state(ba::state *s);

  /**
   * Prints the state spcified.
   * @param s A state to print out to the console.
   */
  void print_state(ba::state *s);

  /**
   * Calls print_state on our current_state. (Prints our current state)
   */
  void print_status();

  /**
   * Determines if there is a deadlock for a specified state.
   * @param *state The state to find a deadlock in.
   * @return bool If the state given has a deadlock.
   */
  bool deadlock_detect(ba::state *state);

  /**
   * Determines if there is a deadlock for a specified state.
   * @param *state The state to find a deadlock in.
   * @return bool If the state given has a deadlock.
   */
  void dl_safe(bool marked[], ba::state *state, std::vector<int> safe);

  /**
   * Determines if there is a deadlock for a specified state.
   * @param *state The state to find a deadlock in.
   * @return bool If the state given has a deadlock.
   */
  bool dl_available(ba::state *state, int process);
  int dl_tmp_total;

  /**
   * Determines if there is a deadlock for a specified state.
   * @param *state The state to find a deadlock in.
   * @return bool If the state given has a deadlock.
   */
  bool request(ba::state *s, int i, int j, int k);

  /**
   * If the data passed in is a valid release
   * @param *s The state to find a deadlock in.
   * @param i Resource Amount.
   * @param j Resource id.
   * @param k Process id.
   * @return bool If the values are within the allocation data.
   */
  bool valid_release(ba::state *s, int i, int j, int k);

  /**
   * Determines whether the value passed in is a array data information (NOT DEFAULT_UNDEFINED_VALUE).
   * @param &val Values to analyze.
   * @return bool If the value is NOT DEFAULT_UNDEFINED_VALUE
   */
  bool valid(int &val);

  // Holds if we should process manula inputs
  bool manual_process_inputs;

  /**
   * Engages the auto thread execution for the automatic mode.
   * @param int Current process/thread being run.
   */
  void auto_thread_run(int thread_id);

public:
  banker_algorithm(arg a) {
    // Arguments passed in from the main method
    this->arg_handle = a;

    // Set up the vector for the configuration
    configuration = std::vector<ba::config>();

    // Run the initialize command
    this->init();

  }

  /**
   * Runs either manual or automatic mode, engages the bankers algorithm program.
   * @return int Return value for the main method, successful run for 0.
   */
  int run();
};
#endif
