#include "ControlLayer.h"
#include "DefineTag.h"

ControlLayer::ControlLayer()
{
	m_pNormal = SpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("game_resume_nor.png") ;
	m_pPressPause = SpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("game_pause_pressed.png");

	closeItem = MenuItemImage::create();
	closeItem->setNormalSpriteFrame(m_pNormal);
	closeItem->setSelectedSpriteFrame(m_pPressPause);
	closeItem->setCallback(CC_CALLBACK_1(ControlLayer::menuCallBack, this));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	const Size menutItemSize = closeItem->getContentSize();

	closeItem->setPosition(ccp(origin.x+visibleSize.width-menutItemSize.width/2, origin.y+menutItemSize.height/2));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	addChild(menu, 1);

	autorelease();
}

void ControlLayer::menuCallBack( Object* apSender )
{
	if (Director::sharedDirector()->isPaused())
	{
		closeItem->setNormalSpriteFrame(m_pNormal);
		closeItem->setSelectedSpriteFrame(m_pPressPause);
		Director::sharedDirector()->resume();
	}
	else
	{
		closeItem->setNormalSpriteFrame(m_pPressPause);
		closeItem->setSelectedSpriteFrame(m_pNormal);
		Director::sharedDirector()->pause();
	}
}
