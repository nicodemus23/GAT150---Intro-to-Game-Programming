#pragma once
#include "Framework/Object.h"

namespace kiko
{
	class Component : public Object
	{
	public:
		virtual void Update(float dt) = 0;

		friend class Actor;

	public:
		class Actor* m_owner = nullptr; // declaring class without .h in header is a forward declaration
	};

	// can't use "new" on pure virtual functions 

}