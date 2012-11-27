#ifndef __BULLET_OBJECT_H__
#define __BULLET_OBJECT_H__ 
//TYPE BULLET

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
