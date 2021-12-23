#pragma once
#include "SFML/Graphics.hpp"
#include <Entt/entt.hpp>
#include "Components.h"
#include "Scene.h"
class Entity
{
public:
	entt::entity EntityID { entt::null};
	Entity(entt::entity id, Scene* scene) : EntityID(id), _scene(scene)
	{};
	Entity() = default;	

	template<typename T, typename ... Args >
	T& AddComponent(Args&& ... args)
	{
		auto& component_ref = _scene->entt_reg.emplace<T>(EntityID,std::forward<Args>(args)...);

		//sort entity registry if the component is RenderableComponent 
		if constexpr (std::is_same<T,RenderableComponent>::value)
		{
			auto sort_render_prio = [] (const RenderableComponent& r1, const RenderableComponent r2)
			{
				return r1.prio < r2.prio;
			};
			_scene->entt_reg.sort<RenderableComponent>(sort_render_prio);
		}

		return component_ref;
	}


	template<typename T>
	void AddComponent()
	{
		return _scene->entt_reg.emplace<T>(EntityID);
	}

	template<typename T>
	bool hasComponent()
	{
		//return _scene->entt_reg.has<T>(EntityID);
		return false;
	}

	template<typename T>
	T& getComponent()
	{
		return _scene->entt_reg.get<T>(EntityID);
	}

	template<typename T>
	int removeComponent()
	{
		return _scene->entt_reg.remove<T>(EntityID);
	}

private:
	Scene* _scene;
};

