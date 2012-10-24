#ifndef __LOADINGSCENE_H__
#define __LOADINGSCENE_H__
#include "cocos2d.h"
#include "IncludeHelper.h"
#include "SelectLevelScene.h"
#include "GamePlay.h"
#include "SpriteManager.h"
#include "GameConfig.h"
#include "LevelManager.h"

class CLoadingScene: public cocos2d::CCLayer
{
	int m_iNumOfStep;
	int m_iCurrentStep;
	CMySprite* m_pLoadingBar;
	bool isTap;
public:
	virtual bool init(); 
	virtual void update(float dt);
	virtual void render();
	virtual void exit();
	static cocos2d::CCScene* scene(int MODE);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	static int MODE;
	CC_SYNTHESIZE_READONLY(cocos2d::CCLabelTTF*, _label, Label);
	CC_SYNTHESIZE_READONLY(int , m_runtime, runtime);
	CREATE_FUNC(CLoadingScene);

};
#endif