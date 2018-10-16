#pragma once
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/size.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <sstream>
#include <iostream>
#include <memory>

#include "util/class_identity.hpp"
#include "util/dumper.hpp"

namespace sapphire::core::ast {
struct base_t : ::util::class_identity<base_t> {};
}

#define SAPPHIRE_AST_DEF_MEMBER_DECLARATION(r, _, tuple) \
BOOST_PP_TUPLE_ELEM(2,0,tuple) BOOST_PP_TUPLE_ELEM(2,1,tuple);


#define SAPPHIRE_AST_DEF_CONSTRUCTOR_ARGUMENTS_CR(z, n, seq) \
BOOST_PP_IF(n, BOOST_PP_COMMA, BOOST_PP_EMPTY)() const BOOST_PP_TUPLE_ELEM(BOOST_PP_TUPLE_SIZE(seq), 0, BOOST_PP_SEQ_ELEM(n,seq))& BOOST_PP_CAT(_,BOOST_PP_TUPLE_ELEM(BOOST_PP_TUPLE_SIZE(seq), 1, BOOST_PP_SEQ_ELEM(n,seq)))
#define SAPPHIRE_AST_DEF_CONSTRUCTOR_ARGUMENTS_MV(z, n, seq) \
BOOST_PP_IF(n, BOOST_PP_COMMA, BOOST_PP_EMPTY)() BOOST_PP_TUPLE_ELEM(BOOST_PP_TUPLE_SIZE(seq), 0, BOOST_PP_SEQ_ELEM(n,seq))&& BOOST_PP_CAT(_,BOOST_PP_TUPLE_ELEM(BOOST_PP_TUPLE_SIZE(seq), 1, BOOST_PP_SEQ_ELEM(n,seq)))
#define SAPPHIRE_AST_DEF_CONSTRUCTOR_ASIGNNER(z, n, seq) \
BOOST_PP_IF(n, BOOST_PP_COMMA, BOOST_PP_EMPTY)() BOOST_PP_TUPLE_ELEM(BOOST_PP_TUPLE_SIZE(seq), 1, BOOST_PP_SEQ_ELEM(n,seq))(BOOST_PP_CAT(_,BOOST_PP_TUPLE_ELEM(BOOST_PP_TUPLE_SIZE(seq), 1, BOOST_PP_SEQ_ELEM(n,seq))))
#define SAPPHIRE_AST_DEF_CONSTRUCTOR_ASSIGNNABLE(name, seq) \
name(BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(seq),SAPPHIRE_AST_DEF_CONSTRUCTOR_ARGUMENTS_CR, seq)) : BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(seq),SAPPHIRE_AST_DEF_CONSTRUCTOR_ASIGNNER, seq) {}; \
name(BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(seq),SAPPHIRE_AST_DEF_CONSTRUCTOR_ARGUMENTS_MV, seq)) : BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(seq),SAPPHIRE_AST_DEF_CONSTRUCTOR_ASIGNNER, seq) {};

#define SAPPHIRE_AST_DEF_CONSTRUCTOR(name) \
name() = default; \
name(const name&) = default; \
name(name&&) = default; \
name& operator=(const name&) = default; \
name& operator=(name&&) = default;

#define SAPPHIRE_AST_DEF_DUMP_INTERNAL_SEQ(z, n, seq) \
BOOST_PP_IF(n, BOOST_PP_COMMA, BOOST_PP_EMPTY)() dumper(this->BOOST_PP_TUPLE_ELEM(BOOST_PP_TUPLE_SIZE(seq), 1, BOOST_PP_SEQ_ELEM(n,seq)),BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(BOOST_PP_TUPLE_SIZE(seq), 1, BOOST_PP_SEQ_ELEM(n,seq))))

#define SAPPHIRE_AST_DEF_DUMP_INTERNAL(seq) \
BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(seq),SAPPHIRE_AST_DEF_DUMP_INTERNAL_SEQ, seq)

