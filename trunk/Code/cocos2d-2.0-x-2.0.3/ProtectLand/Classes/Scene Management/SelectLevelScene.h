#ifndef __SELECTLEVELSCENE_H__
#define __SELECTLEVELSCENE_H__

#include "cocos2d.h"
#include "LevelManager.h"
class CSelectLevelScene : public cocos2d::CCLayer
{

public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(); 
	virtual void update(float dt);
	virtual void render();
	virtual void exit();
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	int m_levelSelected;	
	void menuBackCallBack(CCObject* pSender);  // call when click button back
	void menuNextCallBack(CCObject* pSender);  // call when click button next


	// implement the "static node()" method manually
	CC_SYNTHESIZE_READONLY(cocos2d::CCLabelTTF*, _label, Label);
	CC_SYNTHESIZE_READONLY(int , m_runtime, runtime);
	CREATE_FUNC(CSelectLevelScene);
};

#endif 
