#pragma once
#include "Framework/Components/Component.h"

namespace kiko
{
	class RenderComponent : public Component // Component = derived class // type of component hiererarchy 
	{
	public:
		virtual void Draw(class Renderer& renderer) = 0;
		virtual float GetRadius() { return 0; } //*

	private: // 
	};


}

// virtual float GetRadius() { return 0; } //* Pure virtual would end with {}
