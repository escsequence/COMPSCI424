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
      int frame_length;
      int time_length;

      int* rs;
    public:
      void init(int f, int t) {
        this->frame_length = f;
        this->time_length = t;

        rs = new int[t];
        frame = new int*[f];
        for (int i = 0; i < f; ++i) {
          frame[i] = new int[t];
        }
      }
      // Fil reference string
      void fill(std::string reference) {
        // Go through each char and convert
      }
      virtual std::string run() = 0;
  };
}
#endif
