// Copyright 2025 The OnePointer Authors.
//

#pragma once

#include <initializer_list>
#include <string>
#include <ranges>
#include <utility>


namespace plugin {
namespace util {


template< typename N = uint8_t >
class LinkedRange
    :   public std::pair< LinkedRange< N >*, LinkedRange< N >* >
    ,   public N
{
public:
    const std::string name;
    const N from;
    const N to;

    LinkedRange( const N number, const N from, const N to, const std::string name
               , LinkedRange< N >* lhs = nullptr, LinkedRange< N >* rhs = nullptr )
        :   std::pair{ lhs, rhs }
        ,   N( number )
        ,   name( name )
        ,   from( from )
        ,   to( to )
    {}

    LinkedRange< N >& operator+( const N other_num ) {
        if ( other_num + *this > this->to ) {
            N interval_size = this->to - this->from;
            N overflow = other_num % interval_size;
            overflow += ((*this + other_num) % interval_size) - overflow;
            if ( this->first != nullptr ) {
                this->first + overflow;
            }
            *this += other_num - (overflow * interval_size);
        } else *this += other_num;
        return *this;
    }

    LinkedRange< N >& operator-( const N other_num ) {
        if ( other_num - *this < this->from ) {
            N interval_size = this->to - this->from;
            N overflow = other_num % interval_size;
            overflow += ((*this - other_num) % interval_size) - overflow;
            if ( this->second != nullptr ) {
                this->second - overflow;
            }
            *this -= other_num - (overflow * interval_size);
        } else *this -= other_num;
        return *this;
    }
};


template< class N = uint8_t >
class LinkedRangeCalc {
public:
    LinkedRange< N >& first;
    LinkedRange< N >& last;
    LinkedRange< N >& current;

    LinkedRangeCalc( std::initializer_list< std::pair<N, N> > il );
    LinkedRangeCalc( std::initializer_list< std::pair<std::pair<N, N>, std::string> il );
};


} // namespace util
} // namespace plugin
