#ifndef __GAMEOVERSCENE_H__
#define __GAMEOVERSCENE_H__
#include "cocos2d.h"

class MySprite;
class CGameOverScene : public cocos2d::CCLayer
{

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
	void menuNextCallback(CCObject* pSender);
	void menuRestartCallback(CCObject* pSender);
	MySprite * m_sprite;

	// implement the "static node()" method manually
	CC_SYNTHESIZE_READONLY(cocos2d::CCLabelTTF*, _label, Label);
	CC_SYNTHESIZE_READONLY(int , m_runtime, runtime);
	CREATE_FUNC(CGameOverScene);
};

#endif 