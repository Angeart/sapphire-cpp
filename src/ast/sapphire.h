#pragma once
#include "base.h"
#include "statement.h"
#include <vector>

SAPPHIRE_AST_DEF(sapphire_t,
    (std::vector<all_statement_t>, statements)
)
