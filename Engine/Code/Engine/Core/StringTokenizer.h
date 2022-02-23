#pragma once

#include "CoreIncludes.h"

class StringTokenizer
{
	String m_Input;
	String m_Delimiter;
	Strings m_Tokens;
public:
	StringTokenizer(const String& input, const String& delimiter = String());
	~StringTokenizer();

	void Tokenize();

	inline Strings GetTokens() const { return m_Tokens; }
};