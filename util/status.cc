//
// Created by zhaoyouqing on 2023/11/28.
//

#include "../rocksdb/status.h"

#include <cstring>

namespace ROCKSDB_NAMESPACE {
std::unique_ptr<const char[]> Status::CopyState(const char* s) {
  const size_t cch = std::strlen(s) + 1;  // +1 for the null terminator
  // 创建一个新数组
  char* rv = new char[cch];
  std::strncpy(rv, s, cch);
  return std::unique_ptr<const char[]>(rv);
}

static const char* msgs[static_cast<int>(Status::kMaxSubCode)] = {
    "",                                                   // kNone
    "Timeout Acquiring Mutex",                            // kMutexTimeout
    "Timeout waiting to lock key",                        // kLockTimeout
    "Failed to acquire lock due to max_num_locks limit",  // kLockLimit
    "No space left on device",                            // kNoSpace
    "Deadlock",                                           // kDeadlock
    "Stale file handle",                                  // kStaleFile
    "Memory limit reached",                               // kMemoryLimit
    "Space limit reached",                                // kSpaceLimit
    "No such file or directory",                          // kPathNotFound
    // KMergeOperandsInsufficientCapacity
    "Insufficient capacity for merge operands",
    // kManualCompactionPaused
    "Manual compaction paused",
    " (overwritten)",    // kOverwritten, subcode of OK
    "Txn not prepared",  // kTxnNotPrepared
    "IO fenced off",     // kIOFenced
};

Status::Status(Status::Code _code, Status::SubCode _subcode, const Slice& msg,
               const Slice& msg2, Status::Severity sev)
    : code_(_code),
      subcode_(_subcode),
      sev_(sev),
      retryable_(false),
      data_loss_(false),
      scope_(0) {
  assert(subcode_ != kMaxSubCode);

  const size_t len1 = msg.size();
  const size_t len2 = msg2.size();
  const size_t size = len1 + (len2 ? (2 + len2) : 0);
  char* const result = new char[size + 1];
  // 拷贝 msg
  memcpy(result, msg.data(), len1);
  if (len2 > 0) {
    result[len1] = ':';
    result[len1 + 1] = ' ';
    memcpy(result + len1 + 2, msg2.data(), len2);
  }

  result[size] = '\0'; // c string 的添加终止符
  state_.reset(result);
}


std::string Status::ToString() const {
  const char* type = nullptr;
  switch (code_) {
    case kOk:
      return "OK";
    case kNotFound:
      type = "NotFound: ";
      break;
    case kCorruption:
      type = "Corruption: ";
      break;
    case kNotSupported:
      type = "Not implemented: ";
      break;
    case kInvalidArgument:
      type = "Invalid argument: ";
      break;
    case kIOError:
      type = "IO error: ";
      break;
    case kMergeInProgress:
      type = "Merge in progress: ";
      break;
    case kIncomplete:
      type = "Result incomplete: ";
      break;
    case kShutdownInProgress:
      type = "Shutdown in progress: ";
      break;
    case kTimedOut:
      type = "Operation timed out: ";
      break;
    case kAborted:
      type = "Operation aborted: ";
      break;
    case kBusy:
      type = "Resource busy: ";
      break;
    case kExpired:
      type = "Operation expired: ";
      break;
    case kTryAgain:
      type = "Operation failed. Try again.: ";
      break;
    case kCompactionTooLarge:
      type = "Compaction too large: ";
      break;
    case kColumnFamilyDropped:
      type = "Column family dropped: ";
      break;
    case kMaxCode:
      assert(false);
      break;
  }
  char tmp[30];
  if (type == nullptr) {
    // This should not happen since `code_` should be a valid non-`kMaxCode`
    // member of the `Code` enum. The above switch-statement should have had a
    // case assigning `type` to a corresponding string.
    assert(false);
    snprintf(tmp, sizeof(tmp), "Unknown code(%d): ", static_cast<int>(code()));
    type = tmp;
  }
  std::string result(type);
  if (subcode_ != kNone) {
    uint32_t index = static_cast<int32_t>(subcode_);
    assert(sizeof(msgs) / sizeof(msgs[0]) > index);
    result.append(msgs[index]);
  }

  if (state_ != nullptr) {
    if (subcode_ != kNone) {
      result.append(": ");
    }
    result.append(state_.get());
  }
  return result;
}
}  // namespace ROCKSDB_NAMESPACE
