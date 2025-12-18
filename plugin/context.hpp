// Copyright 2025 The OnePointer Authors.
//

#pragma once

#include "anyclass_client.hpp"

#include <map>

namespace plugin {


using result_map_t = std::map< const std::string, plugin_flags >;


class Context {
private:
    AnyClassClient& ctx_classes;

protected:
    AnyClass& ctx_cls;
    plugin_flags ctx_flags;
    result_map_t ctx_results;

    friend class Context;
public:
    Context( Context&& another );
    Context( AnyClass& cls, plugin_flags& pf, Context& another );
    Context( AnyClass& cls, plugin_flags& pf );

    bool start() const;
    bool stop() const;

    const result_map_t& result_map() const;

    Context& operator+=( const plugin_flag pf );
};


} // namespace plugin
