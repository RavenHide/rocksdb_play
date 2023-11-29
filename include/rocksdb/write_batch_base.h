//
// Created by zhaoyouqing on 2023/11/28.
//

#pragma once

namespace ROCKSDB_NAMESPACE {
class Status;
class Slice;
class ColumnFamilyHandle;

class WriteBatchBase {
 public:
  virtual ~WriteBatchBase(){}
  virtual Status Put(ColumnFamilyHandle* column_family, const Slice& key,
                     const Slice& value) = 0;
};
}
