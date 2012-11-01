#ifndef _MONSTER_H_
#define _MONSTER_H_
#include "cocos2d.h"
#include "MySprite.h"
#include "GameConfig.h"

USING_NS_CC;
//#include "GameObjectLayer.h"
class CMonster: public CCSprite{
private:
	CCPointArray * m_arrPath;
public:
	CCSprite * m_sprite;
	CC_SYNTHESIZE(MonsterType , m_iType, Type);
	CC_SYNTHESIZE(int, m_iHp, HP);
	CC_SYNTHESIZE(float, m_fTimeMove, TimeMove);
	CC_SYNTHESIZE(int, m_iLevel, Level);

	bool havedCreate;
	
	CMonster(MonsterType type, int level, float timemove, CCPointArray* array);
	CMonster();
	~CMonster();
	bool init();
	void onExit();
	void moveMonster();
};
#endif