#pragma once


namespace AI
{

class Entity
{
public:

	Entity(uint32_t type, uint32_t id);

	~Entity();

	X::Math::Vector2& GetPosition()  { return m_position; }

	const uint32_t& GetType() const { return m_type; }
	
	const uint32_t& GetId() const { return m_id; }


protected:
	X::Math::Vector2 m_position{ 0.0f, 0.0f };
	uint32_t m_type;
	uint32_t m_id;
};

using EntityList = std::vector<Entity*>;

} // NAMESPACE AI