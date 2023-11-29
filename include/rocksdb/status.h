//
// Created by zhaoyouqing on 2023/11/27.
//

#pragma once

#include <memory>
#include "slice.h"

namespace ROCKSDB_NAMESPACE {

class Status {
 public:
  Status()
      : code_(kOk),
        subcode_(kNone),
        sev_(kNoError),
        retryable_(false),
        data_loss_(false),
        scope_(0),
        state_(nullptr) {}

  ~Status() {}
  // 从一个Status拷贝
  Status(const Status& s);
  Status& operator=(const Status& s);
  Status(Status&& s) noexcept;
  Status& operator=(Status&& s) noexcept;

  enum Code : unsigned char {
    kOk = 0,
    kNotFound = 1,
    kCorruption = 2,
    kNotSupported = 3,
    kInvalidArgument = 4,
    kIOError = 5,
    kMergeInProgress = 6,
    kIncomplete = 7,
    kShutdownInProgress = 8,
    kTimedOut = 9,
    kAborted = 10,
    kBusy = 11,
    kExpired = 12,
    kTryAgain = 13,
    kCompactionTooLarge = 14,
    kColumnFamilyDropped = 15,
    kMaxCode
  };
  Code code() const {
    return code_;
  }
  enum SubCode : unsigned char {
    kNone = 0,
    kMutexTimeout = 1,
    kLockTimeout = 2,
    kLockLimit = 3,
    kNoSpace = 4,
    kDeadlock = 5,
    kStaleFile = 6,
    kMemoryLimit = 7,
    kSpaceLimit = 8,
    kPathNotFound = 9,
    KMergeOperandsInsufficientCapacity = 10,
    kManualCompactionPaused = 11,
    kOverwritten = 12,
    kTxnNotPrepared = 13,
    kIOFenced = 14,
    kMaxSubCode
  };
  SubCode subcode() const {
    return subcode_;
  }
  enum Severity : unsigned char {
    kNoError = 0,
    kSoftError = 1,
    kHardError = 2,
    kFatalError = 3,
    kUnrecoverableError = 4,
    kMaxSeverity
  };

  Severity severity() const {
    return sev_;
  }

  // Return a success status.
  static Status OK() { return Status(); }

  // Successful, though an existing something was overwritten
  // Note: using variants of OK status for program logic is discouraged,
  // but it can be useful for communicating statistical information without
  // changing public APIs.
  static Status OkOverwritten() { return Status(kOk, kOverwritten); }

  // Return error status of an appropriate type.
  static Status NotFound(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kNotFound, msg, msg2);
  }

  // Fast path for not found without malloc;
  static Status NotFound(SubCode msg = kNone) { return Status(kNotFound, msg); }

  static Status NotFound(SubCode sc, const Slice& msg,
                         const Slice& msg2 = Slice()) {
    return Status(kNotFound, sc, msg, msg2);
  }

  static Status Corruption(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kCorruption, msg, msg2);
  }
  static Status Corruption(SubCode msg = kNone) {
    return Status(kCorruption, msg);
  }

  static Status NotSupported(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kNotSupported, msg, msg2);
  }
  static Status NotSupported(SubCode msg = kNone) {
    return Status(kNotSupported, msg);
  }

  static Status InvalidArgument(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kInvalidArgument, msg, msg2);
  }
  static Status InvalidArgument(SubCode msg = kNone) {
    return Status(kInvalidArgument, msg);
  }

  static Status IOError(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kIOError, msg, msg2);
  }
  static Status IOError(SubCode msg = kNone) { return Status(kIOError, msg); }

  static Status MergeInProgress(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kMergeInProgress, msg, msg2);
  }
  static Status MergeInProgress(SubCode msg = kNone) {
    return Status(kMergeInProgress, msg);
  }

  static Status Incomplete(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kIncomplete, msg, msg2);
  }
  static Status Incomplete(SubCode msg = kNone) {
    return Status(kIncomplete, msg);
  }

  static Status ShutdownInProgress(SubCode msg = kNone) {
    return Status(kShutdownInProgress, msg);
  }
  static Status ShutdownInProgress(const Slice& msg,
                                   const Slice& msg2 = Slice()) {
    return Status(kShutdownInProgress, msg, msg2);
  }
  static Status Aborted(SubCode msg = kNone) { return Status(kAborted, msg); }
  static Status Aborted(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kAborted, msg, msg2);
  }

  static Status Busy(SubCode msg = kNone) { return Status(kBusy, msg); }
  static Status Busy(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kBusy, msg, msg2);
  }

  static Status TimedOut(SubCode msg = kNone) { return Status(kTimedOut, msg); }
  static Status TimedOut(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kTimedOut, msg, msg2);
  }

  static Status Expired(SubCode msg = kNone) { return Status(kExpired, msg); }
  static Status Expired(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kExpired, msg, msg2);
  }

  static Status TryAgain(SubCode msg = kNone) { return Status(kTryAgain, msg); }
  static Status TryAgain(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kTryAgain, msg, msg2);
  }

  static Status CompactionTooLarge(SubCode msg = kNone) {
    return Status(kCompactionTooLarge, msg);
  }
  static Status CompactionTooLarge(const Slice& msg,
                                   const Slice& msg2 = Slice()) {
    return Status(kCompactionTooLarge, msg, msg2);
  }

  static Status ColumnFamilyDropped(SubCode msg = kNone) {
    return Status(kColumnFamilyDropped, msg);
  }

  static Status ColumnFamilyDropped(const Slice& msg,
                                    const Slice& msg2 = Slice()) {
    return Status(kColumnFamilyDropped, msg, msg2);
  }

  static Status NoSpace() { return Status(kIOError, kNoSpace); }
  static Status NoSpace(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kIOError, kNoSpace, msg, msg2);
  }

  static Status MemoryLimit() { return Status(kAborted, kMemoryLimit); }
  static Status MemoryLimit(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kAborted, kMemoryLimit, msg, msg2);
  }

  static Status SpaceLimit() { return Status(kIOError, kSpaceLimit); }
  static Status SpaceLimit(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kIOError, kSpaceLimit, msg, msg2);
  }

  static Status PathNotFound() { return Status(kIOError, kPathNotFound); }
  static Status PathNotFound(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kIOError, kPathNotFound, msg, msg2);
  }

  static Status TxnNotPrepared() {
    return Status(kInvalidArgument, kTxnNotPrepared);
  }
  static Status TxnNotPrepared(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kInvalidArgument, kTxnNotPrepared, msg, msg2);
  }
  bool ok() const {
      return code() == kOk;
  }

  std::string ToString() const;

  // for test
