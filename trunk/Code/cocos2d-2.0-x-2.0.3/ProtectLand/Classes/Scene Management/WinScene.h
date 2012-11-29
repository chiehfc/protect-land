#ifndef __WINSCENE_H__
#define __WINSCENE_H__
#include "cocos2d.h"
#include "SelectLevelScene.h"
#include "AudioManager.h"
#include "GamePlay.h"
#include "MySprite.h"
#include "IncludeHelper.h"

#define LOCATION_TITLE				ccp(250, 520)
#define LOCATION_HP					ccp(300, 473)
#define LOCATION_STAGE				ccp(300, 423)
#define LOCATION_KILL				ccp(300, 362)
#define LOCATION_TOTAL				ccp(388, 139)
#define LOCATION_HP_VALUE			ccp(546, 473)
#define LOCATION_HP_VALUE2			ccp(710, 473)
#define LOCATION_STAGE_VALUE		ccp(546, 423)
#define LOCATION_STAGE_VALUE2		ccp(710, 423)
#define LOCATION_KILL_VALUE			ccp(546, 362)
#define LOCATION_KILL_VALUE2		ccp(710, 362)
#define LOCATION_TOTAL_VALUE		ccp(546, 139)
#define LOCATION_TOTAL_VALUE2		ccp(710, 139)
#define LOCATION_MONTER1			ccp(528, 279) //boss1
#define LOCATION_MONTER2 			ccp(833, 554) //monter1
#define LOCATION_MONTER3 			ccp(827, 159) //monter3
#define LOCATION_MONTER4 			ccp(215, 525) //monter6 -1
#define LOCATION_MONTER5 			ccp(240, 190) //monter5

class CWinScene : public cocos2d::CCLayer
{
	
private:
	CCSprite* m_pT;
	CCLabelBMFont *m_pLabeltemp;
	char buf[20];
	int countTotal;
	int countSocre;
	int countBonus;
	int numStar;
	bool isPlayedScoreCount;
	bool isPlayedWin;
	cocos2d::CCLabelBMFont* m_pLabelScorce;
	cocos2d::CCLabelBMFont* m_pLabelBonus;
	cocos2d::CCLabelBMFont* m_pLabelTotal;
	CMySprite* m_pStitchFun;
	CCSprite* m_pTemp; //use to add item no change all layer
	CCLabelBMFont *m_pLabel;

	
	/*cocos2d::CCLabelTTF* m_pLabelScorce;
	cocos2d::CCLabelTTF* m_pLabelBonus;
	cocos2d::CCLabelTTF* m_pLabelTotal;*/
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(); 
	virtual void update(float dt);
	virtual void render();
	virtual void exit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene(int coinBonus, int HpTowerRemind);
	
	void addStar(eStar star);
	void addSpire(CCSprite **m_sprite, char* path, CCPoint &position, float scaleX,float scaleY);
	void addLabel(CCLabelBMFont **pLabel, ccColor3B &color, int width, CCPoint &position,char* str,float scale);

	// a selector callback
	void menuLevelSelectCallback(CCObject* pSender);
	void menuNextCallback(CCObject* pSender);
	void menuRestartCallback(CCObject* pSender);
	void playSound(CCNode* sender, void* data);
	void particeStar(CCNode* sender);
	void StitchMoveDone(CCNode* sender);

	//so mau hien tai con lia cua tower
	int m_iHpTowerRemind;
	//so coin bonus theo so quai giet duoc
	int m_iCoinBonus;
	// implement the "static node()" method manually
	CREATE_FUNC(CWinScene);
};

#endif // __HELLOWORLD_SCENE_H__
