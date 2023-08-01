#include "Model.h"
#include <sstream>

namespace kiko
{
	bool Model::Load(const std::string& filename)
	{
		std::string buffer;
		kiko::readFile(filename, buffer);

		std::istringstream stream(buffer);

		// read color 
		stream >> m_color;

		// read number of points 
		std::string line;
		std::getline(stream, line);
		int numPoints = std::stoi(line);

		// read Vector2 points 
		for (int i = 0; i < numPoints; i++)
		{
			vec2 point;

			stream >> point;

			m_points.push_back(point);
		}


		return true;
	}


	void Model::Draw(Renderer& renderer, const vec2& position, float rotation, float scale)
	{
		if (m_points.empty()) return;

		renderer.SetColor(Color::ToInt(m_color.r), Color::ToInt(m_color.g), Color::ToInt(m_color.b), Color::ToInt(m_color.a));
		for (int i = 0; i < m_points.size() - 1; i++)
		{
			vec2 p1 = (m_points[i] * scale).Rotate(rotation) + position;
			vec2 p2 = (m_points[i + 1] * scale).Rotate(rotation) + position;

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	void Model::Draw(Renderer& renderer, const Transform& transform)
	{
		Draw(renderer, transform.position, transform.rotation, transform.scale);
	}
	float Model::GetRadius() // different from GetRadius() in Actor.h
	{	//  start off at zero to see if length is greater than our radius 
		// if radius has been set, it won't be zero and return radius. Otherwise, run the for loop to get m_radius.
		if (m_radius != 0) return m_radius;

		for (auto& point : m_points)
		{
			// get length of point from origin
			float length = point.Length();

			// radius is equal to the maximum of these two, (radius or length) // length is always a positive value 
			m_radius = Max(m_radius, length);
			// does the same as above ^
			//if (length > radius) radius = length;
		}

		return m_radius;
	}
}
