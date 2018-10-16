#pragma once
#include "base.h"

#include <string>
#include <vector>
#include <boost/algorithm/string/join.hpp>

SAPPHIRE_AST_DEF(import_t,
    (std::vector<std::string>, functions),
    (std::vector<std::string>, modules)
)
