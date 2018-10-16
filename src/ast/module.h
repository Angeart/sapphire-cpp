#pragma once
#include "base.h"
#include "statement.h"

#include <vector>

SAPPHIRE_AST_DEF(module_t,
    (std::string, name),
    (std::vector<all_statement_t>, statements, SAPPHIRE_AST_DEF_NO_COMPALISON)
)
