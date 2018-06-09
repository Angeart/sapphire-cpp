#pragma once
#include "base.h"
#include "types/variable_attribute.h"

#include <string>
#include <iostream>

namespace sapphire::core::ast {
struct variable_t : ::util::class_identity<variable_t,base_t> {
    ::sapphire::core::types::variable_attribute attribute;
    std::string name;
    std::string type;
    std::string initializer;

    variable_t()
    : attribute(::sapphire::core::types::variable_attribute::unknown)
    , name()
    , initializer()
    {}

    variable_t(const ::sapphire::core::types::variable_attribute& attribute_, const std::string& name_, const std::string& type_, const std::string& initializer_)
    : attribute(attribute_), name(name_), type(type_), initializer(initializer_)
    {}

    bool operator== (const variable_t& rhs) const {
        return this->attribute == rhs.attribute
            && this->name == rhs.name
            && this->type == rhs.type
            && this->initializer == rhs.initializer;
    }
    bool operator!= (const variable_t& rhs) const {
        return !this->operator==(rhs);
    }
};
}

std::ostream& operator<<(std::ostream& os, const sapphire::core::ast::variable_t& data) {
    os << std::endl;
    os << "name: " << data.name << std::endl;
    os << "type: " << data.type << std::endl;
    os << "initializer: " << data.initializer << std::endl;
    return os;
}