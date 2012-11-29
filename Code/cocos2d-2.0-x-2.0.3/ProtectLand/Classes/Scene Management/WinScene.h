#ifndef __WINSCENE_H__
#define __WINSCENE_H__
#include "cocos2d.h"
#include "SelectLevelScene.h"
#include "AudioManager.h"
#include "GamePlay.h"
#include "MySprite.h"
#include "IncludeHelper.h"
#include "PositionConfig.h"



class CWinScene : public cocos2d::CCLayer
{
	
private:
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
