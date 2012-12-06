#ifndef __STARSKILL_OBJECT_H__
#define __STARSKILL_OBJECT_H__

#include "cocos2d.h"

USING_NS_CC;
#define SKILL_1 6 // minus half of hp of all monster
#define SKILL_2 8 // kill all fire monster
#define SKILL_3 10 // kill all water monster
#define SKILL_4 14 // kill all monster
#define MAX_TIME_EXE_SKILL 1.0f

#define	LOCATION_NUMBER_1	ccp(509, 531) 
#define LOCATION_NUMBER_2	ccp(273, 392)
#define LOCATION_NUMBER_3	ccp(354, 110)
#define LOCATION_NUMBER_4	ccp(693, 110)
#define LOCATION_NUMBER_5	ccp(753, 392)
class CSkillLayer: public cocos2d::CCLayer
{
private:	
	CCSprite *m_sprite1;
	CCSprite *m_sprite2;
	CCSprite *m_sprite3;
	CCSprite *m_sprite4;
	CCSprite *m_sprite5;
	CCLabelBMFont *m_number;
	CCPoint arr_PointNumber[5];
	int stt;
	int resultSkill;
	float m_timer; //count time out
	bool arr_isTouched[5];
	int arr_PointTouched[6];//luu vi tri cac diem da cham vao
	int arr_PointCheck[6];//luu cac vi tri random ban dau
	bool arr_exit[5];
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
	void addLabel(CCLabelBMFont **pLabel, ccColor3B &color, int width, CCPoint &position,char* str,float scale);
	void randomPosition();
	int randomNumber(int firstPos, int secondPos);
	int getAvailabePosition();
	CREATE_FUNC(CSkillLayer);
};

#endif
