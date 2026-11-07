
#pragma once

#include "anyclass_client.hpp"
#include "cppvisitor.hpp"


namespace plugin {
namespace util {


template< class _ClientableType >
class AdapterAbstract;
class AdapteeSolution;
class Adapter;
class AnyFulfillment;

template< class FulfillmentType >
class Fulfillable { 
public:
    virtual static AdapteeSolution& fulfill() {
        return this->adapter().concrete_adapter.solutional;
    }

    virtual static AnyFulfillment& fulfillment() {
        AdapterFor& afor =  this->adapter();
        AdapteeSolution& asoluit 
            = afor.concrete_adapter.solutional.fulfillAdaptionalPromise( afor.concrete_adapter.solutional );
        SolutionalTarget& adaptive_solution
                = *new SolutionalTarget( asoluit, afor.concrete_adapter, asoluit );
        return *new AnyFulfillment( afor.concrete_adapter.Resolve().fulfillAbstractPromise(
                                        afor.concrete_adapter.Resolve().ResolveWithAdaptee(
                                            adaptive_solution.searchAdaptee()
                                        ).ResolveToTarget()
                                            .fulfillAbstractPromise(asoluit).Request().Resolve()
                                    )
                                  , adaptive_solution
        );
    }

    class Fulfilled {
        virtual static AnyFulfillment& fulfillment() {
            return Fulfillable<FullfilmentType>::fulfillment();
        }

        static AnyFulfillment& fulfill() final { return FulfillmentType::fulfillment(); }
    };


    template< class _SinceWhenImplementingNonAbstract >
    class UpOnRelyable;
    

    virtual AdapterAbstract< FulfillmentType >& admire( const UpOnRelyable<FulfillmentType>& fulfiller_impl ) {
        return this->admire().Fulfill< FulfillmentType >( this->adhire( this->adore(fulfiller_impl).forFullfillerType() )
                                                        , fulfiller_impl.fulfill()
            );
    }

    virtual AnyFulfillment& adore( const Fulfilled& fulfiller_impl ) {
        return fulfiller_impl.fulfillment();
    }
    
    virtual Adapter& adhire( const AdapteeSolution& fulfillment_adaptee ) {
        return this->admire().forFullfillerType<FulfillmentType>( this->adore().fulfillableAdapter( fulfillment_adaptee ) ).Solve();
    }

    virtual Clientable::Type& adeqs( const AnyFulfillment& fulfilling ) {
        return this->fulfill().Transform()
                    .fulfillSpecificPromise(fulfilling
                            , ((AdapterAbstract<FulfillmentType>) this->adapter().concrete_adapter).fulfillment
                        )
                    .Request().Fulfill();
    }

    virtual  adex( const AnyFulfillment& fulfilling ) {
        return this->fulfill().Transform().fulfillSpecificPromise(fulfilling, ).Request().Transform()
    }

    class AdapterFor { Adapter& concrete_adapter; };

    const AdapterFor& adapter() const final {
        Adapter& adapt = this->adhire( this->fulfill() );
        AdapterFor& afor = *new AdapterFor();
        afor.concrete_adapter = a;
        return afor;
    }

    template< class _FulfillerType >
    class When
        :   public UpOnRelyable< _FulfillerType >
        ,   public Fulfilled
        ,   public AdapterFor
    {
    public:
        virtual static AdaptiveSession& gainAdaptiveRelyableSession() {
            return this->gainAdaption();
        }

        template< class _AdaptiveForWhat >
        virtual static AdaptiveSession& gainAdaptiveRelyableSession() {
            return _AdaptiveForWhat::gainAdaption( this->gainImplementation() );
        }
    };


