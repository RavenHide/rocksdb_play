//
// Created by zhaoyouqing on 2023/11/28.
//

#pragma once

#include "stdint.h"
#include <string>

#include "../rocksdb/db.h"

namespace ROCKSDB_NAMESPACE {

class ColumnFamilyData {
 public:
  // todo test
  ColumnFamilyData(uint32_t id, std::string& name)
      : id_(id),
        name_(name) {}

  // todo test, 临时注释
//  ~ColumnFamilyData();

  uint32_t GetID() const {
    return id_;
  }

  const std::string& GetName() const {
    return name_;
  }

 private:
  uint32_t id_;
  const std::string name_;
};

// todo db/column_family.h 第165行，构造接口
class ColumnFamilyHandleImpl : public ColumnFamilyHandle {

};
}

