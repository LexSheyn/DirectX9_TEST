#ifndef TOOLS_H
#define TOOLS_H

#pragma once

namespace tool
{
// Split:

	// Split a String into a string array at a given token.
	void Split(const std::string& in, std::vector<std::string>& out, std::string token);


// Tail:

	std::string Tail(const std::string& in);


// First Token:

	std::string FirstToken(const std::string& in);


// Get Element:

	// Get element at given index position.
	template <class T>	
	const T& GetElement(const std::vector<T>& elements, std::string& _index)
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
}

#endif / TOOLS_H