// Copyright 2025 The OnePointer Authors.
//

#pragma once

#include "anyclass_client.hpp"
#include "context.hpp"

#include <any>
#include <map>
#include <string_view>
#include <utility>


namespace plugin {
namespace util {

// Forward declaration
class VisitorAcceptor;


class VisitorClient {
protected:
    friend class VisitorAcceptor;

    result_map_t& results;

    class InformationPacket {
    protected:
        friend class VisitorAcceptor;

        result_map_t& results;

        InformationPacket( result_map_t& result );
    };
};

class VisitorClientPair
    :   public std::pair< std::any, std::any >
{
public:
    template< class Client, class Visiting >
    VisitorClientPair( Client& cli, Visiting& vis )
        :   std::pair{ *new std::any(cli), *new std::any(vis) }
    {}

    template< class Client >
    Client& client() const { return std::any_cast< decltype(std::declval(std::type_index(this->first.type).name())) >(this->first); }
    
    template< class Visiting >
    Visiting& client() const { return std::any_cast< decltype(std::declval(std::type_index(this->second.type).name())) >(this->second); }
};


class VisitorAcceptor {
protected:
    std::vector< VisitorClientPair* > informing_abonement;

public:
    template< class Client, class Visiting >
    virtual bool inform_cli_on_visit( Visiting& vis, Client& cli ) {
        return this->informing_abonement.emplace_back( *new VisitorClientPair( cli, vis ) ) != nullptr;
    }

protected:
    typedef VisitorClient::InformationPacket information_t;

    template< class Client >
    virtual information_t inform_client_now( Client& cli, result_map_t& results ) {

    }

    template< class Visiting >
    virtual information_t inform_clients_now( const Visiting& vis ) {
        for ( VisitorClientPair* vcp : this->informing_abonement ) {
            if ( *vcp == vis )
        }
    }
};



// A plugin visitor. Can reach plugins with some information
// from `property_flags_t` without changing a bit at the
// main program's/librarie's and the plugin's execution stack's
// state. Is normally given from `PluginAPI` to `PluginCompositor`,
// so that the plugin context only needs to decide, which strategy to start.
template< typename property_flags_t = plugin_flags >
class Visitor
{
protected:
    AnyClass& cls;
    property_flags_t flags;

    void swap( const property_flags_t pflags ) final {
        flags = pflags;
    }
public:
    Visitor( AnyClass& class_adapter, property_flags_t* pflags = new property_flags_t() )
        :   cls( class_adapter )
        ,   flags( *pflags )
    {}

    virtual property_flags_t& visit() { return this->m_flags; }
    virtual const bool visited( const property_flags_t& property ) { return true; }

    void reset() final {
        this->swap( property_flags_t() );
    }
};



// A plugin visitor with queue. Can reach plugins with some information
// from `property_flags_t` without changing a bit at the
// main program's/librarie's and the plugin's execution stack's
// state. Is normally given from `PluginAPI` to `PluginCompositor`,
// so that the plugin context only needs to decide, which strategy to start.
template< typename property_flags_t >
class PluginVisitorQueue
    :   public PluginVisitor< property_flags_t >
    ,   public std::queue< property_flags_t >
{
public:
    PluginVisitorQueue();

    // Please call `visited()` when the visitor finished visiting completly.
    property_flags_t& visit( const property_flags_t& flags = property_flags_t() ) {
        this->push( flags );
        this->flags = flags;
        return PluginVisitor< property_flags_t >::visit();
    }

    // Please call `visited()` when the visitor finished visiting completly.
    const bool visited() {
        PluginVisitor< property_flags_t >::reset( property_flags_t() );
    }

};


} // namespace util
} // namespace plugin

