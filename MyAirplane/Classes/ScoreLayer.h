#ifndef _SCORELAYER_H_
#define  _SCORELAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

class ScoreLayer : public Layer
{
public:
	ScoreLayer();
	~ScoreLayer();
	void AddScore();
	void AddScore(int aNum);
	int GetHighestScore()const;
	void SaveHighestScore();

private:
	void ReadScoreFromFile();
	
private:
	int m_RealTimeScore;
	int m_HighestScore;
};

#endif