    template< class _SinceWhenImplementingNonAbstract >
    class UpOnRelyable
        :   public Fulfillable< _SinceWhenImplementingNonAbstract >::Fulfilled
    {
        friend class Fulfillable< FulfillmentType >::When< FulfillmentType >;

        static AdaptiveSession& gainImplementation() {
            return _SinceWhenImplementingNonAbstract::gainRelyableSession();
        };
    public:
        virtual AdaptiveSession& gainAdaption() const {
            return When< FulfillmentType >::gainAdaptiveRelyableSession();
        }
    };
};

template< class _ImplementedSince, class _FulfillerT, class ImplementingWhatFulfillableClsSemanticConceptAsTypeT >
class FulfillingSince
    :   public Fulfillable< ImplementingWhatFulfillableClsSemanticConceptAsTypeT >::UpOnRelyable< _ImplementedSince >
    ,   public Fulfillable< ImplementingWhatFulfillableClsSemanticConceptAsTypeT >::When< _FulfillerT >
    ,   public Fulfillable< _FulfillerT >::UpOnRelyable< _FulfillerT >
{};

template< class _FulfillmentType >
class IsAFulfillerFor
{
public:
    template< class _Ty >
    class What : public Fulfillable< _Ty >::When< _FulfillmentType > {
    public:
        virtual AdapteeSolution& gainSolution( const Fulfillable< _Ty >::UpOnRelyable<_Ty>& relyable_since  ) const {
            return relyable_since.gainAdaption().Solve().solutional;
        }
    };

    template< class _WhenIsThisFullfiller >
    class When
        :   public Fulfillable< UpOnRelyable<What<_FulfillmentType>> >::When< What< IsAFulfillerFor< _FulfillmentType > > >
    {};
    
    template< class _FulfillingType >
/*        requires std::is_base_of_v< Fulfillable< _FulfillmentType >, _FulfillmentType >*/
    class OfDestriction
        :   public IsAFulfillerFor< Fulfillable< _FulfillmentType > >
    {
    public:
        template< class ConstraintsAndPremisesFullfilledAsWhatType >
/*            requires std::is_base_of_v< Fulfillable< _FulfillingType >, DestrictFullfilledAsWhatType >*/
        class As
            :   public OfDestriction< IsAFulfillerFor< _FulfillmentType >::When< ConstraintsAndPremisesFullfilledAsWhatType > >
            ,   public IsAFulfillerFor< _FulfillmentType >::What< _FulfillingType >
        {};

        template< class FulfillerLikeAWhatBaseType >
        class LikeA
            :   public IsAFulfillerFor< FulfillerLikeAWhatBaseType >
            ,   public Fulfillable< FulfillerLikeAWhatBaseType >::Fulfilled
            ,   public OfDestriction< As< FulfillerLikeAWhatBaseType > >
        {};

        template< class DestrictionIsFulfillmentForSpecificAt >
/*            requires std::is_base_of_v< _FulfillmentType, DestrictionIsFulfillmentForSpecificAt >*/
        class For
            :   public Fulfillable< DestrictionIsFulfillmentForSpecificAt >::Fulfilled
            ,   public IsAFulfillerFor< Fulfillable< _FulfillmentType > >
            ,   public OfDestriction< LikeA< _FulfillingType > >
            ,   public As< LikeA< DestrictionIsFulfillmentForSpecificAt > >
        {
        public:
            class When : public IsAFulfillerFor< _FulfillmentType >::When< _FulfillingType > {};
        };


        template< class WhatIsFulfillableHereType >
        class AtAn
            :   public OfDestriction< _FulfillingType >::As< _FulfillingType >
            ,   public LikeA< For< Fulfillable< WhatIsFulfillableHereType >::When< _FulfillingType > > >
            ,   public For< Fulfillable< WhatIsFulfillableHereType >::When<
                                                                        IsAFulfillerFor< _FulfillmentType >::What< Fulfillable< WhatIsFulfillableHereType >::Fulfilled >
                                                                    >
        {};
    };

    AdapteeSolution& gainSolution( const Fulfillable<_FulfillmentType>::UpOnRelyable< )

