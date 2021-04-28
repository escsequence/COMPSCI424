#ifndef RA_FIFO_H
#define RA_FIFO_H
#include "ra.h"
namespace ra {
  class fifo_algorithm : protected algorithm {
    public:
      std::string run() {
        std::string ret_val = "";
        int pg_faults = 0;
        int fifo_pointer = 0; // oldest starts at 0
        //return "Test!";
        for (int i = 0; i < time_length; ++i) {
          int v = rs[i]; // Page #
          //std::cout << "!! t = " << i << " | v = " << v << " | pointer = " << fifo_pointer << std::endl;
          bool found_in_frame = false;
          for (int j = 0; j < frame_length; ++j) {
            found_in_frame = (frame[i][j] == v) ? true : found_in_frame;
            //std::cout << "frame[" << i << "][" << j << "] = " << frame[i][j] << std::endl;
          }

          if (!found_in_frame) {
            //std:: cout << "## PAGE FAULT!" << std::endl;

            // Page fault
            frame[i][fifo_pointer] = v; //update the frame

            // Update the future ones too.
            for (int ix = i; ix < time_length; ++ix)
              frame[ix][fifo_pointer] = v;

            // Increment location
            fifo_pointer++;

            // Reset if it exceeds our frame length
            if (fifo_pointer >= frame_length)
              fifo_pointer = 0;

            ret_val += "X ";
            pg_faults++;

          } else {
            ret_val += "O ";
          }
        }

        return ret_val + " | Page Faults = " + std::to_string(pg_faults);
      }
      fifo_algorithm(int f, int t, int ref[]) {
        init(f, t);
        fill(ref);
      }
  };
}
#endif
