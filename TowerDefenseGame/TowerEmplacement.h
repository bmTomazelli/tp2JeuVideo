#pragma once
#include "GameObject.h"
#include "IObserver.h"
#include "Subject.h"
#include "ContentPipeline.h"
#include "Constants.h"
#include "Tower.h" 

class TowerEmplacement : public GameObject, public IObserver
{
public:
	TowerEmplacement();
	~TowerEmplacement();

	void init(const Vector2f& position);
	void update();
	void draw(RenderWindow& renderWindow) const;

	void occupyTower(Tower* t);
	void releaseTower();
	Tower* getTower() const;
	bool isOccupied() const;

	void notify(Subject* subject) override;

private:
	Tower* tower;
};
