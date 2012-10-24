#ifndef __BACKGROUNDLAYER_H__
#define __BACKGROUNDLAYER_H__
#include "cocos2d.h"
class CBackgroundLayer: public cocos2d::CCLayer
{
public:
	virtual bool init();
	virtual void update(float dt);
	virtual void render();
	virtual void exit();
	CREATE_FUNC(CBackgroundLayer);
};

#endif
