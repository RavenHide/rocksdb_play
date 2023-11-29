//
// Created by zhaoyouqing on 2023/11/27.
//
#pragma once

#include "rocksdb_namespace.h"
#include "slice.h"
#include <iostream>

void test_slice() {
  ROCKSDB_NAMESPACE::Slice s{};

  std::cout << "size=" << s.size() << ", is_empty=" << std::boolalpha
            << s.empty() << std::endl;
  std::cout << "data=\"" << s.data() << "\"" << std::endl;

  std::string str1 = "123";
  s = ROCKSDB_NAMESPACE::Slice(str1.data(), str1.size());

  std::cout << "size=" << s.size() << ", is_empty=" << std::boolalpha
            << s.empty() << std::endl;
  std::cout << "data=\"" << s.data() << "\"" << std::endl;

  s.clear();
  std::string str2 = "456";
  s = ROCKSDB_NAMESPACE::Slice(str2);

  std::cout << "size=" << s.size() << ", is_empty=" << std::boolalpha
            << s.empty() << std::endl;
  std::cout << "data=\"" << s.data() << "\"" << std::endl;

  s.clear();
  std::string str3 = "789";
  s = ROCKSDB_NAMESPACE::Slice(str3.data());
  std::cout << "size=" << s.size() << ", is_empty=" << std::boolalpha
            << s.empty() << std::endl;
  std::cout << "data=\"" << s.data() << "\"" << std::endl;

  std::cout << "data[1]=" << s[1] << std::endl;

  s.remove_prefix(1);
  std::cout << "data=\"" << s.data() << "\"" << std::endl;
  s.remove_suffix(1);
  std::cout << "data=\"" << s.data() << "\"" << std::endl;


  s = ROCKSDB_NAMESPACE::Slice("1122");
  ROCKSDB_NAMESPACE::Slice s2("112233");
  auto is_same = s.compare(s2);
  std::cout << "is_same=" << is_same << std::endl;

  s = ROCKSDB_NAMESPACE::Slice("112233");
  is_same = s.compare(s2);
  std::cout << "is_same=" << is_same << std::endl;

  s = ROCKSDB_NAMESPACE::Slice("11223344");
  is_same = s.compare(s2);
  std::cout << "is_same=" << is_same << std::endl;

  bool is_prefix = s2.starts_with(s);
  std::cout << "is_prefix=" << std::boolalpha << is_prefix << std::endl;

  is_prefix = s.starts_with(s2);
  std::cout << "is_prefix=" << std::boolalpha << is_prefix << std::endl;

  s = ROCKSDB_NAMESPACE::Slice("1");
  s2 = ROCKSDB_NAMESPACE::Slice("1");
  is_prefix = s.starts_with(s2);
  std::cout << "is_prefix=" << std::boolalpha << is_prefix << std::endl;

  bool is_suffix = s.ends_with(s2);
  std::cout << "is_suffix=" << std::boolalpha << is_suffix << std::endl;

  s = ROCKSDB_NAMESPACE::Slice("1");
  s2 = ROCKSDB_NAMESPACE::Slice("12");
  is_suffix = s.ends_with(s2);
  std::cout << "is_suffix=" << std::boolalpha << is_suffix << std::endl;

  s = ROCKSDB_NAMESPACE::Slice("112");
  s2 = ROCKSDB_NAMESPACE::Slice("12");
  is_suffix = s.ends_with(s2);
  std::cout << "is_suffix=" << std::boolalpha << is_suffix << std::endl;

  s = ROCKSDB_NAMESPACE::Slice("123");
  s2 = ROCKSDB_NAMESPACE::Slice("124");
  size_t diff_offset = s.difference_offset(s2);
  std::cout << "diff_offset=" << diff_offset << std::endl;

  s = ROCKSDB_NAMESPACE::Slice("12");
  s2 = ROCKSDB_NAMESPACE::Slice("124");
  diff_offset = s.difference_offset(s2);
  std::cout << "diff_offset=" << diff_offset << std::endl;

  std::cout << "s2 to_string=" << s2.ToString() << std::endl;
  std::cout << "s2 to_string hex=" << s2.ToString(true) << std::endl;
}
