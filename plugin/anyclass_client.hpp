// Copyright 2025 The OnePointer Authors.
//

#pragma once


#include "cppenumflag.hpp"

#include <any>
#include <concepts>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <type_traits>


namespace plugin {

typedef typename util::string_flag plugin_flag;
typedef typename util::flag_bundle< plugin_flag > plugin_flags;

// Forward declaration
class AnyClass;


template< class OwnObj >
class AnyClassBase {
protected:
    OwnObj& own;
    std::type_info own_type;

    friend class AnyClass;

public:
    AnyClassBase( OwnObj& own_cls )
        :   own( own_cls )
    {}

    virtual int init( const plugin_flags pflags ) { return own.init(pflags); }
    virtual int startup( const plugin_flags pflags ) { if ( this->init(pflags) == 0 ) return this->run(); else return -1; }
    virtual int run() { return own.run(); }

    virtual int stop( const plugin_flags pflags ) { return own.stop(pflags); }
};


template< class OwnObj >
using is_any_class_t = std::is_base_of< AnyClassBase<OwnObj>, OwnObj >::value;


class AnyClass final
    :   public std::any
{
protected:
    std::type_info type_info;

public:
    template< class B >
        requires is_any_class_t< B >
    AnyClass( B& cls )
        :   std::any( cls )
        ,   type_info( decltype(B) )
    {}

    template< class B >
    AnyClass& operator=( AnyClassBase<B>& anycls ) {
        std::any::operator=< AnyClassBase<B> >( anycls );
        return *this;
    }
    template< class B >
        requires is_any_class_t< B >
    AnyClass& operator=( B& anycls ) {
        std::any::operator=<B>( anycls );
        return *this;
    }

    template< class B >
    operator B() const { return std::any_cast<B>(this); }

    template< class B >
    AnyClassBase< B >& any_cls() const {
        return std::any_cast< AnyClassBase<decltype(std::declval(std::type_index(this->type_info).name()))> >(this);
    }

    int startup( const plugin_flags pf );
    int stop( const plugin_flags pf );
};


class AnyClassClient final {
private:
    std::map< const std::string, AnyClass* > plugin_classes;
    std::set< const std::string > started;

public:
    AnyClassClient();
    AnyClassClient( std::initializer_list<std::string> il );

    int startup( const std::string plugin_service_name, const plugin_flags pf = {} );
    int stop( const std::string plugin_service_name, const plugin_flags pf = {} );
};


} // namespace plugin
