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

#ifndef COMPONENTS_UTILS_PUBLISHER_INTERFACE_H_
#define COMPONENTS_UTILS_PUBLISHER_INTERFACE_H_
#include <vector>
#include <algorithm>
#include "utils/mutex_locker.h"
#include "utils/data_accessor.h"

namespace utils {
template <class T>
class Publisher {
 protected:
  typedef std::vector<T*> ListenersVector;

 public:
  virtual ~Publisher() { listeners_.clear(); }

  bool AddListener(T* const listener) {
    DCHECK_OR_RETURN(listener, false);
    const sync_primitives::AutoLock scope_lock(&listeners_lock_);
    typename ListenersVector::iterator it =
        std::find(listeners_.begin(), listeners_.end(), listener);
    if (it == listeners_.end()) {
      DBG_WARNING("AddListener %p ", listener);
      listeners_.push_back(listener);
      return true;
    }
    DBG_WARNING("Listener is already added %p ", listener);
    return false;
  }

  bool RemoveListener(T* const listener) {
    DCHECK_OR_RETURN(listener, false);
    const sync_primitives::AutoLock scope_lock(&listeners_lock_);
    typename ListenersVector::iterator it =
        std::find(listeners_.begin(), listeners_.end(), listener);
    if (it != listeners_.end()) {
      DBG_WARNING("Remove listener %p ", listener);
      listeners_.erase(it);
      return true;
    }
    DBG_WARNING("Unable to remove listener %p ", listener);
    return false;
  }

 protected:
  DataAccessor<ListenersVector> get_listeners() {
    return DataAccessor<ListenersVector>(&listeners_, &listeners_lock_);
  }

 private:
  ListenersVector listeners_;
  sync_primitives::Lock listeners_lock_;
};
}  // namespace utils
#endif  // SRC_FRAMEWORK_UTILS_PUBLISHER_INTERFACE_H_
