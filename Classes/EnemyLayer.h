#ifndef _ENEMYLAYER_H_
#define  _ENEMYLAYER_H_

#include "cocos2d.h"
#include "DefineTag.h"

using namespace cocos2d;
class EnemySprite;

class EnemyLayer : public Layer
{
public:
	EnemyLayer();
	void addEnemy1(float dt);
	void addEnemy2(float dt);
	void addEnemy3(float dt);

	void enemy1MoveFinished(CCNode* pSender);
	Array* GetEnemyArr();
	void EnemyBlowp(EnemySprite* apSprite);

private:
	SpriteFrame* m_pEnemySpriteFrame1;
	SpriteFrame* m_pEnemySpriteFrame2;
	SpriteFrame* m_pEnemySpriteFrame3_1;
	SpriteFrame* m_pEnemySpriteFrame3_2;
	Array* m_pEnemy1Arr;
};

#endif