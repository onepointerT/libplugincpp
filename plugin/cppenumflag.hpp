/* 
 * @file enumflag.hpp
 * @brief An enum/string flag
 * @author Sebastian Lau <lauseb644 [at] gmail [dot] com>
 **/
/*
	LibLogC++: An intuitive and highly customizable LGPL library for logging with C++.
	Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/


#pragma once

#include "cppview.hpp"

#include <concepts>
#include <ranges>
#include <set>
#include <string>
#include <utility>
#include <vector>


namespace plugin {
namespace util {



class string_flag {
protected:
    std::string str_flag;
    
public:
    string_flag( const std::string flag );
    
    const std::string operator()() const;
    string_flag& operator=( const std::string str_flag );

    virtual operator std::string() const;

    void clear();
};


template< typename enum_t, class flag_t = string_flag >
using toFlagEnum_f = enum_t (*)( const flag_t flag );
template< typename enum_t, class flag_t = string_flag >
using toFlag_f = flag_t (*)( const enum_t flag_enum_val );

// Forward declaration
template< typename enum_t, class flag_t = string_flag >
class FlagFactory;

template< typename enum_t, class flag_t = string_flag >
class flag_definition_bundle {
protected:
    const toFlagEnum_f< enum_t, flag_t > toFlagEnum;
    const toFlag_f< enum_t, flag_t > fromFlagEnum;
    
    // Unconventional as pointer, NULL means unchosen
    const enum_t* value;
    const flag_t* flag;

    friend class FlagFactory< enum_t, flag_t >;
public:
    flag_definition_bundle( const toFlagEnum_f< enum_t, flag_t > toEnumFunc
                          , const toFlag_f< enum_t, flag_t > toFlagFunc
    )   :   toFlagEnum( toEnumFunc )
        ,   fromFlagEnum( toFlagFunc )
        ,   value( nullptr )
        ,   flag( nullptr )
    {}

    void clear() const {
        this->value = nullptr;
        this->flag = nullptr;
    }

    virtual flag_definition_bundle< enum_t, flag_t >& operator=( const enum_t enum_value ) {
        this->value = &enum_value;
        return *this;
    }
    virtual flag_definition_bundle< enum_t, flag_t >& operator=( const flag_t& flag_value ) {
        this->flag = &flag_value;
        return *this;
    }

    virtual operator flag_t() const {
        if ( this->value != nullptr ) return this->fromFlagEnum( *this->value );
        return *new flag_t("undefined");
    }
    virtual operator enum_t() const {
        if ( this->flag != nullptr ) return this->toFlagEnum( *this->flag );
        return enum_t::undefined;
    }

    bool has_value() const { return this->value != nullptr || this->flag != nullptr; }
};


namespace detail {
template< typename enum_t, class flag_t = string_flag >
class CompareFlagBundle {
public:
    constexpr inline bool operator()( const flag_definition_bundle<enum_t, flag_t>& lhs
                                    , const flag_definition_bundle<enum_t, flag_t>& rhs
    ) {
        return ((flag_t) lhs)() < ((flag_t) rhs)();
    }
    constexpr inline bool equals( const flag_definition_bundle<enum_t, flag_t>& lhs
                                , const flag_definition_bundle<enum_t, flag_t>& rhs
    ) {
        return ((enum_t) lhs) == ((enum_t) rhs);
    }
};

//template< typename enum_t, class flag_t = string_flag >

} // namespace detail


template< typename enum_t, typename flag_t = string_flag >
using flag_pair = std::pair< enum_t, flag_t >;
template< typename enum_t, typename flag_t = string_flag >
using flag_definition = std::vector< flag_pair< enum_t, flag_t > >;



template< class flag_t = util::string_flag >
class flag_bundle final
    :   public std::set< flag_t >
    ,   public util::View< flag_bundle< flag_t > >
{
public:
    typedef typename std::set< flag_t > stlset_t;
    typedef typename stlset_t::iterator iterator;
    typedef typename stlset_t::const_iterator const_iterator;

private:
    typename iterator m_begin;
    typename iterator m_end;

public:
    auto begin() const { return this->m_begin; }
    auto end() const { return this->m_end; }

    flag_bundle( std::vector< std::string >& vec )
        :   std::set< flag_t >()
        ,   m_begin( stlset_t::begin() )
        ,   m_end( stlset_t::end() )
    {
        this->insert_range( std::ranges::subrange{ vec.cbegin(), vec.cend() } );
    }
    flag_bundle( std::initializer_list< std::string > il )
        :   std::set< flag_t >()
        ,   m_begin( stlset_t::begin() )
        ,   m_end( stlset_t::end() )
    {
        for ( const std::string s : il ) {
            this->insert( *new flag_t(s) );
        }
    }

    flag_bundle< flag_t >& operator<<( const flag_t flag ) {
        this->insert( *new flag_t(flag) );
        return *this;
    }
    flag_bundle< flag_t >& operator<<( const std::string sflag ) {
        this->insert( *new flag_t(sflag) );
        return *this;
    }
    bool operator>>( const std::string sflag ) const { return this->contains(sflag); }
    bool operator>>( const flag_t flag ) const { return (*this) >> flag(); }
};



template< typename enum_t, class flag_t = string_flag >
class FlagFactory final
    :   public detail::CompareFlagBundle< enum_t, flag_t >
{
public:
    typedef typename flag_pair< enum_t, flag_t > flag_pair_t;
    typedef typename flag_definition< enum_t, flag_t > flag_vector_t;
    typedef typename flag_definition_bundle< enum_t, flag_t > flag_definition_t;
private:
    template< typename U, typename V >
    concept isEnumFlagOr = requires ( const enum_t e, const flag_t f ) -> bool {
        std::is_base_of_v< string_flag, flag_t > && (
            decltype(U) == decltype(e) || decltype(V) == decltype(f) ||
            decltype(V) == decltype(e) || decltype(U) == decltype(f)
        );
    };
public:
    const flag_definition_t flagdef;
    const flag_vector_t flagvec;

    FlagFactory( const flag_vector_t flagvector
               , const flag_definition_t flagdefinition
    )
        :   detail::CompareFlagBundle< enum_t, flag_t >()
        ,   flagdef( flagdefinition )
        ,   flagvec( flagvector )
    {}

    template< typename T, typename R >
        requires detail::isEnumFlagOr< T, R >
    R operator()( const T value ) const {
        for ( typename flag_vector_t::const_iterator cit : this->flagvec ) {
            flag_pair_t fp = *cit;
            if ( decltype(fp.first) == decltype(T) ) {
                if ( fp.first == value ) return fp.second;
            } else if ( decltype(fp.second) == decltype(T) ) {
                if ( fp.second == value ) return fp.first;
            }
        }
    }

    template<>
    enum_t operator()( const flag_t value ) const {
        for ( typename flag_vector_t::const_iterator cit : this->flagvec ) {
            if ( (*cit).second == value ) return (*cit).first;
        }
        return enum_t::undefined;
    }

    template<>
    flag_t operator()( const enum_t value ) const {
        for ( typename flag_vector_t::const_iterator cit : this->flagvec ) {
            if ( (*cit).second == value ) return (*cit).first;
        }
        return flag_t("undefined");
    }

    FlagFactory& operator|( const toFlagEnum_f toFlagEnum_func ) {
        this->flagdef.toFlagEnum = toFlagEnum_func;
        return *this;
    }
    FlagFactory& operator|( const toFlag_f toFlag_func ) {
        this->flagdef.fromFlagEnum = toFlag_func;
        return *this;
    }
    FlagFactory& operator|( const flag_definition_t flag_definition ) {
        this->flagdef = flag_definition
        return *this;
    }

    enum_t operator&( const flag_t value ) const {
        return (enum_t) this->flagdef( value );
    }

    flag_t operator&( const enum_t value ) const {
        return (flag_t) this->flagdef( value );
    }

    static flag_definition_t& operator=( const toFlagEnum_f< enum_t, flag_t > toEnumFunc
                                       , const toFlag_f< enum_t, flag_t > toFlagFunc );
};


} // namespace util
} // namespace plugin