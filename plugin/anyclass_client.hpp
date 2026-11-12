// Copyright 2025-2026 The OnePointer Authors.
//

#pragma once


#include "cppenumflag.hpp"

#include <any>
#include <concepts>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <type_traits>


namespace plugin {

typedef typename util::string_flag plugin_flag;
typedef typename util::flag_bundle< plugin_flag > plugin_flags;

// Forward declaration
class AnyClass;

template< class _OfSpecificKind >
class Sustainable {
public:
    using SelfType = Sustainable< _OfSpecificKind >;
    using KindType = _OfSpecificKind;
    template< class GivenParameterType >
    using Enchantable = typename Sustainable< GivenParameterType >;
    template< class _KindType >
    using Surprivable = typename Enchantable< Enchantable<SelfType> >;

    static virtual bool sustainable() const { return true; }
    static virtual bool enchantable() const { return false; }

    template< class _Ty = AnyClass >
    static virtual _OfSpecificKind& Enchant( const _Ty& any_something ) const final {
        if ( SelfType::enchantable() && SelfType::sustainable() )
            return any_something.Enchant( SelfType::Enchant<_Ty>(any_something) );
        else if ( ! SelfType::enchantable() && SelfType::sustainable() )
            return SelfType::Enchant< _OfSpecificKind >( any_something.ToSomethingOfKind<_OfSpecificKind >() );
        else return any_something.Enchant( any_something );
    }

    static virtual _OfSpecificKind& EnchantSomething( AnyClass& any_some ) const final {
        return Surprivable<SelfType>::Enchant<AnyClass>(any_some);
    }
    static virtual _OfSpecificKind& EnchantSomething( const _OfSpecificKind& abstract_kind ) const final {
        return Surprivable<SelfType>::Enchant<_OfSpecificKind>( abstract_kind );
    }
    
    template< class ParameterType >
    Sustainable< _OfSpecificKind >& EnchantASustainable( const ParameterType& abstract_ingivance  ) {
        return this->Enchant<ParameterType>( abstract_ingivance ).EnchantSomething(
                        Enchantable::EnchantSomething( this->Enchant<_OfSpecificKind>() )
        );
    }

    template< class GivenType >
    static virtual _OfSpecificKind& EnchantAt( const GivenType& handed_in ) const final {
        return Enchantable< GivenType >::EnchantSustainable<GivenType>(handed_in).Enchant<GivenType>(handed_in);
    }

