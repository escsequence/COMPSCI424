/**
 * @file ra.h
 * @author James Johnston
 * @description This include holds the implemention for the replacement algorithm.
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

      /*
       * Initalize our algorithm
       *
       * @param f Frame length
       * @param t Time length
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

      /**
       * Fills a reference string (rs) private variable value.
       *
       * @param c Int array that contains our reference string values
       */
      void fill(int c[]) {
        rs = c;
      }

      /**
       * Returns if a value is contained inside an 1-D integer array.
       *
       * @param val Value to look in the array for
       * @param arr Array to loop through and check the value
       * @param size Size of the array, so we know the bounds
       * @return If the array contained the value
       */
      bool contains(int val, int arr[], int size) {
        for(int i = 0; i < size; ++i) {
          if (arr[i] == val)
            return true;
        }
        return false;
      }

      /**
       * Checks to see if a current reference string value at a given time, is currently in frame or not.
       *
       * @param time The current time to check an rs value resident in the frame
       * @return whether the rs value at a given time is resident in a frame (true/false)
       */
      bool rs_is_resident(int time) {
        int current_rs = rs[time];
        return value_is_resident(current_rs, time);
      }

      /**
       * Checks to see if a value is currently in frame or not.
       *
       * @param v Value to check in all the frames
       * @param time The current time to check a value resident in the frame
       * @return whether the value at a given time is resident in a frame (true/false)
       */
      bool value_is_resident(int v, int time) {
        // Loop through each of the frames
        for (int i = 0; i < frame_length; ++i) {
          if (frame[time][i] == v)
            return true;
        }

        // If nothing every returned true, just return false
        return false;
      }

      /**
       * Updates the frames (aka the residency) for the remaining time slots.
       *
       * @param val Value to update the frames
       * @param time The time to start updating the frames at (time - time_length)
       * @param frame The frame which will be updated for the remaining time slots
       */
      void update_residency(int val, int time, int frame) {
        for (int i = time; i < time_length; ++i) {
          this->frame[i][frame] = val;
        }
      }

      /**
       * Finds if a value exists in a given time frame, if it does the
       * identifier will be returned, if not -1 will be returned.
       *
       * @param time The time to check for a values residency
       * @param rs Value to check if exists in the frames
       * @return identification value (aka the frame buffer position)
       */
      int rs_residency(int time, int rs) {
        for (int i = 0; i < frame_length; ++i)
          if (frame[time][i] == rs)
            return i;
        return -1;
      }
    public:

      /**
       * Virtual function to be inherited by FIFO, OPT, and LRU.
       *
       * @return results of the run - amount of page faults that occured
       */
      virtual std::string run() = 0;
  };
}
#endif
