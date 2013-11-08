#include "BulletLayer.h"
#include "GameLayer.h"
#include "DefineTag.h"

#include <functional>

BulletLayer::BulletLayer(PlaneLayer* apGameLayer)
	: m_pPlaneLayer(apGameLayer)
{
	bool res = cocos2d::Layer::init();

	Texture2D* lpTexTure = TextureCache::sharedTextureCache()->addImage("shoot.png");
	m_pBulletBatchNode = SpriteBatchNode::createWithTexture(lpTexTure);
	addChild(m_pBulletBatchNode);

	m_pAllBulletArray = Array::create();
	m_pAllBulletArray->retain();
}

void BulletLayer::AddBullet( float dt )
{
	Sprite* bullet = Sprite::createWithSpriteFrameName("bullet1.png");
	bullet->retain();
	m_pBulletBatchNode->addChild(bullet);

	m_pAllBulletArray->addObject(bullet);

	Point planePoint = m_pPlaneLayer->getChildByTag(PlaneSpriteTag)->getPosition();
	Size planeSize = m_pPlaneLayer->getChildByTag(PlaneSpriteTag)->getContentSize();

	const Point bulletPos = ccp(planePoint.x, planePoint.y+planeSize.height/2); 
	bullet->setPosition(bulletPos);

	float length = CCDirector::sharedDirector()->getWinSize().height + planeSize.height/2-bulletPos.y;
	float velocity = 420/1;
	float realMoveDuration = length/velocity;

	FiniteTimeAction* actionMove = MoveTo::create(realMoveDuration,ccp(bulletPos.x
		,CCDirector::sharedDirector()->getWinSize().height + planeSize.height/2));

	FiniteTimeAction* actionDone = CCCallFuncN::create(this,callfuncN_selector(BulletLayer::MoveFinished));

	Sequence* sequence = Sequence::createWithTwoActions(actionMove,actionDone);

	bullet->runAction(sequence);
}

void BulletLayer::StartShoot( float dt )
{
	schedule(schedule_selector(BulletLayer::AddBullet),0.2f, kRepeatForever,dt);
}

void BulletLayer::MoveFinished(Node* pSender)
{
	m_pAllBulletArray->removeObject(pSender);
	m_pBulletBatchNode->removeChild(pSender, true);
}

BulletLayer::~BulletLayer()
{
}

Array* BulletLayer::GetBulletArr()
{
	return m_pAllBulletArray;
}

void BulletLayer::RemoveBullet( Sprite* apSprite )
{
	removeChild(apSprite);
	m_pAllBulletArray->removeObject(apSprite);
}
