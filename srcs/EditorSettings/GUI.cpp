#include "EditorSettingsState.hpp"

void		EditorSettingsState::InitGUI()
{
	mf::GUI::ClearWidgets();
	InitSettingsList();
	InitBackButton();
}

void		EditorSettingsState::InitSettingsList()
{
	mSettingsList = mf::List::Create();
	mSettingsList->SetSize(80, 80);
	mSettingsList->SetSizePercentage(true, true);
	mSettingsList->SetPosition(1, 1);
	mSettingsList->SetPositionPercentage(true, true);
	mSettingsList->SetContentOffset(sf::Vector2f(5, 5));
	mSettingsList->GetBackground()->SetBackground(sf::Color::Transparent);
	mf::GUI::AddWidget(mSettingsList);

	InitSettingsListContent();
}

void		EditorSettingsState::InitSettingsListContent()
{
	InitFormatButton();
}

void		EditorSettingsState::InitFormatButton()
{
	auto text = mf::Text::Create();
	text->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	text->GetText()->SetString("Toggle format:");
	text->GetText()->SetSize(18);
	text->GetBackground()->SetBackground(sf::Color::Transparent);
	text->SetSize(150, 20);
	mSettingsList->AddWidget(text);
	
	auto btn = mf::Button::Create();
	btn->SetSize(100, 40);
	btn->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	btn->GetText()->SetString((mData->mMap.GetFormat() == ExportFormat::BASIC) ? "BASIC" : "ADVANCED");
	btn->GetText()->SetSize(15);
	btn->GetText()->SetColor(sf::Color::Black);
	btn->GetText()->SetPos(sf::Vector2f(10, 5));
	Data	*data = mData;
	btn->SetClickEvent([data, btn]{
		data->mMap.SetFormat((data->mMap.GetFormat() == ExportFormat::BASIC) ? ExportFormat::ADVANCED : ExportFormat::BASIC);
		btn->GetText()->SetString((data->mMap.GetFormat() == ExportFormat::BASIC) ? "BASIC" : "ADVANCED");
	});
	mSettingsList->AddWidget(btn);
}

void		EditorSettingsState::InitBackButton()
{
	StateAction					*stateReturnAction = &mStateReturnAction;
	bool						*isRunning = &mIsActive;

	auto btn = mf::Button::Create();
	btn->SetSize(100, 40);
	btn->SetPosition(1, 94);
	btn->SetPositionPercentage(true, true);
	btn->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	btn->GetText()->SetString("Back");
	btn->GetText()->SetSize(15);
	btn->GetText()->SetColor(sf::Color::Black);
	btn->GetText()->SetPos(sf::Vector2f(10, 5));
	btn->SetClickEvent([stateReturnAction, isRunning]{
		*stateReturnAction = StateAction::POP;
		*isRunning = false;
	});
	mf::GUI::AddWidget(btn);
}