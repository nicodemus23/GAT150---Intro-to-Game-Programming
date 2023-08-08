#pragma once
#include "Core/Core.h"
#include "Renderer.h" 
#include "Framework/Resource.h"
#include <vector>

namespace kiko
{
	class Model : public Resource
	{
	public:
		Model() = default;
		Model(const std::vector<vec2>& points) : m_points{ points } {}

		bool Load(const std::string& filename);
		virtual bool Create(std::string filename, ...) override;

		void Draw(Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(Renderer& renderer, const Transform& transform);

		// get radius function
		float GetRadius();

	private:
		std::vector<vec2> m_points;
		Color m_color;
		// setting radius to zero to be used in getRadius()
		float m_radius = 0;
	};
}