#pragma once
#include <type_traits>
#include <utility>

namespace util{

	namespace internal {
		template <typename T, typename Tag, bool IsClass, bool IsConstexpr>
		struct opaque_alias : public T
		{
		private:
			using self = opaque_alias<T, Tag, IsClass, IsConstexpr>;
		public:
			using prototype = T;
			// follow line is need c++0x flag
			// using T::T; // derive ctor
			// instead emurate on variadic template
			template<typename ...Args>
			opaque_alias(Args&& ... args) : T(std::forward<Args>(args)...) {};

			opaque_alias() = default;
			opaque_alias(self const & right) = default;
			opaque_alias(self && right)= default;

			self & operator = (self const & right) = default;
			self & operator = (self && right) = default;

			opaque_alias(T const & value) : T(value) {}
			opaque_alias(T && value) : T(std::move(value)) {}

			T & cast() { return *static_cast<T *>(this); }
			T const & cast() const { return *static_cast<T const *>(this); }
		};

		template <typename T, typename Tag>
		struct opaque_alias<T, Tag, false, false>
		{
		private:
			using self = opaque_alias<T, Tag, false, false>;
			T value;
		public:
			using prototype = T;

			opaque_alias() = default;
			opaque_alias(self const &) = default;
			opaque_alias(self &&) = default;

			self & operator = (self const &) = default;
			self & operator = (self &&) = default;

			opaque_alias(T const & value) : value(value) {}
			opaque_alias(T && value) : value(std::move(value)) {}

			T & cast() { return value; }
			T const & cast() const { return value; }
		};

		template <typename T, typename Tag>
		struct opaque_alias<T, Tag, false, true>
		{
		private:
			using self = opaque_alias<T, Tag, false, true>;
			T value;
		public:
			using prototype = T;

			constexpr opaque_alias() = default;
			constexpr opaque_alias(self const &) = default;
			constexpr opaque_alias(self &&) = default;

			constexpr self & operator = (self const &) = default;
			constexpr self & operator = (self &&) = default;

			constexpr opaque_alias(T const & value) : value(value) {}
			constexpr opaque_alias(T && value) : value(std::move(value)) {}

			constexpr T & cast() { return value; }
			constexpr T const & cast() const { return value; }
		};
	} // internal

    template <typename T, typename Tag>
    using opaque_alias = internal::opaque_alias<T, Tag, std::is_class<T>::value,false>;
    template <typename T, typename Tag>
    using constexpr_opaque_alias = internal::opaque_alias<T, Tag, std::is_class<T>::value,true>;
}