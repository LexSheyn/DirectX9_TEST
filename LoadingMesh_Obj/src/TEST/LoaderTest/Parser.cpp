#include "../../PrecompiledHeaders/stdafx.h"
#include "Parser.h"

namespace str
{
// Constructors and Destructor:

	Parser::Parser()
	{
	}

	Parser::~Parser()
	{
	}


// Functions:

	std::string Parser::FirstToken(std::string& str)
	{
		if (!str.empty())
		{
			size_t token_start = str.find_first_not_of(" \t");

			size_t token_end   = str.find_first_of(" \t", token_start);

			if (token_start != std::string::npos && token_end != std::string::npos)
			{
				return str.substr(token_start, token_end - token_start);
			}
			else if (token_start != std::string::npos)
			{
				return str.substr(token_start);
			}
		}

		return "";
	}

	std::string Parser::Tail(const std::string& str)
	{
		size_t token_start = str.find_first_not_of(" \t");

		size_t space_start = str.find_first_of(" \t", token_start);

		size_t tail_start  = str.find_first_not_of(" \t", space_start);

		size_t tail_end    = str.find_last_not_of(" \t");

		if (tail_start != std::string::npos && tail_end != std::string::npos)
		{
			return str.substr(tail_start, tail_end - tail_start + 1u);
		}
		else if (tail_start != std::string::npos)
		{
			return str.substr(tail_start);
		}

		return "";
	}

	void Parser::Split(const std::string& in_str, 
		                            std::vector<std::string>& out_str, 
		                      const std::string& token)
	{
		out_str.clear();

		std::string temp;

		for (size_t i = 0u; i < in_str.size(); i++)
		{
			std::string test = in_str.substr(i, token.size());

			if (test == token)
			{
				if (!temp.empty())
				{
					out_str.push_back(temp);

					temp.clear();

					i += token.size() - 1u;
				}
				else
				{
					out_str.push_back("");
				}
			}
			else if (i + token.size() >= in_str.size())
			{
				temp += in_str.substr(i, token.size());

				out_str.push_back(temp);

				break;
			}
			else
			{
				temp += in_str[i];
			}
		}
	}

}