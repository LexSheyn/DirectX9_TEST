#ifndef PARSER_H
#define PARSER_H

namespace str
{
	class Parser
	{
	public:

	// Constructors and Destructor:

		Parser();

		~Parser();

	// Functions:

		// Get first token of string.
		static std::string FirstToken(std::string& str);

		// Get tail of string after first token and possibly following spaces.
		static std::string Tail(const std::string& str);

		// Split a String into a string array at a given token.
		static void Split(const std::string& in_str, 
			                    std::vector<std::string>& out_str,
			              const std::string& token);

		// Get element at given index position
		template <class T>
		static const T& GetElement(const std::vector<T>& elements, std::string& _index)
		{
			int32 index = std::stoi(_index);

			if (index < 0)
			{
				index = static_cast<int32>(elements.size()) + index;
			}
			else
			{
				index--;
			}

			return elements[index];
		}
	};
}

#endif // PARSER_H