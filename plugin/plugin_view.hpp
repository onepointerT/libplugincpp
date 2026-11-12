// Copyright 2025-2026 The OnePointer Authors.
//


#include "cppinformative.hpp"


namespace plugin {
namespace util {



class PluginView
{
public:
    template< class IsInformedWith >
    using InformationType = util::Informable< PluginView >;
};


} // namespace util
} // namespace plugin
