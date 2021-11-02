#pragma once

// Turn off all warnings for Third-Party libs at the start and turn it on at the end
#define THIRD_PARTY_INCLUDES_BEGIN #pragma warning(push, 0)
#define THIRD_PARTY_INCLUDES_END #pragma warning(pop)

#include "Engine/Maths/AABB2.h"
#include "Engine/Maths/Mat4.h"
#include "Engine/Maths/Random.h"
#include "Engine/Maths/Disc2D.h"
#include "LogMessage.h"

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

#define UNUSED(x) (void)x;