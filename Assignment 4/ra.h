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
  const bool VERBOSE_DEBUG = true;
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

      bool rs_is_resident(int time) {
        int current_rs = rs[time];
        return value_is_resident(current_rs, time);
      }

      bool value_is_resident(int v, int time) {
        for (int i = 0; i < frame_length; ++i) {
          if (frame[time][i] == v)
            return true;
        }
        return false;
      }

      void update_residency(int val, int time, int frame) {
        for (int i = time; i < time_length; ++i) {
          //frame[time][i] = val;
          this->frame[i][frame] = val;
        }
      }

      int rs_residency(int time, int rs) {
        for (int i = 0; i < frame_length; ++i)
          if (frame[time][i] == rs)
            return i;
        return -1;
      }
      virtual std::string run() = 0;
  };
}
#endif
