#include "Game.h"
#include"Actors/Player.h"
#include"Actors/Enemy.h"
#include"Actors/Enemy2.h"
#include"Actors/Projectile.h"


void Game::Initialize()
{
	engine = std::make_unique<henry::Engine>(); // New Engine()
	engine->Startup();
	scene = std::make_unique<henry::Scene>();
	scene->engine = engine.get();

	engine->Get<henry::AudioSystem>()->AddAudio("explosion", "explosion.wav");
	engine->Get<henry::AudioSystem>()->AddAudio("player_fire", "PlayerShots.wav");
	engine->Get<henry::AudioSystem>()->AddAudio("player_explosion", "PlayerExlosion.wav");
	engine->Get<henry::AudioSystem>()->AddAudio("enemy_fire", "EnemyShot.wav");
	engine->Get<henry::AudioSystem>()->AddAudio("enemy_explosion", "EnemyExlosion.wav");
	engine->Get<henry::AudioSystem>()->AddAudio("BGM", "BackgroundMusic.mp3");

	engine->Get<henry::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<henry::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead, this, std::placeholders::_1));
}

void Game::Shutdown()
{
	scene->RemoveAllActor();
	engine->Shutdown();
}

void Game::Update(float dt)
{
	stateTimer += dt;

	//(this->*stateFunction)(dt);

	switch (state)
	{
	case Game::eState::TitleScreen:
		if (Core::Input::IsPressed(VK_SPACE))
		{
			state = eState::StartGame;
		}
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 5;
		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
		scene->engine->Get<henry::AudioSystem>()->PlayAudio("BGM");
		UpdateLevelStart(dt);
		state = eState::Game;

		break;
	case Game::eState::Game:

		if (scene->GetActors<Enemy>().size() == 0 && scene->GetActors<Enemy2>().size() == 0 || lives == 0)
		{
			state = eState::Gameover;

		}
		break;
	case Game::eState::Gameover:
		scene->RemoveAllActor();
		if (Core::Input::IsPressed(VK_LSHIFT))
		{
			state = eState::TitleScreen;
		}
		break;
	default:
		break;
	}

	engine->Update(dt);
	scene->Update(dt);
}

void Game::Draw(Core::Graphics& graphics)
{
	switch (state)
	{
	case Game::eState::TitleScreen:
		graphics.SetColor(henry::Color::cyan);
		graphics.DrawString(380, 320 + static_cast<int>(std::sin(stateTimer * 6.0f) * 10.0f), "HECTOR");

		graphics.SetColor(henry::Color::red);
		graphics.DrawString(340, 360, "Press Space to Start");
		break;
	case Game::eState::StartGame:
		
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:
		break;
	case Game::eState::Gameover:
		graphics.SetColor(henry::Color::red);
		graphics.DrawString(340, 360, "Game Over");
		graphics.SetColor(henry::Color::purple);
		graphics.DrawString(340, 400, "Hits Left Shift to Go to title screen");
		break;
	default:
		break;
	}
	graphics.SetColor(henry::Color::white);
	graphics.DrawString(30, 20, std::to_string(score).c_str());
	graphics.DrawString(750, 20, std::to_string(lives).c_str());
	scene->Draw(graphics);
	engine->Draw(graphics);
}
void Game::UpdateTitle(float dt)
{
	if (Core::Input::IsPressed(VK_SPACE))
	{
		stateFunction = &Game::UpdateLevelStart;

		//state = eState::StartGame;
	}
}

void Game::UpdateLevelStart(float dt)
{
	scene->AddActor(std::make_unique< Player>(henry::Transform{ henry::Vector2{400, 600}, 0, 3 }, engine->Get<henry::ResourceSystem>()->Get<henry::Shape>("Player.txt"), 500.0f));
	for (size_t i = 0; i < henry::RandomRange(2.0f , 7.0f); i++)
	{
		scene->AddActor(std::make_unique <Enemy>(henry::Transform{ henry::Vector2{ henry::RandomRange(0.0f,800), henry::RandomRange(0.0f,600)}, henry::RandomRange(0, henry::TwoPi), 2 }, engine->Get<henry::ResourceSystem>()->Get<henry::Shape>("Enemy.txt"), 100.0f));
	}
	for (size_t i = 0; i < henry::RandomRange(2.0f, 6.0f); i++)
	{
		scene->AddActor(std::make_unique <Enemy2>(henry::Transform{ henry::Vector2{ henry::RandomRange(0.0f,800), henry::RandomRange(0.0f,600)}, henry::RandomRange(0, henry::TwoPi), 2 }, engine->Get<henry::ResourceSystem>()->Get<henry::Shape>("Astriod.txt"), 100.0f));

	}
	state = eState::Game;
	
}

void Game::OnAddPoints(const henry::Event& event)
{
	score += std::get<int>(event.data);
}

void Game::OnPlayerDead(const henry::Event& event)
{
	lives--;
	std::cout << std::get<std::string>(event.data) << std::endl;
	if (lives == 0)
	{
		state = eState::Gameover;
	}
	else
	{
		scene->AddActor(std::make_unique< Player>(henry::Transform{ henry::Vector2{400, 600}, 0, 3 }, engine->Get<henry::ResourceSystem>()->Get<henry::Shape>("Player.txt"), 500.0f));

	}
}
