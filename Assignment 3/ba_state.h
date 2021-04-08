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
      int* total;
      int** max;
      int** allocation;
      int** request;

      int n, m;

      state(const state& s) {
        this->n = s.n;
        this->m = s.m;

        this->available = new int[m];
        //*this->available = *s.available;

        this->total = new int[m];
        //*this->total = *s.total;

        this->max = new int*[n];
        //*this->max = *s.max;

        this->allocation = new int*[n];
        //*this->allocation = *s.allocation;

        this->request = new int*[n];
        //*this->request = *s.request;

        for (int i = 0; i < n; ++i) {
          this->max[i] = new int[m];
          //*this->max[i] = *s.max[i];

          this->allocation[i] = new int[m];
          //*this->allocation[i] = *s.allocation[i];

          this->request[i] = new int[m];
          //*this->request[i] = *s.request[i];
        }

        for (int in = 0; in < s.n; ++in) {
          for (int im = 0; im < s.m; ++im) {
            this->max[in][im] = s.max[in][im];
            this->allocation[in][im] = s.allocation[in][im];
            this->request[in][im] = s.request[in][im];
          }
        }

        for (int im = 0; im < s.m; ++im) {
          this->total[im] = s.total[im];
          this->available[im] = s.available[im];
        }
      }

      state(int n, int m) {
        this->n = n;
        this->m = m;

        // We allocate our space for this variables
        available = new int[m];
        total = new int[m];
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
            request[in][im] = 0;
          }
        }

        for (int im = 0; im < m; ++im) {
          total[im] = DEFAULT_UNDEFINED_VALUE;
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

      int potential(int r, int p) {
        return max[r][p] - allocation[r][p];
      }

      bool requestr(int i, int j, int k) {
        if (i >= 0 && (i <= this->max[k][j])) {
          if (j >= 0 && (j <= this->m-1)) { // Resource
            if (k >= 0 && (k <= this->n-1)) { // Process
              if (this->request[k][j] == INT_MIN) {
                this->request[k][j] = i;
              } else {
                this->request[k][j]+= i;
              }
              return true;
            }
          }
        }
        return false;
      }

      void aquire(int i, int j, int k) {
        this->available[j] -= i;

        if (this->allocation[k][j] == INT_MIN) {
          this->allocation[k][j] = i;
        } else {
          this->allocation[k][j] += i;
        }

        this->request[k][j] -= i;
      }

      void release(int i, int j, int k) {
        this->available[j] += i;
        this->allocation[k][j] -= i;
      }

  };
}

#endif
