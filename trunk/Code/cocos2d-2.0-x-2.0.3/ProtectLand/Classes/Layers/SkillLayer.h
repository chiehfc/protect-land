#ifndef __STARSKILL_OBJECT_H__
#define __STARSKILL_OBJECT_H__

#include "cocos2d.h"

USING_NS_CC;
#define SKILL_1 1 // minus half of hp of all monster
#define SKILL_2 2 // kill all fire monster
#define SKILL_3 3 // kill all water monster
#define SKILL_4 4 // kill all monster
#define MAX_TIME_EXE_SKILL 2
class CSkillLayer: public cocos2d::CCLayer
{
private:	
	CCSprite *m_sprite1;
	CCSprite *m_sprite2;
	CCSprite *m_sprite3;
	CCSprite *m_sprite4;
	CCSprite *m_sprite5;
	int stt;
	int resultSkill;
	float m_timer; //count time out
	//bool arr_isTouched[5];
	int arr_PointTouched[6];
public:
	virtual bool init();
	virtual void onEnter();
	void addSphere(CCSprite *m_sprite,char *path,int x,int y);
	bool inAreaSphere(int x, int y, CCPoint &p);
	void initVar();
	void checkClick(CCPoint &p);
	int pow(int x,int n);
	void calculateSkill();
	int getResultSkill();
	void removeLayer();
	virtual void onExit();
	virtual void update(float dt);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	CREATE_FUNC(CSkillLayer);
};

#endif
