#ifndef __STARSKILL_OBJECT_H__
#define __STARSKILL_OBJECT_H__

#include "cocos2d.h"

USING_NS_CC;


class CSkillLayer: public cocos2d::CCLayer
{
private:	
	CCSprite *m_sprite1;
	CCSprite *m_sprite2;
	CCSprite *m_sprite3;
	CCSprite *m_sprite4;
	CCSprite *m_sprite5;
	float m_timer;
public:
	CSkillLayer();
	~CSkillLayer();
	virtual bool init();
	void addSphere(CCSprite *m_sprite,char *path,int x,int y);
	virtual void onExit();
	virtual void update(float dt);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	CREATE_FUNC(CSkillLayer);
};

#endif
