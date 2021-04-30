/**
 * @file ra_lru.h
 * @author James Johnston
 * @description This is the implemention of lowest recently used page replacement algorithm for assignment 4.
 */
#ifndef RA_LRU_H
#define RA_LRU_H
#include "ra.h"
#include "lru_queue.h"
namespace ra {

  class lru_algorithm : protected algorithm {
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

        // Hold a temporary new frame buffer position
        int new_frame_pos = 0;

        // Create our queue of least recently used items
        lru_queue queue = lru_queue(frame_length);

        // We start emulating our time
        for (int i = 0; i < time_length; ++i) {

          // Get our current value from our rs (reference string)
          int current_rs = rs[i];

          // Looks in our cache, to see if a frame exists.
          bool found_in_frame = contains(current_rs, queue.get_array(), queue.get_size());

          // It doesn't exist, so a page fault occurs.
          if (!found_in_frame) {

            // We want to identify what frame we are replacing
            int frame_to_replace = -1;

            // Check to see if there are any open
            if (queue.get_size() < frame_length) {

              // The frame we are replacing is one that doesn't exist yet.
              frame_to_replace = new_frame_pos;
              new_frame_pos++;

            } else {
              // Nope, so we replace the last one
              // Get the page that is falling off the cache.
              int lru_pg = queue.head();

              // Find the array location in our frame buffer
              for (int jx = 0; jx < frame_length; ++jx) {
                if (frame[i][jx] == lru_pg) {
                  frame_to_replace = jx; //found
                  break;
                }
              }
            }

            // Update frame
            frame[i][frame_to_replace] = current_rs;

            // Update the future ones too, on the current frame.
            for (int ix = i; ix < time_length; ++ix)
              frame[ix][frame_to_replace] = current_rs;

            // Increment amount of page faults
            ret_val += "X ";
            pg_faults++;

          } else {
            ret_val += "O ";
          }

          // No matter what we are adding in the value.
          queue.add(current_rs);
        }

        // Output how many page faults and the page fault hits/no page faulting.
        return ret_val + " | Page Faults = " + std::to_string(pg_faults);
      }

      /**
       * LRU (Lowest recently used) algorithm constructor
       *
       * @param frame_len Frame length, used to create our frame array and be referenced from frame_length
       * @param time_Len Time Length, used to create our frame array and be referenced from time_length
       * @param ref Reference string value (RS)
       */
      lru_algorithm(int f, int t, int ref[]) {
        init(f, t);
        fill(ref);
      }
  };
}
#endif
