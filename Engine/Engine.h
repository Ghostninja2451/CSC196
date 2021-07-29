#pragma once
#include"Graphics/ParticleSystem.h"
#include"AudioSystem/AudioSystem.h"


#include"Math/Vector2.h"
#include"Math/Color.h"
#include"Math/Random.h"
#include"Math/MathUtils.h"
#include"Math/Transform.h"

#include"Graphics/Shape.h"

#include"Base/Actor.h"
#include"Base/Scene.h"

//framework
#include"FrameWork/EventSystem.h"
#include "FrameWork/ResourceSystem.h"

#define NOMINMAX
#include"core.h"
#include <vector>
#include <memory>
#include<algorithm>


namespace henry
{
	class Engine
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		template<typename T>
		T* Get();

	private:
		std::vector<std::unique_ptr<System>> systems;

	};

	template<typename T>
	inline T* Engine::Get()
	{
		for (auto& system : systems)
		{
			if (dynamic_cast<T*>(system.get())) return dynamic_cast<T*>(system.get());
		}
		
		return nullptr;
	}
}