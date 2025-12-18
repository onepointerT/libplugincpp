// Copyright 2025 The OnePointer Authors.
//

#include "context.hpp"


namespace plugin {


Context::Context( Context&& another )
    :   ctx_cls( another.ctx_cls )
    ,   ctx_flags( another.ctx_flags )
    ,   ctx_results( another.ctx_results )
{}
Context::Context( AnyClass& cls, plugin_flags& pf, Context& another )
    :   ctx_cls( cls )
    ,   ctx_flags( pf )
    ,   ctx_results( another.ctx_results )
{}
Context::Context( AnyClass& cls, plugin_flags& pf )
    :   ctx_cls( cls )
    ,   ctx_flags( pf )
    ,   ctx_results()
{}

bool Context::start() const {
    return this->ctx_cls.any_cls().startup( this->ctx_flags );
}

bool Context::stop() const {
    return this->ctx_cls.any_cls().startup( this->ctx_flags );
}

const result_map_t& Context::result_map() const {
    return this->ctx_results;
}

Context& Context::operator+=( const plugin_flag pf ) {
    this->ctx_flags.insert( pf );
    return *this;
}


} // namespace plugin
