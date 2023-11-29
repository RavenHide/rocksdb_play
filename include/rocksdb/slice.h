//
// Created by zhaoyouqing on 2023/11/27.
//
#pragma once

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>

namespace ROCKSDB_NAMESPACE {
class Slice {
  // 不需要增加析构函数，因为这里的data_都是引用别的对象的指针内容的，只要别的对象析构了，Slice自然会被析构
 public:
  // 创建空 slice
  Slice() : data_(""), size_(0) {}

  Slice(const char* d, size_t n) : data_(d), size_(n) {}

  // 从一个字符串里面创建slice
  explicit Slice(const std::string& s) : data_(s.data()), size_(s.size()) {}

  explicit Slice(const char* s) : data_(s) {
    if (s == nullptr) {
      size_ = 0;
    } else {
      size_ = strlen(s);
    }
  }

  // 返回字符数组
  const char* data() const { return data_; }
  // 返回数组长度
  size_t size() const { return size_; }
  // 判断数组是否为空
  bool empty() const { return size_ == 0; }

  // clear data
  void clear() {
    data_ = "";
    size_ = 0;
  }

  // 支持[]访问操作符
  char operator[](size_t n) const {
    assert(n < size());
    return data_[n];
  }

  void remove_prefix(size_t n) {
    assert(n < size());
    data_ += n;
    size_ -= n;
  }

  void remove_suffix(size_t n) {
    assert(n < size());
    size_ -= n;
  }

  // compare
  // Three-way comparison.  Returns value:
  //   <  0 iff "*this" <  "b",
  //   == 0 iff "*this" == "b",
  //   >  0 iff "*this" >  "b"
  int compare(const Slice& b) const;

  bool starts_with(const Slice& x) const {
    if (size_ < x.size_)  {
      return false;
    } else {
      if (memcmp(data_, x.data_, x.size()) == 0) {
        return true;
      } else {
        return false;
      }
    }
  }

  bool ends_with(const Slice& x) const {
    if (size_ >= x.size_) {
      if (memcmp(data_ + size_ - x.size_, x.data_, x.size_) == 0) {
        return true;
      } else {
        return false;
      }
    } else {
      return false;
    }
  }

  // 返回第一个不相同的数组下标位置
  size_t difference_offset(const Slice& b) const;

  // 返回一个data_的拷贝的字符串，如果hex=true，就返回长度为data_两倍的hex encoded
  std::string ToString(bool hex=false) const;

  // 常量指针
  const char* data_;
  size_t size_;
};

inline int Slice::compare(const Slice& b) const {
  assert(data_ != nullptr && b.data_ != nullptr);
  const size_t min_len = (size_ < b.size_) ? size_ : b.size_;
  int r = memcmp(data_, b.data_, min_len);
  // min_len的长度的内容相等，就看谁的长度长，谁就大
  if (r == 0) {
    if (size_ < b.size_) {
      return -1;
    } else if (size_ > b.size_) {
      return 1;
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}

inline size_t Slice::difference_offset(const Slice& b) const {
  const size_t min_len = (size_ < b.size_) ? size_ : b.size_;
  size_t idx = 0;
  for (; idx < min_len; idx++) {
    if (data_[idx] != b.data_[idx]) {
      return idx;
    }
  }
  return idx;
}



}  // namespace ROCKSDB_NAMESPACE
