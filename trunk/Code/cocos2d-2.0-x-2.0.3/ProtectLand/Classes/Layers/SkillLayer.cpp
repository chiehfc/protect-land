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


bool CSkillLayer::init()
{
	if (!CCLayer::init())
	{		
		return false;
	}
	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 10 , true);
	initVar();
	addSphere(m_sprite1,"Skill\\Skill-Kim.png",CENTRAL_X1,CENTRAL_Y1);
	addSphere(m_sprite2,"Skill\\Skill-Tho.png",CENTRAL_X2,CENTRAL_Y2);
	addSphere(m_sprite3,"Skill\\Skill-Hoa.png",CENTRAL_X3,CENTRAL_Y3);
	addSphere(m_sprite4,"Skill\\Skill-Moc.png",CENTRAL_X4,CENTRAL_Y4);
	addSphere(m_sprite5,"Skill\\Skill-Thuy.png",CENTRAL_X5,CENTRAL_Y5);
	resultSkill = -1;
	m_timer = 0;
	arr_PointNumber[0] = ccp(CENTRAL_X1,CENTRAL_Y1);
	arr_PointNumber[1] = ccp(CENTRAL_X2,CENTRAL_Y2);
	arr_PointNumber[2] = ccp(CENTRAL_X3,CENTRAL_Y3);
	arr_PointNumber[3] = ccp(CENTRAL_X4,CENTRAL_Y4);
	arr_PointNumber[4] = ccp(CENTRAL_X5,CENTRAL_Y5);
	this->setTouchEnabled(true);

	randomPosition();

	scheduleUpdate();
	//this->schedule( schedule_selector(CSkillLayer::update));
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

bool CSkillLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent)
{
	stt = 0;
	//CCLOG("ccp(%d, %d)",(int)pTouch->getLocation().x, (int)pTouch->getLocation().y);
	//m_number->setPosition(pTouch->getLocation());
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
	//CCLOG("ccp(%d, %d)",(int)pTouch->getLocation().x, (int)pTouch->getLocation().y);
	//m_number->setPosition(pTouch->getLocation());
}
void CSkillLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
	calculateSkill();
	removeLayer();
	

}
void CSkillLayer::update(float dt)
{
	m_timer+=dt;
	if(m_timer>MAX_TIME_EXE_SKILL)
	{
		calculateSkill();
		removeLayer();
	}
}

void CSkillLayer::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(CGamePlay::pSkillLayer, 0, false);
	CGamePlay::pGameObjectLayer->setTouchEnabled(false);
	CGamePlay::setEnableMenu(false);
	CGamePlay::pSkillLayer->setTouchEnabled(true);
	
}

void CSkillLayer::initVar()
{
	m_timer=0;
	stt=0;
	for(int i=0;i<5;i++){
		arr_isTouched[i] = false;
		arr_exit[i] = false;
		arr_PointTouched[i] = 0;
		arr_PointCheck[i]= -1;
	}
}

