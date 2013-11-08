#pragma once
#include "cocos2d.h"
USING_NS_CC;

class PlaneLayer : public Layer
{
public:
	PlaneLayer();

	void moverToPos(Point& pos);
	void Bumb();
};