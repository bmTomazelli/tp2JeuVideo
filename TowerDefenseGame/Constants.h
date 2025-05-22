#pragma once

static const int SCREEN_WIDTH = 1680;
static const int SCREEN_HEIGHT = 1050;

enum TowerType {archer, mage, knight, king};
enum ProjectileType { arrow, blast, fireball };
enum SpellType { sacredLight, plague };
enum Maps { map1, map2, map3 };

static const int DESIRED_MUSIC_VOLUME = 10;
static const float DESIRED_FRAMERATE = 60.0f;

static const float RAD_TO_DEGREES_RATIO = 57.295779513f;