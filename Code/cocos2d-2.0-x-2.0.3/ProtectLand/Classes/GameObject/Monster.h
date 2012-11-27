#ifndef _MONSTER_H_
#define _MONSTER_H_
#include "cocos2d.h"
#include "MySprite.h"
#include "GameConfig.h"

USING_NS_CC;
//#include "GameObjectLayer.h"
class CMonster: public CCSprite{
private:
	//CCPointArray * m_arrPath;
public:
	CMySprite * m_sprite, *m_spriteAttack, *m_spriteDie;
	CC_SYNTHESIZE(TypeMonster , m_iType, Type);
	CC_SYNTHESIZE(int, m_iHp, HP);
	CC_SYNTHESIZE(float, m_Speed, Speed);
	CC_SYNTHESIZE(MonsterLevel, m_iLevel, Level);
	CC_SYNTHESIZE(int, m_damage, Damage);
	CC_SYNTHESIZE(int, m_power, Power);
	CC_SYNTHESIZE(int, pos,Pos);
	CC_SYNTHESIZE(int, m_coin, Coin);


	CMonster(TypeMonster type, MonsterLevel level);
	CMonster();
	~CMonster();
	virtual bool init();
	virtual void onExit();
	virtual void draw();

	void moveMonster();
	void attackTower(CCNode* sender);
	void attackDone(CCNode* sender);
	void monsterDie();
	void removeMonster();
	void hitMonster();
};
#endif