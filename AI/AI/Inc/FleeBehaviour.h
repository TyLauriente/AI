#pragma once

#include"SteeringBehaviour.h"
#include "AIWorld.h"

namespace AI
{

	class FleeBehaviour : public SteeringBehaviour
	{
	public:

		FleeBehaviour();

		~FleeBehaviour();

		X::Math::Vector2 Calculate(Agent& agent) override;

		const char* GetName() const override;

	private:
		const char* NAME = "Flee";

	};

} // NAMESPACE AI