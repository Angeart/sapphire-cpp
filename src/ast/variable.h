#pragma once
#include "base.h"
#include <string>

namespace sapphire::core::ast {
struct variable_t : ::util::class_identity<variable_t,base_t> {
    std::string attribute;
    std::string name;
    std::string type;
    std::string initializer;

    variable_t() = default;

    variable_t(const std::string& attribute_, const std::string& name_, const std::string& type_, const std::string& initializer_)
    : attribute(attribute_), name(name_), type(type_), initializer(initializer_)
    {}

    bool operator== (const variable_t& rhs) const {
        return this->attribute == rhs.attribute
            && this->name == rhs.name
            && this->type == rhs.type
            && this->initializer == rhs.initializer;
    }
};
}