#pragma once
#include "Singleton.h"
#include "Core/Logger.h"

#include <memory>
#include <map>
#include <string>

#define CREATE_CLASS(classname) kiko::Factory::Instance().Create<kiko::classname>(#classname); 
#define CREATE_CLASS_BASE(classbase, classname) kiko::Factory::Instance().Create<kiko::classbase>(classname); // actual string without #
#define INSTANTIATE(classbase, classname) kiko::Factory::Instance().Create<kiko::classbase>(classname); // create an instance of this Object

namespace kiko
{
	class CreatorBase
	{
	public:
		virtual ~CreatorBase() = default;

		virtual std::unique_ptr<class Object> Create() = 0;

	};

	template <typename T>
	class Creator : public CreatorBase
	{
	public:
		std::unique_ptr<class Object> Create() override
		{
			return std::make_unique<T>();
		}

	};
	// prefab creator
	template <typename T>
	class PrototypeCreator : public CreatorBase
	{
	public:
		PrototypeCreator(std::unique_ptr<T> prototype) : m_prototype{ std::move(prototype) } {}
		std::unique_ptr<class Object> Create() override
		{
			return m_prototype->Clone(); //std::make_unique<T>();
		}

	private:
		std::unique_ptr<T> m_prototype; // for creating duplicates // prototyper 
	};


	class Factory : public Singleton<Factory>
	{
	public:
		template<typename T>
		void Register(const std::string& key);

		template<typename T>
		void RegisterPrototype(const std::string& key, std::unique_ptr<T> prototype);

		template<typename T>
		std::unique_ptr<T> Create(const std::string& key);

		friend class Singleton;

	protected:
		Factory() = default;

	private:
		std::map<std::string, std::unique_ptr<CreatorBase>> m_registry;

	};

		template<typename T>
		inline void Factory::Register(const std::string& key)
		{
			INFO_LOG("Class Registered: " << key);

			m_registry[key] = std::make_unique<Creator<T>>();
		}

		template<typename T> // (1) key, (2) prototype
		inline void Factory::RegisterPrototype(const std::string& key, std::unique_ptr<T> prototype)
		{
			INFO_LOG("Prototype Class Registered: " << key);

			m_registry[key] = std::make_unique<PrototypeCreator<T>>(std::move(prototype));
		}

		template<typename T>
		inline std::unique_ptr<T> Factory::Create(const std::string& key)
		{
			auto iter = m_registry.find(key);
			if (iter != m_registry.end())
			{
				return std::unique_ptr<T>(dynamic_cast<T*>(iter->second->Create().release()));
			}

			ERROR_LOG("Class not found in Factory: " << key);

			return std::unique_ptr<T>();
		}
}
		


