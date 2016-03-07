#ifndef ANNOTATION_KEY_HPP
#define ANNOTATION_KEY_HPP

/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <proton/scalar.hpp>
#include <proton/symbol.hpp>
#include <proton/types.hpp>

namespace proton {

/// A key for use with AMQP annotation maps.
///
/// An annotation_key can contain either a uint64_t or a proton::symbol.
class annotation_key : public restricted_scalar {
  public:
    annotation_key(uint64_t x = 0) { *this = x; }
    annotation_key(const symbol& x) { *this = x; }
    /// `char*` is encoded as proton::amqp::symbol.
    annotation_key(const char *x) { *this = x; }

    annotation_key& operator=(uint64_t x) { scalar_ = x; return *this; }
    annotation_key& operator=(const symbol& x) { scalar_ = x; return *this; }
    /// `char*` is encoded as proton::amqp::symbol.
    annotation_key& operator=(const char *x) { scalar_ = symbol(x); return *this; }

    /// @name Get methods
    ///
    /// @{
    void get(uint64_t& x) const { scalar_.get(x); }
    void get(symbol& x) const { scalar_.get(x); }
    /// @}

    /// Return the value as type T.
    template<class T> T get() const { T x; get(x); return x; }

  friend class message;
  friend class internal::decoder;
};

}

#endif // ANNOTATION_KEY_HPP
