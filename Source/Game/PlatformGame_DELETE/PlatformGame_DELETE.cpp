
#include "PlatformGame.h"

#include "Audio/AudioSystem.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"


	bool PlatformGame::Initialize()
	{

		// load audio
		kiko::g_audioSystem.AddAudio("hit", "hit.wav");
		kiko::g_audioSystem.AddAudio("laser", "Laser.wav");

		// load audio ideas
		// - game music
		// - if created so that the enemies require two hits - sound for hit different one for explosion
		// - explosion for enemies
		// - brrrr sound for moving forward (subtle)
		// - jingle to play when the game ends

	
		// create scene
		m_scene = std::make_unique<kiko::Scene>();
		// load scene giving it the name
		m_scene->Load("scenes/spacescene.json");
		// initialize the scene
		m_scene->Initialize();
	

		// add events
		EVENT_SUBSCRIBE("OnAddPoints", PlatformGame::OnAddPoints);
		EVENT_SUBSCRIBE("OnPlayerDead", PlatformGame::OnPlayerDead);

		//kiko::EventManager::Instance().Subscribe("OnAddPoints", this, std::bind(&PlatformGame::OnAddPoints, this, std::placeholders::_1));
		//kiko::EventManager::Instance().Subscribe("OnPlayerDead", this, std::bind(&PlatformGame::OnPlayerDead, this, std::placeholders::_1));


		return true;
	}


	void PlatformGame::Shutdown()
	{

	}


	void PlatformGame::Update(float dt)
	{

		switch (m_state)
		{
		case PlatformGame::eState::Title:
			if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
			{
				m_state = eState::StartGame;
				// activates and deactivates the background
				//m_scene->GetActorByName("Background")->active = false;
				m_scene->GetActorByName("Title")->active = true;

			}
			break;


		case PlatformGame::eState::StartGame:
			m_score = 0;
			m_lives = 3;
			m_state = eState::StartLevel;
			break;


		case PlatformGame::eState::StartLevel:
			m_scene->RemoveAll();
		{
			m_scene->GetActorByName("Title")->active = false;
			
			// create player

			auto player = INSTANTIATE(Player, "Player");
			player->transform = kiko::Transform{ { 400, 300 }, 0, 1 };
			player->Initialize();
			m_scene->Add(std::move(player));

			auto renderComponent = CREATE_CLASS(SpriteComponent);
			renderComponent->m_texture = GET_RESOURCE(kiko::Texture, "pShip.png", kiko::g_renderer);
		
		
			player->AddComponent(std::move(renderComponent));


			auto physicsComponent = CREATE_CLASS(EnginePhysicsComponent);
			physicsComponent->m_damping = 0.9f;
			player->AddComponent(std::move(physicsComponent));

			auto collisionComponent = CREATE_CLASS(CircleCollisionComponent);
			collisionComponent->m_radius = 30.0f;
			player->AddComponent(std::move(collisionComponent));

			player->Initialize();
			m_scene->Add(std::move(player));
		}
		m_state = eState::Game;
		break;


		case PlatformGame::eState::Game:
		

			m_gameTimer += dt;
			m_spawnTimer += dt;
			if (m_spawnTimer >= m_spawnTime)
			{
				m_spawnTimer = 0;

				auto enemy = INSTANTIATE(Enemy, "Enemy");
				enemy->transform = kiko::Transform{ { 400, 300 }, 0, 1 };
				enemy->Initialize();
				m_scene->Add(std::move(enemy));

				std::unique_ptr<kiko::SpriteComponent> component = std::make_unique<kiko::SpriteComponent>();

				//put in enemy png
				component->m_texture = GET_RESOURCE(kiko::Texture, "eShip.png", kiko::g_renderer); //kiko::g_resources.Get<kiko::Texture>("eShip.png", kiko::g_renderer);
				enemy->AddComponent(std::move(component));

				auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
				collisionComponent->m_radius = 30.0f;
				enemy->AddComponent(std::move(collisionComponent));

				enemy->Initialize();
				m_scene->Add(std::move(enemy));


			}
			break;


		case eState::PlayerDeadStart:
			m_stateTimer = 3;
			if (m_lives == 0) m_state = eState::GameOver;
			else m_state = eState::PlayerDead;
			break;


		case PlatformGame::eState::PlayerDead:
			m_stateTimer -= dt;
			if (m_stateTimer <= 0)
			{
				m_state = eState::StartLevel;
			}
			break;
	
	
		case PlatformGame::eState::GameOver:
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

		m_scoreText->Create(kiko::g_renderer, std::to_string(m_score), {1, 1, 1, 1});
		m_timerText->Create(kiko::g_renderer, std::to_string((int)m_gameTimer), {1, 1, 1, 1});
		m_scene->Update(dt);
	}


	void PlatformGame::Draw(kiko::Renderer & renderer)
	{
		m_scene->Draw(renderer);


		if (m_state == eState::Title)
		{
			m_titleText->Draw(renderer, 400, 300);
			//m_scene->GetActorByName("Title")->active = true;
		}
		if (m_state == eState::GameOver)
		{
			m_gameoverText->Draw(renderer, 400, 300);
		}

		m_timerText->Draw(renderer, 400, 40);
		m_scoreText->Draw(renderer, 40, 20);
	}


	void PlatformGame::OnAddPoints(const kiko::Event& event)
	{
		m_score += std::get<int>(event.data);

	}

	void PlatformGame::OnPlayerDead(const kiko::Event& event)
	{
		m_lives--;
		m_state = eState::PlayerDeadStart;
	}


