#pragma once

#include "Engine/Core/EngineCommon.h"
#include "Engine/Maths/AABB2.h"

class ShaderDefinition;
class FrameBuffer;


class Game
{
	AABB2 m_AABB2;
	ShaderDefinition* m_ShaderDef = nullptr;
	FrameBuffer* m_SrcBuffer = nullptr;
	FrameBuffer* m_DestBuffer = nullptr;
public:
	Game();
	~Game();

	void BeginFrame();
	void Update(float deltaseconds);
	void Render();
	void EndFrame();
};