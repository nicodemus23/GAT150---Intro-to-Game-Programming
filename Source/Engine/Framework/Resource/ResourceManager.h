#pragma once
#include "Framework/Resource.h"
#include <map>
#include <memory>
#include <string>
#include <cstdarg>

namespace kiko
{
	class ResourceManager
	{
	public:
		template<typename T, typename ...TArgs>
		res_t<T> Get(const std::string& filename, TArgs ... args);

	private:
		std::map<std::string, res_t<Resource>> m_resources; // res_t shared pointer using template for data type in Resource.h

	};


	template<typename T, typename ...TArgs>
	inline res_t<T> ResourceManager::Get(const std::string& filename, TArgs ...args)
	{
		if (m_resources.find(filename) != m_resources.end())
		{
			return std::dynamic_pointer_cast<T>(m_resources[filename]);
		}

		res_t<T> resource = std::make_shared<T>();
		resource->Create(filename, args...);
		m_resources[filename] = resource;

		return resource;
	}

	extern ResourceManager g_resources;

}