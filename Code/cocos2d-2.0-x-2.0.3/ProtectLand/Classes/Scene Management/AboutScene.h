#ifndef __ABOUTSCENE_H__
#define __ABOUTSCENE_H__

#include "MainMenuScene.h"
#include "GameConfig.h"
#include "cocos2d.h"
using namespace cocos2d;

class CAboutScene : public CCLayer
{
protected:
	CCSprite* pSprite_detail1;
	CCSprite* pSprite_detail2;
	CCSprite* pSprite_detail3;
	CCSprite* pSprite_detail4;
	CCSprite* pSprite_detail5;
	CCPoint point1, point2, point3, point4;
	int currentSprite;
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

	// implement the "static node()" method manually
	//CC_SYNTHESIZE_READONLY(CCLabelTTF*, _label, Label);
	CC_SYNTHESIZE_READONLY(int , m_runtime, runtime);
	CREATE_FUNC(CAboutScene);
	void spriteMoveDone(CCNode* sender);
};

#endif // __HELLOWORLD_SCENE_H__
