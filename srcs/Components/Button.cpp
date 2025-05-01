#include "Components.hpp"

std::shared_ptr<mf::Button>		Components::CreateButton(std::string tString, sf::Vector2f tSize, sf::Vector2f tPos, std::function<void()> tClickEvent)
{
	auto btn = mf::Button::Create();
	btn->GetBackground()->SetBackground(sf::Color::White);
	btn->GetBackground()->SetOutlineColor(sf::Color::Black);
	btn->GetBackground()->SetOutlineThickness(1.f);

	btn->SetSize(tSize);
	btn->SetPosition(tPos);
	btn->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	btn->GetText()->SetString(tString);
	btn->GetText()->SetColor(sf::Color::Black);
	btn->GetText()->SetSize(15);
	btn->GetText()->SetPos(sf::Vector2f(10, 5));
	btn->SetClickEvent(tClickEvent);
	btn->AddEventListener(mf::eEvent::ENTERED, [btn] {
		btn->GetBackground()->SetOutlineThickness(3.f);
	});
	btn->AddEventListener(mf::eEvent::EXITED, [btn] {
		btn->GetBackground()->SetOutlineThickness(1.f);
	});

	return (btn);
}