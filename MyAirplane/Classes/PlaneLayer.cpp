#include "PlaneLayer.h"
#include "DefineTag.h"

PlaneLayer::PlaneLayer()
{
	Layer::init();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	auto spriteFrameCache = cocos2d::SpriteFrameCache::sharedSpriteFrameCache(); 
	spriteFrameCache->addSpriteFramesWithFile("shoot.plist");

	auto plane = Sprite::createWithSpriteFrame(spriteFrameCache->spriteFrameByName("hero1.png"));
	plane->setPosition(ccp(winSize.width/2, plane->getContentSize().height/2));
	addChild(plane,1,PlaneSpriteTag);

	Blink* blink = Blink::create(1,3);

	CCAnimation* animation = CCAnimation::create();
	animation->setDelayPerUnit(0.1);
	animation->addSpriteFrame(spriteFrameCache->spriteFrameByName("hero1.png"));
	animation->addSpriteFrame(spriteFrameCache->spriteFrameByName("hero2.png"));

	CCAnimate* animate = CCAnimate::create(animation);

	plane->runAction(blink);
	plane->runAction(CCRepeatForever::create(animate));
}

void PlaneLayer::moverToPos(Point& pos )
{
	if (!Director::sharedDirector()->isPaused())
	{
		Point actualPos;
		Size winSize = Director::sharedDirector()->getWinSize();
		Size planeSize = getChildByTag(PlaneSpriteTag)->getContentSize();

		if (pos.x < planeSize.width/2)
		{
			pos.x = planeSize.width/2;
		}
		
		if (pos.x > winSize.width-planeSize.width/2)
		{
			pos.x = winSize.width-planeSize.width/2;
		}

		if (pos.y < planeSize.height/2)
		{
			pos.y = planeSize.height/2;
		}

		if (pos.y > winSize.height -planeSize.height/2)
		{
			pos.y = winSize.height -planeSize.height/2;
		}

		getChildByTag(PlaneSpriteTag)->setPosition(pos);
	}
}

void PlaneLayer::Bumb()
{
	removeChildByTag(PlaneSpriteTag);
}
