#include <cstdint>
#include <type_traits>
#include <string>
#include <sstream>
#include <boost/optional.hpp>
#include <boost/core/demangle.hpp>
#include <boost/property_tree/ptree.hpp>


#include <boost/property_tree/json_parser.hpp>
#include <sstream>

namespace util {
    namespace detail {
        template<class target_t>
        struct is_dumpable_t {
            template<class U> static auto check_internal(std::nullptr_t n) -> decltype(std::declval<U>().dump(), std::true_type{});
            template<class U> static auto check_internal(...) -> std::false_type;
            static constexpr auto check() -> bool { return decltype(check_internal<target_t>(nullptr))::value; }
        };

        template<class target_t>
        constexpr auto is_dumpable() -> bool { return is_dumpable_t<target_t>::check(); }

        template<class target_t>
        struct is_streamable_t {
            template<class U> static auto check_internal(std::nullptr_t n) -> decltype(std::cout << std::declval<U>(), std::true_type{});
            template<class U> static auto check_internal(...) -> std::false_type;
            static constexpr auto check() -> bool { return decltype(check_internal<target_t>(nullptr))::value; }
        };

        template<class target_t>
        constexpr auto is_streamable() -> bool { return is_streamable_t<target_t>::check(); }

        template<class target_t>
        struct is_iterable_t {
            template<class U> static auto check_internal(std::nullptr_t n)
            -> decltype(
                std::begin(std::declval<U&>()) != std::end(std::declval<U&>()), // begin/end and operator !=
                void(), // Handle evil operator ,
                ++std::declval<decltype(std::begin(std::declval<U&>()))&>(), // operator ++
                void(*std::begin(std::declval<U&>())), // operator*
                std::true_type{}
            );
            template<class U> static auto check_internal(...) -> std::false_type;
            static constexpr auto check() -> bool { return decltype(check_internal<target_t>(nullptr))::value; }
        };

        template<class target_t>
        constexpr auto is_iterable() -> bool { return is_iterable_t<target_t>::check(); }

        template<class target_t>
        struct is_optional_t : public std::false_type {};

        template<class target_t>
        struct is_optional_t<boost::optional<target_t>> : public std::true_type {};

        template<class target_t>
        constexpr auto is_optional() -> bool { return is_optional_t<target_t>::value; }

        template<class target_t>
        std::string type2str() {
            std::stringstream ss;
            ss << "[" << boost::core::demangle(typeid(target_t).name()) << "]";
            return ss.str();
        }
    }
    struct dumper_t {
        using ptree = boost::property_tree::ptree;
    private:
        std::string basename;
        static constexpr const char* const empty_string = "";
    public:
        ptree root;
    public:
        dumper_t() : basename(""), root() {};
        dumper_t(const std::string& basename_) : basename(basename_), root() {};
        template<class target_t>
        auto operator()(const target_t& d, const std::string& name = empty_string)
        -> std::enable_if_t<
            detail::is_dumpable<target_t>()
        , void> {
            auto tree = d.dump();
            //std::stringstream ss;
            //boost::property_tree::write_json(ss, tree);
            //std::cout << get_name(name) << std::endl;
            //std::cout << ss.str() << std::endl;
            root.add_child(get_name(name), tree);
        };
        template<class target_t>
        auto operator()(const target_t& d, const std::string& name = empty_string)
        -> std::enable_if_t<
            !detail::is_dumpable<target_t>()
            && !detail::is_streamable<target_t>()
            && detail::is_iterable<target_t>()
            && !detail::is_optional<target_t>()
        , void> {
            ptree child;
            for(auto &item : d) {
                dumper_t temp{""};
                temp(item,"value");
                child.push_back(std::make_pair("",temp.root));
            }
            root.add_child(get_name(name), child);
        }
        template<class target_t>
        auto operator()(const target_t& d, const std::string& name = empty_string)
        -> std::enable_if_t<
            !detail::is_dumpable<target_t>()
            && !detail::is_streamable<target_t>()
            && !detail::is_iterable<target_t>()
            && !detail::is_optional<target_t>()
        , void> {
            root.put(get_name(name), "can not show a content.");
        };
        template<class target_t>
        auto operator()(const target_t& d, const std::string& name = empty_string)
        -> std::enable_if_t<
            !detail::is_dumpable<target_t>()
            && detail::is_streamable<target_t>()
            && !detail::is_optional<target_t>()
        , void> {
            root.put(get_name(name), d);
        }
        template<class target_t>
        auto operator()(const target_t& d, const std::string& name = empty_string)
        -> std::enable_if_t<
            detail::is_optional<target_t>()
        , void> {
            if(!d) {
                root.put(get_name(name), "none");
            } else {
                this->operator()(*d, name);
            }
        }
    private:
        std::string&& get_name(const std::string& name) const {
            std::string result = (basename.size() == 0u ? "" : (basename + ".")) + name;
            return std::move(result);
        }

    };
}