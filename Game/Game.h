#pragma once
#include"Engine.h"

class Game
{
public:
	enum class eState
	{
		TitleScreen,
		StartGame,
		StartLevel,
		Game,
		Gameover,
	};

public :
	void Initialize();
	void Shutdown();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

private:
	void UpdateTitle(float dt);
	void UpdateLevelStart(float dt);
	void OnAddPoints(const henry::Event& event);
	void OnPlayerDead(const henry::Event& event);
	
public:
	std::unique_ptr<henry::Engine> engine;
	std::unique_ptr<henry::Scene> scene;


private:
	eState state = eState::TitleScreen; 
	float stateTimer = 0.0f;

	void (Game::* stateFunction)(float) = nullptr;

	size_t score = 0;	
	size_t lives = 0;
	size_t rounds = 0;
};
