#pragma once
#include <cstdint>
namespace sapphire::core::types {
enum class top_statement_type : uint32_t {
    statement,
    control_statement,
};

enum class statement_type : uint32_t {
    block,
    expressions,
    declarations,
    eol,
};
}