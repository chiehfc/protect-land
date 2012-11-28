#include "SkillLayer.h"
#include "GameConfig.h"
#define CENTRAL_X1 145
#define CENTRAL_Y1 380

CSkillLayer::CSkillLayer()
{
	init();
}
bool CSkillLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 10 , true);
	
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	float dx=s.width/2.0-250;
	float dy=s.height/2.0-220;
	m_sprite1=CCSprite::create("Skill\\StarSkill.png");
	//m_pCSkillLayer->setScale(0.5);
	m_sprite1->setPosition(ccp(s.width/2.0,s.height/2.0));
	addChild(m_sprite1);
	/*
	addSphere(m_sprite1,"Skill\\SphereYellow.png",146+dx,30+dy);
	addSphere(m_sprite2,"Skill\\SphereOrange.png",194+dx,30+dy);
	addSphere(m_sprite3,"Skill\\SphereRed.png",223+dx,220-92+dy);
	addSphere(m_sprite4,"Skill\\SphereGreen.png",130+dx,220-36+dy);
	addSphere(m_sprite5,"Skill\\SphereBlue.png",42+dx,220-92+dy);
	*/
	m_timer=0;
	
	return true;
}	
void CSkillLayer::addSphere(CCSprite *m_sprite,char *path,int x,int y)
{
	m_sprite=CCSprite::create(path);
	//m_pCSkillLayer->setScale(0.5);
	m_sprite->setPosition(ccp(x,y));
	addChild(m_sprite);

}
void CSkillLayer::onExit()
{
	CCLayer::onExit();
}

CSkillLayer::~CSkillLayer()
{

}
bool CSkillLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent)
{
	if(CCDirector::sharedDirector()->isPaused()) return false;
	CCLOG("%f %f",pTouch->getLocation().x,pTouch->getLocation().y);
	return true;
}

void CSkillLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}
void CSkillLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}
void CSkillLayer::update(float dt)
{

}

void CSkillLayer::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	this->setTouchEnabled(true);
}
