#ifndef __HELPSCENE_H__
#define __HELPSCENE_H__

#include "cocos2d.h"

class CHelpScene : public cocos2d::CCLayer
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
	
	// implement the "static node()" method manually
	CC_SYNTHESIZE_READONLY(cocos2d::CCLabelTTF*, _label, Label);
	CC_SYNTHESIZE_READONLY(int , m_runtime, runtime);
	CREATE_FUNC(CHelpScene);
};

#endif // __HELLOWORLD_SCENE_H__
