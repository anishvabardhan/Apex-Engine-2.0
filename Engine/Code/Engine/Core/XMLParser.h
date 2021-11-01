#pragma once

#include "External/tinyxml2.h"
#include "Engine/Core/CoreIncludes.h"

#include <string>

typedef tinyxml2::XMLElement XMLelement;

int ParseXMLAttrib(const XMLelement& element, const std::string& attribName, int value);
std::string ParseXMLAttrib(const XMLelement& element, const std::string& attribName, std::string value);
float ParseXMLAttrib(const XMLelement& element, const std::string& attribName, float value);
Vec2 ParseXMLAttrib(const XMLelement& element, const std::string& attribName, const Vec2& value);
Vec3 ParseXMLAttrib(const XMLelement& element, const std::string& attribName, const Vec3& value);
Vec4 ParseXMLAttrib(const XMLelement& element, const std::string& attribName, const Vec4& value);