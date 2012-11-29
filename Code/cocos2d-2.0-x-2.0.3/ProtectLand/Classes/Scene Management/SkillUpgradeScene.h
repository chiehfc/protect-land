#ifndef __SKILL_UPGRADE_SCENE_H__
#define __SKILL_UPGRADE_SCENE_H__
#include "MainMenuScene.h"
#include "AudioManager.h"
#include "cocos2d.h"
#include "LevelManager.h"
#define SCALE_BACKROUND 1.2
#define SCALE_ITEM 1.5
#define HP_UPDATE 10 
#define LEVEL_UPDATE 1 
#define LOCATION_WALL_ITEM ccp(380, 520)
#define LOCATION_SPEED_ITEM ccp(210, 382)
#define LOCATION_LEVEL_ITEM ccp(550, 382)
#define LOCATION_RATEDAME_ITEM ccp(210, 258)
#define LOCATION_DAME_ITEM ccp(550, 258)
#define LOCATION_NAME_LABEL ccp(712, 500)
#define LOCATION_DETAIL_LABEL ccp(712, 462)
#define LOCATION_CURRENT_LABEL ccp(712, 365)
#define LOCATION_CURRENTVALUE_LABEL ccp(822, 365)
#define LOCATION_NEXT_LABEL ccp(712, 335)
#define LOCATION_NEXTVALUE_LABEL ccp(822, 335)
#define LOCATION_BACKGROUND ccp(size.width/2.0, size.height/2.0 +40)
#define LOCATION_LINE ccp(700, size.height/2.0 +40)
using namespace cocos2d;

class CSkillUpgradeScene : public cocos2d::CCLayer
{

protected:
	CCMenu* pMenu;	
	CCSize size;
	CCSprite * m_pBackground;
	CCLabelBMFont *m_lBackground;
	CCMenuItemImage *m_pWall;
	CCMenuItemImage *m_pSpeed;
	CCMenuItemImage *m_pLevel;
	CCMenuItemImage *m_pDamage;	
	CCMenuItemImage *m_pRateDamage;
	CCSprite *m_pLine;
	CCSprite *m_pBorder;
	CCSprite *m_pLogoSelect;
	CCLabelBMFont *m_lable1;
	CCLabelBMFont *m_lable2;
	CCLabelBMFont *m_lable3;
	CCLabelBMFont *m_lable4;
	CCLabelBMFont *m_lable5;
	CCLabelBMFont *m_lable6;
	char *str[6];
	float m_fTowerSpeed;
	int m_iDameTowerCurrent;
	int m_iLevelTower;
	int m_iRateDoubleDamge;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(); 
	virtual void update(float dt);
	virtual void render();
	virtual void exit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	void menuPlayCallBack(CCObject* pSender);
	// implement the "static node()" method manually
	CREATE_FUNC(CSkillUpgradeScene);
	void addSpire(CCSprite **m_sprite, char* path, CCPoint &position, float scale);
	void setButton(CCMenuItemImage *m_button,CCPoint &position, float scale );
	void addLabel(CCLabelBMFont **pLabel, ccColor3B &color, int width, CCPoint &position, char* str,float scale);
	void createLabelAndItem();
	
	void buttonWallCallback(CCObject* pSender);
	void buttonLevelCallback(CCObject* pSender);
	void buttonSpeedCallback(CCObject* pSender);
	void buttonDamageCallback(CCObject* pSender);
	void buttonRateCallback(CCObject* pSender);

};

#endif // __HELLOWORLD_SCENE_H__