    AdapteeSolution& gain() const {
        return this->gainSolution();
    }
};


class Clientable { 
public:
    class Type;

    class DecayResult : public util::AnyResult {
        static DecayResult& fromAnyClientableResult( const Clientable::Type& any_result ) {
            return *new DecayResult( any_result() );
        }

        Clientable::TypeResult& toTypeResult() const;
    };

    class DecayTarget {
        const Clientable::Guarantee& decay_preliminary;
        const Clientable::Type& can_fulfill;

        DecayTarget( const Clientable::Type& can_preliminary_decay )
            :   decay_preliminary( can_preliminary_decay.Request() )
            ,   can_fulfill( can_preliminary_decay )
        {}

        Clientable::Target& deabstracted_clientable() const {
            Clientable::Type& decay_to_clientable_type = this->decay_preliminary.Fulfill();
            return this->decay_preliminary.Resolve().Transform( decay_to_clientable_type );
        }
    };


    class TypeResult 
        :   public util::TypeResult<DecayResult, Clientable::Type>
    {
    public:
        TypeResult( const TypeResult::GenericResult& generic_result )
            :   util::TypeResult<DecayResult, Clientable::Type>( generic_result )
        {}
        
        virtual Clientable::TypeResult::NeutralTo makeDecayFree() final;
        virtual static Clientable::Type& beNeutralTo( TypeResult::GenericResult& resulting_decay ) final;
    };

    class AnyResult {
    public:
        Clientable::TypeResult::NeutralTo& neutral_and_fair;

        virtual Clientable::TypeResult::GivesFromAny& neutral() const final {
            return Clientable::TypeResult::makeNeutral( this->neutral_and_fair )
        }
        
        DecayResult& get( const Clientable::Target& clientable_fare );
        DecayResult& get( const DecayTarget& abstract_decay ) const {
            return AnyResult::get( Clientable::Request( abstract_decay.deabstracted_clientable() ) );
        }
    };

    virtual Clientable::AnyResult& Request( const Clientable::Target& fulfilling_target ) const;

    class Guarantee;

    class Type : public IsAFulfillerFor<Clientable::AnyResult> {
    public:
        friend class Adapter;

        static Guarantee& Request() const;

        util::AnyResult& operator()() const { return this->Request().; }
    };

    class Target;
    class DecayResult;
    class DecayTarget;
    class DescriptiveDecayTarget;
    class Guarantee;
    class RessortDecay;

    class AbstractGuarantee
        :   public Fulfillable< Clientable::AnyResult >
        ,   public IsAFulfillerFor< Clientable::Type >
    {
    protected:
        virtual Clientable::Type& Fullfill() const = 0;
        virtual Clientable::Adaptee& Resolve() const final { return this->fulfill(); };
    };

    class DecayTarget { virtual Clientable::Type& Fulfill( const Clientable::Target& goal_towards_archivement ); };

    class DescriptiveGuarantee : public AbstractGuarantee, public DecayTarget {
        DescriptiveDecayTarget( const DescriptiveDecayTarget& goal_to_archive )
            :   DecayTarget( goal_to_archive )
        {}

        virtual Clientable::Type& begin( const Clientable::Target& target_fulfiller ) const {
            return DecayResult( DecayTarget::Fulfill(target_fulfiller) ).Fulfill();
        }
        DecayResult& gain_archivement();
        DecayTarget& sayIGuarantee();
        DescriptiveGuarantee& showHowYouGuarantee();
        Guarantee& showWarranty();
        RessortDecay& offer();
    };

