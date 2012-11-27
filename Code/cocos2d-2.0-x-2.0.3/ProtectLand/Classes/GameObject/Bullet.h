#ifndef __BULLET_OBJECT_H__
#define __BULLET_OBJECT_H__ 
//TYPE BULLET
#define BULLET_LEVEL_1 1
#define BULLET_LEVEL_2 2
#define BULLET_LEVEL_3 3
#define FIRE_BULLET 9
#define WATER_BULLET 10
#include "cocos2d.h"

USING_NS_CC;




class Bullet: public cocos2d::CCSprite
{
private:	
	CC_SYNTHESIZE(int, m_iType, Type);
	//CC_SYNTHESIZE(CCSprite*, m_pSprite, Sprite);
public:
	CCSprite *m_sprite;
	Bullet(int type,CCSprite* p);
	Bullet();
	bool init(CCSprite * p);
	void onExit();
	~Bullet();
};

#endif
