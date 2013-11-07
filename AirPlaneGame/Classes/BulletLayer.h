#ifndef _BULLETLAYER_H_
#define  _BULLETLAYER_H_

#include "cocos2d.h"

using namespace cocos2d;
class PlaneLayer;

class BulletLayer : public Layer
{
public:
	BulletLayer(PlaneLayer* apGameLayer);
	~BulletLayer();

	void AddBullet(float dt);
	void StartShoot(float dt);
	void MoveFinished(Node* pSender);
	Array* GetBulletArr();
	void RemoveBullet(Sprite* apSprite);

private:
	SpriteBatchNode* m_pBulletBatchNode;
	CCArray* m_pAllBulletArray;
	PlaneLayer* m_pPlaneLayer;
};

#endif