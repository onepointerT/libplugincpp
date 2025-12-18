// Copyright 2025 The OnePointer Authors.
//

#include <ranges>


namespace plugin {
namespace util {

template< class C >
class View
    :   public std::ranges::view_interface< C >
{
protected:

    friend class C;
public:
    View() = default;
};


} // namespace util
} // namespace plugin
