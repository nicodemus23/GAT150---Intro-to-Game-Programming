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
	//game->Initialize();

	// create texture
	//kiko::res_t<kiko::Texture> texture = GET_RESOURCE (kiko::Texture, "test.png", kiko::g_renderer); // <-----NEED THIS?

	////// STARS //////
	/*vector<Star> stars;
	for (int i = 0; i < 1500; i++)
	{
		kiko::Vector2 pos(kiko::Vector2(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight())));
		kiko::Vector2 vel(kiko::randomf(10, 200), 0.0f);

		stars.push_back(Star(pos, vel));
	}*/

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
		//game->Update(kiko::g_time.GetDeltaTime());

		// draw game
		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();

		//game->Draw(kiko::g_renderer);

		//draw stars
		//for (auto& star : stars)
		//{
		//	star.Update(kiko::g_renderer.GetWidth(), kiko::g_renderer.GetHeight());
		//	//kiko::g_renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), kiko::random(255));
		//	kiko::g_renderer.SetColor(static_cast<Uint8>(star.m_color.r), static_cast<Uint8>(star.m_color.g), static_cast<Uint8>(star.m_color.b), static_cast<Uint8>(star.m_color.a));
		//	//star.Draw(kiko::g_renderer);

		//	int circleRadius = 200;
		//	kiko::g_renderer.DrawFilledCircle(star.m_pos.x, star.m_pos.y, star.m_color.a, circleRadius);
		//}

		// draw particles
		kiko::g_particleSystem.Draw(kiko::g_renderer);

		kiko::g_renderer.EndFrame();
	}
	//stars.clear();

	return 0;
}




// first twinkle solution

				// randomize alpha component of stars for twinkle effect 
				//if (kiko::randomf(0.1f, 5.0f) < 2.5)
				//{
				//	m_color.a = kiko::random(50); // lower value
				//}
				//else if (kiko::randomf(0.0f, 10.0f) > 2.5f)
				//{
				//	m_color.a = kiko::random(50)+ 20; // higher value
				//}


