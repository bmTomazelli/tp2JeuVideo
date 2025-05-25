#pragma once

static const int SCREEN_WIDTH = 1680;
static const int SCREEN_HEIGHT = 1050;

enum TowerType {archer, mage, knight, king};
enum ProjectileType { arrow, blast, fireball };
enum SpellType { sacredLight, plague };
enum Maps { map1, map2, map3 };

enum ActiveAction { BUILD_ARCHER, BUILD_MAGE, CAST_PLAGUE, CAST_SACRED_LIGHT };

static const int DESIRED_MUSIC_VOLUME = 10;
static const float DESIRED_FRAMERATE = 60.0f;

static const float RAD_TO_DEGREES_RATIO = 57.295779513f;

static const int ARROW_MAX_DAMAGE = 5;
static const int BLAST_MAX_DAMAGE = 13;
static const int FIREBALL_MAX_DAMAGE = 11;

static const int MAX_WAVES = 10;

static const float MANA_GAIN_TIMER = 0.2f;
static const int DEFAULT_MANA_AMOUNT = 500;
static const int BUILD_ARCHER_TOWER_COST = 70;
static const int BUILD_MAGE_TOWER_COST = 100;
static const int CAST_PLAGUE_SPELL_COST = 20;
static const int CAST_SACRED_LIGHT_COST = 60;
