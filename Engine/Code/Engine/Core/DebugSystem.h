#pragma once

#include "Engine/Core/CoreIncludes.h"

class DebugSystem
{
public:
	DebugSystem();
	~DebugSystem();

	static void DebugCircle(float scale);
	static void DebugLine();
};