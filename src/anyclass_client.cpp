// Copyright 2025 The OnePointer Authors.
//

#include "anyclass_client.hpp"


namespace plugin {


int AnyClass::startup( const plugin_flags pf ) {
    return this->any_cls().startup(pf);
}

int AnyClass::stop( const plugin_flags pf ) {
    return this->any_cls().stop(pf);
}


AnyClassClient::AnyClassClient()
    :   plugin_classes()
    ,   started()
{}


AnyClassClient::AnyClassClient( std::initializer_list<std::string> il )
    :   plugin_classes()
    ,   started()
{
    for ( const std::string s : il ) {
        (*this)[s] = nullptr;
    }
}

int AnyClassClient::startup( const std::string plugin_service_name, const plugin_flags pf ) {
    if ( this->plugin_classes.count( plugin_service_name ) > 0 ) {
        this->started.emplace( plugin_service_name );
        return this->plugin_classes[plugin_service_name]->any_cls().startup(pf);
    } return 1;
}

int AnyClassClient::stop( const std::string plugin_service_name, const plugin_flags pf ) {
    if ( this->started.count( plugin_service_name ) > 0 ) {
        this->started.erase( plugin_service_name );
        return this->plugin_classes[plugin_service_name]->any_cls().stop(pf);
    } return 1;
}


} // namespace plugin
