#include "MenuState.hpp"

void		MenuState::LoadProfiles()
{
	Data		*data = mData;
	StateAction	*stateReturnAction = &mStateReturnAction;
	bool		*isRunning = &mIsActive;
	for (const auto &entry : std::filesystem::directory_iterator(PROFILE_DIR_PATH))
	{
		Profile profile(entry.path());
		mf::Button		*btn = mf::Button::Create(sf::Color::White, sf::Color::Yellow);
		btn->SetSize(90, 5)->SetSizePercentage(true);
		btn->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetText(profile.GetName())
		->SetCharacterSize(15)->SetTextColor(sf::Color::Black)->SetTextPosition(sf::Vector2f(10, 5));
		btn->SetClickEvent([data, profile, stateReturnAction, isRunning]{
			data->mProfile = profile;
			*stateReturnAction = StateAction::PROFILE;
			*isRunning = false;
		});
		mProfileList->AddWidget(btn);
	}
}

void		MenuState::LoadMenu()
{
	Data		*data = mData;
	mf::Text	*text = mf::Text::Create("assets/fonts/Roboto-Regular.ttf", "Welcome to the map builder, create or select a profile to start editing some maps...");
	text->SetBackgroundColor(sf::Color::Transparent);
	text->SetSize(90, 10)->SetSizePercentage(true);
	text->SetCharacterSize(18);
	mMenuList->AddWidget(text);

	mf::Button	*settingsButton = mf::Button::Create(sf::Color::White, sf::Color::Yellow);
	settingsButton->SetSize(90, 7)->SetSizePercentage(true);
	settingsButton->SetText("Settings")->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetTextColor(sf::Color::Black);
	settingsButton->SetCharacterSize(20);
	bool		*active = &mIsActive;
	StateAction	*action = &mStateReturnAction;
	settingsButton->SetClickEvent([action, active]{
		*active = false;
		*action = StateAction::OPTIONS;
	});
	mMenuList->AddWidget(settingsButton);

	mf::Button	*createButton = mf::Button::Create(sf::Color::White, sf::Color::Yellow);
	createButton->SetSize(90, 7)->SetSizePercentage(true);
	createButton->SetText("Create new profile")->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetTextColor(sf::Color::Black);
	createButton->SetCharacterSize(20);
	createButton->SetClickEvent([active, action, data]{
		
		time_t	t = time(0);
		int random = rand() % 100;
		std::string path = std::string(PROFILE_PATH) + std::to_string(t) + std::to_string(random) + ".profile";
		std::filesystem::create_directory(PROFILE_RESOURCE_PATH + std::to_string(t) + std::to_string(random));
		Profile	profile(path);
		profile.SetAssetsPath(PROFILE_RESOURCE_PATH + std::to_string(t) + std::to_string(random));
		profile.SaveToFile();
		data->mProfile = profile;
		*active = false;
		*action = StateAction::PROFILE;
	});
	mMenuList->AddWidget(createButton);
}