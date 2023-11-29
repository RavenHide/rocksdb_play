//
// Created by zhaoyouqing on 2023/11/28.
//

#include "../rocksdb/slice.h"

namespace ROCKSDB_NAMESPACE {

// 简易高效的hex函数
char toHex(unsigned char v) {
  if (v  <= 9) {
    // '0' = 48
    // 值的范围是: [48, 57]
    return '0' + v;
  } else {
    // 'A' = 65, v是个大于等于10的数值
    // 值的范围是: [65, 255]
    return 'A' + v - 10;
  }
}

std::string Slice::ToString(bool hex) const {
  std::string result;
  if (hex) {
    // 分配两倍的字符长度的空间
    result.reserve(2 * size_);
    for (size_t i = 0; i < size_; ++i) {
      // 遍历字符数组
      unsigned char c = data_[i];
      // 数值范围：48 ~ 57, 65 ~ 70
      // 保留高4位，并且右移覆盖低四位，然后做hex 编码
      result.push_back(toHex(c >> 4));
      // 保留低四位，然后做 hex 编码
      result.push_back(toHex(c & 0xf));
    }
    return result;
  } else {
    // 拷贝字符串
    result.assign(data_, size_);
    return result;
  }
}

}  // namespace ROCKSDB_NAMESPACE