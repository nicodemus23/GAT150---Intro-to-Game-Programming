#pragma once

namespace kiko
{
	template <typename T>
	class Singleton
	{
	public:
		// copy constructor
		Singleton(const Singleton& other) = delete;

		// assignment operator
		Singleton& operator = (const Singleton& other) = delete;

		// classic Singleton Object
		static T& Instance()
		{
			static T instance;
			return instance;
		}

		
	protected: //*
		Singleton() = default;

	};
}

//protected can still call base Class constructor but can't with private'