#include "Player.h"
#include "Enemy.h"
#include "Framework/Scene.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"
#include "SpaceGame.h"
#include <cmath>
#include "Framework/Resource/ResourceManager.h"
#include "Framework/Resource.h"
#include "Framework/SpriteComponent.h"
#include "Framework/Components/EnginePhysicsComponent.h"

bool SpaceGame::Initialize()
{
	

	// CREATE FONT AND TEXT OBJECTS // shared pointer used so multiple assets can use it. 
	
	m_font = kiko::g_resources.Get<kiko::Font>("arcade.ttf", 100);
	//std::make_shared<kiko::Font>("arcade.ttf", 100);
	m_scoreFont = std::make_shared<kiko::Font>("arcade.ttf", 50);
	m_timerFont = std::make_shared<kiko::Font>("arcade.ttf", 50);
	//m_messageFont = std::make_shared<kiko::Font>("arcade.ttf", 35);
	

	m_scoreText = std::make_unique<kiko::Text>(m_scoreFont);
	m_scoreText->Create(kiko::g_renderer, "Score: 0000", kiko::Color{ 255, 0 , 0, 1 });

	m_titleText = std::make_unique<kiko::Text>(m_font);
	m_titleText->Create(kiko::g_renderer, "Crack Attack!", kiko::Color{ 255, 255, 0, 0 });

	/*m_messageText = std::make_unique<kiko::Text>(m_messageFont);
	m_messageText->Create(kiko::g_renderer, "and all of my players/fx are broken!", kiko::Color{ 255, 255, 0, 1 });*/

	m_gameoverText = std::make_unique<kiko::Text>(m_font);
	m_gameoverText->Create(kiko::g_renderer, "FAIL", kiko::Color{ 255, 255, 0, 1 });

	m_timerText = std::make_unique<kiko::Text>(m_timerFont);
	m_timerText->Create(kiko::g_renderer, "00", kiko::Color{ 1, 1, 1, 1 });

	// load audio //
	kiko::g_audioSystem.AddAudio("laser", "Laser_Shoot.wav");

	// create scene //
	m_scene = std::make_unique<kiko::Scene>();

	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{

	switch (m_state)
	{
	case SpaceGame::eState::Title:
	{
		//// Animate the title alpha from 0 to 255
		const float animationDuration = 0.1f; // Adjust the duration of the animation as needed
		m_titleAlpha += 255.0f * (dt / animationDuration);
		m_titleAlpha = std::min(m_titleAlpha, 10.0f);

		 // Animate the title alpha using the easing function
		//const float animationDuration = 0.1f; // Adjust the duration of the animation as needed
		//float t = std::min(m_titleAlpha / 255.0f, 1.0f); // Clamp t between 0 and 1
		//float easedT = t < 0.5f ? 2.0f * t * t : 1.0f - std::pow(-2.0f * t + 2.0f, 2.0f) * 0.5f;
		//m_titleAlpha = easedT * 255.0f;


		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
		}
		//std::cout << "Title Alpha: " << m_titleAlpha << std::endl;
		
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
			// CREATE PLAYER //
			std::unique_ptr<Player> player = std::make_unique<Player>(200.0f, kiko::Pi, kiko::Transform{ { 365, 300 }, 0, 6 });
			player->m_tag = "Player";
			player->m_game = this;
			player->SetDamping(0.5f);

			// CREATE COMPONENTS
			std::unique_ptr<kiko::SpriteComponent> component = std::make_unique<kiko::SpriteComponent>();
			component->m_texture = kiko::g_resources.Get<kiko::Texture>("AngryNerds.jpg", kiko::g_renderer);
			player->AddComponent(std::move(component));

			auto physicsComponent = std::make_unique<kiko::EnginePhysicsComponent>();
			player->AddComponent(std::move(physicsComponent));


			m_scene->Add(std::move(player));

		}
		m_state = eState::Game;
		break;
	case SpaceGame::eState::Game:
		m_gameTimer += dt;
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{	// ENEMY //
			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(75.0f, 150.0f), kiko::Pi, kiko::Transform{ { kiko::random(800), kiko::random(600) }, kiko::randomf(kiko::TwoPi), 3}, kiko::g_manager.Get("enemy_ship.txt"));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
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
	if (m_state == eState::Title)
	{
		//m_titleText->Draw(renderer, 100, 200);
	}
	if (m_state == eState::GameOver)
	{
		m_gameoverText->Draw(renderer, 300, 200);
	}

	m_timerText->Draw(renderer, 725, 550);
	m_scoreText->Draw(renderer, 35, 550);
	//m_messageText->Draw(renderer, 115, 285);
	m_scene->Draw(renderer);
}