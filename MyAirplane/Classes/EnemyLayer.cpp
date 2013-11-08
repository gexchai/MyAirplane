#include "EnemyLayer.h"
#include "EnemySprite.h"

EnemyLayer::EnemyLayer()
{
	Layer::init();

	m_pEnemySpriteFrame1 = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1.png");
	m_pEnemySpriteFrame2 = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2.png");
	m_pEnemySpriteFrame3_1 = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n1.png");
	m_pEnemySpriteFrame3_1 = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n2.png");

	CCAnimation* animation1=CCAnimation::create();
	animation1->setDelayPerUnit(0.1f);
	animation1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down1.png"));
	animation1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down2.png"));
	animation1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down3.png"));
	animation1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down4.png"));

	CCAnimation* animation2=CCAnimation::create();
	animation2->setDelayPerUnit(0.1f);
	animation2->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down1.png"));
	animation2->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down2.png"));
	animation2->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down3.png"));
	animation2->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down4.png"));

	CCAnimation* animation3=CCAnimation::create();
	animation3->setDelayPerUnit(0.1f);
	animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down1.png"));
	animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down2.png"));
	animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down3.png"));
	animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down4.png"));
	animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down5.png"));
	animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down6.png"));

	CCAnimationCache::sharedAnimationCache()->addAnimation(animation1,"Enemy1Blowup");
	CCAnimationCache::sharedAnimationCache()->addAnimation(animation2,"Enemy2Blowup");
	CCAnimationCache::sharedAnimationCache()->addAnimation(animation3,"Enemy3Blowup");

	this->schedule(schedule_selector(EnemyLayer::addEnemy1),1.0f);
	//this->schedule(schedule_selector(EnemyLayer::addEnemy2),3.0f);
	//this->schedule(schedule_selector(EnemyLayer::addEnemy3),6.0f);

	m_pEnemy1Arr = Array::create();
	m_pEnemy1Arr->retain();
}

void EnemyLayer::addEnemy1(float dt)
{
	auto enemySprite1 = new EnemySprite(m_pEnemySpriteFrame1,1);
	m_pEnemy1Arr->addObject(enemySprite1);

	Size sprite1Size = enemySprite1->getContentSize();
	const Size winSize = Director::sharedDirector()->getWinSize();
	const int minX = sprite1Size.width/2;
	const int maxX = winSize.width - minX;
	const int rangeX = maxX-minX;
	const int actualX = ( rand() % rangeX)+sprite1Size.width/2;
	enemySprite1->setPosition(ccp(actualX, winSize.height+sprite1Size.height/2));
	addChild(enemySprite1,1,Enemy1Tag);

	const int minDuration = 2;
	const int maxDuration = 4;
	const int actualDuration = (rand() % (maxDuration-minDuration))+minDuration;

	FiniteTimeAction* actionMove = MoveTo::create(actualDuration, ccp(actualX,-sprite1Size.height/2));

	FiniteTimeAction* actionDone = CCCallFuncN::create(this,callfuncN_selector(EnemyLayer::enemy1MoveFinished));

	Sequence* seq = Sequence::create(actionMove, actionDone,nullptr);
	enemySprite1->runAction(seq);
}

void EnemyLayer::addEnemy2( float dt )
{

}

void EnemyLayer::addEnemy3( float dt )
{

}

void EnemyLayer::enemy1MoveFinished( CCNode* pSender )
{
	if (nullptr != pSender)
	{
		removeChild(pSender);
		m_pEnemy1Arr->removeObject(pSender);
		pSender->release();
	}
}

Array* EnemyLayer::GetEnemyArr()
{
	return m_pEnemy1Arr;
}

void EnemyLayer::EnemyBlowp( EnemySprite* apSprite )
{
	removeChild(apSprite);
}
