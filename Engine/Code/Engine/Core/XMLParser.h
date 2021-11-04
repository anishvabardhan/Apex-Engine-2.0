#pragma once

#include "Engine/Core/CoreIncludes.h"

int ParseXMLAttrib(const XMLElement& element, const std::string& attribName, int value);
std::string ParseXMLAttrib(const XMLElement& element, const std::string& attribName, std::string value);
float ParseXMLAttrib(const XMLElement& element, const std::string& attribName, float value);
Vec2 ParseXMLAttrib(const XMLElement& element, const std::string& attribName, const Vec2& value);
Vec3 ParseXMLAttrib(const XMLElement& element, const std::string& attribName, const Vec3& value);
Vec4 ParseXMLAttrib(const XMLElement& element, const std::string& attribName, const Vec4& value);