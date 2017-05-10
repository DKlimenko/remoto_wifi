/*
 * Copyright (c) 2016, Ford Motor Company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef COMPONENTS_UTILS_ATOMIC_H_
#define COMPONENTS_UTILS_ATOMIC_H_

#include "utils/rwlock.h"
#include "utils/condition_variable.h"
#include "utils/macro.h"
#include "utils/types.h"

#ifdef __QNXNTO__
#include <atomic.h>
#endif

#if defined(__QNXNTO__)
#define atomic_post_inc(ptr) atomic_add_value((ptr), 1)
#elif defined(__GNUG__)
#define atomic_post_inc(ptr) __sync_fetch_and_add((ptr), 1)
#else
#warning "atomic_post_inc() implementation is not atomic"
#define atomic_post_inc(ptr) (*(ptr))++
#endif

#if defined(__QNXNTO__)
#define atomic_post_dec(ptr) atomic_sub_value((ptr), 1)
#elif defined(__GNUG__)
#define atomic_post_dec(ptr) __sync_fetch_and_sub((ptr), 1)
#else
#warning "atomic_post_dec() implementation is not atomic"
#define atomic_post_dec(ptr) (*(ptr))--
#endif

#if defined(__QNXNTO__)
// on QNX pointer assignment is believed to be atomic
#define atomic_pointer_assign(dst, src) (dst) = (src)
#elif defined(__GNUG__)
// with g++ pointer assignment is believed to be atomic
#define atomic_pointer_assign(dst, src) (dst) = (src)
#else
#warning atomic_pointer_assign() implementation may be non-atomic
#define atomic_pointer_assign(dst, src) (dst) = (src)
#endif

#if defined(__QNXNTO__)
#define atomic_post_set(dst) atomic_set_value(dst, 1)
#elif defined(__GNUG__)
#define atomic_post_set(dst) __sync_val_compare_and_swap((dst), 0, 1)
#else
#error "atomic post set operation not defined"
#endif

#if defined(__QNXNTO__)
#define atomic_post_clr(dst) atomic_clr_value(dst, 1)
#elif defined(__GNUG__)
#define atomic_post_clr(dst) __sync_val_compare_and_swap((dst), 1, 0)
#else
#error "atomic post clear operation not defined"
#endif
namespace sync_primitives {

/**
 * @brief Allows to safely change stored value from different threads.
 *
 * The usage example:
 *
 * threads::Atomic<int> i;
 *
 * i = 5; // here SDL is able to guarantee that this value will be safely
 *        // assigned even in multi threaded environment.
 */
template <typename T>
class Atomic {
 public:
  /**
   * @brief Atomic allows to construct atomic object.
   * The operation is not atomic.
   *
   * @param value the value to initialize object with.
   */
  explicit Atomic(const T& value) : value_(value) {}

  /**
   * @brief operator = thread safe setter for stored value.
   *
   * @param val value to assign.
   *
   * @return mofified value.
   */
  T& operator=(const T& val) {
    sync_primitives::AutoWriteLock lock(rw_lock_);
    value_ = val;
    return value_;
  }

  /**
   * @brief operator T thread safe getter
   *
   * return stored value.
   */
  operator T() const {
    sync_primitives::AutoReadLock lock(rw_lock_);
    return value_;
  }

  /**
   * @brief operator T thread safe getter
   *
   * return stored value.
   */
  template <typename U>
  operator U() const {
    sync_primitives::AutoReadLock lock(rw_lock_);
    return static_cast<U>(value_);
  }

 private:
  T value_;
  mutable sync_primitives::RWLock rw_lock_;
};

typedef Atomic<Int8> atomic_int8;
typedef Atomic<UInt8> atomic_uint8;
typedef Atomic<Int16> atomic_int16;
typedef Atomic<UInt16> atomic_uint16;
typedef Atomic<Int32> atomic_int32;
typedef Atomic<UInt32> atomic_uint32;
typedef Atomic<Int64> atomic_int64;
typedef Atomic<UInt64> atomic_uint64;
typedef Atomic<size_t> atomic_size_t;
typedef Atomic<bool> atomic_bool;

}  // namespace sync_primitives

#endif  // SRC_FRAMEWORK_UTILS_ATOMIC_H_
