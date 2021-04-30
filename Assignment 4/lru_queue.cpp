#include "lru_queue.h"

/**
 * Add an item into the queue.
 *
 * @param val Value that gets removed or updated in the queue
 */
void lru_queue::add(int val) {
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

/**
 * Returns the size of the queue at a given point
 *
 * @return current size of the queue
 */
int lru_queue::get_size() {
  int count = 0;
  for (auto it = keys.begin(); it != keys.end(); it++) {
    count++;
  }
  return count;
}

/**
 * Returns an integer array of the queue items currently that exist.
 *
 * @return queue as an integer array
 */
int* lru_queue::get_array() {
  int* m = new int[size];
  int pos = 0;
  for (auto it = keys.begin(); it != keys.end(); it++) {
    m[pos] = (*it);
    pos++;
  }
  return m;
}

/**
 * Returns the head of the queue.
 *
 * @return head of the queue
 */
int lru_queue::head() {
  int head;
  for (auto it = keys.begin(); it != keys.end(); it++) {
    head = (*it);
  }
  return head;
}
