// Copyright 2025 The OnePointer Authors.
//

#include <ranges>


namespace plugin {

class InformationPacket;

template< class IsInformedWith = InformationPacket >
class Informable {
public:
    using TransformToInformation
            = util::TypeResult< IsInformedWith, InformationPacket >;


    TransformToInformation::GivesFromAny< InformationPacket >&
            Inform( const IsInformedWith& informate_with ) const final {
        return TransformToInformation::makeDecayFree( informate_with );
    }

    InformationPacket& InformationOf() const final {
        return this->Inform( this ).own.
    }
}


class PluginView
{
public:
    template< class IsInformedWith >
    using 
};


} // namespace plugin
