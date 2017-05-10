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

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "utils/mutex_locker.h"

namespace sync_primitives {

Lock::Lock()
#ifndef NDEBUG
    : lock_taken_(0),
      is_mutex_recursive_(false)
#endif  // NDEBUG
{
  const Int32 status = pthread_mutex_init(&mutex_, NULL);
  if (status != 0) {
    DBG_ERROR("Failed to initialize mutex");
  }
}

Lock::Lock(bool is_mutex_recursive)
#ifndef NDEBUG
    : lock_taken_(0),
      is_mutex_recursive_(is_mutex_recursive)
#endif  // NDEBUG
{
  Int32 status = 0;

  if (is_mutex_recursive) {
    pthread_mutexattr_t attr;

    if (0 != pthread_mutexattr_init(&attr)) {
      DBG_ERROR("Failed to initialize mutex attribute");
    }

    if (0 != pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)) {
      DBG_ERROR("Failed to set mutex type");
    }

    status = pthread_mutex_init(&mutex_, &attr);

    if (0 != pthread_mutexattr_destroy(&attr)) {
      DBG_ERROR("Failed to destroy mutex attribute");
    }
  } else {
    status = pthread_mutex_init(&mutex_, NULL);
  }

  if (status != 0) {
    DBG_ERROR("Failed to initialize mutex");
  }
}

Lock::~Lock() {
#ifndef NDEBUG
  if (lock_taken_ > 0) {
    DBG_ERROR("Destroying non-released mutex(%p)", &mutex_);
  }
#endif
  Int32 status = pthread_mutex_destroy(&mutex_);
  if (status != 0) {
    DBG_ERROR("Failed to destroy mutex(%p) '%s'", &mutex_, strerror(status));
  }
}

void Lock::Acquire() {
  const Int32 status = pthread_mutex_lock(&mutex_);
  if (status != 0) {
    DBG_ERROR("Failed to acquire mutex(%p) '%s'", &mutex_, strerror(status));
  } else {
    AssertFreeAndMarkTaken();
  }
}

void Lock::Release() {
  AssertTakenAndMarkFree();
  const Int32 status = pthread_mutex_unlock(&mutex_);
  if (status != 0) {
    DBG_ERROR("Failed to unlock mutex(%p) '%s'", &mutex_, strerror(status));
  }
}

bool Lock::Try() {
  const Int32 status = pthread_mutex_trylock(&mutex_);
  if (status == 0) {
#ifndef NDEBUG
    lock_taken_++;
#endif
    return true;
  }
  return false;
}

#ifndef NDEBUG
void Lock::AssertFreeAndMarkTaken() {
  if ((lock_taken_ > 0) && !is_mutex_recursive_) {
    DBG_ERROR("Locking already taken not recursive mutex");
    NOTREACHED();
  }
  lock_taken_++;
}
void Lock::AssertTakenAndMarkFree() {
  if (lock_taken_ == 0) {
    DBG_ERROR("Unlocking a mutex that is not taken");
    NOTREACHED();
  }
  lock_taken_--;
}
#endif

}  // namespace sync_primitives
