//
// Created by zhaoyouqing on 2023/11/28.
//

#pragma once

#include "slice.cc"

void test_slice_impl() {
  printf("A=%d, Z=%d, a=%d, z=%d, 0=%d, 9=%d\n", 'A', 'Z', 'a', 'z', '0', '9');
  unsigned char c = ROCKSDB_NAMESPACE::toHex('Z' & 0xf);
  printf("c=%d\n", c);
}
