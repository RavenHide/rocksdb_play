//
// Created by zhaoyouqing on 2023/11/28.
//

#pragma once

#include "write_batch_base.h"
#include <stdio.h>

namespace ROCKSDB_NAMESPACE {
class Slice;
class ColumnFamilyHandle;

class WriteBatch : public WriteBatchBase {
 public:
  explicit WriteBatch(size_t reserved_bytes=0, size_t max_bytes=0)
      : WriteBatch(reserved_bytes, max_bytes, 0, 0) {}
  explicit WriteBatch(size_t reserved_bytes, size_t max_bytes,
                      size_t protection_bytes_per_key, size_t default_cf_ts_sz);

  ~WriteBatch() override;

  using WriteBatchBase::Put;
  Status Put(ColumnFamilyHandle* column_family, const Slice& key,
             const Slice& value) override;
};
}
