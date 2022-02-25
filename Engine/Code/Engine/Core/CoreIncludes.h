#pragma once

#include "Engine/Core/CoreMACROS.h"
#include "Engine/Maths/AABB2.h"
#include "Engine/Maths/Mat4.h"
#include "Engine/Maths/Random.h"
#include "Engine/Maths/Disc2D.h"

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdint>

namespace tinyxml2 
{ 
	class XMLElement; 
	class XMLDocument;
}

using XMLElement = tinyxml2::XMLElement;
using XMLDocument = tinyxml2::XMLDocument;
using String = std::string;
using Strings = std::vector<std::string>;