//  Code code_;
//  SubCode subcode_;
//  Severity sev_;
//  bool retryable_;
//  bool data_loss_;
//  unsigned char scope_;
//  std::unique_ptr<const char[]> state_;
 protected:
  Code code_;
  SubCode subcode_;
  Severity sev_;
  bool retryable_;
  bool data_loss_;
  unsigned char scope_;
  std::unique_ptr<const char[]> state_;

  explicit Status(Code _code, SubCode _subcode = kNone)
      : code_(_code),
        subcode_(_subcode),
        sev_(kNoError),
        retryable_(false),
        data_loss_(false),
        scope_(0) {}

  explicit Status(Code _code, SubCode _subcode, bool retryable, bool data_loss,
                  unsigned char scope)
      : code_(_code),
        subcode_(_subcode),
        sev_(kNoError),
        retryable_(retryable),
        data_loss_(data_loss),
        scope_(scope) {}

  Status(Code _code, SubCode _subcode, const Slice& msg, const Slice& msg2,
         Severity sev = kNoError);
  Status(Code _code, const Slice& msg, const Slice& msg2)
      : Status(_code, kNone, msg, msg2) {}
  static std::unique_ptr<const char[]> CopyState(const char* s);
};

inline Status::Status(const Status& s)
    : code_(s.code_),
      subcode_(s.subcode_),
      sev_(s.sev_),
      retryable_(s.retryable_),
      data_loss_(s.data_loss_),
      scope_(s.scope_) {
  if (s.state_ == nullptr) {
    state_ = nullptr;
  } else {
    state_ = Status::CopyState(s.state_.get());
  }
}
Status& Status::operator=(const Status& s) {
  if (this == &s) {
    // 同一个对象，直接返回
    return *this;
  } else {
    // 不是同一个对象，数据拷贝
    code_ = s.code_;
    subcode_ = s.subcode_;
    sev_ = s.sev_;
    retryable_ = s.retryable_;
    data_loss_ = s.data_loss_;
    scope_ = s.scope_;
    state_ = (s.state_ == nullptr) ? nullptr : CopyState(s.state_.get());
    return *this;
  }
}
inline Status::Status(Status&& s) noexcept : Status() { *this = std::move(s); }
inline Status& Status::operator=(Status&& s) noexcept {

  if (this == &s) {
    return *this;
  } else {
    code_ = std::move(s.code_);
    s.code_ = kOk;
    subcode_ = std::move(s.subcode_);
    s.subcode_ = kNone;
    sev_ = std::move(s.sev_);
    s.sev_ = kNoError;
    retryable_ = std::move(s.retryable_);
    s.retryable_ = false;
    data_loss_ = std::move(s.data_loss_);
    s.data_loss_ = false;
    scope_ = std::move(s.scope_);
    s.scope_ = 0;
    state_ = std::move(s.state_);
    return *this;
  }
}
}  // namespace ROCKSDB_NAMESPACE