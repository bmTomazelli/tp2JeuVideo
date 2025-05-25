#pragma once
#include "Scene.h"
#include "Hud.h"
#include "Inputs.h"
#include "Waypoint.h"
#include "Constants.h"
#include "Demon.h"
#include "TowerEmplacement.h"
#include "ArcherTower.h"
#include "MageTower.h"
#include "KingTower.h"
#include "SacredLight.h"
#include "Plague.h"
#include "Projectile.h"
#include <iostream>
#include <list>

class SceneGame : public Scene, public IObserver
{
public:
	SceneGame(RenderWindow& renderWindow, Event& event, int currentWave, int score, int highScore);
	scenes run() override;
	bool init() override;

    void updateScore(int points);
    void updateKill();
    bool isGameEnded() const;
    const int getScore() const;
    const int getHighScore() const;
    const bool isVictory() const;

protected:
	void getInputs() override;
	void update() override;
	void draw() override;
	bool unload() override;

	virtual void initWaypoints() = 0;
    virtual void initTowersEmplacements() = 0;
    
    void manageActiveAction();
    void manageWaypoints();
    void manageDemonsSpawning();
    void managePause();
    void manageGameOver();
    void manageActiveActionChange();
    void manageTimedManaGain();
    void transitionToNextScene();

    void handleArchersAttackingDemons();
    void handleDemonsTargets();
    void handleProjectilesOnScreen();

	virtual Waypoint* getNextWaypointForDemon(Demon* demon) const;
    Tower* findNearestTowerFromDemon(const Demon* source, const std::vector<TowerEmplacement*>& towers);
    TowerEmplacement* getTowerEmplacementFromClickedPosition(const Vector2f clickedPosition);

	void notify(Subject* subject) override;

	const String MUSIC_FILENAMES[3] = {
		"Ressources\\Sounds\\Music\\Theme01.ogg",
		"Ressources\\Sounds\\Music\\Theme02.ogg",
		"Ressources\\Sounds\\Music\\Theme03.ogg"
	};

	// Demons
	static const int MAX_DEMONS_AMOUNT = 50;
	static const int MAX_DEMONS_ON_SCREEN = 20;
	int demonsAmount = 0;

	View view;
	Hud hud;
	Inputs inputs;

	Sprite map;
	Music music;

	// Valeurs à modifier dans les différents niveaux
	int waypointsAmount;
	Vector2f demonDefaultPosition;
	int towerEmplacementAmount;

	// Waypoints
	std::vector<Waypoint*> waypoints;
	bool showWaypoints = false;

	Demon demons[MAX_DEMONS_ON_SCREEN];
	float demonSpawningTimer = 0.0f;
	float nextDemonSpawnTime = 0.0f;

	// Vagues
	int currentWave;

	// Emplacements de tour
    std::vector<TowerEmplacement*> listTowerEmplacements;
    TowerEmplacement* selectedEmplacement = nullptr;

    // Tours
    static const int MAX_ARCHER_TOWERS = 9;
    static const int MAX_MAGE_TOWERS = 9;

    ArcherTower archerTowers[MAX_ARCHER_TOWERS];
    MageTower mageTowers[MAX_MAGE_TOWERS];
    KingTower kingTower;

    // Projectiles
    static const int MAX_FIREBALL_AMOUNT = 20;
    static const int MAX_TOWERS_PROJECTILES = 9;

    Projectile fireballs[MAX_FIREBALL_AMOUNT];
    Projectile arrows[MAX_TOWERS_PROJECTILES];
    Projectile blasts[MAX_TOWERS_PROJECTILES];

	// Informations du jeu
	int mana = 0;
	int kills = 0;
	int score;
	int highScore;

    float manaGainTimer = 0.0f;

    bool isInPause = false;

    ActiveAction activeAction;

	bool isKingDead = false;
    bool isGameEnd = false;

	//Spells
	SacredLight sacredLight;
	Plague plague;

    //score
    int scorePerDemon = 50;
};