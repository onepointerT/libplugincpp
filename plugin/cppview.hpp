// Copyright 2025-2026 The OnePointer Authors.
//

#include <initializer_list>
#include <map>
#include <queue>
#include <ranges>
#include <string>
#include <string_view>

#include "anyclass_client.hpp"


namespace plugin {
namespace util {

template< class C >
class View
    :   public std::ranges::view_interface< C >
{
protected:
    C* obj;

    friend class C;

    void setObject( const C& object ) {
        this->obj = &object;
    }

public:
    View() = default
        :   std::ranges::view_interface< C >()
        ,   obj( nullptr )
    {}

    View( const C& object )
        :   std::ranges::view_interface< C >( object )
        ,   obj( &object )
    {}

    template< class V = std::string_view >
    class Template
        :   public std::map< std::string, V* >
    {
    protected:
        AnyClass& from_obj;

    private:
        void addkeys( const std::initializer_list<std::string> keys
                    , std::queue<V*>* qua_values = nullptr
        ) {
            for ( const std::string sk : keys ) {
                if ( qua_values == nullptr )
                    (*this)[sk] = nullptr;
                else {
                    if ( qua_values->size() == 0 )
                        (*this)[sk] = nullptr;
                    else (*this)[sk] = qua_values->pop();
                }
            }
        }
    public:
        template< class O = C >
        virtual static std::queue<V*>& from( const O& from_obj ) = 0;
        
        Template( const std::initializer_list<std::string> keys )
            :   std::map< std::string, V* >()
        {
            this->addkeys( keys );
        }

        template< class O = C >
        Template( const std::initializer_list<std::string> keys, const O& from_object )
            :   std::map< std::string, V* >()
            ,   from_obj( from_object )
        {
            std::queue<V*>& result_objs = Template::from<O>(from_object);
            this->addkeys( keys, &result_objs );
        }

        template< class ValueTypePresenting >
        using Matter = Template< ValueTypePresenting >;

        class Object {
        public:
            template< class TypeToTransformTo = std::string_view >
            virtual static const TypeToTransformTo& Transform() const = 0;
        };

        template< class ValueTypePresenting >
        const Matter< ValueTypePresenting >& get( const std::string key
                                                , const std::initializer_list<std::string> keys = {}
        ) {
            try {
                if ( typeof(this->at(key)).name() == decltype(ValueTypePresenting).name() )
                    return *new Matter< ValueTypePresenting >( keys.length() == 0 ? { key } : keys + { key }, this->at(key) );
                else return *new Matter< ValueTypePresenting >( keys.length() == 0 ? { key } : keys + { key } );
            } catch ( std::out_of_range& oor ) {
                return *new Matter< ValueTypePresenting >( keys.length() == 0 ? { key } : keys + { key } );
            }
        }

        const V* get( const std::string key ) const {
            try {
                return this->at(key);
            } catch ( std::out_of_range& oor ) {
                return nullptr;
            }
        }
    };

    using Values = Template< std::string_view >;
    using Objects = Template< AnyClass >;
    using Matter = Template< C >;

    Matter& matter( const std::string key = "view_default_matter" ) const {
        return *new Matter( key, this->obj );
    }
};


} // namespace util
} // namespace plugin
