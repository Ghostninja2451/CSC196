#pragma once
#include"Base/Actor.h"


class Enemy2 : public henry::Actor
{
public:
	Enemy2(const henry::Transform& transform, std::shared_ptr<henry::Shape> shape, float speed) : henry::Actor{ transform , shape }, speed{ speed }  {}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float speed = 300;

};