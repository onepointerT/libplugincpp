// Copyright 2025 The OnePointer Authors.
//


#include "anyclass_client.hpp"
#include "plugin_view.hpp"
#include "cppvisitor.hpp"


namespace plugin {

template< class AnySpecificPlugginableType = AnyClass >
class ContextView
    :   public PluginView
    ,   public Adaption< Visitor< AnySpecificPlugginableType > >
    ,   public VisitableType< AdaptiveVisitor<AnySpecificPlugginableType>::PluginView >
        >
{};


} // namespace plugin
