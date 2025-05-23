#pragma once
#include "Tower.h"
#include <vector>

class MageTower : public Tower
{
public:
	// Cadence
    const float MAGE_FIRE_RATE = 1.5f;

    // Mage Animation
    std::vector<float> frameDuration;
    const int MAGE_FRAME_WIDTH = 150;
    const int MAGE_FRAME_HEIGHT = 150;

    MageTower();
    void update(float deltaTime, std::vector<Demon*>& demons) override;
    void draw(RenderWindow& renderWindow) const override;

    void setLife();

    void init();
    void spawn(const Vector2f& position);

    void notify(Subject* subject) override;

private:
    std::vector<IntRect> animationFrames;
    std::vector<float> animationSpeed;
    float animationTimer;
    size_t currentFrame;
    bool animating;
    Demon* target;

    //fire
	float fireCooldown;
	float fireTimer;

    void setupAnimation();
    void shoot();
};
