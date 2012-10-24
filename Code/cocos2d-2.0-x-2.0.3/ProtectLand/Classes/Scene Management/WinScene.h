#ifndef __WINSCENE_H__
#define __WINSCENE_H__
#include "cocos2d.h"
#include "SelectLevelScene.h"
#include "AudioManager.h"
#include "GamePlay.h"
#include "MySprite.h"
#include "IncludeHelper.h"

class CWinScene : public cocos2d::CCLayer
{
	
private:
	int countTotal;
	int countSocre;
	int countBonus;
	int numStar;
	bool isPlayedScoreCount;
	bool isPlayedWin;
	cocos2d::CCLabelBMFont* m_pLabelScorce;
	cocos2d::CCLabelBMFont* m_pLabelBonus;
	cocos2d::CCLabelBMFont* m_pLabelTotal;
	int * star_1_id;
	int * star_2_id;
	int * star_3_id;
	CMySprite* m_pStitchFun;
	/*cocos2d::CCLabelTTF* m_pLabelScorce;
	cocos2d::CCLabelTTF* m_pLabelBonus;
	cocos2d::CCLabelTTF* m_pLabelTotal;*/
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(); 
	virtual void update(float dt);
	virtual void render();
	virtual void exit();
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene(eStar star);
	
	void addStar(eStar star);
	// a selector callback
	void menuLevelSelectCallback(CCObject* pSender);
	void menuNextCallback(CCObject* pSender);
	void menuRestartCallback(CCObject* pSender);
	void playSound(CCNode* sender, void* data);
	void particeStar(CCNode* sender);
	void StitchMoveDone(CCNode* sender);

	// implement the "static node()" method manually
	CREATE_FUNC(CWinScene);
};

#endif // __HELLOWORLD_SCENE_H__
