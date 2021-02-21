#include "ProfileState.hpp"

void		ProfileState::InitConfirmBox()
{
	mConfirmBox = mf::List::Create();
	mConfirmBox->SetDisabled(true);

	mConfirmBox->SetPositionPercentage(true)->SetPosition(30, 30);
	mConfirmBox->SetSizePercentage(true)->SetSize(30, 20);
	
	mf::GUI::AddWidget(mConfirmBox);

	mf::Text		*text = mf::Text::Create("assets/fonts/Roboto-Regular.ttf", "Are you sure?");
	text->SetSize(200, 30);
	text->SetCharacterSize(18);
	text->SetTextColor(sf::Color::Black);
	mConfirmBox->AddWidget(text);

	mf::Widget *tmp = mConfirmBox;
	mf::Button	*btn = mf::Button::Create(sf::Color::White, sf::Color::Yellow);
	btn->SetText("No")->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetTextColor(sf::Color::Black);
	btn->SetSizePercentage(true)->SetSize(99, 30);
	btn->SetCharacterSize(14);
	btn->SetClickEvent([tmp]{
		tmp->SetDisabled(true);
	});
	mConfirmBox->AddWidget(btn);
	btn = mf::Button::Create(sf::Color::White, sf::Color::Yellow);
	btn->SetText("Delete")->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetTextColor(sf::Color::Black);
	btn->SetSizePercentage(true)->SetSize(99, 30);
	btn->SetCharacterSize(14);

	StateAction				*stateReturnAction = &mStateReturnAction;
	bool					*isRunning = &mIsActive;
	Data					*data = mData;
	btn->SetClickEvent([tmp, stateReturnAction, isRunning, data]{
		tmp->SetDisabled(true);
		data->mProfile.Delete();
		*stateReturnAction = StateAction::POP;
		*isRunning = false;
	});
	mConfirmBox->AddWidget(btn);

}

void		ProfileState::InitDeleteButton()
{
	mf::List		*confirm = mConfirmBox;
	mf::Button		*btn = mf::Button::Create(sf::Color::Red, sf::Color::Yellow);
	btn->SetSize(100, 40);
	btn->SetPosition(90, 94)->SetPositionPercentage(true);
	btn->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetText("Delete")->SetCharacterSize(15)
	->SetTextColor(sf::Color::Black)->SetTextPosition(sf::Vector2f(10, 5));
	btn->SetClickEvent([confirm]{
		confirm->SetDisabled(false);
	});
	mf::GUI::AddWidget(btn);
}
