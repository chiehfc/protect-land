#include "SkillLayer.h"
#include "GameConfig.h"
#include "GamePlay.h"
#define CENTRAL_X1 408
#define CENTRAL_Y1 190
#define CENTRAL_X2 650
#define CENTRAL_Y2 192
#define CENTRAL_X3 707
#define CENTRAL_Y3 387
#define CENTRAL_X4 518
#define CENTRAL_Y4 500
#define CENTRAL_X5 345
#define CENTRAL_Y5 386
#define RADIUS_SPHERE 60

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
	initVar();
	addSphere(m_sprite1,"Skill\\SphereYellow.png",CENTRAL_X1,CENTRAL_Y1);
	addSphere(m_sprite2,"Skill\\SphereOrange.png",CENTRAL_X2,CENTRAL_Y2);
	addSphere(m_sprite3,"Skill\\SphereRed.png",CENTRAL_X3,CENTRAL_Y3);
	addSphere(m_sprite4,"Skill\\SphereGreen.png",CENTRAL_X4,CENTRAL_Y4);
	addSphere(m_sprite5,"Skill\\SphereBlue.png",CENTRAL_X5,CENTRAL_Y5);
	resultSkill=-1;
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

bool CSkillLayer::inAreaSphere(int x, int y, CCPoint &p)
{
	float dx = p.x - x;
	float dy = p.y - y;
	bool r= dx*dx + dy*dy < RADIUS_SPHERE*RADIUS_SPHERE;
	return r;
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
	stt=0;
	if(CCDirector::sharedDirector()->isPaused()) return false;
	CCLOG("%f %f",pTouch->getLocation().x,pTouch->getLocation().y);
	if(stt<6){	
		checkClick(pTouch->getLocation());
	}
		return true;
}

void CSkillLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if(stt<6){	
		checkClick(pTouch->getLocation());
	}

}
void CSkillLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
	calculateSkill();
	initVar();
	removeLayer();
	

}
void CSkillLayer::update(float dt)
{

}

void CSkillLayer::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	this->setTouchEnabled(true);
}
void CSkillLayer::initVar()
{
	stt=0;
	for(int i=0;i<5;i++){
		//arr_isTouched[i]=false;
		arr_PointTouched[i]=0;
	}
}

void CSkillLayer::checkClick(CCPoint &p)
{
	if(arr_PointTouched[stt-1]!=1) 
	{
		if(inAreaSphere(CENTRAL_X1,CENTRAL_Y1,p)){
		arr_PointTouched[stt]=1;
		stt++;
		}
	}
	if(arr_PointTouched[stt-1]!=2) {
		if(inAreaSphere(CENTRAL_X2,CENTRAL_Y2,p))
		{
			arr_PointTouched[stt]=2;
			stt++;
		}
		
	}
	if(arr_PointTouched[stt-1]!=3) {
		if(inAreaSphere(CENTRAL_X3,CENTRAL_Y3,p))
		{
			arr_PointTouched[stt]=3;
			stt++;
		}
		
	}
	if(arr_PointTouched[stt-1]!=4) {
		if(inAreaSphere(CENTRAL_X4,CENTRAL_Y4,p))
		{
			arr_PointTouched[stt]=4;
			stt++;
		}
	}
	if(arr_PointTouched[stt-1]!=5) {
		if(inAreaSphere(CENTRAL_X5,CENTRAL_Y5,p))
		{
			arr_PointTouched[stt]=5;
			stt++;
		}
		
	}
}
int CSkillLayer::pow(int x,int n)
{
	int r=1;
	for(int i=n;i>0;i--)
	{
		r*=x;
	}
	return r;
}
int CSkillLayer::getResultSkill()
{
	int temp = resultSkill;
	resultSkill=-1;
	return temp;
}
void CSkillLayer::calculateSkill()
{
	int chainClick=0;
	for(int i=0;i<stt;i++)
	{
		chainClick+= arr_PointTouched[i]*pow(10,stt-i-1);
	}
	switch(chainClick){
	case 2142: 
		resultSkill=SKILL_1;
		break;
	case 4314: 
		resultSkill=SKILL_2;
		break;
	case 5425: 
		resultSkill=SKILL_3;
		break;
	case 413524: 
		resultSkill=SKILL_4;
		break;
	}
	int t=1;
	resultSkill=-1;
}
void CSkillLayer::removeLayer()
{
	CGamePlay::removeLayerByTag(TAG_GAMEPLAY_SKILL_LAYER);
	CGamePlay::removeLayerByTag(TAG_GAMEPLAY_COLOR_LAYER);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(CGamePlay::pGameObjectLayer, TOUCH_PRIORITY_MAIN_LAYER , true);
	CGamePlay::pGameObjectLayer->setTouchEnabled(true);
}

