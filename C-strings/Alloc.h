#include <iostream>
using namespace std;

class Alloc {
  static int total_bytes;
  static int net_allocations;
  static int total_allocations;

 public:
  static char* new_char_array(size_t n_bytes);
  static void delete_char_array(char* p);
  static void report_allocations();
};