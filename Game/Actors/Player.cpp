#include"Player.h"
#include"Projectile.h"
#include"Engine.h"
#include"Enemy.h"
#include"Enemy2.h"
#include"Math/MathUtils.h"
#include<memory>

Player::Player(const henry::Transform& transform, std::shared_ptr<henry::Shape> shape, float speed) : henry::Actor{ transform , shape }, speed{ speed } 
{
	
}
void Player::Initialize()
{

	std::unique_ptr locator = std::make_unique<Actor>();
	locator->transform.localPosition = henry::Vector2{ 8,0 };
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = henry::Vector2{ 0, 5 };
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = henry::Vector2{ 0, -5 };
	AddChild(std::move(locator));

	std::unique_ptr engine = std::make_unique<Actor>(henry::Transform{},scene->engine->Get<henry::ResourceSystem>()->Get<henry::Shape>("Engine.txt"));
	engine->transform.localPosition = henry::Vector2{ -9,0 };
	engine->transform.localRotation = henry::DegToRad(180);
	AddChild(std::move(engine));
}
void Player::Update(float dt)
{
	Actor::Update(dt);
	//children[0]->transform.localRotation += 5 * dt;

	//movement
	float thrust = 0;
	if (Core::Input::IsPressed('A')) transform.rotation -= 5 * dt;
	if (Core::Input::IsPressed('D')) transform.rotation += 5 * dt;
	if (Core::Input::IsPressed('W')) thrust = speed;

	transform.position += henry::Vector2::Rotate(henry::Vector2::right, transform.rotation) * thrust * dt;

	// acceleration
	//henry::Vector2 acceleration;
	//acceleration += henry::Vector2::Rotate(henry::Vector2::right, transform.rotation) * thrust;
	////henry::Vector2 gravity = (henry::Vector2{ 400, 300 } - transform.position).Normalized() * 50;
	////henry::Vector2 gravity = henry::Vector2::down * 50;
	////acceleration += gravity;

	//velocity += acceleration * dt;
	//transform.position += velocity * dt;
	//velocity *= 0.989f;

	transform.position.x = henry::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = henry::Wrap(transform.position.y, 0.0f, 600.0f);

	//fire
	fireTimer -= dt;
	if (fireTimer <= 0 && Core::Input::IsPressed(VK_SPACE))
	{
		fireTimer = fireRate;

		std::vector<henry::Vector2> points = { {-5,-5}, {5,-5}, {0,10}, {-5,-5} };
		std::shared_ptr <henry::Shape> shape1 = std::make_shared<henry::Shape>(points, henry::Color{ 0 , 1 ,0 });

		henry::Transform t = children[0]->transform;
		t.scale = 0.5f;

		std::unique_ptr<Projectile> projectile = std::make_unique <Projectile>(t, scene->engine->Get<henry::ResourceSystem>()->Get<henry::Shape>("Missile.txt"), 600.0f);
		projectile->tag = "Player";
		scene->AddActor(std::make_unique <Projectile>( t , shape, 600.0f ));
		scene->AddActor(std::move(projectile));
		scene->engine->Get<henry::AudioSystem>()->PlayAudio("player_fire");

	}
	std::vector<henry::Color> colors = { henry::Color::white, henry::Color::cyan, henry::Color::purple };
	scene->engine->Get<henry::ParticleSystem>()->Create(children[3]->transform.position, 3, 2, colors, 50, children[3]->transform.rotation, henry::DegToRad(30));
}
	void Player::OnCollision(Actor* actor)
	{
		

		if ((dynamic_cast<Projectile*>(actor) && actor->tag == "Enemy") || (dynamic_cast<Enemy2*>(actor)) || (dynamic_cast<Enemy*>(actor)))
		{
			destroy = true;
			actor->destroy = true;

			std::vector<henry::Color> colors = { henry::Color::white, henry::Color::red, henry::Color::green, henry::Color::blue, henry::Color::yellow };
			scene->engine->Get<henry::ParticleSystem>()->Create(transform.position, 200, 1, henry::Color::red, 50);
			scene->engine->Get<henry::AudioSystem>()->PlayAudio("player_explosion");

			henry::Event event;
			event.name = "PlayerDead";
			event.data = std::string("Yes I'm dead!");
			scene->engine->Get<henry::EventSystem>()->Notify(event);
		}
	
	}

