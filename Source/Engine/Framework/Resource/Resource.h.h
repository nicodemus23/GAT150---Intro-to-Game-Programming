#pragma once
// need to add resource folder under Framework and add this file
#include <string>

namespace kiko
{
	class Resource
	{
	public:
		virtual ~Resource() = default;

		virtual bool Create(std::string filename, ...) =0;
	

	};
}