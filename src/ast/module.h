#pragma once
#include "base.h"
#include "statement.h"

#include <vector>

namespace sapphire::core::ast {
struct module_t : ::util::class_identity<module_t,base_t> {
    std::string name;
    std::vector<all_statement_t> statements

    module_t()
    : name()
    {}

    module_t(const std::string& name_)
    : name(name_)
    {}

    bool operator== (const module_t& rhs) const {
        return this->name == rhs.name;
    }
    bool operator!= (const module_t& rhs) const {
        return !this->operator==(rhs);
    }
};
}