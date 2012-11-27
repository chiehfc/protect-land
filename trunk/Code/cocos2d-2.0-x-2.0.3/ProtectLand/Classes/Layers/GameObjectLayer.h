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
	CCSprite*	m_pSpriteWood;
	CMySprite*	m_pSpriteKillThief;
	int			m_iTouchedItem;
	CCArray* 	m_pSpriteList;
	bool		m_bIscol;
	bool		m_bIsTouching;
	CCSprite*	m_pObject;
	CCSprite*	pMoveSprite;
	CCMenuItemImage *pMute;
	CThief**	pThief;
	CTarget**	pTarget;
	CBeet*		m_pBeet;
	CTeleport*  m_pTeleport;
	bool		m_bIsChooseKillThief;
	bool		m_bIsAllowTouchKillThief;
	bool		m_bIsStopPlay;
	eAudioState eAstate;
	CCMenu* pMenu;
	CCLabelBMFont *labelTarget;
	CCLabelBMFont* _label_score;
	bool isShowTip;
	CCSprite* pSpriteTip;
	CCSprite* pTipText1;
	CCSprite *pWoodSprite ;
	bool isAntTakeWater;
	bool isDeleteAround;
	//Area shoot bullet
	int m_iCurrentBullet;
	CCSprite *m_pBaseTower;
	CMySprite *m_pTowerItem;
	int m_angleRotate;
	bool m_isClickChangeBullet;
	//Bullet
	float m_fSpeed;
	float m_fTimeRetireBullet;
    float m_TimeDelayBullet;
	//Skill
	CCSprite *m_pSkill;
	float m_timeSkill;
	bool m_isClickSkill;
	bool m_isFullEmergy;
	//vector<Bullet *> *m_vBullet;
	CCArray *m_arrBullet;
	
	float length;
	//Physic

	int index ;	
	
	
	CCSize s; // win size
	int currentItemPhysicIndex;
	int countLiquidSleep;
	int m_iNumWater;
	int *sound_water_id;
	int *sound_waterdrop_id;

	CCArray *m_arrMonster;
	CCPointArray *m_array1;
	CCPointArray *m_array2;
	CCPointArray *m_array3;
	CCPointArray *m_array4;
	float m_time;
	int m_index;
	CTower *m_tower;
	bool m_checkLose;
	
	
	void changeBullet();
	void addBullet(CCPoint &p);
	bool inAreaShoot(const CCPoint *p);
	bool isSelectSkill(CCPoint *p);
	CCPoint getDestination(float X,float Y);
	void updateBullet();
	float caculateAngle(CCPoint v,CCPoint v1,CCPoint v2)
	void removeStarSkill();
	void addStarSkill();
	
	void checkScore();
	void spriteMoveDone( CCNode* sender );
	void tipTextSpriteDone(CCNode* sender);
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
	void addElement();
	void menuRestartCallback(CCObject* pSender);
	bool checkColision(CCTouch* pTouch, int ID);
	//CC_SYNTHESIZE(cocos2d::CCLabelTTF*, _label, Label);
	CC_SYNTHESIZE(cocos2d::CCLabelTTF*, _label_wood, LabelWood);
	CC_SYNTHESIZE(cocos2d::CCLabelTTF*, _label_killThief, LabelKillThief);

	//Physic
	void gameLogic(float dt);		
	
	void openBox(float dt);
	void shakeBeet(float dt);
	void delayWinScene(float dt);

	virtual bool init();
	virtual void update(float dt);
	virtual void onExit();
	virtual void draw();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	//virtual void ccTouchesBegan(cocos2d::CCSet* touch, cocos2d::CCEvent* touchEvent); 


	CREATE_FUNC(CGameObjectLayer);
};




//////////////////////////////////////////////////////////////////////////
// PhysicsSprite Class													//
//////////////////////////////////////////////////////////////////////////
class PhysicsWithSprite : public cocos2d::CCSprite
{
public:
	PhysicsWithSprite();	
	
	virtual bool isDirty(void);
	virtual CCAffineTransform nodeToParentTransform(void);

};



#endif
