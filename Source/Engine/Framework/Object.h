#pragma once
#include <string>


namespace kiko
{

	class Object
	{
	public:
		Object() = default;
		Object(const std::string& name) : m_name{ name } {};
		virtual ~Object() { OnDestroy(); } // destructor 

		virtual bool Initialize() { return true; } //*
		virtual void OnDestroy() {} 


	protected:
		std::string m_name;

	};

}

// virtual = when you know you want to override the values
		// {} in these avoids setting it equal to anything and leaves it open