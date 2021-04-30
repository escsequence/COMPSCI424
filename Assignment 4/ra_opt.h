/**
 * @file ra_opt.h
 * @author James Johnston
 * @description This is the implemention of optimal page replacement algorithm for assignment 4.
 */
#ifndef RA_OPT_H
#define RA_OPT_H
#include "ra.h"
#include <map>
#include <limits.h>
namespace ra {
  class opt_algorithm : protected algorithm {
  private:
    /**
     * Find the furthest away item in the rs that also exists in the frame buffer.
     *
     * @param time Time to start looking, goes until time_length
     * @return the value of the furthest away reference number, if an item in the frame doesn't re-occur then it will be returned to get re-used.
     */
    int find_furthest_away(int time){

      // Create a integer distance map
      std::map<int, int> distance_map;

      // Create our map with items that CAN be replaced, as in they exist in our frame at this point in time.
      for (int i = 0; i < frame_length; ++i) {
        int current_frame = this->frame[time][i];
        if (distance_map.find(current_frame) ==  distance_map.end()) {
            distance_map.insert({current_frame, 0});
        }
      }

      // Go through the entire RS and see what value will be addressed the least
      int last_rs = -1;
      for (int i = time; i < time_length; ++i) {
        int current_rs = rs[i];
        if (distance_map.find(current_rs) !=  distance_map.end()) {
          if (distance_map[current_rs] == 0) {
            distance_map[current_rs] = i;
            last_rs = current_rs;
          }
        }
      }

      // Create a temporary value that holds the furthest value away - starts with the smallest value
      int furthest_away = INT_MIN;

      // Hold a value (last_rs) as a temporary one.
      int furthest_away_val = last_rs;

      // We want the LEAST and the furthest away, so we iterate over all the map items
      for (std::map<int, int>::iterator it = distance_map.begin(); it != distance_map.end(); it++)
      {
          // First lets check to see if there are items that WONT be addressed later so they still have 0 as their value
          if (it->second == 0) {
            // Just return it, nothing else to do.
            return it->first;

          } else {
            // Item will be addressed later
            // Next, we want an item that exists in the RS and the frame that will be addressed the furthest away.
            if (it->second > furthest_away) {
              furthest_away = it->second;
              furthest_away_val = it->first;
            }
          }
      }

      // Return the furthest value away from the origin
      return furthest_away_val;
    }

    public:
      /**
       * Runs our algorithm.
       *
       * @return results of the run - amount of page faults that occured
       */
      std::string run() {
        std::string ret_val = "";
        int pg_faults = 0;
        int new_frame_pos = 0;

        for (int i = 0; i < time_length; ++i) {
          if (rs_is_resident(i)) {

            ret_val += "O ";
          } else {

            int current_rs = rs[i];


            if (new_frame_pos < frame_length) {
              update_residency(current_rs, i, new_frame_pos);

              new_frame_pos++;

            } else {
              // Find the furthest away
              int farthest_away = find_furthest_away(i);
              int farthest_away_buffer_location = rs_residency(i, farthest_away);

              update_residency(current_rs, i, farthest_away_buffer_location);

            }

            // Increment amount of page faults
            ret_val += "X ";
            pg_faults++;
          }
        }

        return ret_val + " | Page Faults = " + std::to_string(pg_faults);
      }

      /**
       * OPTIMAL algorithm constructor
       *
       * @param frame_len Frame length, used to create our frame array and be referenced from frame_length
       * @param time_Len Time Length, used to create our frame array and be referenced from time_length
       * @param ref Reference string value (RS)
       */
      opt_algorithm(int frame_len, int time_len, int ref[]) {
        init(frame_len, time_len);
        fill(ref);
      }
  };
}
#endif
