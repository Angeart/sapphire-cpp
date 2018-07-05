#include <iostream>
#include "grammar/function.hpp"
#include "grammar/skipper.hpp"

namespace detail {

namespace error {
struct unable_parse {};
}
template<
  template<class iterator, class skipper> class rule_t
, class iterator_t = std::string::const_iterator
, class skipper_t = sapphire::core::parser::skipper<iterator_t>
, class result_t = typename rule_t<iterator_t, skipper_t>::start_type::attr_type
>
struct tester_t {
    using result_type = result_t;
    static result_t parse(const std::string& input) {
        skipper_t skipper;
        rule_t<iterator_t,skipper_t> rule;
        result_t result;
        auto it = input.begin();
        const auto& end = input.end();
        if(!boost::spirit::qi::phrase_parse(it,end,rule,skipper,result) || it != end) {
            std::cout << "parse failed" << std::endl;
            std::cout << std::string(it,end) << std::endl;
            // throw error::unable_parse();
            return {};
        }
        return result;
    }
};
}

using tester_t = detail::tester_t<sapphire::core::parser::function>;

int main() {
    const std::string source = "test_03(let arg1 : int) | pattern1 { pattern_body } | { default }";
    std::cout << "input : " << source << std::endl;
    std::cout << "====================================" << std::endl;
    tester_t::result_type result = tester_t::parse(source);
    std::cout << result << std::endl;

}