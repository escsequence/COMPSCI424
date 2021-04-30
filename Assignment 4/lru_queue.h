#ifndef LRU_QUEUE_H
#define LRU_QUEUE_H
#include <list>
#include <unordered_map>
class lru_queue {
  private:
    // Holds the key values for items that exist in the queue
    std::list<int> keys;

    // tbd
    std::unordered_map<int, std::list<int>::iterator> map;

    // Size of the queue
    int size;

  public:
    /**
     * Constructor for lru_queue
     *
     * @param v Max size of the queue
     */
    lru_queue(int v) {
      size = v;
    }

    /**
     * Add an item into the queue.
     *
     * @param val Value that gets removed or updated in the queue
     */
    void add(int val);

    /**
     * Returns the size of the queue at a given point
     *
     * @return current size of the queue
     */
    int get_size();

    /**
     * Returns an integer array of the queue items currently that exist.
     *
     * @return queue as an integer array
     */
    int* get_array();

    /**
     * Returns the head of the queue.
     *
     * @return head of the queue
     */
    int head();
};
#endif
