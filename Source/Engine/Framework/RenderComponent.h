#pragma once
#include "Component.h"

namespace kiko
{
	class RenderComponent : public Component // type of component hiererarchy 
	{
	public:
		virtual void Draw(class Renderer& renderer) = 0;
	};


}