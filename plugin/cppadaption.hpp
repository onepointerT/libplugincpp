// Copyright (C) 2026 The OnePointer Authors.
//

/*
* adapt the concrete abstract type of any specific type (equal to AnyView<SpecificType>)
    (e.g. specific view to adapting to any visitor)
* context the visitor
*/

#pragma once

#include "cppadapter.hpp"
#include "cppinformative.hpp"
#include "cppvisitor.hpp"


namespace plugin {
namespace meta {


template< class _IsForSortOfKind, class InformedWithType
        , class _ResolvingClassT = util::Adapter
        , class... RecipientsT
>
class Adaptive
    :   public meta::MetaInformative< _IsForSortOfKind, InformedWithType
                                    , _ResolvingClassT, RecipientsT...
                                >
    ,   public _ResolvingClassT
{
public:
    _ResolvingClassT& resolver;
};

template< class _IsForSortKind, class InformedWithType = util::Visitor< _IsForSortKind > >
class MetaAdaption
    :   public AdaptiveVisitor< _IsForSortKind, _IsForSortKind >
    ,   public VisitorClient
    ,   public Adaptive< _IsForSortKind, InformedWithType, util::Adapter
                       , InformedWithType, _IsForSortKind
                >
{
public:

};

template< class _IsFor >
class Adaption
    :   public MetaAdaption< _IsFor, util::Informable< _IsFor > >
{
public:
    
};


} // namespace meta
} // namespace plugin