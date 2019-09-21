#ifndef CAMERAMANAGER_INCLUDED_H
#define CAMERAMANAGER_INCLUDED_H

#include<XEngine.h>

class CameraManager
{
public:
	static void StaticInitialize();

	static void StaticTerminate();

	static CameraManager* Get();

public:

	CameraManager();
	~CameraManager();

	void XInitialize();

	void SetViewPosition(X::Math::Vector2 viewPos);

	X::Math::Vector2 ConvertToWorld(X::Math::Vector2 screenPos) const;

	X::Math::Vector2 ConvertToScreen(X::Math::Vector2 worldPos) const;

	void Render(X::TextureId id, X::Math::Vector2 worldPos);

	bool IsOnScreen(X::Math::Vector2 screenPos) const;


	X::Math::Vector2 m_position;
private:
	const float VERSION_OFFSET = 25.0f;
	const float TILE_WIDTH = 32.0f;
	float m_screenWidth;
	float m_screenHeight;
};

#endif