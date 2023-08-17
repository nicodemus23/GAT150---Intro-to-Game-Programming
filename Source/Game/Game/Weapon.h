#pragma once
#include "Framework/Actor.h"
#include "Framework/Object.h"

namespace kiko
{
	class Weapon : public Actor
	{
	public:
		/*WeaponComponent(float speed, const kiko::Transform& transform) :
			Actor{ transform},
			speed{ speed }
			{
				lifespan = 2.0f;
			}*/
		bool Initialize() override;
		void Update(float dt) override;
		void OnCollision(Actor* other) ;
		void Read(const json_t& value);

	private:
		float speed = 0;

	};
}


//decrement time, fire WeaponComponent, reset time 