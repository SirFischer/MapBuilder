#include "MenuState.hpp"
#include "Components.hpp"

void		MenuState::LoadProfiles()
{
	Data		*data = mData;
	StateAction	*stateReturnAction = &mStateReturnAction;
	bool		*isRunning = &mIsActive;
	for (const auto &entry : std::filesystem::directory_iterator(PROFILE_DIR_PATH))
	{
		Profile profile(entry.path());
		auto btn = Components::CreateButton(profile.GetName(), sf::Vector2f(90, 5), sf::Vector2f(0, 0), [data, profile, stateReturnAction, isRunning]{
			data->mProfile = profile;
			*stateReturnAction = StateAction::PROFILE;
			*isRunning = false;
		});
		btn->SetSizePercentage(true, true);
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

	auto settingsButton = Components::CreateButton("Settings", sf::Vector2f(90, 7), sf::Vector2f(0, 0), [this]{
		mIsActive = false;
		mStateReturnAction = StateAction::OPTIONS;
	});
	settingsButton->SetSizePercentage(true, true);
	settingsButton->GetText()->SetSize(20);
	bool		*active = &mIsActive;
	StateAction	*action = &mStateReturnAction;
	mMenuList->AddWidget(settingsButton);

	auto createButton = Components::CreateButton("Create new profile", sf::Vector2f(90, 7), sf::Vector2f(0, 0), [active, action, data]{
		
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
	
	createButton->SetSizePercentage(true, true);
	createButton->GetText()->SetSize(20);
	mMenuList->AddWidget(createButton);
}