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
namespace util {


template< class _Ty, class _NeutralTo >
class TypeResult
{
public:
    using NeutralTo = _NeutralTo;
    using GenericResult = AnyClassBase< NeutralTo >;
    using GivesFromAny = AnyClass::any GenericResult;
    using Type = _Ty;

    const GenericResult& origin;
    const _Ty value;

    virtual GivesFromAny makeNeutral( const NeutralTo elem_result );
    virtual NeutralTo& makeDecayFree( const _Ty with_decay_and_preliminary_giving_type ) {
        return this->makeNeutral(  )
    }
    virtual static _Ty& beNeutralTo( TypeResult::GenericResult& resulting_decay ) {
        
    }
    virtual static 

    template< class _GivesFromAny >
    TypeResult( GenericResult& generic_result )
        :   origin( generic_result )
        ,   value( this->beNeutralTo(generic_result) )
    {}

    TypeResult( const GenericResult& generic_result )
        :   TypeResult<_Ty, _NeutralTo>::TypeResult<NeutralTo>( this->makeDecayFree(
                                                                            this->beNeutralTo(generic_result)
                                                        ) );
    {}
};


} // namespace util
} // namespace plugin
