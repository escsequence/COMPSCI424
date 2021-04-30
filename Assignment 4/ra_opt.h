#ifndef RA_OPT_H
#define RA_OPT_H
#include "ra.h"
#include <map>
#include <limits.h>
namespace ra {
  class opt_algorithm : protected algorithm {
  private:
    int find_furthest_away(int time){

      std::map<int, int> distance_map;

      // Create our map with items that CAN be replaced.
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

      int furthest_away = INT_MIN;
      int furthest_away_val = last_rs;
      // // We want the LEAST and the furthest away
      for (std::map<int, int>::iterator it = distance_map.begin(); it != distance_map.end(); it++)
      {
          // First lets check to see if there are items that WONT be addressed later
          if (it->second == 0) {
            return it->first;
          } else {
            // Next, we want an item that exists in the RS and the frame that will be addressed the furthest away.
            if (it->second > furthest_away) {
              furthest_away = it->second;
              furthest_away_val = it->first;
            }
          }
      }

      return furthest_away_val;
    }

    // If a value is contained in an int array
    bool contains(int val, int arr[], int size) {
      for(int i = 0; i < size; ++i) {
        if (arr[i] == val)
          return true;
      }
      return false;
    }

    public:
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
          //std::cout << "!! t = " << i << " | v = " << v << std::endl;

          //cache.display();

          // Looks in our cache, to see if a frame exists.
        //   bool found_in_frame = contains(v, cache.get_array(), cache.get_size());
        //
        //   // It doesn't exist, so a page fault occurs.
        //   if (!found_in_frame) {
        //     //std:: cout << "## PAGE FAULT!" << std::endl;
        //     int frame_to_replace = -1;
        //     //std::cout << "DIDNT FIND IN FRAME!" << std::endl;
        //     if (cache.get_size() < frame_length) {
        //       //std::cout << "SIZE!" << std::endl;
        //       frame[i][new_frame_pos] = v;
        //       frame_to_replace = new_frame_pos;
        //       new_frame_pos++;
        //     } else {
        //       // Get the page that is falling off the cache.
        //       int lru_pg = cache.head();
        //
        //       // Find the array location in our frame buffer
        //       for (int jx = 0; jx < frame_length; ++jx) {
        //         if (frame[i][jx] == lru_pg) {
        //           frame_to_replace = jx; //found
        //         }
        //       }
        //     }
        //
        //     // Update frame
        //     frame[i][frame_to_replace] = v;
        //
        //     // Update the future ones too, on the current frame.
        //     for (int ix = i; ix < time_length; ++ix)
        //       frame[ix][frame_to_replace] = v;
        //
        //     // Increment amount of page faults
        //     ret_val += "X ";
        //     pg_faults++;
        //
        //   } else {
        //     ret_val += "O ";
        //   }
        //
        //   cache.add(v);
        // }

        return ret_val + " | Page Faults = " + std::to_string(pg_faults);
      }
      opt_algorithm(int f, int t, int ref[]) {
        init(f, t);
        fill(ref);
      }
  };
}
#endif
