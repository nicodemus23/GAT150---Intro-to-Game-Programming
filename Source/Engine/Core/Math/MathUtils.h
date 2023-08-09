#pragma once
#include <utility>

#include <cmath>

namespace kiko
{
	constexpr float Pi = 3.14159265359f;
	constexpr float TwoPi = 6.28318530718f;
	constexpr float HalfPi = 1.57079632679f;

	constexpr float RadiansToDegrees(float radians) { return radians * (180.0f / Pi); }
	constexpr float DegreesToRadians(float degrees) { return degrees * (Pi / 180.0f); }

	constexpr int Wrap(int value, int max)
	{
		return (value % max) + ((value < 0) ? max : 0);
	}

	inline float Wrap(float value, float max)
	{
		return std::fmod(value, max) + ((value < 0) ? max : 0);
	}

	template <typename T>
	inline T Max(T a, T b)
	{
		return (a > b) ? a : b;
	}

	template <typename T>
	inline T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	template <typename T>
	inline T Clamp(T value, T min, T max)  // 4 - 10 -> 3
	{
		if (min > max) std::swap(min, max);

		return (value < min) ? min : (value > max) ? max : value;
	}

	// LINEAR INTERPOLATION // 
	template<typename T>
	constexpr T Lerp(const T& a, const T& b, float t) // t = 0 <-> 1 // if it's first, it's zero, if second, 1 and interpolates between the two
	{
		return (a * (1.0f - t)) + (b * t);
	}


}