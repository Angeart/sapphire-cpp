#pragma once
#include <type_traits>
namespace util {
    template<class... T>
    struct inherit{
        template<class...Args>
        inherit(Args&&...){};
    };

    template<class T>
    struct inherit<T> : T{
        template<class...Args>
        inherit(Args&&...args) : T(std::forward<Args>(args)...){};
    };

    template<class H, class... T>
    struct inherit<H,T...> : H, inherit<T...> {
        template<class...Args>
        inherit(Args&&... args) : H(args...), inherit<T...>(std::forward<Args>(args)...){};
    };
}