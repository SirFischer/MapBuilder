#pragma once

#include <mfGUI.hpp>

class Components
{
	public:

	static std::shared_ptr<mf::Button>		CreateButton(std::string tString, sf::Vector2f tSize, sf::Vector2f tPos, std::function<void()> tClickEvent);

};