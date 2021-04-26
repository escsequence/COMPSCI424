/**
 * ra - (Replacement Algorithm)
 * ra.h
 * Author: James Johnston
 * This include holds the implemention for the replacement algorithm.
 */
#ifndef RA_H
#define RA_H
#include <iostream>
namespace ra {
  class algorithm {
    protected:
      int** frame;
      // These are two values that max u pthe frame array
      int frame_size;
      int time_length;

    public:
      virtual void init() = 0;
      virtual std::string run() = 0;
  };
}
#endif
