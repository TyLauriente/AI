#pragma once

#include"SteeringBehaviour.h"
#include "AIWorld.h"

namespace AI
{

class SeekBehaviour : public SteeringBehaviour
{
public:

	SeekBehaviour();
	
	~SeekBehaviour();

	X::Math::Vector2 Calculate(Agent& agent) override;

	const char* GetName() const override;

private:
	const char* NAME = "Seek";

};

} // NAMESPACE AI
