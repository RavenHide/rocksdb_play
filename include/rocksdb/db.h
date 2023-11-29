//
// Created by zhaoyouqing on 2023/11/28.
//

#pragma once

#include <string>

#include "comparator.h"
#include "status.h"

namespace ROCKSDB_NAMESPACE {

struct ColumnFamilyOptions;
struct WriteOptions;

// 可以外部指定default name
extern const std::string kDefaultColumnFamilyName("default");

// 先引用ColumnFamilyDescriptor 一小部分的参数 ，需要的时候再额外添加
struct ColumnFamilyDescriptor {
  std::string name;
  ColumnFamilyOptions options;
  ColumnFamilyDescriptor()
      : name(kDefaultColumnFamilyName), options(ColumnFamilyOptions()) {}
  ColumnFamilyDescriptor(const std::string& _name,
                         const ColumnFamilyOptions& _options)
      : name(_name), options(_options) {}
};

class ColumnFamilyHandle {
 public:
  virtual ~ColumnFamilyHandle() {}
  virtual const std::string& GetName() const = 0;
  virtual uint32_t GetID() const = 0;

  virtual Status GetDescriptor(ColumnFamilyDescriptor* desc) = 0;
  virtual const Comparator* GetComparator() const = 0;
};

// A DB is a persistent, versioned ordered map from keys to values.
// A DB is safe for concurrent access from multiple threads without
// any external synchronization.
// DB is an abstract base class with one primary implementation (DBImpl)
// and a number of wrapper implementations.
// 先开发一个 只有内存的临时性DB操作函数
class DB {
  DB() {}
  // No Copying allowed
  DB(const DB&) = delete;
  void operator=(const DB&) = delete;

  virtual ~DB();

  virtual Status Put(const WriteOptions& options,
                     ColumnFamilyHandle* column_family, const Slice& key,
                     const Slice& value) = 0;

  // Returns default column family handle
  virtual ColumnFamilyHandle* DefaultColumnFamily() const = 0;
};

}  // namespace ROCKSDB_NAMESPACE
