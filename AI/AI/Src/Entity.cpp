#include"Precompiled.h"
#include"Entity.h"

using namespace AI;

Entity::Entity(uint32_t type, uint32_t id)
	: m_type{ type }
	, m_id{ id }
{

}

Entity::~Entity()
{

}