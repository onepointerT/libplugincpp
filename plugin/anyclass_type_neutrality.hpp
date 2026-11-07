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
    template< template< class _ForWhat > class _OfType, class _ForWhat = NeutralTo >
    class GenericResult;

    template< class _ForWhat = _Ty > 
    class OfType
        :   public util::Decay< _ForWhat >
    {
    public:
        class GenericType
            :   public util::Decay< _NeutralTo >
            ,   public GenericResult< util::Decay< _ForWhat >, _NeutralTo >
        {
        public:
            static util::Decay< _NeutralTo > decay() const final { return util::Decay< _NeutralTo >(*this); }

            template< class _ForDecayTypeOf >
            using DecayFreeType = OfType< _NeutralTo >::GenericType::DecayType< GenericType::decay()::DecayTypeFor<_ForDecayTypeOf> >;
            template< class _LessDecayingType = util::Decay< DecayFreeType<util::Decay<_NeutralTo> > >
            using DecayType = util::Decay< _LessDecayingType >::DecayType;
            template< class _DecayFreeType = typename DecayType >
            using NeutralType = typename GenericType::NeutralType< GenericType::DecayFreeType;
        };

        using DecayType = util::Decay< _ForWhat >;
        using NeutralType = typename GenericType::NeutralType<>;
        
    };

    using NeutralTo = _NeutralTo;

    template< template< class _ForWhat > class _OfType = OfType, class _ForWhat = NeutralTo >
    using GenericResult = _OfType< _ForWhat >::GenericType::DecayType<_ForWhat>;

    template< class _WhatMakesLessGeneric >
    using GivesFromAny
        = typename GenericResult< _WhatMakesLessGeneric >::GenericType< GenericResult< OfType, NeutralTo > >;

    
    using Type = _Ty;

    template< class _DecayFreeType = NeutralTo
            , class _ToType = TypeResult< _Ty, _DecayFreeType >
    >
    using GivesFromAnyTo = typename GivesFromAny< _DecayFreeType >::give< _ToType >();

    template< class _ForType >
    using Origin = GenericResult< _Ty, _ForType >

    const Origin< NeutralTo >& origin;
    const _Ty& value;

    template< class _WhatIsNearlyNeutralNorAbstract = NeutralTo >
    virtual GivesFromAny< TypeResult<NeutralTo, Origin<NeutralTo> > >::NeutralType&
                makeNeutral( const _WhatIsNearlyNeutralNorAbstract elem_result
    ) {
        return GivesFromAnyTo<typename Origin<NeutralTo>::Decay>
                    ::create< TypeResult<NeutralTo, Origin<NeutralTo> >(elem_result)
                        .createFrom<_Ty>( this->makeDecayFree<_Ty>(this->value) );
    }

    template< class _OfType = NeutralTo >
    virtual NeutralTo& makeDecayFree( const _OfType with_decay_and_preliminary_giving_type ) {
        return this->makeNeutral<_OfType >( with_decay_and_preliminary_giving_type  );
    }
    template< class _ForTypeT = _Ty >
    virtual _Ty& beNeutralTo( TypeResult::GenericResult<util::Decay, _ForTypeT>::Decay& resulting_decay ) {
        return this->makeNeutral<NeutralTo>(
                            this->makeDecayFree<GenericResult<util::Decay, _ForTypeT>>(resulting_decay)
        ).;
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
