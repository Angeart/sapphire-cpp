#pragma once
#include "base.h"

#include <string>
#include <vector>
#include <boost/algorithm/string/join.hpp>

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

std::ostream& operator<<(std::ostream& os, const sapphire::core::ast::import_t& data) {
    os << "functions: " << boost::algorithm::join(data.functions, ",") << std::endl;
    os << "modules: " << boost::algorithm::join(data.modules, ",") << std::endl;
    return os;
}