#ifndef __GAMEOBJECTLAYER_H__
#define __GAMEOBJECTLAYER_H__
#include <vector>
#include "cocos2d.h"


#include "Utils.h"
#include "IncludeHelper.h"
#include "GamePlay.h"
#include "MySprite.h"
#include "Bullet.h"
#include "Monster.h"
#include "Tower.h"
#include "SkillLayer.h"
USING_NS_CC;

enum {
	kTagParentNode = 11,
	kTagStaticNode = 12,
	kTagWaterNode = 13,
	kTagCoconutNode = 14,
};

class CThief;
class CBeet;
class CTeleport;
class CTarget;

class CGameObjectLayer: public cocos2d::CCLayer
{
private:
	//Sprite layer

	CCArray* 	m_pSpriteList;
	bool		m_bIscol;
	bool		m_bIsTouching;
	CCSprite*	m_pObject;
	CCSprite*	pMoveSprite;
	CCMenuItemImage *pMute;

	eAudioState eAstate;
	CCMenu* pMenu;
	
	//Area shoot bullet
	int m_iCurrentBullet;
	CCSprite *m_pBaseTower;
	CMySprite *m_pTowerItem;
	int m_angleRotate;
	bool m_isClickChangeBullet;
	//Bullet
	float m_fSpeed;
	CCPoint m_pCurrentPoint;
	float m_fTimeRetireBullet;
    float m_TimeDelayBullet;
	int m_levelBullet;
	//Skill
	CCSprite *m_pSkill;
	float m_timeSkill;
	bool m_isClickSkill;
	bool m_isFullEmergy;
	//vector<Bullet *> *m_vBullet;
	CCArray *m_arrBullet;
	
	float length;
	//Physic

	
	

	CCArray *m_arrMonster;
	CCPointArray *m_array1;
	CCPointArray *m_array2;
	CCPointArray *m_array3;
	CCPointArray *m_array4;
	float m_time;
	int m_index;
	CTower *m_tower;
	bool m_checkLose;
	bool oneMonster;
	
	
	void changeBullet();
	void addOneBullet(CCPoint &p,float angle);
	void addBullets(CCPoint &centerPoint);
	
	bool isSelectSkill(CCPoint *p);
	CCPoint getDestination(float X,float Y);
	void updateBullet();
	float caculateAngle(CCPoint v,CCPoint v1);
	void removeStarSkill();
	void addStarSkill();
	

	void spriteMoveDone( CCNode* sender );

	void playSound(CCNode* sender, void* data);	

public:	
	//Sprite	
	void loadMap();
	void creatMonster();
	void attackTower();
	void actionKillMonster(CMonster* pMonster);
	void actionDestroyTower();
	void attackMonster();
	
	void menuSubMenuCallback(CCObject* pSender);
	void menuReplayMenuCallback(CCObject* pSender);
	void menuMuteMenuCallback(CCObject* pSender);

	void menuRestartCallback(CCObject* pSender);

	void delayWinScene(float dt);

	virtual bool init();
	virtual void update(float dt);
	virtual void onExit();
	virtual void draw();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);


	CREATE_FUNC(CGameObjectLayer);
};


#endif
