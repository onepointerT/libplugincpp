// Copyright 2025 The OnePointer Authors.
//

#include "cppenumflag.hpp"


namespace plugin {
namespace util {


string_flag::string_flag( const std::string flag )
    :   str_flag( flag )
{}
    
const std::string string_flag::operator()() const {
    return this->str_flag;
}

string_flag& string_flag::operator=( const std::string str_flag ) {
    this->str_flag = str_flag;
    return *this;
}

string_flag::operator std::string() const {
    return (*this)();
}

void string_flag::clear() {
    this->str_flag.clear();
}


} // namespace util
} // namespace plugin
