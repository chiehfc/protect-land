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
	CMySprite * m_sprite;
	CMySprite * m_spriteCoin;
	float timeMove;
	typeMove typeMove;
	CC_SYNTHESIZE(float, m_delayTimeDie,DelayTimeDie);
	CC_SYNTHESIZE(TypeMonster , m_iType, Type);
	CC_SYNTHESIZE(int, m_iHp, HP);
	CC_SYNTHESIZE(float, m_Speed, Speed);
	CC_SYNTHESIZE(MonsterLevel, m_iLevel, Level);
	CC_SYNTHESIZE(int, m_damage, Damage);
	CC_SYNTHESIZE(int, m_power, Power);
	CC_SYNTHESIZE(float, pos,Pos);
	CC_SYNTHESIZE(int, m_coin, Coin);


	CMonster(TypeMonster type, MonsterLevel level, int height);
	CMonster();
	~CMonster();
	virtual bool init();
	virtual void onExit();
	virtual void draw();

	void moveMonster();
	void attackTower();
	void attackDone(CCNode* sender);
	void monsterDie();
	void removeMonster();
	void hitMonster();

	CCRect getRectCurrentOfMonsters();  //lay rect cua frame hien tai
	void monsterAction(CCNode* sender);
	void coinAppear();
	void collectCoin(CCNode* sender);
	void collectDone(CCNode * sender);
};
#endif