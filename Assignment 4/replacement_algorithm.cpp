#include "replacement_algorithm.h"

const int PAGE_FRAME_LIMIT = 6;
const int REFERENCE_LENGTH_LIMIT = 20;

int ra_program::random(int min, int max) {
    return min + (rand() % static_cast<int>(max - min + 1));
}

int* ra_program::random_array(int min, int max, int size) {
  int *arr = new int[size];
  for (int i = 0; i < size; ++i)
    arr[i] = random(min, max);
  return arr;
}

std::string ra_program::int_array_to_string(int arr[], int size) {
  std::string full_buffer = "";
  char buffer[size];
  for (int i = 0; i < size; ++i) {
    sprintf(buffer, "%d", arr[i]);
    full_buffer+=buffer;
  }

  return full_buffer;
}

int ra_program::run() {
  // Ask the user to enter the number of page frames in the system. If the number of frames is not between 1 and 6 (inclusive), ask them to try again, and give them enough information so that they know what to do.

  int page_frames_from_user = -1;
  std::cout << "Enter amount of page frames in the system = ";
  while(page_frames_from_user < 0 || page_frames_from_user > PAGE_FRAME_LIMIT) {
    std::cin >> page_frames_from_user;

    if (page_frames_from_user < 0 || page_frames_from_user > PAGE_FRAME_LIMIT) {
      std::cout << "Invalid amount. Please make sure page frames are within 0 and " << PAGE_FRAME_LIMIT << "." << std::endl << std::endl;
      std::cout << "Enter amount of page frames in the system = ";
    }
  }

  // Generate and then display a random reference string of length 20, whose page numbers range from 0 to 9.
  int* reference_array = random_array(0, 9, REFERENCE_LENGTH_LIMIT);

  // Test case 1
  //int reference_array[] = {0, 1, 4, 0, 2, 3, 0, 1, 0, 2, 3, 4, 2, 3, 0, 4, 2, 1, 3, 2};

  // Test case 2
  //int reference_array[] = {0, 8, 5, 6, 4, 3, 8, 1, 5, 9, 1, 5, 6, 4, 5, 4, 9, 3, 6, 7};

  // Test case 3
  //int reference_array[] = {0, 8, 5, 6, 4, 3, 8, 1, 5, 9, 1, 5, 7, 4, 5, 4, 9, 3, 6, 7};

  std::string reference_string = int_array_to_string(reference_array, REFERENCE_LENGTH_LIMIT);
  std::cout << "| Random generated reference string = " << reference_string << std::endl << std::endl;

  // Display the number of page faults produced by using FIFO page replacement with this reference string.
  ra::fifo_algorithm fa = ra::fifo_algorithm(page_frames_from_user, REFERENCE_LENGTH_LIMIT, reference_array);
  std::cout << "| FIFO results = " << fa.run() << std::endl;

  // Display the number of page faults produced by using LRU page replacement with this reference string.
  ra::lru_algorithm lrua = ra::lru_algorithm(page_frames_from_user, REFERENCE_LENGTH_LIMIT, reference_array);
  std::cout << "| LRU results  = " << lrua.run() << std::endl;

  // Display the number of page faults produced by using optimal (OPT) page replacement with this reference string.
  ra::opt_algorithm opta = ra::opt_algorithm(page_frames_from_user, REFERENCE_LENGTH_LIMIT, reference_array);
  std::cout << "| OPT results  = " << opta.run() << std::endl << std::endl;



  //std::cout << "Test array = " << int_array_to_string(random_array(0, 1, 5), 5) << std::endl;
  return 0;
}
