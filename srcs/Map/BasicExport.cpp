#include "Map.hpp"

std::string	Map::GetBasicFormat()
{
	std::string result = "";
	if (mElements.size() < 1)
		return "";
	SortElements();
	std::list<Element>::iterator it = mElements.begin();
	std::list<Element>::iterator tmp;
	while (it != mElements.end())
	{
		tmp = it;
		it++;
		if (it->GetGridPosition() == tmp->GetGridPosition())
			mElements.erase(tmp);
	}
	sf::Vector2i	max = mElements.front().GetGridPosition(), min = mElements.front().GetGridPosition();
	for (auto &i : mElements)
	{
		sf::Vector2i	pos = i.GetGridPosition();
		if (pos.x < min.x)
			min.x = pos.x;
		if (pos.y < min.y)
			min.y = pos.y;
		if (pos.x > max.x)
			max.x = pos.x;
		if (pos.y > max.y)
			max.y = pos.y;
	}
	it = mElements.begin();
	for (int i = min.y; i <= max.y; i++)
	{
		for (int j = min.x; j <= max.x; j++)
		{
			if (it->GetGridPosition().x > j || it->GetGridPosition().y > i )
				result += ' ';
			else
			{
				int signature = (int)(' ');
				for (auto &k : mSignatures)
				{
					if (k.second == it->GetPath())
						signature = k.first;
				}
				result += (char)signature;
				it++;
			}
		}
		result += '\n';
	}
	return (result);
}