#ifndef RA_FIFO_H
#define RA_FIFO_H
#include "ra.h"
namespace ra {
  class fifo_algorithm : protected algorithm {
    public:
      std::string run() {

        std::string ret_val = "";
        int pg_faults = 0;
        int fifo_pointer = 0;

        for (int i = 0; i < time_length; ++i) {

          // Check if the rs we are currently on is resident in a given frame.
          if (rs_is_resident(i)) {
            // Yep. Keep going on.
            ret_val += "O ";

          } else {
            // Nope, so we call a page fault.

            // Get our current value from our rs (reference string)
            int current_rs = rs[i];


            // Update frames for a position
            frame[i][fifo_pointer] = current_rs;

            // Update the future ones too.
            for (int ix = i; ix < time_length; ++ix)
              frame[ix][fifo_pointer] = current_rs;

            // Increment location
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

        return ret_val + " | Page Faults = " + std::to_string(pg_faults);
      }
      fifo_algorithm(int f, int t, int ref[]) {
        init(f, t);
        fill(ref);
      }
  };
}
#endif
