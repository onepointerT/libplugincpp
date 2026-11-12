// Copyright 2026 The OnePointer Authors.
//

#pragma once

#include "anyclass_client.hpp"
#include "anyclass_type_neutrality.hpp"
#include "any_view.hpp"
#include "cppview.hpp"
#include "cppvisitor.hpp"

#include <cstdarg>
#include <functional>
#include <list>
#include <meta>
#include <ranges>
#include <utility>


namespace plugin {

namespace meta {
template< class _IsForKind >
class Informational;
} // namespace meta


namespace util {

template< class _IsForKind, class IsInformedWith = meta::Informational< _IsForKind > >
class Informable final
    :   public util::meta::AnyView
{
public:
    typedef typename bool (*inform_f)( const IsInformedWith& );
    typedef typename std::pair< AnyClass*, std::function<bool(const IsInformedWith&)> > informable_t;

protected:
    std::list< informable_t > inform_me;
    std::list< IsInformedWith > information;
    size_t information_new_until;

public:
    using TransformToInformation
            = util::TypeResult< IsInformedWith, _IsForKind >;

    template< class RCPI >
    bool InformMe( const RCPI& recipient_instance, const inform_f informable_func ) {
        this->inform_me.emplace( std::make_pair( new AnyClass(recipient_instance)
                                               , informational_func 
        ) );
    }
    
    
    bool Inform( const IsInformedWith& informate_with ) const final {
        for ( informable_t iat : this->inform_me ) {
            if ( std::meta::is_function(iat.first->get().Inform) )
                iat.first->get().Inform(informate_with);
            else if ( ! iat.second(informate_with) )
                return false;
        }
        return true;
    }

    bool InformationFlush() const final {
        size_t info_idx = 0;
        bool miss = false;
        while ( info_idx < this->information_new_until ) {
            for ( const IsInformedWith& info : this->information ) {
                miss = miss && this->Inform(info);
                ++info_idx;
            }
        }
        return false;
    }

    template< class O >
    InformationPacket& InformationOf( const O& obj ) final {
        IsInformedWith& info;
        try {
            info = static_cast<IsInformedWith>(obj);
        } catch ( std::exception& e ) {
            try {
                info = static_cast<InformationOf>(static_cast<_IsForKind>(obj));
            } catch ( std::exception& e2 ) {
                info = *new IsInformedWith<O>( obj );
            }
        }
        this->information.emplace_front( info );
        ++this->information_new_until;
        return this->information.front();
    }
};
} // namespace util

namespace meta {

class Unknown { const static bool resolvable = false;  };

template< class _IsForSort
        , class InformWithType
        , class _ResolvingClassT = plugin::util::Informable< _IsForSort, InformWithType >
        , class... RecipientsT
>
class MetaInformative {
public:
    std::list< va_list >& getRecipients() const;
    std::list< std::meta::info >& getRecipientsInfo() const;
    std::meta::info& getResolvingClassTypeInfo() const;

    typedef typename _IsForSort SortOfKind;
    typedef typename _ResolvingClassT NeedsTypeForSort;
};

template< class _IsForSortOrItsKind, class _Ty >
class MetaInformativeAbsolver {
public:
    typedef typename MetaInformative< _IsForSortOrItsKind
                                    , MetaInformativeAbsolver< _IsForSortOrItsKind, _Ty >
                                    , _Ty > InformativeType;
    typedef typename _IsForSortOrItsKind TypeOfSortOrItsKind;
    typedef typename _Ty InheritorType;
    typedef typename MetaInformativeAbsolver< _IsForSortOrItsKind, _Ty >
                                        InformativeAbsolverType;
    
    void GatherMe( const InformativeType& new_information );
    std::queue< InformativeType* >& GetInformation() const;
};

} // namespace meta

namespace util {

template< class _IsForKind >
class Informational final
    :   public meta::MetaInformative< typename _IsForKind::SortOfKind >
    ,   public typename _IsForKind::NeedsTypeForSort
    ,   public util::View< _IsForKind >
    ,   protected util::VisitorAcceptor< _IsForKind, _IsForKind, util::View< _IsForKind > >
{
protected:
    friend class Visitor< _IsForKind >;

public:
    typedef typename _IsForKind SpecificKind;
};


} // namespace util
} // namespace plugin

