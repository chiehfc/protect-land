#ifndef __BULLET_OBJECT_H__
#define __BULLET_OBJECT_H__
//TYPE BULLET
#define FIRE_BULLET_SMALL 0
#define FIRE_BULLET_BIG 1
#define WATER_BULLET_SMALL 2
#define WATER_BULLET_BIG 3
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
