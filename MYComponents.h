#pragma once
#include <ecstasy/core/Component.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "vector2.h"

using namespace std;
using namespace ecstasy;


class MYComponents
{
public:
	MYComponents();
	~MYComponents();
};


struct MaterialComponent : public Component<MaterialComponent> {
	string name;
	string textureName;
	float speed = 250;

	sf::Sprite sprite;
	
};


struct ControllComponent : public Component<ControllComponent> {
	bool loaded = true;
	float timeToLoad = 100.0f;
	float currentLoadTime = 0.0f;
};

struct HealthComponent : public Component <HealthComponent> {

	int currentHP;
	int maxHP;

};

struct WeopenHolder : public Component <WeopenHolder> {
	string weopenName;
	string textureName;

	sf::Sprite weopenSprite;
	float angle;

	float aimX;
	float aimY;

	float handleX;
	float handleY;

	float firingPointX;
	float firingPointY;
};



struct EnemyComponent : public Component <EnemyComponent> {
	string enemyAItype;
	sf::IntRect viewRange;
};

struct Projectile : public Component<Projectile> {
	int damage;
	const int stop = 0;
	const int moving = 1;
	int state = stop;

	float distance;
	VECTOR2 direction;
	VECTOR2 start;
	VECTOR2 end;

	int damageClass = 0;

	float timer ;
};