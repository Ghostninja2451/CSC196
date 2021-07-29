#pragma once
#include"Base/Actor.h"


class Enemy : public henry::Actor
{
public:
	Enemy(const henry::Transform& transform, std::shared_ptr<henry::Shape> shape, float speed) : henry::Actor{transform , shape}, speed{speed}  {}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float speed = 300;
	float fireTimer{ 0 };
	float fireRate{ 1.3f };
};