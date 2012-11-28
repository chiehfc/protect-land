#ifndef _TOWER_H_
#define _TOWER_H_

#include "cocos2d.h"
#include "GameConfig.h"
#include "MySprite.h"

#define FIRE_TOWER 0
#define WATER_TOWER 1
USING_NS_CC;

class CTower: public CCSprite{
public:
	CCSprite * m_sprite;
	CC_SYNTHESIZE(int,m_iHp,HP);
	CTower(int hp);
	~CTower();
	bool init();
	void onExit();
};

#endif