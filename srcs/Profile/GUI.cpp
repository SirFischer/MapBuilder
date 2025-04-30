#include "ProfileState.hpp"

void		ProfileState::InitConfirmBox()
{
	mConfirmBox = mf::List::Create();
	mConfirmBox->SetDisabled(true);

	mConfirmBox->SetPositionPercentage(true, true);
	mConfirmBox->SetPosition(30, 30);
	mConfirmBox->SetSizePercentage(true, true);
	mConfirmBox->SetSize(30, 20);
	
	mf::GUI::AddWidget(mConfirmBox);

	auto text = mf::Text::Create();
	text->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	text->GetText()->SetString("Are you sure?");
	text->SetSize(200, 30);
	text->GetText()->SetSize(18);
	text->GetText()->SetColor(sf::Color::Black);
	mConfirmBox->AddWidget(text);

	auto tmp = mConfirmBox;
	auto btn = mf::Button::Create();
	btn->GetText()->SetString("No");
	btn->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	btn->GetText()->SetColor(sf::Color::Black);
	btn->SetSizePercentage(true, true);
	btn->SetSize(99, 30);
	btn->GetText()->SetSize(14);
	btn->SetClickEvent([tmp]{
		tmp->SetDisabled(true);
	});

	mConfirmBox->AddWidget(btn);
	btn = mf::Button::Create();
	btn->GetText()->SetString("Delete");
	btn->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	btn->GetText()->SetColor(sf::Color::Black);
	btn->SetSizePercentage(true, true);
	btn->SetSize(99, 30);
	btn->GetText()->SetSize(14);

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
	auto confirm = mConfirmBox;
	auto btn = mf::Button::Create();
	btn->SetSize(100, 40);
	btn->SetPosition(90, 94);
	btn->SetPositionPercentage(true, true);
	btn->GetText()->SetString("Delete");
	btn->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	btn->GetText()->SetSize(15);
	btn->GetText()->SetColor(sf::Color::Black);
	btn->GetText()->SetPos(sf::Vector2f(10, 5));
	btn->SetClickEvent([confirm]{
		confirm->SetDisabled(false);
	});
	mf::GUI::AddWidget(btn);
}
