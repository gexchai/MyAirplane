#include "GameLayer.h"
#include "BulletLayer.h"
#include "GameOverLayer.h"
#include "DefineTag.h"
#include "EnemyLayer.h"
#include "EnemySprite.h"
#include "ControlLayer.h"
#include "ScoreLayer.h"

GameLayer::GameLayer()
	: m_IsPlaneTouch(false)
{
	cocos2d::Layer::init();

	auto spriteFrameCache = cocos2d::SpriteFrameCache::sharedSpriteFrameCache(); 
	spriteFrameCache->addSpriteFramesWithFile("shoot_background.plist");

	m_pBackground1= Sprite::createWithSpriteFrame(spriteFrameCache->getSpriteFrameByName("background.png"));
	m_pBackground1->setPosition(ccp(0,0));
	m_pBackground1->setAnchorPoint(ccp(0,0));
	addChild(m_pBackground1);

	m_pBackground2= Sprite::createWithSpriteFrame(spriteFrameCache->getSpriteFrameByName("background.png"));
	m_pBackground2->setPosition(ccp(0,m_pBackground2->getContentSize().height-5));
	m_pBackground2->setAnchorPoint(ccp(0,0));
	addChild(m_pBackground2);

	schedule(schedule_selector(GameLayer::backGroupMove), 0.01f);

	m_pPlaneLayer = new PlaneLayer;
	m_pPlaneLayer->autorelease();
	addChild(m_pPlaneLayer);

	m_pGameOverLayer = new GameOverLayer;
	m_pGameOverLayer->autorelease();
	addChild(m_pGameOverLayer);

	m_pBulletLayer = new BulletLayer(m_pPlaneLayer);
	m_pBulletLayer->autorelease();
	addChild(m_pBulletLayer);
	m_pBulletLayer->StartShoot(0.01f);

	m_pEnemyLayer = new EnemyLayer;
	m_pEnemyLayer->autorelease();
	addChild(m_pEnemyLayer);

	m_pControlLayer = new ControlLayer;
	addChild(m_pControlLayer);

	m_pScoreLayer = new ScoreLayer;
	addChild(m_pScoreLayer);

	setTouchEnabled(true);
	createEventListener();

	scheduleUpdate();
}

void GameLayer::backGroupMove(float dt)
{
	m_pBackground1->setPositionY(m_pBackground1->getPositionY()-2);
	m_pBackground2->setPositionY(m_pBackground1->getPositionY() + m_pBackground1->getContentSize().height -2);

	if (m_pBackground2->getPositionY() == 0)
	{
		m_pBackground1->setPositionY(0);
	}
}

void GameLayer::createEventListener()
{
	auto dispatcher = EventDispatcher::getInstance();
	auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);

	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::myonTouchBegan, this)	;
	listener->onTouchMoved = CC_CALLBACK_2(GameLayer::myonTouchMoved, this)	;
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::myonTouchEnded, this)	;
	listener->onTouchCancelled = CC_CALLBACK_2(GameLayer::myTouchCancelled, this)	;

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool GameLayer::myonTouchBegan( Touch *touch, Event *event )
{
	return true;
}

void GameLayer::myonTouchMoved( Touch *touch, Event *event )
{
	const Point startPos = touch->getStartLocation();
	const Point prePoint = touch->getPreviousLocation();
	const Point point = touch->getLocation();

	Node* planeSprite = m_pPlaneLayer->getChildByTag(PlaneSpriteTag);
	
	Rect planeRect = planeSprite->getBoundingBox();
	planeRect.origin.x -=15;
	planeRect.origin.y -= 15;
	planeRect.size.width += 30;
	planeRect.size.height += 30;

	if (planeRect.containsPoint(startPos))
	{
		m_IsPlaneTouch = true;

		Point offset = point-startPos;

		Point toPos = planeSprite->getPosition()+offset;

		m_pPlaneLayer->moverToPos(toPos);
	}
}

void GameLayer::myonTouchEnded( Touch *touch, Event *event )
{
}

void GameLayer::myTouchCancelled( Touch *touch, Event *event )
{

}

void GameLayer::update( float dt )
{
	Object* bullet = nullptr;
	Array* bulletToDelete = Array::create();
	bulletToDelete->retain();

	CCARRAY_FOREACH(m_pBulletLayer->GetBulletArr(), bullet)
	{
		Sprite* bulletSprite = static_cast<Sprite*>(bullet);

		Array* enenyToDelete = Array::create();
		enenyToDelete->retain();

		Object* enemy = nullptr;
		CCARRAY_FOREACH(m_pEnemyLayer->GetEnemyArr(), enemy)
		{
			EnemySprite* enemySprite = static_cast<EnemySprite*>(enemy);
			if (bulletSprite->getBoundingBox().intersectsRect(enemySprite->getBoundingBox()))
			{
				enemySprite->LoseLifenum();

				m_pScoreLayer->AddScore();

				if (!enemySprite->IsAlive())
				{
					enenyToDelete->addObject(enemySprite);
					bulletToDelete->addObject(bullet);
				}
			}
		}
		CCARRAY_FOREACH(enenyToDelete, enemy)
		{
			EnemySprite* enemy1 = static_cast<EnemySprite*>(enemy);
			m_pEnemyLayer->EnemyBlowp(enemy1);
		}
		enenyToDelete->release();
	}
	CCARRAY_FOREACH(bulletToDelete, bullet)
	{
		Sprite* bulletSprite = static_cast<Sprite*>(bullet);
		m_pBulletLayer->RemoveBullet(bulletSprite);
	}
	bulletToDelete->release();


	CCARRAY_FOREACH(m_pBulletLayer->GetBulletArr(), bullet)
	{
		Sprite* bulletSprite = static_cast<Sprite*>(bullet);
		Sprite* airplane = static_cast<Sprite*>(m_pPlaneLayer->getChildByTag(PlaneSpriteTag));

		if(bulletSprite->getBoundingBox().intersectsRect(airplane->getBoundingBox()))
		{
			m_pBulletLayer->RemoveBullet(bulletSprite);
			m_pPlaneLayer->Bumb();

			m_pScoreLayer->SaveHighestScore();
		}
	}

}
