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

	// CREATE FONT AND TEXT OBJECTS // shared pointer used so multiple assets can use it. 
	
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



	//m_font = GET_RESOURCE(kiko::Font, "Fonts/StarJediLogoMonoline-6nGg.ttf", 30);
	//	m_scoreFont = GET_RESOURCE (kiko::Font, "arcade.ttf", 50);
	//	m_timerFont = GET_RESOURCE (kiko::Font, "arcade.ttf", 50);

		//m_scoreText = std::make_unique<kiko::Text>(m_scoreFont);
		//m_scoreText->Create(kiko::g_renderer, "Score: 0000", kiko::Color{ 255, 0 , 0, 1 });

		/*m_titleText = std::make_unique<kiko::Text>(m_font);
		m_titleText->Create(kiko::g_renderer, "Crack Attack!", kiko::Color{ 255, 255, 0, 0 });

		m_gameoverText = std::make_unique<kiko::Text>(m_font);
		m_gameoverText->Create(kiko::g_renderer, "FAIL", kiko::Color{ 255, 255, 0, 1 });

		m_timerText = std::make_unique<kiko::Text>(m_timerFont);
		m_timerText->Create(kiko::g_renderer, "00", kiko::Color{ 1, 1, 1, 1 });*/

		// load audio //
	kiko::g_audioSystem.AddAudio("laser", "Laser_Shoot.wav");

	// create scene //
	m_scene = std::make_unique<kiko::Scene>();
	m_scene->Load("Scenes/spaceScene.json");
	m_scene->Initialize();
	//m_scene->SetGame(this);

	// add events

	kiko::EventManager::Instance().Subscribe("OnAddPoints", this, std::bind(&SpaceGame::OnAddPoints, this, std::placeholders::_1));
	kiko::EventManager::Instance().Subscribe("OnPlayerDead", this, std::bind(&SpaceGame::OnPlayerDead, this, std::placeholders::_1));

	EVENT_SUBSCRIBE("OnAddPoints", SpaceGame::OnAddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", SpaceGame::OnPlayerDead);

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
			enemy->transform = kiko::Transform{ { kiko::random(800), kiko::random(600) }, 0, 0.075f};
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

	//m_scoreText->Create(kiko::g_renderer, std::to_string(m_score), { 255, 0, 0, 1 });
	//m_timerText->Create(kiko::g_renderer, std::to_string((int)m_gameTimer), { 1, 1, 1, 1 });
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
		//m_gameoverText->Draw(renderer, 300, 200);
		m_scene->GetActorByName("Title")->active = true;
	}

	//m_timerText->Draw(renderer, 725, 550);
	//m_scoreText->Draw(renderer, 35, 550);
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

// CREATE COMPONENTS //

			// sprite component //
			/*auto renderComponent = CREATE_CLASS(SpriteRenderComponent)
			renderComponent->m_texture = GET_RESOURCE (kiko::Texture, "Jet_01.png", kiko::g_renderer);
			player->AddComponent(std::move(renderComponent));*/

			//// physics component //
			//auto physicsComponent = CREATE_CLASS(EnginePhysicsComponent)
			//physicsComponent->m_damping = 0.9f;
			//player->AddComponent(std::move(physicsComponent));

			//// collision component //
			//auto collisionComponent = CREATE_CLASS(CircleCollisionComponent)
			//collisionComponent->m_radius = 30.0f;
			//player->AddComponent(std::move(collisionComponent));

			// initialize player //
			//player->Initialize(); // doing Initialize() operation before move because the unique pointer is no longer valid once moved
			//m_scene->Add(std::move(player));

/*std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(75.0f, 150.0f), kiko::Pi, kiko::Transform{ { kiko::random(800), kiko::random(600) }, kiko::randomf(kiko::TwoPi), 0.05f});
			enemy->tag = "Enemy";
			enemy->m_game = this;

			auto renderComponent = std::make_unique<kiko::SpriteRenderComponent>();
			renderComponent->m_texture = GET_RESOURCE (kiko::Texture, "enemy_01.png", kiko::g_renderer);
			enemy->AddComponent(std::move(renderComponent));

			auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
			collisionComponent->m_radius = 30.0f;
			enemy->AddComponent(std::move(collisionComponent));

			enemy->Initialize();
			m_scene->Add(std::move(enemy));*/
