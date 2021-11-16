#pragma once
#include "SFML/Graphics.hpp"
#include <Entt/entt.hpp>
#include "Scene.h"
class Entity
{
public:
	Entity(entt::entity id, Scene* scene) : EntityID(id), _scene(scene)
	{};
	Entity(Entity& other) = default;
	Entity() = default;	
	
	template<typename T, typename ... Args >
	T& AddComponent(Args&& ... args)
	{
		return _scene->entt_reg.emplace<T>(EntityID,std::forward<Args>(args)...);
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
	entt::entity EntityID { entt::null};
	Scene* _scene;
	sf::Sprite sprite;	
};

