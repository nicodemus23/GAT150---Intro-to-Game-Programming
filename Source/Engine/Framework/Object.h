#pragma once
#include "Object.h"
#include "Factory.h"
#include "Core/Json.h"
#include <string>
#include <memory>

//MACRO //
// for headers
#define CLASS_DECLARATION(classname) \
	virtual const char* GetClassName() {return #classname;} \
	virtual void Read(const json_t& value); \
	virtual std::unique_ptr<Object> Clone() { return std::make_unique<classname>(*this); } \
	class Register \
		{ \
	public: \
			Register() \
			{ \
				Factory::Instance().Register<classname>(#classname); \
			} \
		}; 
		

// for source code 
#define CLASS_DEFINITION(classname) \
	classname::Register register_class;


namespace kiko
{

	class Object
	{
	public:

		Object() = default;
		Object(const std::string& name) : name{ name } {}
		virtual ~Object() { OnDestroy(); } // destructor 

		CLASS_DECLARATION(Object);

		virtual bool Initialize() { return true; } //*
		virtual void OnDestroy() {}

	public:
		std::string name;
		bool active = true;

	};

}

// virtual = when you know you want to override the values
		// {} in these avoids setting it equal to anything and leaves it open

//Factory::Instance().Register<classname>(#classname);	\ //* Putting a # in front of a MACRO automatically puts quotes "" around it. See SpriteRenderComponent 
