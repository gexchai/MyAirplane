#ifndef _CONTROLLAYER_H_
#define  _CONTROLLAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

class ControlLayer : public Layer
{
public:
	ControlLayer();
	void menuCallBack(Object* apSender);

private:
	SpriteFrame* m_pNormal;
	SpriteFrame* m_pPressPause;
	CCMenuItemImage* closeItem;
};

#endif