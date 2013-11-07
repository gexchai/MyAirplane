#ifndef _GAMEOVERLAYER_H_
#define  _GAMEOVERLAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class GameOverLayer : public Layer
{
public:
	GameOverLayer();
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) override;
};

#endif