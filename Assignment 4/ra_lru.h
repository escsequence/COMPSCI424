#ifndef RA_LRU_H
#define RA_LRU_H
#include "ra.h"
#include <list>
#include <unordered_map>
#include <queue>
namespace ra {
  class lru_cache {
    private:
      std::list<int> keys;
      std::unordered_map<int, std::list<int>::iterator> map;
      int size;
    public:
      lru_cache(int v) {
        size = v;
      }

      void add(int val) {
        if (map.find(val) == map.end()) {
          if (keys.size() == size) {
            int last = keys.back();
            keys.pop_back();
            map.erase(last);
          }
        } else {
          keys.erase(map[val]);
        }

        keys.push_front(val);
        map[val] = keys.begin();
      }

      void display() {
        for (auto it = keys.begin(); it != keys.end();
             it++)
            std::cout << (*it) << " ";

        std::cout << std::endl;
      }

      int get_size() {
        int count = 0;
        for (auto it = keys.begin(); it != keys.end(); it++) {
          count++;
        }
        return count;
      }

      int* get_array() {
        int* m = new int[size];
        int pos = 0;
        for (auto it = keys.begin(); it != keys.end(); it++) {
          m[pos] = (*it);
          pos++;
        }
        return m;
      }

      int head() {
        int head;
        for (auto it = keys.begin(); it != keys.end(); it++) {
          head = (*it);
        }
        return head;
      }



  };
  class lru_algorithm : protected algorithm {
  private:
    // If a value is contained in an int array
    bool contains(int val, int arr[], int size) {
      for(int i = 0; i < size; ++i) {
        //std::cout << "arr[i]=" << arr[i] << " == " << val << std::endl;
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

        lru_cache cache = lru_cache(frame_length);

        for (int i = 0; i < time_length; ++i) {

          // Get our current value from our rs (reference string)
          int current_rs = rs[i];

          // Looks in our cache, to see if a frame exists.
          bool found_in_frame = contains(current_rs, cache.get_array(), cache.get_size());

          // It doesn't exist, so a page fault occurs.
          if (!found_in_frame) {

            // We want to identify what frame we are replacing
            int frame_to_replace = -1;

            // Check to see if there are any open
            if (cache.get_size() < frame_length) {

              // The frame we are replacing is one that doesn't exist yet.
              frame_to_replace = new_frame_pos;
              new_frame_pos++;

            } else {
              // Nope, so we replace the last one
              // Get the page that is falling off the cache.
              int lru_pg = cache.head();

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
          cache.add(current_rs);
        }

        // Output how many page faults and the page fault hits/no page faulting.
        return ret_val + " | Page Faults = " + std::to_string(pg_faults);
      }
      lru_algorithm(int f, int t, int ref[]) {
        init(f, t);
        fill(ref);
      }
  };
}
#endif
