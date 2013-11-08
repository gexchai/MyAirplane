#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"

class GameSence : public cocos2d::Scene
{
public:
	GameSence();

private:
	GameLayer* m_pGameLayer;
};

#endif // __HELLOWORLD_SCENE_H__
