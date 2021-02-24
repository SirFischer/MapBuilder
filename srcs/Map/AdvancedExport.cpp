#include "Map.hpp"

std::string	Map::GetAdvancedFormat()
{
	std::string result = "";
	if (mElements.size() < 1)
		return "";
	SortElements();
	for (auto &elem : mElements)
	{
		int signature = (int)(' ');
		for (auto &k : mSignatures)
		{
			if (k.second == elem.GetPath())
				signature = k.first;
		}
		result += "elem=" + std::to_string(signature) + "\n";
		result += "gpos=" + std::to_string(elem.GetGridPosition().x) + " " + std::to_string(elem.GetGridPosition().y) + "\n";
		result += "pos=" + std::to_string(elem.GetPosition().x) + " " + std::to_string(elem.GetPosition().y) + "\n";
	}
	return (result);
}