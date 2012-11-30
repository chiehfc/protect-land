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
	CCSprite * m_activeHP;
	CCSprite * m_inactiveHP;
	float timeMove;
	typeMove typeMove;
	CCLabelTTF * bloothOut1,*bloothOut2, *bloothOut3;
	bool check1, check2, check3;
	int index;
	CC_SYNTHESIZE(float, m_delayTimeDie,DelayTimeDie);
	CC_SYNTHESIZE(TypeMonster , m_iType, Type);
	CC_SYNTHESIZE(int, m_iHp, HP);
	CC_SYNTHESIZE(float, m_Speed, Speed);
	CC_SYNTHESIZE(MonsterLevel, m_iLevel, Level);
	CC_SYNTHESIZE(int, m_damage, Damage);
	CC_SYNTHESIZE(int, m_power, Power);
	CC_SYNTHESIZE(float, pos,Pos);
	CC_SYNTHESIZE(int, m_coin, Coin);
	CC_SYNTHESIZE(float, m_timeAttackDelay, TimeAttackDelay);
	CC_SYNTHESIZE(float, m_currentTime, CurrentTime);
	CC_SYNTHESIZE(int, m_numOfAttack, NumOfAttack);
	CC_SYNTHESIZE(int, m_coinBonus, CointBonus);
	CC_SYNTHESIZE(int, m_maxHP, MaxHP);
	//CC_SYNTHESIZE(char *, m_text, text);
	//CC_SYNTHESIZE(CCLabelTTF *, m_bloothOut, bloothOut);


	CMonster(TypeMonster type, MonsterLevel level, int height);
	CMonster();
	~CMonster();
	virtual bool init();
	virtual void onExit();
	virtual void draw();

	void moveMonster();
	void attackTower();
	void attackDone(CCNode* sender);
	void monsterDie(int damage);
	void removeMonster();
	void hitMonster(int damage);

	CCRect getRectCurrentOfMonsters();  //lay rect cua frame hien tai
	void monsterAction(CCNode* sender);
	void coinAppear();
	void collectCoin(CCNode* sender);
	void collectDone(CCNode * sender);

	//tru mau tren dau quai.
	void numberDamageIn(int damage);
	void hurtDone1(CCNode* sender);
	void hurtDone2(CCNode* sender);
	void hurtDone3(CCNode* sender);
	int attackTowerWithDamage(float m_time);

	//void bloodBar();
};
#endif