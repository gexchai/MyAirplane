#include "HelloWorldScene.h"

GameSence::GameSence()
{
	m_pGameLayer = new GameLayer;
	m_pGameLayer->autorelease();

	addChild(m_pGameLayer);
}
