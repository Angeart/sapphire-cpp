#pragma once
#include "base.h"
#include "statement.h"
#include <vector>

namespace sapphire::core::ast {
struct block_t : ::util::class_identity<block_t,base_t> {
    std::vector<statement_t> statements;
};
}