#pragma once
#include <SDL2-2.28.0/include/SDL.h>
#include <string>
#include "Core/Color.h"

namespace kiko
{
	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer() = default;

		bool Initialize();
		void Shutdown();

		void CreateWindow(const std::string& title, int width, int height);
		void BeginFrame();
		void EndFrame();

		// color only goes from 0-255 so use uint8_t for data type 
		void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		void DrawLine(int x1, int y1, int x2, int y2);
		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawPoint(int x, int y);
		void DrawPoint(float x, float y);
		void DrawFilledCircle(float x, float y, float radius, Uint8 alpha);
		

		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }
		SDL_Renderer* GetSDLRenderer() const { return m_renderer; }

		friend class Text;

	private:
		int m_width = 0;
		int m_height = 0;
		float radius = 0;

		SDL_Renderer* m_renderer = nullptr;
		SDL_Window* m_window = nullptr;
	};

	extern Renderer g_renderer;
}