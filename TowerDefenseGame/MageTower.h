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
    const float BLAST_RECOIL = 1.5f;

    MageTower();
    void update(float deltaTime, std::vector<Demon*>& demons) override;
    void handleTargeting(const std::vector<Demon*>& demons);
    void handleAnimation(float deltaTime);
    void updateSpell(float deltaTime) override;

    void init();
    void spawn(const Vector2f& position);

    void notify(Subject* subject) override;
    Demon* getTarget() const;

private:
    std::vector<IntRect> animationFrames;
    std::vector<float> animationSpeed;
    float animationTimer;
    size_t currentFrame;
    bool animating;
    Demon* target;

    void setupAnimation();
};
