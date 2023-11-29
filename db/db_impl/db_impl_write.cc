//
// Created by zhaoyouqing on 2023/11/28.
//

#include "db_impl.h"

namespace ROCKSDB_NAMESPACE {
Status DBImpl::Put(const WriteOptions &options,
                   ColumnFamilyHandle *column_family, const Slice &key,
                   const Slice &value) {
  const Status s = FailIfCfHasTs(column_family);
  if (!s.ok()) {
    return s;
  } else {
    return DB::Put(options, column_family, key, value);
  }
}

Status DB::Put(const WriteOptions &options, ColumnFamilyHandle *column_family,
               const Slice &key, const Slice &value) {

}
}  // namespace ROCKSDB_NAMESPACE