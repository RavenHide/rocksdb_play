//
// Created by zhaoyouqing on 2023/11/28.
//
#pragma once
#include "../util/status.cc"

void test_status() {
//  ROCKSDB_NAMESPACE::Status s1{};
//  s1.subcode_ = ROCKSDB_NAMESPACE::Status::kDeadlock;
//  // copy from s1
//  ROCKSDB_NAMESPACE::Status s2 = ROCKSDB_NAMESPACE::Status(s1);
//  s1.subcode_ = ROCKSDB_NAMESPACE::Status::kIOFenced;
//  std::cout << "s1=" << s1.subcode_ << std::endl;
//  std::cout << "s2=" << s2.subcode_ << std::endl;
//
//  s1 = s2;
//  std::cout << "s1=" << s1.subcode_ << std::endl;
//  s1.subcode_ = ROCKSDB_NAMESPACE::Status::kLockLimit;
//
//  s1 = ROCKSDB_NAMESPACE::Status(std::move(s2));
//  std::cout << "s1=" << s1.subcode_ << std::endl;
  ROCKSDB_NAMESPACE::Status s1 = ROCKSDB_NAMESPACE::Status::Aborted(
    ROCKSDB_NAMESPACE::Status::kLockLimit
    );
  std::cout << "s1=" << s1.ToString() << std::endl;

  s1 = ROCKSDB_NAMESPACE::Status::InvalidArgument(ROCKSDB_NAMESPACE::Slice("111"));
  std::cout << "s1=" << s1.ToString() << std::endl;
}
