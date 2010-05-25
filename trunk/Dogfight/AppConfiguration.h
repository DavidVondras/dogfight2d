#ifndef APPCONFIGURATION_H
#define APPCONFIGURATION_H

#define SCENE_MAX_WIDTH 128
#define SCENE_MAX_HEIGHT 32

#define SCENE_MAX_OBJECTENTITY_NB 64

enum EnumSceneSprite
{
	Grass,
	Dirt,
	Piste
};

enum EnumSceneSpriteCollision
{
	CanLand,
	Liquid,
	Crash
};

#endif