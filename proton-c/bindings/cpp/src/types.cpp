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

#include <proton/types.hpp>
#include <proton/type_traits.hpp>
#include <proton/codec.h>
#include <ostream>
#include <iomanip>
#include <algorithm>
#include <sstream>

namespace proton {

std::string type_name(type_id t) {
    switch (t) {
      case NULL_TYPE: return "null";
      case BOOLEAN: return "boolean";
      case UBYTE: return "ubyte";
      case BYTE: return "byte";
      case USHORT: return "ushort";
      case SHORT: return "short";
      case UINT: return "uint";
      case INT: return "int";
      case CHAR: return "char";
      case ULONG: return "ulong";
      case LONG: return "long";
      case TIMESTAMP: return "timestamp";
      case FLOAT: return "float";
      case DOUBLE: return "double";
      case DECIMAL32: return "decimal32";
      case DECIMAL64: return "decimal64";
      case DECIMAL128: return "decimal128";
      case UUID: return "uuid";
      case BINARY: return "binary";
      case STRING: return "string";
      case SYMBOL: return "symbol";
      case DESCRIBED: return "described";
      case ARRAY: return "array";
      case LIST: return "list";
      case  MAP: return "map";
    }
    return "unknown";
}

bool type_id_is_signed_int(type_id t) { return t == BYTE || t == SHORT || t == INT || t == LONG; }
bool type_id_is_unsigned_int(type_id t) { return t == UBYTE || t == USHORT || t == UINT || t == ULONG; }
bool type_id_is_integral(type_id t) { return t == BOOLEAN || t == CHAR || t == TIMESTAMP || type_id_is_unsigned_int(t) || type_id_is_signed_int(t); }
bool type_id_is_floating_point(type_id t) { return t == FLOAT || t == DOUBLE; }
bool type_id_is_decimal(type_id t) { return t == DECIMAL32 || t == DECIMAL64 || t == DECIMAL128; }
bool type_id_is_signed(type_id t) { return type_id_is_signed_int(t) || type_id_is_floating_point(t) || type_id_is_decimal(t); }
bool type_id_is_string_like(type_id t) { return t == BINARY || t == STRING || t == SYMBOL; }
bool type_id_is_container(type_id t) { return t == LIST || t == MAP || t == ARRAY || t == DESCRIBED; }
bool type_id_is_scalar(type_id t) { return type_id_is_integral(t) || type_id_is_floating_point(t) || type_id_is_decimal(t) || type_id_is_string_like(t) || t == TIMESTAMP || t == UUID; }


std::ostream& operator<<(std::ostream& o, type_id t) { return o << type_name(t); }

namespace internal {
start::start(type_id t, type_id e, bool d, size_t s) : type(t), element(e), is_described(d), size(s) {}
start start::array(type_id element, bool described) { return start(ARRAY, element, described); }
start start::list() { return start(LIST); }
start start::map() { return start(MAP); }
start start::described() { return start(DESCRIBED, NULL_TYPE, true); }
}
}
