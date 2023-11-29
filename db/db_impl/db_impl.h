//
// Created by zhaoyouqing on 2023/11/28.
//

#pragma once
#include "options.h"
#include "status.h"
#include "../include/rocksdb/db.h"
#include <string>

namespace ROCKSDB_NAMESPACE {
class DBImpl : public DB {
  DBImpl(const DBOptions& options, const std::string& dbname,
         const bool seq_per_batch=false, const bool batch_per_txn=true,
         bool read_only=false);

  // No copying allowed
  DBImpl(const DBImpl&) = delete;
  void operator=(const DBImpl&) = delete;

  virtual ~DBImpl();
  // ---- Implementations of the DB interface ----
  using DB::PUt;
  Status Put(const WriteOptions &options, ColumnFamilyHandle *column_family,
             const Slice &key, const Slice &value) override;

  Status FailIfCfHasTs(const ColumnFamilyHandle* column_family) const;
};

inline Status DBImpl::FailIfCfHasTs(const ColumnFamilyHandle *column_family) const {
  // todo
  return Status::OK();
}
}
