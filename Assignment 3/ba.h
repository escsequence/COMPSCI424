/**
 * ba - (Bankers Algorithm)
 * ba.h
 * Author: James Johnston
 * Some additional help with trimming strings:
 * https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
 *
 * This holds all the ba namespace items for easy inclusion.
 */
#ifndef BA_H
#define BA_H
#include <vector>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <mutex>
#include <random>

/**
 * Trims from the left side of a string.
 *
 * @param str Raw string to be trimmed.
 * @return std::string Santized string.
 */
static inline std::string &ltrim(std::string &str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return str;
}

/**
 * Trims from the right side of a string.
 *
 * @param str Raw string to be trimmed.
 * @return std::string Santized string.
 */
static inline std::string &rtrim(std::string &str) {
    str.erase(std::find_if(str.rbegin(), str.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());
    return str;
}

/**
 * Trims a string.
 *
 * @param str Raw string to be trimmed.
 * @return std::string Santized string.
 */
static inline std::string &trim(std::string &str) {
    return ltrim(rtrim(str));
}

/**
 * Split a string of elements into a vector of multiple items.
 *
 * @param s Raw string to be split.
 * @param delim Delimiter to split based on.
 * @param result Result output
 */
template <typename Out>
static void split (const std::string &s, char delim, Out result) {
  std::istringstream iss(s);
  std::string item;
  while(std::getline(iss, item, delim)) {
    *result++ = trim(item);
  }
}

/**
 * Split a string of elements into a vector of multiple items.
 *
 * @param s Raw string to be split.
 * @param delim Delimiter to split based on.
 * @return std::vector<std::string> Vector of items that have been separated.
 */
static std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, std::back_inserter(elems));
  return elems;
}
#include "ba_mode.h"
#include "ba_config.h"
#include "ba_command.h"
#include "ba_state.h"
#include "ba_log.h"
#endif
