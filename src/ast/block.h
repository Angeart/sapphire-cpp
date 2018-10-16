#pragma once
#include "base.h"
#include "statement.h"
#include <vector>


SAPPHIRE_AST_DEF(block_t,
    (std::vector<statement_t>, statements)
)