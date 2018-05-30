#pragma once
#include <string>
#include <set>

namespace util
{
	namespace detail
	{
		// need types
		//     Key::pointer
		// need functions
		//     Key::empty()->bool const
		template<class Key = std::string, class Comp =std::less<Key> >
		class basic_symbol {
		public:
			typedef unsigned long hash_type;
			typedef Key key_type;

			basic_symbol()
				{ k = &(*key_pool().insert(key_type()).first); }
			basic_symbol(const key_type& key)
				{ k = &(*key_pool().insert(key).first); }
			basic_symbol(typename key_type::const_pointer key)
				{ k = &(*key_pool().insert(key).first); }
			basic_symbol(const basic_symbol& sym)
				: k(sym.k) {}

			basic_symbol& operator=(const basic_symbol& sym)
				{ k = sym.k; return *this; }
			basic_symbol& operator=(const key_type& key)
				{ k = &(*key_pool().insert(key).first); return *this; }

			const key_type& key() const { return *k; }
			hash_type hash() const { return hash_type(k); }

			bool empty() const { return k->empty(); }

		public:
			// explicit delete
			static void pool_erase(const key_type& key)
				{ key_pool().erase(key); }
			static void pool_erase(const basic_symbol& sym)
				{ key_pool().erase(sym.key()); }

		private:
			typedef std::set<key_type, Comp> pool_allocator;
			static pool_allocator& key_pool();
			const key_type* k;

		};

		template<class Key, class Comp>
		typename basic_symbol<Key,Comp>::pool_allocator&
		basic_symbol<Key,Comp>::key_pool() {
			static pool_allocator pool;
			return pool;
		}

		template<class K, class C>
		inline bool operator==(const basic_symbol<K,C>& x, const basic_symbol<K,C>& y)
			{ return x.hash() == y.hash(); }

		template<class K, class C>
		inline bool operator!=(const basic_symbol<K,C>& x, const basic_symbol<K,C>& y)
			{ return x.hash() != y.hash(); }

		template<class K, class C>
		inline bool operator<(const basic_symbol<K,C>& x, const basic_symbol<K,C>& y)
			{ return x.hash() < y.hash(); }

		template<class K, class C>
		inline bool operator<=(const basic_symbol<K,C>& x, const basic_symbol<K,C>& y)
			{ return x.hash() <= y.hash(); }

		template<class K, class C>
		inline bool operator>(const basic_symbol<K,C>& x, const basic_symbol<K,C>& y)
			{ return x.hash() > y.hash(); }

		template<class K, class C>
		inline bool operator>=(const basic_symbol<K,C>& x, const basic_symbol<K,C>& y)
			{ return x.hash() >= y.hash(); }

	}


	using string_symbol = detail::basic_symbol<>;

}

namespace std {
template <class Key>
struct hash<util::detail::basic_symbol<Key>> {
    typename util::detail::basic_symbol<Key>::hash_type operator()(const util::detail::basic_symbol<Key> &v) const {
        return v.hash();
    }
};
}