void CSkillLayer::checkClick(CCPoint &p)
{
	if(arr_PointTouched[stt-1]!=0) 
	{
		if(inAreaSphere(CENTRAL_X1,CENTRAL_Y1,p)){
			arr_PointTouched[stt]=0;
			stt++;
			if(!arr_isTouched[0])
			{
				arr_isTouched[0] = true;
				removeChild(m_sprite1,true);
				addSphere(m_sprite1,"Skill\\Skill-Kim2.png",CENTRAL_X1,CENTRAL_Y1);
			}
			
		}
	}
	if(arr_PointTouched[stt-1]!=1) {
		if(inAreaSphere(CENTRAL_X2,CENTRAL_Y2,p))
		{
			arr_PointTouched[stt]=1;
			stt++;
			if(!arr_isTouched[1])
			{
				arr_isTouched[1] = true;
				removeChild(m_sprite2,true);
				addSphere(m_sprite2,"Skill\\Skill-Tho2.png",CENTRAL_X2,CENTRAL_Y2);
			}
		}
		
	}
	if(arr_PointTouched[stt-1]!=2) {
		if(inAreaSphere(CENTRAL_X3,CENTRAL_Y3,p))
		{
			arr_PointTouched[stt]=2;
			stt++;
			if(!arr_isTouched[2])
			{
				arr_isTouched[2] = true;
				removeChild(m_sprite3,true);
				addSphere(m_sprite3,"Skill\\Skill-Hoa2.png",CENTRAL_X3,CENTRAL_Y3);
			}
		}
		
	}
	if(arr_PointTouched[stt-1]!=3) {
		if(inAreaSphere(CENTRAL_X4,CENTRAL_Y4,p))
		{
			arr_PointTouched[stt]=3;
			stt++;
			if(!arr_isTouched[3])
			{
				arr_isTouched[3] = true;
				removeChild(m_sprite4,true);
				addSphere(m_sprite4,"Skill\\Skill-Moc2.png",CENTRAL_X4,CENTRAL_Y4);
			}
		}
	}
	if(arr_PointTouched[stt-1]!=4) {
		if(inAreaSphere(CENTRAL_X5,CENTRAL_Y5,p))
		{
			arr_PointTouched[stt]=4;
			stt++;
			if(!arr_isTouched[4])
			{
				arr_isTouched[4] = true;
				removeChild(m_sprite5,true);
				addSphere(m_sprite5,"Skill\\Skill-Thuy2.png",CENTRAL_X5,CENTRAL_Y5);
			}
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
	int numberPointOK=0;
	for(int i=0;i<stt;i++)
	{
		if(arr_PointTouched[i] == arr_PointCheck[i])
		{
			numberPointOK++;
		}
		else
		{
			break;
		}
	}
	resultSkill=-1;
	switch(numberPointOK){
	case 3: 
		resultSkill=SKILL_1;
		break;
	case 4: 
		resultSkill=SKILL_2;
		break;
	case 5: 
		resultSkill=SKILL_3;
		break;
	case 6: 
		resultSkill=SKILL_4;
		break;
	}
	
}
void CSkillLayer::removeLayer()
{
	initVar();
	((CGameObjectLayer*)CGamePlay::pGameObjectLayer)->m_bIsFinshChooseSkill = true;
	((CGameObjectLayer*)CGamePlay::pGameObjectLayer)->m_iTypeSkillReturn=getResultSkill();
	CGamePlay::removeLayerByTag(TAG_GAMEPLAY_SKILL_LAYER);
	CGamePlay::removeLayerByTag(TAG_GAMEPLAY_COLOR_LAYER);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(CGamePlay::pGameObjectLayer, TOUCH_PRIORITY_MAIN_LAYER , true);
	CGamePlay::pGameObjectLayer->setTouchEnabled(true);
	CGamePlay::setEnableMenu(true);

}

void CSkillLayer::addLabel( CCLabelBMFont **pLabel, ccColor3B &color, int width, CCPoint &position,char* str,float scale )
{
	*pLabel = CCLabelBMFont::create(str, "fonts/myFont.fnt",width );

	(*pLabel)->setColor(color);
	(*pLabel)->setScale(scale);

	(*pLabel)->setAnchorPoint(ccp(0, 0));
	(*pLabel)->setPosition( position);
	this->addChild(*pLabel, 2);
}

void CSkillLayer::randomPosition()
{
	int position = 0;
	char buf[2];
	for(int i=1; i<6; i++)
	{
		position = getAvailabePosition();
		arr_PointCheck[i-1] = position;
		sprintf(buf,"%d",i);
		addLabel(&m_number,ccc3(255,255,255),10,arr_PointNumber[position],buf,2.0f);
	}
	arr_PointCheck[5] = arr_PointCheck[0];
	

}

int CSkillLayer::randomNumber(int firstPos, int secondPos)
{
	int minDuration = firstPos;
	int maxDuration = secondPos;
	int rangeDuration = maxDuration - minDuration;
	//srand(time(NULL));
	//CCRANDOM_0_1()
	int actualDuration = (rand()%rangeDuration) + minDuration;
	return actualDuration;
}
int CSkillLayer::getAvailabePosition()
{
	int position = -1;
	position = randomNumber(0,4);
	while(arr_exit[position]){
		position = (position+1)%5;
	}
	arr_exit[position] = true;
	return position;
	
}
