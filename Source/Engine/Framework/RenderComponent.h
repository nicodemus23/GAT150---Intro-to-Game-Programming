#pragma once
#include "Components/Component.h"

namespace kiko
{
	class RenderComponent : public Component // Component = derived class // type of component hiererarchy 
	{
	public:
		virtual void Draw(class Renderer& renderer) = 0;

	private: // 
	};


}