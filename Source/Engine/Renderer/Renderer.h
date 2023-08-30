#pragma once
#include "Font.h"
#include "Model.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "Text.h"
#include "Texture.h"

#include <string>
#include <SDL2-2.28.0/include/SDL.h>

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

		void DrawTexture(class Texture* texture, float x, float y, float angle = 0.0f);
		void DrawTexture(class Texture* texture, const Transform& transform);
		void DrawTexture(class Texture* texture, const Rect& source,const Transform& transform); // makes copy of e'rthing 
		void DrawTexture(class Texture* texture, const Rect& source,const Transform& transform, const vec2& origin, bool flipH); // makes copy of e'rthing 

		SDL_Renderer* GetSDLRenderer() const { return m_renderer; }

		friend class Text;

	private:
		int m_width = 0;
		int m_height = 0;
		float radius = 0;

		SDL_Renderer* m_renderer = nullptr;
		SDL_Window* m_window = nullptr;

		friend class Texture;
	};

	extern Renderer g_renderer;
}
