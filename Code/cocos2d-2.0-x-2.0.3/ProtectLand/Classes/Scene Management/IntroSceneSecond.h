#ifndef __INFORSCENESECOND_SCENE_H__
#define __INFORSCENESECOND_SCENE_H__

#include "cocos2d.h"

#include "AudioManager.h"
#include "GameOverScene.h"
#include "SplashScene.h"
#include "IncludeHelper.h"
#include "MySprite.h"

USING_NS_CC;
class IntroSceneSecond : public cocos2d::CCLayer
{
	CCSprite* pSprite;
	CCSprite* pSprite2;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(); 
	virtual void update(float dt);
	virtual void destroy();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void buttonMuteCallBack(CCObject* pSender);
    //void menuPlayCallback(CCObject* pSender);
	// implement the "static node()" method manually
	CC_SYNTHESIZE_READONLY(cocos2d::CCMenuItemImage*,m_pMute,MUTE);
	CC_SYNTHESIZE_READONLY(int , m_runtime, runtime);
	CREATE_FUNC(IntroSceneSecond);
private:
	bool m_bselected;
//private:
};

#endif // __HELLOWORLD_SCENE_H__
