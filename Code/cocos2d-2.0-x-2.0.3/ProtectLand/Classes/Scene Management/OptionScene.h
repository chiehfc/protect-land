#ifndef __OPTIONSCENE_H__
#define __OPTIONSCENE_H__
#include "MainMenuScene.h"
#include "AudioManager.h"
#include "cocos2d.h"
#include "LevelManager.h"


using namespace cocos2d;
class COptionScene : public cocos2d::CCLayer
{

protected:
	CCMenu* pMenu;
	CCMenu* pPopupMenu;
	CCSprite* pPopupBackground;
	CCSprite* pPopupQuestion;

	CCMenuItemImage *pSoundItemOn;
	CCMenuItemImage *pSoundItemOff;
	CCMenuItemImage *pResetLevelItem;
	CCLayerColor *m_pBlurLayer;
	void SetStateSoundButton(bool isSoundOn);
	
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(); 
	virtual void update(float dt);
	virtual void render();
	virtual void exit();
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void menuMainMenuCallback(CCObject* pSender);
	void soundOnCallback(CCObject* pSender);

	

	void soundOffCallback(CCObject* pSender);
	void resetLevelCallback(CCObject* pSender);
	void PopupYesCallback(CCObject* pSender);
	void PopupNoCallback(CCObject* pSender);
	// implement the "static node()" method manually
	CC_SYNTHESIZE_READONLY(int , m_runtime, runtime);
	CREATE_FUNC(COptionScene);
};

#endif // __HELLOWORLD_SCENE_H__
