#pragma once
#include "Vector2.h"
#include "Matrix33.h"
#include "Core/Json.h"

namespace kiko
{
	class Transform
	{
	public:
		vec2 position;
		float rotation = 0;
		float scale = 1;

	public:
		Transform() = default;
		Transform(const vec2& position, float rotation, float scale = 1) :
			position{ position },
			rotation{ rotation },
			scale{ scale }
			
		{}

		mat3 GetMatrix() const // has to be const since Model.cpp transform is expecting a const 
		{
			mat3 ms = mat3::CreateScale(scale);
			mat3 mr = mat3::CreateRotation(rotation); // already in radians
			mat3 mt = mat3::CreateTranslation(position); // already in radians
			mat3 mx = mt * ms * mr;

			return mx; // concatenation
		}

		void Read(const json_t& value);
	};
}