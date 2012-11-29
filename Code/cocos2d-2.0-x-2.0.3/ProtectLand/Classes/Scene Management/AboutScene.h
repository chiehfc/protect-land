#ifndef __ABOUTSCENE_H__
#define __ABOUTSCENE_H__

#include "MainMenuScene.h"
#include "GameConfig.h"
#include "cocos2d.h"
using namespace cocos2d;

class CAboutScene : public CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(); 
	virtual void update(float dt);
	virtual void render();
	virtual void exit();
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static CCScene* scene();

	// a selector callback
	void menuMainMenuCallback(CCObject* pSender);
	CREATE_FUNC(CAboutScene);
};

#endif // __HELLOWORLD_SCENE_H__
