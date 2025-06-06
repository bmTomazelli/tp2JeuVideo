#pragma once
#include "GameObject.h"
#include "Waypoint.h"
#include "IObserver.h"
#include "Subject.h"
#include "HealthGauge.h"

class SceneGame; // Forward declaration

class Demon : public GameObject, public IObserver, public Subject
{
public:
	Demon();
	~Demon();

	void init(const int wave);
	void update(const float deltaTime);
	void drawDemonHealth(RenderWindow& renderWindow) const;

	void assignWaypointToFollow(Waypoint* waypoint);
	void spawnDemon(const Vector2f position);
	void loseHealth(const int damage);

    void prepareShooting();

	bool isDying() const;
    bool canShoot() const;
	Waypoint* getWaypointToFollow() const;
    FloatRect getTargetDetectionBox() const;
    const float getRangeOfFire() const;
    void resetStatus();

    void setSceneGame(SceneGame* sceneGame);

private:
	void checkStatus();
	void manageMovement(const float deltaTime);
    void manageRecoil(const float deltaTime);
    void manageSpellEffect(const float deltaTime);
	void checkCollisionWithWaypoint();
	void manageAnimation(const float deltaTime);
	void runAnimation(const float deltaTime, const float timePerFrame, const int imageNumber, const bool linear, IntRect* images);
	void notify(Subject* subject) override;

	enum DemonState { FLYING, DYING };
	void setDemonState(DemonState animationState);

	const int RECTANGLE_WIDTH = 100;
	const int RECTANGLE_HEIGHT = 25;
	const int ANIM_DEMON = 5;

	const int MAX_DEMON_HEALTH = 60;
	const float DEFAULT_DEMON_SPEED = 54.0f;
	const float SPEED_WAVE_MULTIPLIER = 6.0f;

    const int SCORE_DEAD_DEMON = 50;

	const float HEALTHGAUGE_OFFSET_X = 25.0f;
	const float HEALTHGAUGE_OFFSET_Y = RECTANGLE_HEIGHT * 2.0f;
    const int TARGET_DETECTION_BOX_SIZE = 200;

    const float MAX_RECOIL = 1.05f;
    const float DEMON_RANGE_OF_FIRE = 250.0f;

	IntRect* imagesFlying;
	IntRect* imagesDying;

	DemonState demonState;
	float timeCounter = 0.0f;
	int currentImage = 0;
	const float TIME_PER_FRAME = 0.1f;

	Waypoint* waypointToFollow;
    
    HealthGauge healthGauge;
	int health = MAX_DEMON_HEALTH;
	float speed = 0;
	int wave = 0;
	float moveAngle;
	float angle = 0;
    float recoil = 0;
    float recoilTimer = 0;
    float rangeOfFire = 250.0f;

    FloatRect targetDetectionBox;

    float spellTimer = 0.f;
    float plagueTickTimer = 0.f;
    float plagueDamageMultiplier = 1.f;

	Sound attackSound;
    SceneGame* sceneGame = nullptr; // R�f�rence � la sc�ne de jeu pour notifier les observateurs
};

