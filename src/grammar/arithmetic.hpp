#pragma once
#include <boost/fusion/include/std_tuple.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>
#include <cstdint>
#include <string>
#include <tuple>

namespace opal {
namespace core {
namespace parser {
enum op_list {
  add,
  sub,
  mul,
  div,
};
struct op_symbols : public boost::spirit::qi::symbols<char, op_list> {
  op_symbols() {
      add
      ("+", op_list::add)
      ("-", op_list::sub)
      ("*", op_list::mul)
      ("/", op_list::div);
  }
};
struct arithmetic_t {
  int32_t left;
  op_list op;
  int32_t right;
};
template <class Iterator>
class test : public boost::spirit::qi::grammar<Iterator, arithmetic_t()> {
 public:
  test() : test::base_type(root) {
    namespace qi = boost::spirit::qi;
    namespace ph = boost::phoenix;
    root = (
      qi::omit[*qi::space] >>
      (qi::int_[(&qi::_val)->*&arithmetic_t::left = qi::_1]) >>
      qi::omit[*qi::space] >>
      op_[(&qi::_val)->*&arithmetic_t::op = qi::_1] >>
      qi::omit[*qi::space] >>
      (qi::int_[(&qi::_val)->*&arithmetic_t::right = qi::_1]));
  };

 private:
  boost::spirit::qi::rule<Iterator, arithmetic_t()> root;
  op_symbols op_;
};
}  // namespace parser
}  // namespace core
}  // namespace opal