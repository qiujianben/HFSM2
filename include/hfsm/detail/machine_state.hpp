namespace hfsm {

////////////////////////////////////////////////////////////////////////////////

template <typename TContext, unsigned TMaxSubstitutions>
template <typename TH>
struct M<TContext, TMaxSubstitutions>::_S {
	using Head = TH;

	enum : unsigned {
		ReverseDepth = 1,
		DeepWidth	 = 0,
		StateCount	 = 1,
		ForkCount	 = 0,
		ProngCount	 = 0,
		Width		 = 1,
	};

	_S(StateRegistry& stateRegistry,
	   const Parent parent,
	   Parents& stateParents,
	   Parents& forkParents,
	   ForkPointers& forkPointers);

	inline void deepForwardSubstitute(Control&, Context&)					{}
	inline bool deepSubstitute(Control& control, Context& context);

	inline void deepEnterInitial(Context& context);
	inline void deepEnter(Context& context);

	inline bool deepUpdateAndTransition(Control& control, Context& context);
	inline void deepUpdate(Context& context);

	template <typename TEvent>
	inline void deepReact(const TEvent& event, Control& control, Context& context);

	inline void deepLeave(Context& context);

	inline void deepForwardRequest(const enum Transition::Type)				{}
	inline void deepRequestRemain()											{}
	inline void deepRequestRestart()										{}
	inline void deepRequestResume()											{}
	inline void deepChangeToRequested(Context&)	{}

#ifdef HFSM_ENABLE_STRUCTURE_REPORT
	static constexpr bool isBare() { return std::is_same<Head, _B<Bare>>::value; }

	enum : unsigned {
		NameCount	 = isBare() ? 0 : 1,
	};

	static const char* name();

	void deepGetNames(const unsigned parent,
					  const enum StateInfo::RegionType region,
					  const unsigned depth,
					  StateInfos& stateInfos) const;

	void deepIsActive(const bool isActive,
					  unsigned& index,
					  MachineStructure& structure) const;
#endif

	Head _head;

	HSFM_IF_DEBUG(const TypeInfo _type = TypeInfo::get<Head>());
};

////////////////////////////////////////////////////////////////////////////////

}

#include "machine_state_methods.inl"
