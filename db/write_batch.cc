//
// Created by zhaoyouqing on 2023/11/28.
//

#include "../include/rocksdb/write_batch.h"

namespace ROCKSDB_NAMESPACE {
Status WriteBatch::Put(ColumnFamilyHandle *column_family, const Slice &key,
                       const Slice &value) {
  // todo 先不支持时间戳的key

  // get column family id
}

}  // namespace ROCKSDB_NAMESPACE