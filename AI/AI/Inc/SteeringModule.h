#pragma once

#include<iostream>
#include"SteeringBehaviour.h"

namespace AI
{

class SteeringModule
{
public:
	SteeringModule(Agent& agent);
	~SteeringModule();

	template <class BehaviourType>
	BehaviourType* AddBehaviour();

	template <class BehaviourType>
	BehaviourType* GetBehaviour(const char* name);

	void Purge();

	X::Math::Vector2 Calculate();


private:
	Agent& m_agent;
	std::vector<std::unique_ptr<SteeringBehaviour>> m_behaviours;
};

//====================================================================

template <class BehaviourType>
BehaviourType* SteeringModule::AddBehaviour()
{
	m_behaviours.push_back(std::make_unique<BehaviourType>());
	return static_cast<BehaviourType*>(m_behaviours.back().get());
}

template <class BehaviourType>
BehaviourType* SteeringModule::GetBehaviour(const char* name)
{
	for (auto& b : m_behaviours)
	{
		if (b->GetName() == name)
		{
			return static_cast<BehaviourType*>(b.get());
		}
	}

	return nullptr;
}

} // Namespace AI