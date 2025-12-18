// Copyright 2025 The OnePointer Authors.
//

#pragma once

#include "plugin.hpp"


namespace plugin {


class PluginAdapter
{
public:
    PluginAdapter& operator<<( Plugin& plugin );
    PluginAdapter& operator>>( Plugin& plugin );
};


} // namespace plugin
