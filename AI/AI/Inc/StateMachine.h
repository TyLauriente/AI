#pragma once

#include<iostream>
#include<XEngine.h>
#include"State.h"

namespace AI
{
template<class AgentType>
class StateMachine
{
public:
	using StateType = State<AgentType>;


	StateMachine(AgentType& agent);
	~StateMachine();

	template<class NewStateType>
	void AddState();
	void Purge();

	void Update(float deltaTime);
	void ChangeState(uint32_t index);

	int GetCurrentState() const { return m_currentStateIndex; }

private:
	AgentType& m_agent;
	StateType* m_currentState;
	int m_currentStateIndex;
	std::vector<std::unique_ptr<StateType>> m_states;
};

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

template <class AgentType>
StateMachine<AgentType>::StateMachine(AgentType& agent)
	: m_agent{ agent }
	, m_currentState{ nullptr }
{}

template <class AgentType>
StateMachine<AgentType>::~StateMachine()
{
	XASSERT(m_states.empty(),
		"[StateMachine] purge must be called before destruction");
}

template <class AgentType>
template <class NewStateType>
void StateMachine<AgentType>::AddState()
{
	static_assert(std::is_base_of<StateType, NewStateType>::value,
		"[StateMachine] Can only add state for AgentType.");
	m_states.emplace_back(std::make_unique<NewStateType>());
}

template <class AgentType>
void StateMachine<AgentType>::Purge()
{
	m_states.clear();
}

template <class AgentType>
void StateMachine<AgentType>::Update(float deltaTime)
{
	XASSERT(m_currentState != nullptr,
		"[StateMachine] m_current is null!");
	m_currentState->Update(m_agent, deltaTime);
}


template <class AgentType>
void StateMachine<AgentType>::ChangeState(uint32_t index)
{
	XASSERT(index < (uint32_t)m_states.size(),
		"[StateMachine] Invalid index %d.", index);
	if (m_currentState)
	{
		m_currentState->Exit(m_agent);
	}
	m_currentState = m_states[index].get();
	m_currentStateIndex = index;
	m_currentState->Enter(m_agent);
}


} // namespace AI