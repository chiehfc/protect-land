#ifndef __SKILL_UPGRADE_SCENE_H__
#define __SKILL_UPGRADE_SCENE_H__
#include "MainMenuScene.h"
#include "AudioManager.h"
#include "cocos2d.h"
#include "LevelManager.h"
#define SCALE_BACKROUND 1.2
#define SCALE_ITEM 1.5

#define WALL_ITEM 1
#define LEVEL_ITEM 2
#define SPEED_ITEM 3
#define DAMAGE_ITEM 4
#define RATEDAMAGE_ITEM 5

#define HP_UPDATE 10 
#define LEVEL_UPDATE 1 
#define SPEED_UPDATE 1 
#define DAMAGE_UPDATE 10 
#define RATEDAMAGE_UPDATE 2 

#define LOCATION_WALL_ITEM ccp(380, 520)
#define LOCATION_SPEED_ITEM ccp(210, 382)
#define LOCATION_LEVEL_ITEM ccp(550, 382)
#define LOCATION_RATEDAME_ITEM ccp(550, 258)
#define LOCATION_DAME_ITEM ccp(210, 258)
#define LOCATION_NAME_LABEL ccp(712, 505)
#define LOCATION_DETAIL_LABEL ccp(712, 467)
#define LOCATION_CURRENT_LABEL ccp(713, 403)
#define LOCATION_CURRENTVALUE_LABEL ccp(822, 403)
#define LOCATION_NEXT_LABEL ccp(712, 352)
#define LOCATION_NEXTVALUE_LABEL ccp(822, 352)
#define LOCATION_BACKGROUND ccp(size.width/2.0, size.height/2.0 +40)
#define LOCATION_LINE ccp(700, size.height/2.0 +40)
#define LOCATION_COIN ccp(900, 29) 
#define LOCATION_COIN2 ccp(736, 286)
#define LOCATION_UPGRADE ccp(795, 230)
#define LOCATION_UPGRADE_BORDER ccp(795, 230)
#define LOCATION_COIN_LABEL ccp(851, 50)
#define LOCATION_COIN2_LABEL ccp(771, 306)
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
	CCMenuItemImage *m_pBuy;
	CCSprite *m_pLine;
	CCSprite *m_pBorder;
	CCSprite *m_pLogoSelect;
	CCSprite *m_pCoin;
	CCSprite *m_pCoin2;
	CCSprite *m_pBuyBorder;
	CCLabelBMFont *m_lable1;
	CCLabelBMFont *m_lable2;
	CCLabelBMFont *m_lable3;
	CCLabelBMFont *m_lable4;//current valu
	CCLabelBMFont *m_lable5;
	CCLabelBMFont *m_lable6;//next value
	CCLabelBMFont *m_lable7;//coin to buy
	CCLabelBMFont *m_lable8;//current coin
	char *str[6];
	float m_fTowerSpeed;
	int m_iDameTowerCurrent;
	int m_iLevelTower;
	int m_iRateDoubleDamge;
	int m_iCoinToBuy;
	int m_iCurentItemSelect;
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
	void addSpire(CCSprite **m_sprite, char* path, CCPoint &position, float scaleX,float scaleY);
	void setButton(CCMenuItemImage *m_button,CCPoint &position, float scale );
	void addLabel(CCLabelBMFont **pLabel, ccColor3B &color, int width, CCPoint &position, char* str,float scale);
	void createLabelAndItem();
	
	void buttonWallCallback(CCObject* pSender);
	void buttonLevelCallback(CCObject* pSender);
	void buttonSpeedCallback(CCObject* pSender);
	void buttonDamageCallback(CCObject* pSender);
	void buttonRateCallback(CCObject* pSender);
	void buttonBuyCallback(CCObject* pSender);
};

#endif // __HELLOWORLD_SCENE_H__
