#pragma once
#include <string>
#include <memory>

namespace kiko
{
	class Resource
	{
	public:
		virtual ~Resource() = default;

		virtual bool Create(std::string filename, ...) = 0;
	};

	//using uint = unsigned int; // using uint is same as "typedef unsigned int"


	template <typename T>
	using res_t = std::shared_ptr<T>; // alias for shared pointer using template 

}