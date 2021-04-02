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

// Help: https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

template <typename Out>
static void split (const std::string &s, char delim, Out result) {
  std::istringstream iss(s);
  std::string item;
  while(std::getline(iss, item, delim)) {
    *result++ = trim(item);
  }
}

static std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, std::back_inserter(elems));
  return elems;
}
#include "ba_mode.h"
#include "ba_config.h"
#include "ba_command.h"
#include "ba_state.h"
#endif
