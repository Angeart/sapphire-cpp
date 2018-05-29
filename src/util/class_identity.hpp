#pragma once
#include <cstdint>
#include "util/inherit.hpp"

namespace util {
    namespace class_identity_detail {
        using class_identifier_t = uint32_t;
        struct identity_factory {
            static class_identifier_t get_id() {
                static class_identifier_t value = 0;
                return value++;
            }
        };

        template<class T>
        struct identity_holder {
            using value_type = class_identifier_t;
            identity_holder() : value(identity_factory::get_id()) {};
            static class_identifier_t get_identity() {
                static const identity_holder temp;
                return temp.get_internal_identity();
            }
        private:
            class_identifier_t get_internal_identity() const {
                return this->value;
            }
            const class_identifier_t value;
        };
        template<class T, class...Bases>
        struct class_identity : public inherit<Bases...>{
            template<class...Args>
            class_identity(Args&&... args) : inherit<Bases...>(std::forward<Args>(args)...) {};
            using base_type = class_identity;
            using identity_type = identity_holder<T>;
            virtual typename identity_type::value_type get_identity() const {
                return identity_type::get_identity();
            }
            static typename identity_type::value_type get_identity_static() {
                return identity_type::get_identity();
            }
        };
    }
    namespace types {
        using class_identifier_t = class_identity_detail::class_identifier_t;
    }
    template<class T, class... Bases>
    using class_identity = class_identity_detail::class_identity<T, Bases...>;
}