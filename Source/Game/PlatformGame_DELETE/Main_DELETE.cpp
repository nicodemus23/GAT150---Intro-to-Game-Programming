#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Framework.h"
#include "Physics/PhysicsSystem.h"

#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <map>
#include <functional>


using namespace std;

template <typename T>
void print(const std::string& s, const T& container)
{
	std::cout << s << std::endl;
	for (auto element : container)
	{
		std::cout << element << " ";
	}
	std::cout << std::endl;
}


//MAIN
int main(int argc, char* argv[])
{

	// singleton is trying to prevent this (there can be only one)
	//kiko::ResourceManager manager;



	INFO_LOG("Initialize Engine...")

	kiko::MemoryTracker::Initialize();
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	// initialize engine
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 800, 600);

	// initialize systems
	kiko::g_inputSystem.Initialize();
	kiko::g_audioSystem.Initialize();
	kiko::PhysicsSystem::Instance().Initialize();


	// main game loop
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
		//game->Draw(kiko::g_renderer); // move below stars if we dont want it painted

		kiko::g_particleSystem.Draw(kiko::g_renderer);

		// Single image on the screen to make sure that png is being drawn
		//kiko::g_renderer.DrawTexture(texture.get(), 150.0f, 150.0f, 0.0f, 1.0f, 1.0f);


		kiko::g_renderer.EndFrame();
	}

	return 0;
}
