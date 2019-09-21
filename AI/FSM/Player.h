#pragma once

#include<XEngine.h>

class Player
{
public:

	void XInitiaize()
	{
		m_texture_id = X::LoadTexture("Player.png");
		m_spriteHeight = X::GetSpriteHeight(m_texture_id);
		m_spriteWidth = X::GetSpriteWidth(m_texture_id);
		m_screenWidth = X::GetScreenWidth();
		m_screenHeight = X::GetScreenHeight();
		m_position = { m_screenWidth * 0.5f, m_screenHeight * 0.5f };
	}

	void Update(float deltaTime)
	{
		if(X::IsKeyDown(X::Keys::LEFT) && m_position.x - SPEED * deltaTime >= m_spriteWidth * 0.5f)
		{
			m_position.x -= SPEED * deltaTime;
		}
		else if(X::IsKeyDown(X::Keys::RIGHT) && m_position.x + SPEED * deltaTime < m_screenWidth - (m_spriteWidth * 0.5f))
		{
			m_position.x += SPEED * deltaTime;
		}
		else if(X::IsKeyDown(X::Keys::UP) && m_position.y - SPEED * deltaTime >= m_spriteHeight * 0.5f)
		{
			m_position.y -= SPEED * deltaTime;
		}
		else if(X::IsKeyDown(X::Keys::DOWN) && m_position.y + SPEED * deltaTime < m_screenHeight - (m_spriteHeight * 0.5f))
		{
			m_position.y += SPEED * deltaTime;
		}
	}

	void Render() const
	{
		X::DrawSprite(m_texture_id, m_position);
	}

	X::Math::Vector2 GetPosition() const { return m_position; }

	X::Math::Circle GetBoundingCircle() const
	{
		X::Math::Circle c;
		c.center = m_position;
		c.center.x += m_spriteWidth * 0.5f;
		c.center.y += m_spriteHeight * 0.5f;
		c.radius = m_spriteWidth * 0.5f;
		return c;
	}

private:
	const float SPEED = 500.0f;
	X::Math::Vector2 m_position;
	X::TextureId m_texture_id;
	float m_spriteWidth;
	float m_spriteHeight;
	float m_screenWidth;
	float m_screenHeight;
};