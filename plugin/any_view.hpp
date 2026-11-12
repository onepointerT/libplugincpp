// Copyright 2026 The OnePointer Authors.
//

#pragma once

#include "cppview.hpp"

#include "anyclass_client.hpp"

#include <meta>
#include <type_traits>


namespace plugin {
namespace meta {


class AnyView
    :   public util::View< AnyClass >
{
protected:
    AnyClass& any;

public:
    template< class CoF >
    AnyView( const CoF& data )
        :   any( *new AnyClass(data) )
    {}

    template< class CoF >
    CoF& as() const {
        if ( std::meta::is_function(^^CoF::Transform<CoF>) ) {
            if ( std::is_pointer(this->any.get())::value )
                return *(this->any.get()->Transform<CoF>());
            else if ( std::is_reference(this->any.get())::value )
                return this->any.get().Transform<CoF>();
        }
        return static_cast<CoF>(this->any.get());
    }

    template< class _MTy >
    using Matter = Template< _MTy > override ;

    template< class _MTy >
    Matter< _MTy >& matter( const std::string key = "view_default_matter" ) const {
        return *new Matter<_MTy=decltype(std::declval<std::type_index(this->any.type)>)>( { key }
                                    , this->any.getAs<decltype(std::declval<std::type_index(this->type)>)>()
                                );
    }
};


} // namespace meta
} // namespace plugin