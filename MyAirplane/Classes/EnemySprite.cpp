#include "EnemySprite.h"

EnemySprite::EnemySprite( SpriteFrame* apSpriteFrame ,int aLifeNum)
	: m_Life(aLifeNum)
{
	initWithSpriteFrame(apSpriteFrame);
}

int EnemySprite::GetLife() const
{
	return m_Life;
}

void EnemySprite::SetLife( int life )
{
	m_Life = life;
}

void EnemySprite::AddLifenum()
{
	++m_Life;
}

void EnemySprite::LoseLifenum()
{
	--m_Life;
}

bool EnemySprite::IsAlive()
{
	return m_Life > 0;
}
