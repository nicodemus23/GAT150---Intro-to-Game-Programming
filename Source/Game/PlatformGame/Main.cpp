#include "PlatformGame.h"

#include "Core/Core.h"
#include "Framework/Framework.h"

#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Physics/PhysicsSystem.h"

#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <list>
#include <map>
#include <functional>

using namespace std;


int main(int argc, char* argv[])
{

	INFO_LOG("Initialize Engine, yo...")

		kiko::MemoryTracker::Initialize();
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");


	// Initialize Game Engine // 
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("GAT150", 800, 600);

	// Set blend render blend mode for alpha
	SDL_SetRenderDrawBlendMode(kiko::g_renderer.GetSDLRenderer(), SDL_BLENDMODE_BLEND);

	// Initialize inputSystem
	kiko::g_inputSystem.Initialize();

	// initialize AudioSystem
	kiko::g_audioSystem.Initialize();

	// initialize PhysicsSystem
	kiko::PhysicsSystem::Instance().Initialize();

	// create game // 
	unique_ptr<PlatformGame> game = make_unique<PlatformGame>();
	game->Initialize();

	// MAIN GAME LOOP //

	bool quit = false;
	while (!quit)
	{
		// update engine
		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());
		kiko::PhysicsSystem::Instance().Update(kiko::g_time.GetDeltaTime());

		// update game
		game->Update(kiko::g_time.GetDeltaTime());

		// draw game
		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();

		game->Draw(kiko::g_renderer);

		// draw particles
		kiko::g_particleSystem.Draw(kiko::g_renderer);

		kiko::g_renderer.EndFrame();
	}

	return 0;
}

