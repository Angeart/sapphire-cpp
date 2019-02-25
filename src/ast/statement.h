#pragma once
#include "base.h"
#include "import.h"
#include "comment.h"
#include "types/statement_attribute.h"
#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <vector>

// SAPPHIRE_AST_DEF(statement_t)

SAPPHIRE_AST_DEF(control_statement_t,
    (import_t, imports)
)

// SAPPHIRE_AST_DEF(code_statement_t,
//     (boost::variant<comment_t>, code)
// )

SAPPHIRE_AST_DEF(one_statement_t,
    (boost::optional<control_statement_t>, control_statement),
    (boost::optional<comment_t>, comment)
)

namespace sapphire::core::ast {
using all_statement_t = std::vector<one_statement_t>;
}