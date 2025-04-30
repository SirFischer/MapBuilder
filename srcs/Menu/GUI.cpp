#include "MenuState.hpp"

void		MenuState::LoadProfiles()
{
	Data		*data = mData;
	StateAction	*stateReturnAction = &mStateReturnAction;
	bool		*isRunning = &mIsActive;
	for (const auto &entry : std::filesystem::directory_iterator(PROFILE_DIR_PATH))
	{
		Profile profile(entry.path());
		auto btn = mf::Button::Create();
		btn->SetSize(90, 5);
		btn->SetSizePercentage(true, true);
		btn->GetText()->SetString(profile.GetName());
		btn->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
		btn->GetText()->SetSize(15);
		btn->GetText()->SetColor(sf::Color::Black);
		btn->GetText()->SetPos(sf::Vector2f(10, 5));
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
	
	auto text = mf::Text::Create();
	text->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	text->GetText()->SetString("Welcome to the map builder, create or select a profile to start editing some maps...");
	text->GetBackground()->SetBackground(sf::Color::Transparent);
	text->SetSize(90, 10);
	text->SetSizePercentage(true, true);
	text->GetText()->SetSize(18);
	mMenuList->AddWidget(text);

	auto settingsButton = mf::Button::Create();
	settingsButton->SetSize(90, 7);
	settingsButton->SetSizePercentage(true, true);
	settingsButton->GetText()->SetString("Settings");
	settingsButton->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	settingsButton->GetText()->SetColor(sf::Color::Black);
	settingsButton->GetText()->SetSize(20);
	bool		*active = &mIsActive;
	StateAction	*action = &mStateReturnAction;
	settingsButton->SetClickEvent([action, active]{
		*active = false;
		*action = StateAction::OPTIONS;
	});
	mMenuList->AddWidget(settingsButton);

	auto createButton = mf::Button::Create();
	createButton->SetSize(90, 7);
	createButton->SetSizePercentage(true, true);
	createButton->GetText()->SetString("Create new profile");
	createButton->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	createButton->GetText()->SetColor(sf::Color::Black);
	createButton->GetText()->SetSize(20);
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