#pragma once
#include <type_traits>
namespace util::helper {
template<class T>
struct bit_sizeof {
    using size = std::integral_constant<size_t,sizeof(T) * 8u>;
};
template<class T>
constexpr auto bit_sizeof_v = bit_sizeof<T>::size::value;
}