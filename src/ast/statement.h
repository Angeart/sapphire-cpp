#pragma once
#include "base.h"
#include "import.h"
#include "types/statement_attribute.h"
#include <boost/optional.hpp>

namespace sapphire::core::ast {
struct statement_t : ::util::class_identity<statement_t,base_t> {
};
struct control_statement_t : ::util::class_identity<control_statement_t,base_t> {
    import_t imports;

    control_statement_t()
    : imports()
    {};

    control_statement_t(const import_t& imports_)
    : imports(imports_)
    {};
};
struct all_statement_t : ::util::class_identity<all_statement_t,base_t> {
    ::sapphire::core::types::top_statement_type type;
    boost::optional<statement_t> statement;
    boost::optional<control_statement_t> control_statement;

    all_statement_t()
    : statement()
    , control_statement()
    {};

    all_statement_t(const control_statement_t& control_statement_)
    : statement()
    , control_statement(control_statement_)
    {};
};
}

std::ostream& operator<<(std::ostream& os, const ::sapphire::core::ast::statement_t& data) {
    return os;
}

std::ostream& operator<<(std::ostream& os, const ::sapphire::core::ast::control_statement_t& data) {
    os << "import : " << data.imports << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const ::sapphire::core::ast::all_statement_t& data) {
    if(data.statement)
        os << "statement: " << *data.statement << std::endl;
    if(data.control_statement)
        os << "control statement: " << *data.control_statement << std::endl;
    return os;
}