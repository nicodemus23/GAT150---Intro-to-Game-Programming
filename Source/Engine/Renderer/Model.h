#pragma once
#include "Core/Core.h"
#include "Framework/Resource/Resource.h"
#include <vector>

namespace kiko
{
	class Renderer;

	class Model : public Resource
	{
	public:
		Model() = default;
		Model(const std::vector<vec2>& points) : m_points{ points } {}

		virtual bool Create(std::string filename, ...) override;
		bool Load(const std::string& filename);

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