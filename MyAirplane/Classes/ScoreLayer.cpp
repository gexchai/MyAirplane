#include "ScoreLayer.h"
#include "DefineTag.h"

ScoreLayer::ScoreLayer()
	: m_RealTimeScore(0)
	, m_HighestScore(0)
{
	Layer::init();
	autorelease();
}

void ScoreLayer::ReadScoreFromFile()
{
	auto userDefault = UserDefault::sharedUserDefault();
	if (!userDefault->getBoolForKey(ScoreFileKey))
	{
		userDefault->setBoolForKey(ScoreFileKey,true);
		userDefault->setIntegerForKey(ScoreKey,0);
		userDefault->flush();
	}
	else
	{
		m_HighestScore = userDefault->getIntegerForKey(ScoreKey);
	}
}

void ScoreLayer::AddScore()
{
	++m_RealTimeScore;
}

void ScoreLayer::AddScore( int aNum )
{
	m_RealTimeScore += aNum;
}

ScoreLayer::~ScoreLayer()
{
	SaveHighestScore();
}

void ScoreLayer::SaveHighestScore()
{
	if (m_RealTimeScore > m_HighestScore)
	{
		m_HighestScore = m_RealTimeScore;
		UserDefault::sharedUserDefault()->setIntegerForKey(ScoreKey,m_HighestScore);
		UserDefault::sharedUserDefault()->flush();
	}
}

int ScoreLayer::GetHighestScore() const
{
	return m_HighestScore;
}
