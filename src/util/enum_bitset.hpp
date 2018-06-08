#pragma once
#include <utility>
#include <bitset>
#include <type_traits>
#include "util/helper.hpp"
namespace util {

template<class target, class base = std::bitset<::util::helper::bit_sizeof_v<std::underlying_type_t<target>>>>
class enum_bitset : public base {
public:
    using base::base;
};
}