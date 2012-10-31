#ifndef __BULLET_OBJECT_H__
#define __BULLET_OBJECT_H__
#define FIRE_BULLET 0
#define WATER_BULLET 1

#include "cocos2d.h"

USING_NS_CC;




class Bullet: public cocos2d::CCSprite
{
private:	
	CC_SYNTHESIZE(int, m_iType, Type);
	CC_SYNTHESIZE(CCSprite*, m_pSprite, Sprite);
public:
	Bullet(int type,CCSprite* p);
};

#endif
