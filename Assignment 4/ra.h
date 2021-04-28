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

      // A simulation of the frame buffer, used for debugging and visualization.
      int** frame;

      // These are two values that max up the frame array.
      int frame_length;
      int time_length;

      // Reference string (aka reference integer array lol)
      int* rs;

    public:

      /*
       *
       */
      void init(int f, int t) {
        this->frame_length = f;
        this->time_length = t;

        rs = new int[t];
        frame = new int*[t];
        for (int i = 0; i < t; ++i) {
          frame[i] = new int[f];

          for (int j = 0; j < f; ++j) {
            frame[i][j] = -1;
          }
        }
      }
      // Fil reference string
      void fill(int c[]) {
        rs = c;
      }
      virtual std::string run() = 0;
  };
}
#endif
