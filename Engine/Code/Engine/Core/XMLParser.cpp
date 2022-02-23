#include "XMLParser.h"
#include "StringTokenizer.h"
#include "tinyxmlH.h"

int ParseXMLAttrib(const XMLElement& element, const String& attribName, int value)
{
	int intValue = value;
	const char* intText = element.Attribute(attribName.c_str());

	if (intText)
	{
		int temp = stoi(static_cast<String>(intText));
		intValue = temp;
	}

	return intValue;
}

String ParseXMLAttrib(const XMLElement& element, const String& attribName, String value)
{
	String stringValue = value;
	const char* charText = element.Attribute(attribName.c_str());

	if (charText)
	{
		stringValue = charText;
	}

	return stringValue;
}

float ParseXMLAttrib(const XMLElement& element, const String& attribName, float value)
{
	float val = value;
	const char* floatText = element.Attribute(attribName.c_str());

	if (floatText)
	{
		float temp = stof(static_cast<String>(floatText));
		val = temp;
	}

	return val;
}

Vec2 ParseXMLAttrib(const XMLElement& element, const String& attribName, const Vec2& value)
{
	Vec2 vec2 = value;
	const char* vecText = element.Attribute(attribName.c_str());

	if (vecText)
	{
		String temp = vecText;
		String newX, newY;
		size_t commaIndex = 0;

		commaIndex = temp.find(",", commaIndex);
		
		newX = String(temp, 0, commaIndex);
		newY = String(temp, commaIndex + 1);

		vec2.m_X = stof(newX);
		vec2.m_Y = stof(newY);
	}

	return vec2;
}

Vec3 ParseXMLAttrib(const XMLElement& element, const String& attribName, const Vec3& value)
{
	Vec3 vec3 = value;
	const char* vecText = element.Attribute(attribName.c_str());

	if (vecText)
	{
		StringTokenizer tokenizer(vecText, ",");
		tokenizer.Tokenize();

		Strings tokens(3);

		tokens = tokenizer.GetTokens();

		vec3.m_X = strtof(tokens[0].c_str(), nullptr);
		vec3.m_Y = strtof(tokens[1].c_str(), nullptr);
		vec3.m_Z = strtof(tokens[2].c_str(), nullptr);
	}

	return vec3;
}

Vec4 ParseXMLAttrib(const XMLElement& element, const String& attribName, const Vec4& value)
{
	Vec4 vec4 = value;
	const char* vecText = element.Attribute(attribName.c_str());

	if (vecText)
	{
		StringTokenizer tokenizer(vecText, ",");
		tokenizer.Tokenize();

		Strings tokens(4);

		tokens = tokenizer.GetTokens();

		vec4.m_X = strtof(tokens[0].c_str(), nullptr);
		vec4.m_Y = strtof(tokens[1].c_str(), nullptr);
		vec4.m_Z = strtof(tokens[2].c_str(), nullptr);
		vec4.m_W = strtof(tokens[3].c_str(), nullptr);
	}

	return vec4;
}