#ifndef _ENEMYSPRITE_H_
#define  _ENEMYSPRITE_H_

#include "cocos2d.h"

USING_NS_CC;

class EnemySprite : public Sprite
{
public:
	EnemySprite(SpriteFrame* aSpriteFrame, int aLifenum);
	int GetLife() const;
	void SetLife(int life);
	void AddLifenum();
	void LoseLifenum();
	bool IsAlive();
private:
	int m_Life;
};

#endif