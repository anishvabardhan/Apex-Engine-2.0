#include "StringTokenizer.h"

#include <stdarg.h>

StringTokenizer::StringTokenizer(const std::string& input, const std::string& delimiter)
	: m_Input(input), m_Delimiter(delimiter)
{
}

StringTokenizer::~StringTokenizer()
{
}

void StringTokenizer::Tokenize()
{
	m_Tokens.clear();

	size_t prevIndex = 0;
	size_t currentIndex = 0;

	currentIndex = m_Input.find_first_of(m_Delimiter, currentIndex);

	while (prevIndex != std::string::npos && prevIndex < m_Input.size())
	{
		std::string token = m_Input.substr(prevIndex, currentIndex - prevIndex);

		if (prevIndex != 0)
		{
			prevIndex += m_Delimiter.size();
		}

		size_t quoteIndex = token.find_first_of("\"");

		if (quoteIndex != m_Input.npos && token[quoteIndex - 1] != '\\')
		{
			if (prevIndex == -1)
			{
				return;
			}

			if (m_Input[prevIndex] != m_Delimiter[0])
			{
				currentIndex = m_Input.find_first_of(m_Delimiter, prevIndex);
				m_Tokens[m_Tokens.size() - 1].append(m_Input.substr(prevIndex, currentIndex - prevIndex));
				prevIndex = currentIndex;
			}
		}
		else
		{
			token = std::string(m_Input, prevIndex, currentIndex - prevIndex);
			prevIndex = currentIndex;
			m_Tokens.push_back(token);
		}

		currentIndex = m_Input.find_first_of(m_Delimiter, currentIndex + m_Delimiter.size());

		if (m_Tokens.empty())
			m_Tokens.push_back(m_Input);
	}
}