    class Guarantee
        :   public AbstractGuarantee
        ,   public Clientable::Type
        ,   public IsAFulfillerFor< Clientable::Adaptee >
        ,   public IsAFulfillerFor< AbstractGuarantee >::OfDestriction< Clientable::Adaptee >::As< Guarantee >
        ,   public Fulfillable< Clientable::Target >
    {
    public:
        virtual Clientable::Target& ResolveWithAdaptee( const Adaptee& adaptee ) const {
            return adaptee.Transform( adaptee );
        }

        virtual Clientable::Type fulfill() const {
            return this->ResolveWithAdaptee( this->Resolve() ).fulfillAbstractPromise();
        }

        virtual Clientable::Target& ResolveToTarget() const {
            return this->ResolveWithAdaptee( this->Resolve() );
        }

        /*
        Guarantee( const Clientable::Type& from_decay, const Guarantee& unpreliminar_other )
            :   
        {}
        Guarantee( const Clientable::TypeResult& without_decay_and_clientable_fair );
        */


        Clientable::Type& fromDecay( const Clientable::Type& nearly_clientable ) {
            return *new Guarantee( nearly_clientable, this );
        }
    };

    class Adaptee
        :   public TypeResult
    {
    public:
        const Guarantee& fulfillment;
        
        Adaptee( const Guarantee& guarantee_to_fulfill_or_fulfilling_clientable_target )
            :   fulfillment( guarantee_to_fulfill_or_fulfilling_clientable_target )
        {}

        static Clientable::Target& Transform( const Adaptee& adapting ) final {
            return adapting.Resolve();
        }

        static Clientable::Target& Transform( const Clientable::Type& nearly_clientable ) {
            return Guarantee( nearly_clientable, this->fulfillment ).ResolveToTarget();
        }

        virtual Clientable::AnyResult Resolve() const {
            return Adaptee::Transform( *this ).fulfill();
        }
    };


    class SolutionalTarget;

    using DecayTarget = Clientable::Target;
    using DecayResult = SolutionalTarget;

    class Ressort
        :   public AbstractGuarantee, protected Adaptee
    {
    public:
        class Decay : public Clientable::Target {
        public:
            Decay( const DescriptiveGuarantee& abstract_issues_and_target_goals );
            DecayTarget& sayAbstract() const;
            DecayResult& abstractlyFulfillPromise() const;
            Decay& abstractFulfillmentDescription() const;
            AbstractGuarantee& explainAbstractPromise() const;
        };


        class ResilientDecay : public Decay, public Clientable::SolutionalTarget {};


        virtual Adaptee& fulfill_at( const DecayTarget& at_ressort_or_place ) {
            return *new Adaptee( at_ressort_or_place );
        }

        virtual Guarantee& fulfill_for( const Ressort::Decay& decay_or_customer ) {
            return this->fulfill_at( decay_or_customer.sayAbstract() );
        }
        virtual Guarantee& fulfill_for( const DescriptiveGuarantee& abstract_milestone_so_far ) {
            return Ressort::fulfill_for( *new Ressort::Decay(abstract_milestone_so_far.Resolve()) );
        }
        virtual SolutionalTarget& fulfill_of( const DecayTarget& ressort_decay ) const {
            return *new SolutionalTarget( ressort_decay );
        }
        virtual SolutionalTarget& fulfill_of( const AbstractGuarantee& abstractResolveOffer ) {
            return Ressort::fulfill_of( abstractResolveOffer );
        }
        virtual SolutionalTarget& fulfill_of( const Decay& customer_decay ) const {
            SolutionalTarget& solution( customer_decay.abstractlyFulfillPromise(), *this );
            for ( const SolutionalTarget& decay_target_or_issue : customer_decay ) {
                    solution << Ressort::fulfill_of( decay_target_or_issue );
            }
            return solution;
        }
    };

    class Target : public Guarantee {
    protected:
        virtual static Clientable::Type& fulfillAbstractPromise( const Adaptee& adapting ) const final {
            return AnyFulfillment::fulfill( this, Adaptee::Transform( adapting ).Resolve() );
        }
    };

    class AdapteeSolution : public DescriptiveGuarantee, public Ressort::Decay {
    public:
        AdapteeSolution( const AnyFulfillment& another_solution
                       , const Guarantee& concrete_guarantee
        );
    };

