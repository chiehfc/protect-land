#ifndef __SPLASHSCENE_H__
#define __SPLASHSCENE_H__
#include "cocos2d.h"

class CSPlashScene: public cocos2d::CCLayer
{
public:
	virtual bool init(); 
	virtual void update(float dt);
	static cocos2d::CCScene* scene();
	CC_SYNTHESIZE_READONLY(cocos2d::CCLabelTTF*, _label, Label);
	CC_SYNTHESIZE_READONLY(int , m_runtime, runtime);
	CREATE_FUNC(CSPlashScene);

};
#endif