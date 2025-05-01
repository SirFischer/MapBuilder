#include "ProfileState.hpp"
#include "Components.hpp"

void		ProfileState::InitConfirmBox()
{
	mConfirmBox = mf::List::Create();
	mConfirmBox->SetDisabled(true);

	mConfirmBox->SetPositionPercentage(true, true);
	mConfirmBox->SetPosition(30, 30);
	mConfirmBox->SetSizePercentage(true, true);
	mConfirmBox->SetSize(30, 20);
	mConfirmBox->GetBackground()->SetOutlineColor(sf::Color::Black);
	mConfirmBox->GetBackground()->SetOutlineThickness(1.f);
	mConfirmBox->GetBackground()->SetBackground(sf::Color(130, 130, 130));
	
	mf::GUI::AddWidget(mConfirmBox);

	auto text = mf::Text::Create();
	text->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	text->GetText()->SetString("Are you sure?");
	text->SetSize(200, 30);
	text->GetText()->SetSize(18);
	text->GetText()->SetColor(sf::Color::Black);
	mConfirmBox->AddWidget(text);

	auto tmp = mConfirmBox;
	auto btn = Components::CreateButton("Cancel", sf::Vector2f(100, 40), sf::Vector2f(0, 0), [tmp]{
		tmp->SetDisabled(true);
	});
	mConfirmBox->AddWidget(btn);

	StateAction				*stateReturnAction = &mStateReturnAction;
	bool					*isRunning = &mIsActive;
	Data					*data = mData;

	btn = Components::CreateButton("Delete", sf::Vector2f(100, 40), sf::Vector2f(0, 0), [tmp, stateReturnAction, isRunning, data]{
		tmp->SetDisabled(true);
		data->mProfile.Delete();
		*stateReturnAction = StateAction::POP;
		*isRunning = false;
	});
	mConfirmBox->AddWidget(btn);

}

void		ProfileState::InitDeleteButton()
{
	auto confirm = mConfirmBox;
	auto btn = Components::CreateButton("Delete", sf::Vector2f(100, 40), sf::Vector2f(90, 94), [confirm]{
		confirm->SetDisabled(false);
	});
	btn->SetPositionPercentage(true, true);
	mf::GUI::AddWidget(btn);
}
