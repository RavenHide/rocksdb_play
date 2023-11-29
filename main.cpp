#include <iostream>

#include "include/rocksdb/slice_test.cc"
#include "util/slice_test.cc"
#include "include/rocksdb/status_test.cc"
#include "db/column_family_test.cc"

int main() {
  std::cout << "========= test_slice ===========" << std::endl;
  test_slice();
  std::cout << "========= test_slice_impl ===========" << std::endl;
  test_slice_impl();
  std::cout << "========= test_status ===========" << std::endl;
  test_status();
  std::cout << "========= test_column_family ===========" << std::endl;
  test_column_family();
  return 0;
}

