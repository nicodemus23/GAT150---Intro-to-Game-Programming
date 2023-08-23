#pragma once
#include "Framework/Game.h"
#include "Framework/Event/EventManager.h"
#include "Renderer/Text.h"


class SpaceGame : public kiko::Game, kiko::IEventListener // an object that can listen for events 
{
public:

	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDeadStart,
		PlayerDead,
		GameOverStart,
		GameOver
	};

public:
	virtual bool Initialize() override;
	virtual void Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Draw(kiko::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }
	void OnAddPoints(const kiko::Event& event);
	void OnPlayerDead(const kiko::Event& event);

private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnTime = 3;

	float m_stateTimer = 0;
	float m_gameTimer = 0;

	float m_titleAlpha =0;
	std::shared_ptr<kiko::Font> m_font;
	std::shared_ptr<kiko::Font> m_scoreFont;
	std::shared_ptr<kiko::Font> m_timerFont;
	std::shared_ptr<kiko::Font> m_messageFont;

	std::unique_ptr<kiko::Text> m_titleText;
	std::unique_ptr<kiko::Text> m_timerText;
	std::unique_ptr<kiko::Text> m_scoreText;
	std::unique_ptr<kiko::Text> m_gameoverText;
	std::unique_ptr<kiko::Text> m_messageText;
};