#include "Monster.h"
#include "cocos2d.h"
//#include "GameObjectLayer.h"

CMonster::CMonster(TypeMonster type, MonsterLevel level){	
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	int minDuration = (int)1.0;
	int maxDuration = (int)4.0;
	int rangeDuration = maxDuration - minDuration;
	srand(time(NULL));
	//CCRANDOM_0_1()
	int actualDuration = (rand()%rangeDuration) + minDuration;
	setPos(actualDuration);

	setPosition(ccp(s.width,s.height/5*getPos()));


	setLevel(level);
	setType(type);
	init();
}
CMonster::CMonster(){
}
void CMonster::moveMonster(){
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	//addChild(m_spriteAttack);
	m_sprite->PlayAnimation(0,getSpeed()/10.0f, 10, false,CCCallFuncN::actionWithTarget(this,callfuncN_selector(CMonster::attackTower)));
	runAction(CCMoveBy::create(getSpeed(),ccp(-s.width*3/4,0)));
	//m_sprite->PlayAnimationToPosition(-s.width*3/4,0,getSpeed(),2,0.8f,false,CCCallFuncN::actionWithTarget(this,callfuncN_selector(CMonster::attackTower)));
}

CMonster::~CMonster(){

	m_sprite->release();
	//delete (m_arrPath);
}

bool CMonster::init()
{
	if (!CCSprite::init())
	{
		return false;
	}
	switch(getLevel()){
	case LEVEL1_MONSTER:
		setHP(LEVEL1_MONSTER_HP);
		setSpeed(LEVEL1_MONSTER_SPEED);
		setDamage(LEVEL1_MONSTER_DAMAGE);
		setPower(LEVEL1_MONSTER_POWER);
		setCoin(LEVEL1_MONSTER_COIN);
		if(getType()==WATER_MONSTER){
			m_sprite = new CMySprite(LEVEL1_WATER_MONSTER_TEXTURE);
		}else{
			m_sprite = new CMySprite(LEVEL1_FIRE_MONSTER_TEXTURE);
		}
		break;
	case LEVEL2_MONSTER:
		setHP(LEVEL2_MONSTER_HP);
		setSpeed(LEVEL2_MONSTER_SPEED);
		setDamage(LEVEL2_MONSTER_DAMAGE);
		setPower(LEVEL2_MONSTER_POWER);
		setCoin(LEVEL1_MONSTER_COIN);
		if(getType()==WATER_MONSTER){
			m_sprite = new CMySprite(LEVEL2_WATER_MONSTER_TEXTURE);
		}else{
			m_sprite = new CMySprite(LEVEL2_FIRE_MONSTER_TEXTURE);
		}
		break;
	case LEVEL3_MONSTER:
		setHP(LEVEL3_MONSTER_HP);
		setSpeed(LEVEL3_MONSTER_SPEED);
		setDamage(LEVEL3_MONSTER_DAMAGE);
		setPower(LEVEL3_MONSTER_POWER);
		setCoin(LEVEL1_MONSTER_COIN);
		if(getType()==WATER_MONSTER){
			m_sprite = new CMySprite(LEVEL3_WATER_MONSTER_TEXTURE);
		}else{
			m_sprite = new CMySprite(LEVEL3_FIRE_MONSTER_TEXTURE);
		}
		break;
	}
	//init here

	//m_spriteAttack = m_sprite;
	//m_spriteDie = m_spriteAttack;
	m_sprite->setPosition(ccp(0, 0));
	addChild(m_sprite);
	moveMonster();
	return true;
}

void CMonster::onExit()
{
	CCSprite::onExit();

}

void CMonster::attackTower(CCNode* sender)
{
	m_sprite->PlayAnimation(1, 1.0f, 100, false, CCCallFuncN::actionWithTarget(this, callfuncN_selector(CMonster::attackDone)));
}

void CMonster::attackDone( CCNode* sender )
{
	
}

void CMonster::monsterDie()
{
	m_sprite->PlayAnimation(0,1.0f,100,false,CCCallFuncN::actionWithTarget(this,callfuncN_selector(CMonster::attackDone)));
}

void CMonster::hitMonster()
{

}

void CMonster::removeMonster()
{
	this->removeChild(m_sprite,false);
}

void CMonster::draw()
{
	/*ccDrawColor4F(1.0f, 0.0f, 0.0f, 1.0f);
	CCRect rect = getRectCurrentOfMonsters();
	ccDrawRect(rect.origin, ccpAdd(rect.origin, ccp(rect.size.width, rect.size.height)));
	ccDrawColor4F(1.0f, 1.0f, 1.0f, 1.0f);*/
}

cocos2d::CCRect CMonster::getRectCurrentOfMonsters()
{
	//set rect for check collison
	return CCRectMake(m_sprite->getPosition().x - m_sprite->getContentSize().width/2.0f, m_sprite->getPosition().y - m_sprite->getContentSize().height/2.0f, m_sprite->getContentSize().width, m_sprite->getContentSize().height);
}
