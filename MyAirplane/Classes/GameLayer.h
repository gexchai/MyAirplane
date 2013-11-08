#include "cocos2d.h"
#include "PlaneLayer.h"

class BulletLayer;
class GameOverLayer;
class EnemyLayer;
class ControlLayer;
class ScoreLayer;

using namespace cocos2d;

class GameLayer : public cocos2d::Layer
{
public:
	GameLayer();
	void backGroupMove(float dt);
	void createEventListener();
	bool myonTouchBegan(Touch *touch, Event *event);
	void myonTouchMoved(Touch *touch, Event *event);
	void myonTouchEnded(Touch *touch, Event *event);
	void myTouchCancelled(Touch *touch, Event *event);
	virtual void update(float dt) override;

private:
	cocos2d::Sprite* m_pBackground1;
	cocos2d::Sprite* m_pBackground2;
	PlaneLayer* m_pPlaneLayer;
	BulletLayer* m_pBulletLayer;
	GameOverLayer* m_pGameOverLayer;
	EnemyLayer* m_pEnemyLayer;
	ControlLayer* m_pControlLayer;
	ScoreLayer* m_pScoreLayer;
	bool m_IsPlaneTouch;
};