/**
 * @file ra_fifo.h
 * @author James Johnston
 * @description This is the implemention of first in first out page replacement algorithm for assignment 4.
 */
#ifndef RA_FIFO_H
#define RA_FIFO_H
#include "ra.h"
namespace ra {
  class fifo_algorithm : protected algorithm {
    public:
      /**
       * Runs our algorithm.
       *
       * @return results of the run - amount of page faults that occured
       */
      std::string run() {

        // Create our returning string holder
        std::string ret_val = "";

        // Hold how many page faults occured
        int pg_faults = 0;

        // Create a pointer so we know what part in the array we are updating.
        int fifo_pointer = 0;

        // We start emulating our time
        for (int i = 0; i < time_length; ++i) {

          // Check if the rs we are currently on is resident in a given frame.
          if (rs_is_resident(i)) {

            // Yep. Keep going on, and mark that no page fault occured.
            ret_val += "O ";

          } else {
            // Nope, so we call a page fault.

            // Get our current value from our rs (reference string)
            int current_rs = rs[i];

            // Update frames for a position and future ones too.
            update_residency(current_rs, i, fifo_pointer);

            // Increment location of the pointer
            fifo_pointer++;

            // Reset if it exceeds our frame length
            if (fifo_pointer >= frame_length)
              fifo_pointer = 0;

            // Mark an X since this is a page fault
            ret_val += "X ";

            // Increment our page fault counter.
            pg_faults++;
          }
        }

        // Return our results
        return ret_val + " | Page Faults = " + std::to_string(pg_faults);
      }

      /**
       * FIFO algorithm constructor
       *
       * @param frame_len Frame length, used to create our frame array and be referenced from frame_length
       * @param time_Len Time Length, used to create our frame array and be referenced from time_length
       * @param ref Reference string value (RS)
       */
      fifo_algorithm(int frame_len, int time_Len, int ref[]) {
        init(frame_len, time_Len);
        fill(ref);
      }
  };
}
#endif
