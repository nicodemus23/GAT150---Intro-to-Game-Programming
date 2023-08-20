#pragma once
#include "Framework/Actor.h"

namespace kiko
{
	class Weapon : public Actor
	{
	public:
		CLASS_DECLARATION(Weapon) // to Register in order to Clone() // contains const json_t value Read()
	
		bool Initialize() override;
		void Update(float dt) override;
		void OnCollision(Actor* other);

	private:
		float speed = 0;

	};
}