#define SAPPHIRE_AST_DEF_DUMP(name, seq) \
virtual boost::property_tree::ptree dump() const { \
    util::dumper_t dumper{#name}; \
    SAPPHIRE_AST_DEF_DUMP_INTERNAL(seq); \
    return dumper.root; \
} \
std::string&& to_string() const { \
    std::stringstream ss; \
    auto tree = this->dump(); \
    boost::property_tree::write_json(ss, tree); \
    return std::move(ss.str()); \
}

#define SAPPHIRE_AST_DEF_NO_COMPALISON 0

#define SAPPHIRE_AST_DEF_COMPALISON_INTERNAL_SEQ_OP() &&

#define SAPPHIRE_AST_DEF_COMPALISON_INTERNAL_SEQ_WRAP_C(z, n, seq) BOOST_PP_EMPTY()

#define SAPPHIRE_AST_DEF_COMPALISON_INTERNAL_SEQ_WRAP_B(z, n, seq) \
BOOST_PP_IF(n, SAPPHIRE_AST_DEF_COMPALISON_INTERNAL_SEQ_OP, BOOST_PP_EMPTY)() this->BOOST_PP_TUPLE_ELEM(BOOST_PP_TUPLE_SIZE(seq), 1, BOOST_PP_SEQ_ELEM(n,seq)) == rhs.BOOST_PP_TUPLE_ELEM(BOOST_PP_TUPLE_SIZE(seq), 1, BOOST_PP_SEQ_ELEM(n,seq))

#define SAPPHIRE_AST_DEF_COMPALISON_INTERNAL_SEQ_WRAP_A(z, n, seq) \
BOOST_PP_IF(BOOST_PP_EQUAL(BOOST_PP_TUPLE_ELEM(BOOST_PP_TUPLE_SIZE(BOOST_PP_SEQ_ELEM(n,seq)), 2, BOOST_PP_SEQ_ELEM(n,seq)),SAPPHIRE_AST_DEF_NO_COMPALISON),SAPPHIRE_AST_DEF_COMPALISON_INTERNAL_SEQ_WRAP_C,SAPPHIRE_AST_DEF_COMPALISON_INTERNAL_SEQ_WRAP_B)(z,n,seq)

#define SAPPHIRE_AST_DEF_COMPALISON_INTERNAL_SEQ_WRAP(z, n, seq) \
BOOST_PP_IF(BOOST_PP_EQUAL(BOOST_PP_TUPLE_SIZE(BOOST_PP_SEQ_ELEM(n,seq)),3),SAPPHIRE_AST_DEF_COMPALISON_INTERNAL_SEQ_WRAP_A,SAPPHIRE_AST_DEF_COMPALISON_INTERNAL_SEQ_WRAP_B)(z,n,seq)

#define SAPPHIRE_AST_DEF_COMPALISON_INTERNAL(seq) \
BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(seq),SAPPHIRE_AST_DEF_COMPALISON_INTERNAL_SEQ_WRAP, seq)

#define SAPPHIRE_AST_DEF_COMPALISON(name, seq) \
bool operator== (const name& rhs) const { \
    return SAPPHIRE_AST_DEF_COMPALISON_INTERNAL(seq); \
} \
bool operator!= (const name& rhs) const { \
    return !this->operator==(rhs); \
}

#define SAPPHIRE_AST_DEF_I(name, seq) \
namespace sapphire::core::ast { \
    struct name : ::util::class_identity<name,base_t> { \
        BOOST_PP_SEQ_FOR_EACH(SAPPHIRE_AST_DEF_MEMBER_DECLARATION, _, seq) \
        SAPPHIRE_AST_DEF_CONSTRUCTOR(name) \
        SAPPHIRE_AST_DEF_CONSTRUCTOR_ASSIGNNABLE(name, seq) \
        SAPPHIRE_AST_DEF_DUMP(name, seq) \
        SAPPHIRE_AST_DEF_COMPALISON(name, seq) \
    }; \
}

#define SAPPHIRE_AST_DEF(name, ...) SAPPHIRE_AST_DEF_I(name, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))