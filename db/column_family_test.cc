//
// Created by zhaoyouqing on 2023/11/28.
//
#pragma once

#include "column_family.h"


void test_column_family() {
  std::string name = "123";
  ROCKSDB_NAMESPACE::ColumnFamilyData d(11, name);
  std::cout << "id=" << d.GetID() << ", name=" << d.GetName() << std::endl;
}