    class AdapteeArchivement : public Clientable::SolutionalTarget, public Ressort::Decay {
    public:
        static AdapteeArchivement& get( const Adaptee& specific_promise_fulfilled
                                      , const DescriptiveGuarantee& adaptee_guarantee
        );

        virtual DescriptiveGuarantee& descriptive() const;

        virtual  ( Clientable::Target& ) const {
            return this->descriptive().
        }
    };

    class SolutionalTarget : public AnyFulfillment, public Adaptee, public Clientable::Target {
    protected:
        SolutionalTarget( const Clientable::Target& client_guaranteed_solution_target
                        , const Clientable::Adaptee& ressort_or_footstare_milestones_resolved
        )   :   AnyFulfillment( ressort_or_footstare_milestones_resolved )
            ,   Clientable::Adaptee( ressort_or_footstare_milestones_resolved )
            ,   Clientable::Target( client_guaranteed_solution_target )
        {}
        SolutionalTarget( const AdapteeSolution& solution
                        , const AdapterAbstract< Clientable::Target >& adaptive_target_fulfiller
                        , const Clientable::Adaptee& adaptive_fulfilling_worker
        )   :   AnyFulfillment( adaptive_target_fulfiller.requestResolver(solution) )
            ,   Clientable::Adaptee( adaptive_fulfilling_worker )
            ,   Clientable::Target( adaptive_target_fulfiller.Request() )
        {}

        friend class AdapteeSolution;

        virtual DescriptiveGuarantee& toDescriptiveGuarantee() const {

        }

        static AdapteeArchivement& fulfillSpecificPromise( const AnyFulfillment& another_solution
                                              , const Guarantee& concrete_guarantee
        ) {

        }

    public:
        void append( const SolutionalTarget& target_that_resolutes_this );
        SolutionalTarget& operator<<( const SolutionalTarget& target_that_resolutes_here );
    };

    class AdapteeSolution : public Clientable::TypeResult, public Adaptee {
    protected:
        AdapteeSolution( const Adaptee& solving_adaptee )
            :   Adaptee( solving_adaptee )
        {}

    public:
        virtual SolutionalTarget& Transform() const final {
            return *new Clientable::SolutionalTarget( Adaptee::Transform( *this ) );
        }
        virtual Clientable::AnyResult Resolve() const final {
            return this->Resolve( *this );
        }
        virtual Clientable::Target& Resolve( const Clientable::Adaptee& adaptee ) final {
            return adaptee.Transform( *this ).fulfill();
        }

        template< class _FulfillFor >
        static Fullfillable<_FulfillFor>::AdapterFor& fulfillableAdapter( 
                                                                    const AnySolution& fufilling_resolution
                                                                  , const AdapteeSolution& fulfillment_adaptee  
        ) final {
            return fufilling_resolution.ClientableAdapterFor<_FulfillFor>( fulfillment_adaptee.Transform()
                                                                         , fulfillment_adaptee
            );
        }
    };

