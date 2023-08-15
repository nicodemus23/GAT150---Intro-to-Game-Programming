#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"

#include "Renderer/Renderer.h"
#include "Renderer/Text.h"

#include "Framework/Scene.h"
#include "Framework/Resource/ResourceManager.h"
#include "Framework/Resource/Resource.h"
#include "Framework/Framework.h"
#include "Framework/Factory.h"

#include <cmath>

bool SpaceGame::Initialize()
{

	// CREATE FONT AND TEXT OBJECTS // shared pointer used so multiple assets can use it. 
	m_font = GET_RESOURCE(kiko::Font, "arcade.ttf", 100);
	//m_font = kiko::ResourceManager::Instance().Get<kiko::Font>("arcade.ttf", 100); // do I still need this? 
	//std::make_shared<kiko::Font>("arcade.ttf", 100);
	m_scoreFont = GET_RESOURCE (kiko::Font, "arcade.ttf", 50);
	m_timerFont = GET_RESOURCE (kiko::Font, "arcade.ttf", 50);
	

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
		//// Animate the TITLE alpha from 0 to 255
		const float animationDuration = 0.1f; // Adjust the duration of the animation as needed
		m_titleAlpha += 255.0f * (dt / animationDuration);
		m_titleAlpha = std::min(m_titleAlpha, 10.0f);

		 // Animate the TITLE alpha using the easing function
		//const float animationDuration = 0.1f; // Adjust the duration of the animation as needed
		//float t = std::min(m_titleAlpha / 255.0f, 1.0f); // Clamp t between 0 and 1
		//float easedT = t < 0.5f ? 2.0f * t * t : 1.0f - std::pow(-2.0f * t + 2.0f, 2.0f) * 0.5f;
		//m_titleAlpha = easedT * 255.0f;

		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
		}

		// check:
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

			// CREATE COMPONENTS //

			// sprite component //
			
			// for Factory.h //
			auto renderComponent = CREATE_CLASS(SpriteRenderComponent)
			renderComponent->m_texture = GET_RESOURCE (kiko::Texture, "test.png", kiko::g_renderer);
			player->AddComponent(std::move(renderComponent));

			// physics component //
			auto physicsComponent = CREATE_CLASS(EnginePhysicsComponent)
			physicsComponent->m_damping = 0.9f;
			player->AddComponent(std::move(physicsComponent));

			// collision component //
			auto collisionComponent = CREATE_CLASS(CircleCollisionComponent)
			collisionComponent->m_radius = 30.0f;
			player->AddComponent(std::move(collisionComponent));

			// initialize player //
			player->Initialize(); // doing Initialize() operation before move because the unique pointer is no longer valid once moved
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
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(75.0f, 150.0f), kiko::Pi, kiko::Transform{ { kiko::random(800), kiko::random(600) }, kiko::randomf(kiko::TwoPi), 1});
			enemy->m_tag = "Enemy";
			enemy->m_game = this;

			auto renderComponent = std::make_unique<kiko::SpriteRenderComponent>();
			renderComponent->m_texture = GET_RESOURCE (kiko::Texture, "test.png", kiko::g_renderer);
			enemy->AddComponent(std::move(renderComponent));

			auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
			collisionComponent->m_radius = 30.0f;
			enemy->AddComponent(std::move(collisionComponent));

			enemy->Initialize();
			m_scene->Add(std::move(enemy));


			// add weapons here
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
	m_scene->Draw(renderer);
}