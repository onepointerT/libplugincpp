// Copyright 2026 The OnePointer Authors.
//

#pragma once


#include "anyclass_client.hpp"

#include "cppenumflag.hpp"

#include <any>
#include <typeindex>
#include <typeinfo>
#include <type_traits>


namespace plugin {

class AnyFunction final
    :   public std::any
{
protected:
    std::type_info type_info;

public:
    template< class F >
    AnyFunction( F& func )
        :   std::any( std::make_any< F >(func) )
        ,   std::type_info( decltype(F) )
    {}

    template< class F >
    AnyClass& operator=( F& anycls ) {
        std::any::operator=<F>( anycls );
        return *this;
    }

    template< class B >
    operator B() const { return std::any_cast<B>(this); }

    template< class B >
    AnyClassBase< B >& any_cls() const {
        return std::any_cast< AnyClassBase<decltype(std::declval(std::type_index(this->type_info).name()))> >(this);
    }

    template< class GenericType, class AnyClassBaseT >
    GenericType& generic() {
        return AnyClassBaseT::generic( this->any_class< GenericType >().own );
    }

    int startup( const plugin_flags pf );
    int stop( const plugin_flags pf );
};

} // namespace plugin