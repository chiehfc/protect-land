#ifndef __SKILL_UPGRADE_SCENE_H__
#define __SKILL_UPGRADE_SCENE_H__
#include "MainMenuScene.h"
#include "AudioManager.h"
#include "cocos2d.h"
#include "LevelManager.h"

using namespace cocos2d;

class CSkillUpgradeScene : public cocos2d::CCLayer
{

protected:
	CCMenu* pMenu;	
	
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(); 
	virtual void update(float dt);
	virtual void render();
	virtual void exit();
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	void menuPlayCallBack(CCObject* pSender);
	// implement the "static node()" method manually
	CREATE_FUNC(CSkillUpgradeScene);
};

#endif // __HELLOWORLD_SCENE_H__
