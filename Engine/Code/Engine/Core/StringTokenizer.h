#pragma once

#include <string>
#include <vector>

class StringTokenizer
{
	std::string m_Input;
	std::string m_Delimiter;
	std::vector<std::string> m_Tokens;
public:
	StringTokenizer(const std::string& input, const std::string& delimiter = "");
	~StringTokenizer();

	void Tokenize();

	inline std::vector<std::string> GetTokens() const { return m_Tokens; }
};