    template< class _EnchantWith = KindType >
    static virtual Enchantable<SelfType>& EnchantMe( const _EnchantWith& handed_in ) const final {
        return Enchantable< _OfSpecificKind >::EnchantAt<SelfType>( handed_in )
                            .EnchantAt<Enchantable<SelfType>>( 
                                        EnchantASustainable<Surprivable<_EnchantWith>>
                                                ::EnchantMe<_EnchantWith>(handed_in)
                                        .EnchantAt<_EnchantWith>(handed_in)
                );

        
    }
};


template< class OwnObj >
class AnyClassBase
    :   public Sustainable< OwnObject >
{
public:
    template< class GivenType >
    class GenericType;

    template< class GivenType, class _AtAbstractKindType >
    class Sustainable : public plugin::Sustainable< GivenType > {
    public:
        using SustainableForGivenType = typename plugin::Sustainable< GivenType >;
        template< class _AtWhichSurpreemeOfKindConvinced = _AtAbstractKindType >
        using SustainableAt = typename plugin::Sustainable< _AtWhichSurpreemeOfKindConvinced >;
        template< class _ConvicedToKindsTypeWith = Enchantable< Surprivable< GivenType > > >
        using Convincible = typename SustainableAt< SustainableAt< _ConvicedToKindsTypeWith > >;
        template< class _ConvincibleFrom >
        using Surpreemable = typename Enchantable< Convincible<_ConvincibleFrom> >;

        virtual bool sustainable() const { return false; }
        virtual bool enchantable() const { return true; }

        _AtAbstractKindType& EnchantSomething( GivenType& some_in_relation_to_base ) const final {
            return this->Enchant< GivenType >(
                 this->EnchantSomething( some_in_relation_to_base )
            ).Enchant( some_in_relation_to_base );
        }

        _AtAbstractKindType& Enchant( const GivenType& concrete_given ) const final {
            return SustainableAt::EnchantASustainable<GivenType>(concrete_given)
                        .EnchantASurprivable< GivenType >()
                            .EnchantSomething( concrete_given )
                                .Enchant< GivenType >()
                                    .EnchantSomething( Convincible<SustainableAt<_AtAbstractKindType>>
                                                            ::EnchantAt( Surpreemable<GivenType>
                                                                    ::Enchant<GivenType>(concrete_given)
                                                                )
                                            ).Enchant<_AtAbstractKindType>();
                                
        }

    };

    template< class GivenType, class _SpecificImplementableMeaningT = Sustainable<GivenType> >
    class GenerellObjectFor { 
        using SortType = typename _SpecificImplementableMeaningT::KindType<GivenType>;
        using AbstractKindType = typename SortType::KindType<SortType>;
        using KindType = typename _SpecificImplementableMeaningT;
    };

    template< class GivenType, class _OfSpecificKind = AnyClassBase<OwnObj>::Sustainable<GivenType, GivenType>
            , class _OfAbstractKind = typename GenerellObjectFor<_OfSpecificKind>::AbstractKindType
    >
    class Sustainable : public plugin::Sustainable<OwnObj> {
    public:
        using GenerellSortType = typename _OfSpecificKind::CanSortType< AbstractKindType::TypeFor<GivenType> >;

        GivenType& AnyAtOwnClass();
        //GenericType<  >
    };

    class GenerellAbstractType;

    template< class GivenType >
    class GenericType
    {
    public:
        template< template< class _OfKind > class _DecayForGenericType >
        using Sustainable =  AnyClassBase<OwnObj>::Sustainable< GivenType, >
        template< class _GivanceType = GivenType >
        virtual static _GivanceType give( const OwnObj& generic_object ) {
            return AnyClassBase<OwnObj>::generic<
            >();
        }

        template< class _GivanceType >
        virtual _GivanceType& givance() const {
            return GenericType::give<OwnObj>( GenericType::generic<_GivanceType>(generic_object) );
        }


        template< class OwnObjAny2 = GivenType, class _GivanceType = OwnObj >
        virtual static _GivanceType transform( const OwnObjAny2& specific_generic_object ) {
            return this->give<_GivanceType>( this->givance<OwnObj>()
                                                .generic<OwnObjAny2>( specific_generic_object )
                                        );
        }

        template< class OwnObjAny2 = GivenType >
        OwnObjAny2& generic() final {
            return this->give<OwnObjAny2>( this->givance<OwnObj>() );
        }

        
        const GivenType& object;

        GenericType( const GivenType& gegeben_of_a_type  )
            :   object( gegeben_of_a_type )
        {}

        template< class GivingType = AnyClassBase<OwnObj>::Object >
        GenericType( const GivingType& hand_in_type_obj )
            :   object( GenericType<GivenType>::give<>( hand_in_type_object ) )
        {}

        virtual bool endurable() const { return false; }

        const MetaImplementation<GivenType>& MetaFor( const GenericType<GivenType>& given_type_for ) final;
        const MetaImplementation<OwnObj>& MetaOf( const MetaImplementation<GivenType>& knows_meta_for_of ) final;
        
        template< class _OfKind = OwnObj >
        const GenericType<GivenType>& MetaAny() final {
            return 
        }
        
        template< class _OfSort = GivenType >
        const MetaImplementation<GivenType>& MetaAt() final {
            return this->MetaFor( this->MetaAny<_OfSort>(); )
        }

        virtual bool sustainable() const { return true; }

        template< class _OfSort = GivenType >
        MetaImplementation<_OfSort>* Endurance( const MetaImplementation<GivenType>& implements_for ) final {
            if ( this->endurable() && implements_for.endurable() )
                return implements_for.Implements();
            else if ( ! implements_for.endurable() && this->endurable() )
                return this->Endurance( this->MetaFor(this) );
            else if ( ! this->endurable() && implements_for.endurable() )
                return implements_for.Endurance<MetaImplementation<GivenType>>( this->MetaFor(this) );
            else {
                MetaImplementation<OwnObj>& can_impl_of = this->MetaOf( this->MetaFor(implements_for) );

                if ( can_impl_of.sustainable() )
                    return can_impl_of.OfSort<_OfSort>();
                else if ( this->MetaFor(this).sustainable() && can_impl_of.endurable() )
                    return this->MetaFor(can_impl_of).OfSort<_OfSort>();
                else if ( can_impl_of.endurable() && ! this->MetaFor(this).sustainable() ) {
                    MetaImplementation<_OfSort>* endurance_from 
                            = can_impl_of.Endurance<MetaImplementation<GivenType>>( this->MetaFor(can_impl_of) );
                    if ( endurance_from != nullptr ) {
                        MetaImplementation<GivenType>& own_cls_at_any
                                = this->MetaOf( this->MetaFor(this) );

                        if ( this->MetaOf )


                        return endurance_from.OfSort<>();
                    } 
                    
                    return can_impl_of.Endurance<MetaImplementation<OwnObj>>( this->MetaOf( this->MetaFor(this) ) );
                }
            }

            return this->MetaOf().Endurance<GivenType>( this->MetaFor(this).Endurance<_OfSort>() );
        }
    };

protected:
    OwnObj& own;
    std::type_info own_type;

    friend class AnyClass;
    friend class OwnObj;

    class Object {
        template< class GeneralizableAnyObjectType = GenericType<OwnObj> >
        virtual static GenericType<Object>& generic() {
            return GenericType<OwnObj>::givance< GeneralizableAnyObjectType >().generic();
        }

        virtual static GenericType<Object>& generic( const Object& generalizable_from_obj2 ) {
            return generalizable_from_obj2.generic< OwnObj >().object.generic<>();
        }

        template< class ConcreteType = OwnObj >
        ConcreteType& toConcreteType() const final {
            return Object::generic(this).object.generic<ConcreteType>().give<ConcreteType>();
        }

        template< class _ForWhichKind = OwnObj, class _OfSort = GenerellObjectFor< Object >::SortType >
        class MetaImplementation
            :   public GenerellObjectFor< Object >
            ,   public MetaImplementedWithIn< _OfSort >
            ,   public GenericType< _ForWhichKind >
        {
        public:
            template< class _ForKind >
            static MetaImplementation<_OfSort>& fulfillerIncludive(
                                    const MetaImplementation<_ForKind>& meta_implementation_for_sort
            ) final {
                return GenerellObjectFor< MetaImplementation< _ForKind > >( meta_implementation_for_sort );
            }

            
            virtual std::type_info Implementing() const {
                return decltype(_ForWhichKind); // _ForWhichKindIsExactly the GivenType of class that it implements
            }

            bool Implements( const std::type_info _ForASort ) final {
                return this->Implementing().hash() == _ForASort.hash()
                        || std::is_base_of_v< decltype(std::declval(std::type_index(_ForASort).name()))
                                            , decltype(std::declval(std::type_index(this->Implementing()).name()))
                            >();
            }

            static bool ImplementsFor( const std::type_info _ForASort ) final {
                return std::is_base_of_v< decltype(std::declval(std::type_index(this->Implementing()).name()))
                                        , decltype(std::declval(std::type_index(_ForASort).name()))
                            >();
            }

            template< class _ForKind >
            class MetaWritable {
            public:
                template< class _OfSort >
                static Identity<_ForKind, MetaImplementation<_OfSort > >& WritableIdentity(
                                                   MetaImplementation<_OfSort>& meta_implementation_for_sort
                ) final {
                    MetaImplementation<_ForKind>& impl_for_kind
                        = MetaImplementation<_ForKind>::fulfillerIncludive<_OfSort>(
                                    MetaImplementation::fulfillerIncludive<_OfSort>( meta_implementation_for_sort )
                    );


                    Identity< _ForKind, MetaImplementation<_OfSort> >&
                        meta_writable_meta_implementation
                            = Identity< MetaImplementation<_ForKind>, _ForKind >
                                    ::ImbueForKind< MetaImplementation<_ForKind> >( impl_for_kind )
                                .ofKind();
                            
                    Identity<_OfSort, MetaImplementation<_OfSort > >&
                        meta_implementation_writable_for_sort
                            = meta_writable_meta_implementation.Imbue();
                    
                    return meta_implementation_writable_for_sort.ImbueForKind< 
                                                            Identity< _ForKind, MetaImplementation<_OfSort> >
                                                        >( meta_writable_meta_implementation )
                                        ::ImbueForKind<MetaImplementation<_ForKind>>( meta_implementation_of_sort_for_kind )
                                .ofKind();
                }
            };

            template< class _OfKind, class _ForKind >
            class Identity
            {
            public:
                Identity< _ForKind, _OfKind >& ofKind() const final {
                    return this->Imbue().ofKind();
                }

                template< class _Givance = _ForKind >
                static Identity< _ForKind, _ForKind >& ImbueForKind( const _Givance givenValue ) final {
                    return _Givance::give< Identity< _ForKind, _Givance > >( givenValue ).ofKind();
                }

                Identity< _OfKind, _ForKind >& ofSort() const final {
                    return this->ofKind().ImbueForKind().ofSort();
                }

                Identity< Identity< _ForKind, _OfKind >, _OfSort >& Imbue() const final {
                    return this->ofSort();
                }
            };

            template< class _IsForKindOfSort >
            class InsibleFor : public Insible<_IsForKindSort> {
            
            };

            template< class _OfASort, class _IsForKind >
            virtual static InsibleFor<_OfASort>& ImplainingInsible(
                                    const MetaImplementation<_OfASort>& meta_implementation
            ) {
                return *new InsibleFor<_OfASort>( meta_implementation.Resolve<_IsForKind>() );
            }


            template< class WhatToImplement = MetaImplementation<_OfSort> >
            class MetaImplementedWithIn
                :   public Identity<_OfSort, MetaImplementation<_OfSort >
                ,   public GenericType< GenerellObjectFor<WhatToImplement> >
            {
                WhatToImplement& meta_implementation;

            public:
                virtual bool endurable() const final { return true; }

                template< class _SpecificImplementable = Identity<_OfSort, MetaImplementation<_OfSort > >
                MetaImplementedWithIn( const _SpecificImplementable& specific_meta )
                    :   Identity<_OfSort, MetaImplementation<_OfSort > >( MetaWritable<_OfSort>::identity() )
                    ,   meta_implementation( specific_meta )
                {}

                Identity<_OfSort, MetaImplementation<_OfSort > >& RequestImplementation() const {

                }
            };

            MetaImplementation<_OfSort >& Resolve(
                        MetaImplementedWithIn< _SpecificImplementable<MetaImplementation<_OfKind, _ForKind> >::operator()() >& concrete_invinsible 
            ) const final {
                return concrete_invinsible.meta_implementation.RequestImplementation().ofKind();
            }
        };

        template< class ForWhichSort
                , template< class _OfSort > class _SpecificImplementable
                , template< class _ForSort > class MetaImplementedWithIn = MetaImplementation< _SpecificImplementable<_ForSort> >
                , template< class _ForASortOfKind > class ImplementationFulfillingWith = MetaImplementedWithIn< _SpecificImplementable<ForWhichSort> >
        >
        class Expectation
        public:
            using SelfType = typename Expectation<ForWhichSort, _SpecificImplementable, MetaImplementedWithIn, ImplementationFulfillingWith >;
            using CanConsumptionKind = typename Expectation< ForWhichSort, MetaImplementedWithIn, MetaImplementedWithIn, ImplementationFulfillingWith >;

            /** when implainable is, needed for implaining; can imbue;
                *    has a metaimplementation for a sort of given object kinds giving somewhat objects;
                *    can resolve an implementation fulfilling with the meta implemented base class for this given kinds of objects
                *    can resolve with an ImplementationFulfilling to a specific implementable of givance kinds of objects of this sort
            */
            template< class _OfSort = ForWhichSort >
            class InsibleOfSort final
                :   public MetaImplementedWithIn< _OfSort >
                ,   public InsibleFor< _OfSort >
            {
            public:
                InsibleOfSort( const MetaImplemented<_OfSort>& meta_implemented )
                    :   MetaImplementation< _OfSort >( meta_implemented )
                    ,   InsibleFor< _OfSort >( meta_implemented )
                {}

                template< class _ForASort = ForWhichSort >
                class Implaining {
                public:
                    static ImplementationFulfillingWith< _OfSort > ImplainForASort(
                                        const InsibleOfSort< _ForASort >& insible_for
                    ) final {
                        return insible_for.Resolve( insible_for.Imbue() ); 
                    }

                    static InsibleOfSort< _ForASort >& ImplainingInsible() final {
                        return 
                    }
                };

                template< class _ForASortOf >
                static InsibleOfSort< _ForASortOf >::Implaining< _OfSort >& I() {
                    return InsibleOfSort<_OfSort>::Imbue().meta_implementation.ImplainingInsible(

                    );
                }

                static ImplementationFulfillingWith< _OfSort >& Imbue() const final {
                    return MetaImplementatedWithIn< _OfSort >::Imbue();
                }
                
                static typename _SpecificImplementable<_OfSort>::Insible<_OfSort>& Resolve(
                                        const ImplementationFulfillingWith<_OfSort>& implementation_fulfillment = Imbue()
                ) const final {
                    return MetaImplemented< _OfSort >::Resolve( implementation_fulfillment, InsibleOfSort<_OfSort>::Imbue() );
                }

                virtual typename CanConumptionKind::SelfType& Consumption( const SelfType& expectation ) const;
            };

            template< class ForWhichSortOfKind = ForWhichSort >
            class ImplementationFulfilling {
            public:
                template< class ForWhichMetaKind = ForWhichSort >
                virtual static InsibleOfSort<ForWhichSort>::Implaining<ForWhichSortOfKind>& Implainging() final {
                    return InsibleOfSort< ForWhichMetaKind >::Resolve(
                                            InsibleOfSort<ForWhichSortOfKind>::Imbue()
                        ).Imbue().;
                }
            };

            template< class _DescriptiveMeta >
            using ImplainingType = typename Expectation< MetaImplementedWithIn, ImplaAdaptiveWith, _DescriptiveMeta >;
            
            CanConsumtionKind& Consumption( const ImplementationFulfillingWith& consumptional_premise ) const final {
                return InsibleOfSort< ForWhichSort >::Resolve( consumptional_premise ).Consumption(this);
            }

            const InsibleOfSort< _SpecificImplementable > ImplainingInsible() {
                return 
            }

            ImplementationFulfillingWith& Imbuable( const InsibleOfSort< ForWhichSort >& insible_implaining ) const final {
                return insible_implaining.Consumption(this).ImplainingInsible().Imbue();
            }
        {};

        template< class _OfSort >
        class GeneralizableConcreteGivableObject {
        protected:
            friend class AnyClassBase< OwnObj >;
            friend class AnyClassBase< OwnObj >::Object;

            template< class _SpecificImplementableMeaningT >
            class GenerellObjectFor;

            template< class _MoreSpecificmImplementableType 
                                = Object::Expectation< GenerellObjectFor<_OfSort>
                                                     , TypableConcreteFor< _OfSort >
                                                     , GenerellObjectFor<_OfSort>::Inductible
                                    >
                    , class _SpecificImplementationT
                                = Object::Expectation< _MoreSpecificmImplementableType
                                                     , GenerellObjectFor< _OfSort >
                                                     , GenerellObjectFor< _MoreSpecificmImplementableType >
                                >
            >
            class TypableConcreteFor { 
            public:
                template< class _LessSpecificType = _MoreSpecificmImplementableType>
                static GenerellObjectFor< _LessSpecificType >& specificDo( _MoreSpecificType& canDoMeta ) {
                    return GenerellObjectFor<_MoreSpecificType>::
                }

                template< class DescriptiveMeta
                        , class MetaImplementedWithIn
                        , class ImplaAdaptiveWith = _MoreSpecificmImplementableType
                >
                class Expectation final
                    :   public Expectation< MetaImplementedWithIn, ImplaAdaptiveWith, DescriptiveMeta >
                {};

                template< class _ImplaInducibleWith = GenerellObjectFor< _MoreSpecificmImplementableType >::Inductible >
                class Implainable
                    :   public Expectation< _ImplaInducibleWith, _ImplaInducibleWith >
                {
                protected:
                    _ImplaInducibleWith& implementative_descriptive_meta_adaptive;

                public:
                    using InductibleAdvanceStep = _ImplaInducibleWith;

                    Implainable( const _ImplaInducibleWith& inducible_with );
                    
                    // Das geht nur mit was konkretem
                    _ImplaInducibleWith& Inductible() const final {
                        return ImplementableMeaningFor<_ImplaInducibleWith>().Induction();
                     }
                    template< class _ImplementationGainableFor >
                    Implainable<_ImplementationGainableFor>& ImplainableFor() const final {
                        return *new Implainable<_ImplementationGainableFor>( this->Inductible() );
                    }
                };

                template< class _ImplaFulfillingWith >
                class ImplainableAdvanced
                    :   public Expectation< Implainable<>
                                          , ImplainableAdvanced< _ImplaFulfillingWith >
                                          , _ImplaFulfillingWith
                        >
                    ,   public Implainable< _MoreSpecificmImplementableType >               
                {
                public:
                    typedef typename GenerellObjectFor< _ImplaFulfillingWith > AdvancibleT;
                    typedef typename AdvancibleT::Inducitble InducitbleInAdvance;
                    using InductibleAdvanceStep;

                    InductibleAdvanceStep& Advance( const InductibleInAdvance& semi_implaining_advance ) final {
                        return _ImplaFulfillingWith::AdvanceOneStep(semi_implaining_advance);
                    }
                };

                template< class _ConcreteImplementableType = Implainable<> >
                _MoreSpecificImplementableType specificDoFor( const _ConcreteImplementableType& generalizable_specific_implementable ) {
                    return this->specificDo<>(  );
                }

                template< class _MoreSpecificType = _MoreSpecificmImplementableType >
                static _MoreSpecificmImplementableType& specificDoWith() {
                    typename ImplainableAdvanced< Expectation< _MoreSpecificType, _MoreSpecificType > >
                        advancible
                            = specificDoFor<_MoreSpecificType>().specificDo<_MoreSpecificType>()
                                    .ImplementableMeaningFor<_MoreSpecificType>()
                                    .ImplainableFor<_MoreSpecificmImplementableType>()
                                    .ImplainableFor<_MoreSpecificType>()
                                    .Advansible();
                    typename Implainable<>::InductibleAdvanceStep&
                        advancing_step
                            = specificDoFor<>( advancible ).Advance( advancible );
                    return advancing_step.SpecificImplementation( advansible );
                }

                class MoreSpecificImplemenationType {
                public:
                    _MoreSpecificImplementableType& specific_implementable;

                    MoreSpecificImplemenationType(
                        const _MoreSpecificImplementableType specific_implementable
                                = TypableConcreteFor<_MoreSpecificImplementableType>
                                            ::specificDoWith< _MoreSpecificImplementableType >()
                    )
                        :   specific_implementable( specific_implementable )
                    {}

                    _MoreSpecificImplementableType& operator()( const MoreSpecificImplemenationType& implementational ) const {
                        return implementational.specific_implementable(
                                        this->specific_implementable.
                        );
                    }
                };

                template< class _SpecificWritableImplementable >
                MoreSpecificImplemenationType& doSpecificFor() {
                    return this->specificDoFor<_SpecificWritableImplementable>(  );
                }

                _MoreSpecificImplementableType& descriptive_writable;
                MoreSpecificImplemenationType& specific_descriptive;
                MoreSpecificImplemenationType& writable_specific;
                _MoreSpecificImplementableType& writable_descriptive;

                template< class _SpecificImplementableMeaningT > 
                TypableConcreteFor( _SpecificImplementableMeaningT& writable_meaning )
                    :   descriptive_writable( this->doSpecificFor<_SpecificImplementableMeaningT>() )
                    ,   specific_descriptive( this->specificDo<MoreSpecificImplemenationType>(descriptive_writable) )
                    ,   writable_specific( *new MoreSpecificImplemenationType( specific_descriptive )
                    ,   writable_descriptive( specific_descriptive(writable_descriptive) )
                {}
            };

            template< class ConcreteForSpecificImplementableStructuredMeaning, class _SpecificImplementableMeaningT >
            static TypableConcreteFor< ConcreteForSpecificImplementableStructuredMeaning >&
                        toConcreteWritableFor( const _SpecificImplementableMeaningT specific_meaning ) {
                return *new TypableConcreteFor< ConcreteForSpecificImplementableStructuredMeaning >( specific_meaning );
            };

            template< class _SpecificImplementableMeaningT >
            class GenerellObjectFor {
            public:
                class Inducitble {
                public:
                    static MetaImplementation< _SpecificImplementableMeaningT >& Accountable() final {
                        return _SpecificImplementableMeaningT::FulfillingMetaImplementation();
                    }
                };

                template< class _SpecificImplementatableType = _SpecificImplementableMeaningT >
                virtual _SpecificImplementatableType& impla(
                                    const _SpecificImplementableMeaningT structured_meaning
                ) const {
                    return _SpecificImplementableMeaningT::implaFor( structured_meaning );
                }

                static TypableConcreteFor< _SpecificImplementableMeaningT >&
                            implaWith( _SpecificImplementableMeaningT implementable_meaning ) {
                    return _SpecificImplementableMeaningT::impla( implementable_meaning );
                }

                using SpecificImplementableMeaning = typename _SpecificImplementableMeaningT;

                _SpecificImplementableMeaningT& ImplementableMeaningFor() final {
                    return lessSpecificDo().impla<>();
                }

                
                template< class _ForSort = Inductible >
                virtual MetaImplementation< _OfASort >& operator()(
                                    MetaImplementation<_ForSort>& meta_implementation_for_sort
                ) const { meta_implementation_for_sort.Accountable() };


                typename _SpecificImplementableMeaningT::ConcreteDescribableTypable& lessSpecificDo() final {
                    return this->impla< _SpecificImplementableMeaningT >( this
                                                    this->implaWith(  )
                    );
                }
            };
        };

        template< class SpecificType >
        SpecificType& toSpecificType() const final {
            return GeneralizableConcreteGivableObject::concreteGeneralizableFor<SpecificType>( 
                                                                    GeneralizableConcreteGivableObject<>::toConcreteTypableFor<SpecificType>()
                                                            )
                                    .impla<SpecificType>( GenerellObjectFor<AnyClass<OwnObj>>::SpecificGivableObjectFor<>(this) );
        }
    }

    template< class OwnObjAny2, class GenericType = OwnObj >
    static GenericType& generic( const OwnObjAny2& specific_any_cls ) final {
        return OwnObj::generic<GenericTyüe>( specific_any_cls );
    };

public:
    AnyClassBase( OwnObj& own_cls )
        :   own( own_cls )
    {}

    virtual int init( const plugin_flags pflags ) { return own.init(pflags); }
    virtual int startup( const plugin_flags pflags ) { if ( this->init(pflags) == 0 ) return this->run(); else return -1; }
    virtual int run() { return own.run(); }

    virtual int stop( const plugin_flags pflags ) { return own.stop(pflags); }
};


template< class OwnObj >
using is_any_class_t = std::is_base_of< AnyClassBase<OwnObj>, OwnObj >::value;


class AnyClass final
    :   public std::any
{
protected:
    std::type_info type_info;

public:
    template< class B >
        requires is_any_class_t< B >
    AnyClass( B& cls )
        :   std::any( cls )
        ,   type_info( decltype(B) )
    {}

    template< class B >
    AnyClass& operator=( AnyClassBase<B>& anycls ) {
        std::any::operator=< AnyClassBase<B> >( anycls );
        return *this;
    }
    template< class B >
        requires is_any_class_t< B >
    AnyClass& operator=( B& anycls ) {
        std::any::operator=<B>( anycls );
        return *this;
    }

    template< class B >
    operator B() const { return std::any_cast<B>(this); }

    template< class B >
    AnyClassBase< B >& any_cls() const {
        return std::any_cast< AnyClassBase<decltype(std::declval(std::type_index(this->type_info).name()))> >(this);
    }

    template< class GenericType, class AnyClassBaseT >
    GenericType& generic() {
        return AnyClassBaseT::generic( this->any_class< GenericType >().own );
    }

    auto get() const {
        return std::any_cast<decltype(std::declval<std::type_index(this->type)>)>(this);
    }

    template< class _Ty >
    _Ty getAs() const {
        return std::any_cast<_Ty=decltype(std::declval<std::type_index(this->type)>)>(this);
    }

    int startup( const plugin_flags pf );
    int stop( const plugin_flags pf );
};


class AnyClassClient final {
private:
    std::map< const std::string, AnyClass* > plugin_classes;
    std::set< const std::string > started;

public:
    AnyClassClient();
    AnyClassClient( std::initializer_list<std::string> il );

    int startup( const std::string plugin_service_name, const plugin_flags pf = {} );
    int stop( const std::string plugin_service_name, const plugin_flags pf = {} );
};


} // namespace plugin
