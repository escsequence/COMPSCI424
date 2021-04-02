#ifndef BA_STATE_H
#define BA_STATE_H
#include <climits>
namespace ba {
  class state {
    private:
      // This value is the default value our array items are set to
      const int DEFAULT_UNDEFINED_VALUE = INT_MIN;

      // Our arrays
      int* available;
      int** max;
      int** allocation;
      int** request;

      int n, m;

      void _init();
    public:
      state(int n, int m) {
        this->n = n;
        this->m = m;

        _init();
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
