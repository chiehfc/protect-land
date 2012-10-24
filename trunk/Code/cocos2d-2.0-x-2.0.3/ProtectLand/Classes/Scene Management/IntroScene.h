#ifndef __INFORSCENE_SCENE_H__
#define __INFORSCENE_SCENE_H__

#include "cocos2d.h"
#include "AudioManager.h"
#include "GameOverScene.h"
#include "SplashScene.h"
#include "IncludeHelper.h"
#include "MySprite.h"
#include "LevelManager.h"

USING_NS_CC;
class IntroScene : public cocos2d::CCLayer
{
	CMySprite* Stitch;
	CMySprite* SimpSon;
	CMySprite* SimpSonHit;
	CMySprite* arrow;
	CMySprite* arrow1;
	CMySprite* arrow2;
	CMySprite* arrow3;
	CMySprite* arrow4;
	CMySprite* arrow5;
	CMySprite* arrow6;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(); 
	virtual void update(float dt);
	virtual void destroy();
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void buttonMuteCallBack(CCObject* pSender);
    //void menuPlayCallback(CCObject* pSender);
	// implement the "static node()" method manually
	CC_SYNTHESIZE_READONLY(cocos2d::CCMenuItemImage*,m_pMute,MUTE);
	CC_SYNTHESIZE_READONLY(int , m_runtime, runtime);
	CREATE_FUNC(IntroScene);
	void spriteMoveDone(CCNode* sender);
	void SimpSonMove(CCNode* sender);
	void SimpSonMoveDone(CCNode* sender);
	void Arrowdone(CCNode* sender);
	void Arrowdone1(CCNode* sender);
	void Arrowdone2(CCNode* sender);
	void Arrowdone3(CCNode* sender);
	void Arrowdone4(CCNode* sender);
	void Arrowdone5(CCNode* sender);
	void Arrowdone6(CCNode* sender);
private:
	bool m_bselected;
//private:
};

#endif // __HELLOWORLD_SCENE_H__
