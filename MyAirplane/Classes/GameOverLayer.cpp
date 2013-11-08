#include "GameOverLayer.h"

void GameOverLayer::onKeyReleased( EventKeyboard::KeyCode keyCode, Event* event )
{
	CC_UNUSED_PARAM(event);
	if(EventKeyboard::KeyCode::KEY_BACKSPACE == keyCode)
	{
		CCLog("back clicked!");
		CCDirector::sharedDirector()->end();
	}
}

GameOverLayer::GameOverLayer()
{
	Layer::init();
	setKeypadEnabled(true);
}
