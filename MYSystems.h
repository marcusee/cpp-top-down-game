#pragma once
#include <ecstasy/core/EntitySystem.hpp>
#include <ecstasy/systems/IteratingSystem.hpp>
#include <ecstasy/core/Engine.hpp>
using namespace ecstasy;
class MYSystems
{
public:
	MYSystems();
	~MYSystems();
};

class MaterialSystem : public IteratingSystem<MaterialSystem> {
private:

public:
	MaterialSystem();

protected:


	void processEntity(Entity *entity, float deltaTime) override;

};

class ControllSystem : public IteratingSystem<ControllSystem> {
private:

public:
	ControllSystem();

protected:


	void processEntity(Entity *entity, float deltaTime) override;

};

class ProjectileSystem : public IteratingSystem<ProjectileSystem> {
private:

public:
	ProjectileSystem();
protected:


	void processEntity(Entity *entity, float deltaTime) override;

};

class WeopenSystem : public IteratingSystem<WeopenSystem> {
private:
public:
	WeopenSystem();

protected:
	void processEntity(Entity *entity, float deltaTime) override;

};

class EnemySystem : public IteratingSystem<EnemySystem> {
private:
public:
	EnemySystem();
protected:
	void processEntity(Entity *entity, float deltaTime) override;

};

namespace EngineAPI {
	void setUpEngine(Engine& engine);
}