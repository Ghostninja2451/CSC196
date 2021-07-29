#pragma once
#include"Base/Actor.h"

class Projectile : public henry::Actor
{
public:
	Projectile(const henry::Transform& transform, std::shared_ptr<henry::Shape> shape, float speed) : henry::Actor{ transform , shape }, speed{ speed }  {}

	void Update(float dt) override;

private:
	float lifetime{ 1 };
	float speed = 300;
};
