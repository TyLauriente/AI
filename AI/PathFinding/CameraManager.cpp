#include "CameraManager.h"

namespace
{
	CameraManager* sInstance = nullptr;
}

void CameraManager::StaticInitialize()
{
	XASSERT(sInstance == nullptr, "[EnemyManager] Singleton already initialized.");
	sInstance = new CameraManager();
}

void CameraManager::StaticTerminate()
{
	delete sInstance;
	sInstance = nullptr;
}

CameraManager* CameraManager::Get()
{
	XASSERT(sInstance != nullptr, "[EnemyManager] Singleton not initialized.");
	return sInstance;
}

CameraManager::CameraManager()
	: m_position{ 0.0f, 0.0f }
	, m_screenWidth{ 0.0f }
	, m_screenHeight{ 0.0f }
{
	
}


CameraManager::~CameraManager()
= default;

void CameraManager::XInitialize()
{
	m_screenWidth = static_cast<float>(X::GetScreenWidth());
	m_screenHeight = static_cast<float>(X::GetScreenHeight());
}

void CameraManager::SetViewPosition(X::Math::Vector2 viewPos)
{
	viewPos.x -= 625;
	viewPos.y -= 345;
	m_position = viewPos;
}

X::Math::Vector2 CameraManager::ConvertToWorld(X::Math::Vector2 screenPos) const
{
	return screenPos + m_position;
}

X::Math::Vector2 CameraManager::ConvertToScreen(X::Math::Vector2 worldPos) const
{
	return worldPos - m_position;
}

void CameraManager::Render(X::TextureId id, X::Math::Vector2 worldPos)
{
	if (IsOnScreen(ConvertToScreen(worldPos)))
	{
		X::Math::Vector2 newPos = ConvertToScreen(worldPos);
		newPos.x += VERSION_OFFSET;
		newPos.y += 25;
		X::DrawSprite(id, newPos);
	}	
}

bool CameraManager::IsOnScreen(X::Math::Vector2 screenPos) const
{
	return screenPos.x > (0 - TILE_WIDTH) && screenPos.y > (0 - TILE_WIDTH) && 
		screenPos.x < m_screenWidth && screenPos.y < m_screenHeight;
}
