#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"

#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

#include <cmath>

bool SpaceGame::Initialize()
{
	// CREATE FONT AND TEXT OBJECTS // 
	m_font = GET_RESOURCE(kiko::Font, "arcadeclassic.ttf", 24);
	m_scoreText = std::make_unique<kiko::Text>(m_font);
	m_scoreText->Create(kiko::g_renderer, "SCORE 0000", kiko::Color{ 1, 0, 1, 1 });

	m_titleText = std::make_unique<kiko::Text>(m_font);
	m_titleText->Create(kiko::g_renderer, "AZTEROIDS", kiko::Color{ 1, 1, 1, 1 });

	m_gameoverText = std::make_unique<kiko::Text>(m_font);
	m_gameoverText->Create(kiko::g_renderer, "GAME OVER", kiko::Color{ 1, 1, 1, 1 });

	m_timerText = std::make_unique<kiko::Text>(m_font);
	m_timerText->Create(kiko::g_renderer, "TIMER", kiko::Color{ 1, 1, 1, 1 });

	// load audio
	kiko::g_audioSystem.AddAudio("hit", "hit.wav");
	kiko::g_audioSystem.AddAudio("laser", "Laser.wav");

	m_font = GET_RESOURCE(kiko::Font, "Fonts/StarJediLogoMonoline-6nGg.ttf", 30);
	m_scoreFont = GET_RESOURCE(kiko::Font, "arcade.ttf", 50);
	m_timerFont = GET_RESOURCE(kiko::Font, "arcade.ttf", 50);

	m_scoreText = std::make_unique<kiko::Text>(m_scoreFont);
	m_scoreText->Create(kiko::g_renderer, "Score: 0000", kiko::Color{ 255, 0 , 0, 1 });

	m_titleText = std::make_unique<kiko::Text>(m_font);
	m_titleText->Create(kiko::g_renderer, "Crack Attack!", kiko::Color{ 255, 255, 0, 0 });

	m_gameoverText = std::make_unique<kiko::Text>(m_font);
	m_gameoverText->Create(kiko::g_renderer, "FAIL", kiko::Color{ 255, 255, 0, 1 });

	m_timerText = std::make_unique<kiko::Text>(m_timerFont);
	m_timerText->Create(kiko::g_renderer, "00", kiko::Color{ 1, 1, 1, 1 });

	// load audio //
	kiko::g_audioSystem.AddAudio("laser", "Laser_Shoot.wav");

	// create scene //
	m_scene = std::make_unique<kiko::Scene>();
	// load scene
	m_scene->Load("Scenes/spaceScene.json");
	// initialize scene
	m_scene->Initialize();

	// add events
	EVENT_SUBSCRIBE("OnAddPoints", SpaceGame::OnAddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", SpaceGame::OnPlayerDead);

	return true;
}

void SpaceGame::Shutdown()
{
	//
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case SpaceGame::eState::Title:
	{
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
			// activates and deactivates the background
			//m_scene->GetActorByName("Background")->active = false;
			m_scene->GetActorByName("Title")->active = true;

		}
		break;
	}
	case SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;

	case SpaceGame::eState::StartLevel:
		m_scene->RemoveAll();
		{
			m_scene->GetActorByName("Title")->active = false;

			// CREATE PLAYER //

			auto player = INSTANTIATE(Player, "Player");
			player->transform = kiko::Transform{ { 365, 300 }, 0, 0.075f };
			player->Initialize();
			m_scene->Add(std::move(player));
		}

		m_state = eState::Game;
		break;

	case SpaceGame::eState::Game:
		m_gameTimer += dt;
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			//  CREATE ENEMY //
			m_spawnTimer = 0;
			auto enemy = INSTANTIATE(Enemy, "Enemy");
			enemy->transform = kiko::Transform{ { kiko::random(800), kiko::random(600) }, 0, 0.075f };
			enemy->Initialize();
			m_scene->Add(std::move(enemy));

		}
		break;

	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;
		break;

	case SpaceGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::StartLevel;
		}
		break;
	case SpaceGame::eState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAll();
			m_state = eState::Title;
		}
		break;

	default:
		break;
	}

	m_scoreText->Create(kiko::g_renderer, std::to_string(m_score), { 255, 0, 0, 1 });
	m_timerText->Create(kiko::g_renderer, std::to_string((int)m_gameTimer), { 1, 1, 1, 1 });
	m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer& renderer)
{
	m_scene->Draw(renderer);
	if (m_state == eState::Title)
	{
		m_titleText->Draw(renderer, 400, 300);
		m_scene->GetActorByName("Title")->active = true;
	}
	if (m_state == eState::GameOver)
	{
		m_gameoverText->Draw(renderer, 300, 200);
		m_scene->GetActorByName("Title")->active = true;
	}

	m_timerText->Draw(renderer, 725, 550);
	m_scoreText->Draw(renderer, 35, 550);
}
void SpaceGame::OnAddPoints(const kiko::Event& event)
{
	m_score += std::get<int>(event.data);
}

void SpaceGame::OnPlayerDead(const kiko::Event& event)
{
	m_lives--;
	m_state = eState::PlayerDeadStart;
}

