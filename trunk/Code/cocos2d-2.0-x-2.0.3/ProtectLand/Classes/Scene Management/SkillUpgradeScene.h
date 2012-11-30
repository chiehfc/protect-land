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
#define RATEDAMAGE_UPDATE 5 


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
	void menuBackCallBack(CCObject* pSender);
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
