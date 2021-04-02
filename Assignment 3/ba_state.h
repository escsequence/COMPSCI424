#ifndef BA_STATE_H
#define BA_STATE_H
#include <climits>
namespace ba {
  class state {
    private:
      // This value is the default value our array items are set to
      const int DEFAULT_UNDEFINED_VALUE = INT_MIN;

    public:
      // Our arrays
      int* available;
      int** max;
      int** allocation;
      int** request;

      int n, m;

      state(int n, int m) {
        this->n = n;
        this->m = m;

        // We allocate our space for this variables
        available = new int[m];
        max = new int*[n];
        allocation = new int*[n];
        request = new int*[n];

        // Since max, allocation, and request are 2d arrays
        for (int i = 0; i < n; ++i) {
          max[i] = new int[m];
          allocation[i] = new int[m];
          request[i] = new int[m];
        }

        // Santize our array to be all DEFAULT_UNDEFINED_VALUE
        for (int in = 0; in < n; ++in) {
          for (int im = 0; im < m; ++im) {
            max[in][im] = DEFAULT_UNDEFINED_VALUE;
            allocation[in][im] = DEFAULT_UNDEFINED_VALUE;
            request[in][im] = DEFAULT_UNDEFINED_VALUE;
          }
        }

        for (int im = 0; im < m; ++im) {
          available[im] = DEFAULT_UNDEFINED_VALUE;
        }
      }
      ~state() {
        for (int i = 0 ; i < n; ++i) {
            delete[] max[i];
            delete[] allocation[i];
            delete[] request[i];
          }
          delete[] available;
          delete[] max;
          delete[] allocation;
          delete[] request;
      }
  };
}

#endif
