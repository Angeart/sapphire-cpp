#pragma once
#include "base.h"

#include <string>
#include <vector>

namespace sapphire::core::ast {
struct import_t : ::util::class_identity<import_t,base_t> {
    std::vector<std::string> functions;
    std::vector<std::string> modules;

    import_t(const std::vector<std::string>& functions_, const std::vector<std::string>& modules_)
    : functions(functions_)
    , modules(modules_)
    {}

    import_t()
    : functions()
    , modules()
    {}

    bool operator== (const import_t& rhs) const {
        return this->functions == rhs.functions
            && this->modules == rhs.modules;
    }
    bool operator!= (const import_t& rhs) const {
        return !this->operator==(rhs);
    }
};
}