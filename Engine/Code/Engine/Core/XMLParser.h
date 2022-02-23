#pragma once

#include "Engine/Core/CoreIncludes.h"

int ParseXMLAttrib(const XMLElement& element, const String& attribName, int value);
String ParseXMLAttrib(const XMLElement& element, const String& attribName, String value);
float ParseXMLAttrib(const XMLElement& element, const String& attribName, float value);
Vec2 ParseXMLAttrib(const XMLElement& element, const String& attribName, const Vec2& value);
Vec3 ParseXMLAttrib(const XMLElement& element, const String& attribName, const Vec3& value);
Vec4 ParseXMLAttrib(const XMLElement& element, const String& attribName, const Vec4& value);