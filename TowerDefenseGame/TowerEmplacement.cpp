#include "TowerEmplacement.h"

TowerEmplacement::TowerEmplacement()
{
	tower = nullptr;
}

TowerEmplacement::~TowerEmplacement()
{
}

void TowerEmplacement::init(const Vector2f& position)
{
	setTexture(ContentPipeline::getInstance().getTowerEmplacementTexture());
	setPosition(position);
    activate();
}

void TowerEmplacement::update()
{
}

void TowerEmplacement::draw(RenderWindow& renderWindow) const
{
	if (!isOccupied())
		GameObject::draw(renderWindow);
}

void TowerEmplacement::occupyTower(Tower* towerP)
{
	if (!isOccupied() && towerP)
	{
		tower = towerP;
		towerP->addObserver(this);
	}
}

void TowerEmplacement::releaseTower()
{
	tower = nullptr;
}

Tower* TowerEmplacement::getTower() const
{
	return tower;
}

bool TowerEmplacement::isOccupied() const
{
	return tower != nullptr;
}

void TowerEmplacement::notify(Subject* subject)
{
	if (tower && subject == tower)
	{
        if (tower->isDead())
		    releaseTower();
	}
}
