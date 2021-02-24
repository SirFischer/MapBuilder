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
	mSettingsList->SetSizePercentage(true)->SetSize(80, 80);
	mSettingsList->SetPositionPercentage(true)->SetPosition(1, 1);
	mSettingsList->SetContentPosition(sf::Vector2f(5, 5));
	mSettingsList->SetBackgroundColor(sf::Color::Transparent);
	mf::GUI::AddWidget(mSettingsList);

	InitSettingsListContent();

}

void		EditorSettingsState::InitSettingsListContent()
{
	InitFormatButton();
}

void		EditorSettingsState::InitFormatButton()
{
	mf::Text	*text = mf::Text::Create("assets/fonts/Roboto-Regular.ttf", "Toggle format:");
	text->SetBackgroundColor(sf::Color::Transparent);
	text->SetSize(90, 10)->SetSizePercentage(true);
	text->SetCharacterSize(18);
	mSettingsList->AddWidget(text);
	mf::Button		*btn = mf::Button::Create(sf::Color::White, sf::Color::Yellow);
	btn->SetSize(100, 40);
	btn->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetText((mData->mMap.GetFormat() == ExportFormat::BASIC) ? "BASIC" : "ADVANCED")->SetCharacterSize(15)
	->SetTextColor(sf::Color::Black)->SetTextPosition(sf::Vector2f(10, 5));
	Data	*data = mData;
	btn->SetClickEvent([data, btn]{
		data->mMap.SetFormat((data->mMap.GetFormat() == ExportFormat::BASIC) ? ExportFormat::ADVANCED : ExportFormat::BASIC);
		btn->SetText((data->mMap.GetFormat() == ExportFormat::BASIC) ? "BASIC" : "ADVANCED");
	});
	mSettingsList->AddWidget(btn);
}

void		EditorSettingsState::InitBackButton()
{
	StateAction					*stateReturnAction = &mStateReturnAction;
	bool						*isRunning = &mIsActive;

	mf::Button		*btn = mf::Button::Create(sf::Color::White, sf::Color::Yellow);
	btn->SetSize(100, 40);
	btn->SetPosition(1, 94)->SetPositionPercentage(true);
	btn->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetText("Back")->SetCharacterSize(15)
	->SetTextColor(sf::Color::Black)->SetTextPosition(sf::Vector2f(10, 5));
	btn->SetClickEvent([stateReturnAction, isRunning]{
		*stateReturnAction = StateAction::POP;
		*isRunning = false;
	});
	mf::GUI::AddWidget(btn);
}