#pragma once
#include "base.h"
#include "import.h"
#include "types/statement_attribute.h"
#include <boost/optional.hpp>

// SAPPHIRE_AST_DEF(statement_t)

SAPPHIRE_AST_DEF(control_statement_t,
    (import_t, imports)
)

SAPPHIRE_AST_DEF(all_statement_t,
    (boost::optional<control_statement_t>, constrol_statement)
)