    friend class AdapterAbstract< Clientable::Adaptee >;
    friend class AdapterAbstract< Clientable::Target >;
};



class AnyFulfillment
    :   protected Clientable::AdapteeSolution
    ,   protected AnyClassBase< Clientable::Guarantee >
    ,   public IsAFulfillerFor< Clientable::Target >::OfDestrict< Clientable::Guarantee >
{
protected:
    static Clientable::Adaptee& fulfillAbstractPromise( const AnyFulfillment& any_fulfiller, const Adaptee& adapting ) final {
        return any_fulfiller.fulfillAdaptionalPromise( adapting );
    }

    friend class AnyFulfillment;

    virtual Clientable::Adaptee& fulfillAdaptionalPromise( const Clientable::Adaptee& adaptee ) const final {
        return AnyFulfillment::fulfillAbstractPromise( this->Transform(adaptee), adaptee );
    }


public:
    Clientable::SolutionalTarget& solutional_howto_target;
    Clientable::SolutionalTarget& target_goal;

    virtual Clientable::Type& fulfill() const final {
        return this->fulfillAdaptionalPromise( *this ).Resolve();
    }

    AnyFulfillment( Clientable::Adaptee& guaranteeing_worker,
         Clientable::SolutionalTarget& solution )
        :   Clientable::AdapteeSolution( guaranteeing_worker )
        ,   solutional_target( *new Clientable::SolutionalTarget(solution, guaranteeing_worker) )
        ,   target_goal( solution )
    {}
    AnyFulfillment( const Adaptee& fulfillingAdaptee )
        :   AdapteeSolution( fulfillingAdaptee )
    {}
    AnyFulfillment( const Guarantee& guaranteeImplemented )
        :   AdapteeSolution()
    {}

    template< class _FulfillsFor >
    AdapterAbstract< _FulfillsFor > ClientableAdapterFor( const Clientable::SolutionalTarget& fufillment
                                                       , const AdapteeSolution& fulfillment_adaptee   
    ) {
        return *new AdapterAbstract< _FulfillsFor >( this->fulfillAdaptionalPromise(
                                                         fufillment.fulfillSpecificPromise( fulfillment_adaptee )
            ) );
    }



};


template< class _ClientableType >
class AdapterAbstract
    :   public Clientable::AdapteeSolution
    ,   public Fulfillable< _ClientableType >
{
public:
    class AdaptiveSession {
    public:
        AnyFulfillment& resolver;
        Clientable::AdapteeSolution& solution_for_adapting;

        AdaptiveSession( const AnyFulfillment& resolv
                       , Clientable::AdapteeSolution solution_to_adapt_type_in_fulfillment
        )   :   resolver( resolv )
            ,   solution_for_adapting( solution_to_adapt_type_in_fulfillment )
        
        Clientable::AdapteeSolution& adapteeSolution() const;

        Adapter& Solve() const {
            return this->adapteeSolution().Resolve();
        }
    };

    static AnyFulfillment& Fulfill( Clientable::SolutionalTarget& resolut_target
                               , Clientable::AdapteeSolution& competive_solution
    ) const {
        return Fulfill( requestResolver( competive_solution ), resolut_target );
    }

    Adapter& forFullfillerType() {
        return *new Adapter( AdapterAbstract<_ClientableType>, AdapteeSolution& solution );
    }


    static Clientable::Guarantee& requestResolver( const Clientable::AdapteeSolution& specificRequestResult ) final {
        return specificRequestResult.fulfillment();
    }

    //static 

    virtual friend class Adapter;
public:
    virtual Clientable::Target& Request() const {
        return AdapterAbstract< _ClientableType >::requestResolver( _ClientableType::Request() ).ResolveWithAdaptee(*this);
    }

    virtual Clientable::Target& Resolve( const Clientable::Adaptee& adaptee ) final {
        return adaptee.fulfillment.Resolve();
    }
};



class Adapter
    :   public AdapterAbstract< Clientable::Target >
    ,   protected AnyClassBase< AnyFulfillment >
    ,   public IsAFulfillerFor< Clientable::Target >
{
public:
    template< class _AdaptiveWithBaseType >
    Adapter( AdapterAbstract< _AdaptiveWithBaseType >& adaptive
           , AnyFulfillment& competive_complete_generic_fulfillment
    )   :   AdapterAbstract< Clientable::Target >( adaptive )
        ,   AnyClassBase< AnyFulfillment >( competive_complete_generic_fulfillment )
    {}


    Clientable::AdapteeSolution& solutional;

    virtual Clientable::Target& Resolve() const {
        return this->Resolve(  this->own->Request() );
    }

    virtual util::AnyResult& Request() const {
        return this->Resolve( this->solutional ).fulfill;
    }
};


class AdapterClient
    :   public Adapter
    ,   public VisitorClient
{};


} // namespace util
} // namespace plugin