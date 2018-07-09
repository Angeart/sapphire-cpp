#pragma once
#include "base.h"
#include "statement.h"
#include <vector>

namespace sapphire::core::ast {
struct sapphire_t : ::util::class_identity<sapphire_t,base_t> {
    std::vector<all_statement_t> statements;

    sapphire_t()
    : statements()
    {};

    sapphire_t(const std::vector<all_statement_t>& statements_)
    : statements(statements_)
    {};
};
}

std::ostream& operator<<(std::ostream& os, const ::sapphire::core::ast::sapphire_t& data) {
    for(const auto& statement : data.statements) {
        os << statement << std::endl;
    }
    return os;
}