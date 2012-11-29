#include "Monster.h"
#include "cocos2d.h"
//#include "GameObjectLayer.h"

CMonster::CMonster(TypeMonster type, MonsterLevel level, int height){	
	timeMove = 0.0f;
	typeMove = MOVE;
	setDelayTimeDie(0.0f);
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	/*int minDuration = (int)1.0;
	int maxDuration = (int)4.0;
	int rangeDuration = maxDuration - minDuration;
	srand(time(NULL));
	//CCRANDOM_0_1()
	int actualDuration = (rand()%rangeDuration) + minDuration;*/
	setPos(height);

	setPosition(ccp(s.width,getPos()));


	setLevel(level);
	setType(type);
	init();
}
CMonster::CMonster(){
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
		setCoin(LEVEL2_MONSTER_COIN);
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
		setCoin(LEVEL3_MONSTER_COIN);
		if(getType()==WATER_MONSTER){
			m_sprite = new CMySprite(LEVEL3_WATER_MONSTER_TEXTURE);
		}else{
			m_sprite = new CMySprite(LEVEL3_FIRE_MONSTER_TEXTURE);
		}
		break;
	}
	//init here
	m_sprite->setPosition(ccp(0, 0));
	m_spriteCoin = new CMySprite(COIN);
	m_spriteCoin->setPosition(ccp(0,0));
	addChild(m_sprite);
	addChild(m_spriteCoin);
	m_spriteCoin->setVisible(false);
	moveMonster();
	return true;
}



void CMonster::onExit()
{
	CCSprite::onExit();

}

void CMonster::moveMonster(){
	timeMove = timeMove + getSpeed()/10.0f;
	if(timeMove>getSpeed()){
		typeMove = ATTACK;
	}
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	runAction(CCMoveBy::create(getSpeed()/10.0f,ccp(-s.width*3/45.0f,0)));
	m_sprite->PlayAnimation(0,getSpeed()/10.0f, 1, false, CCCallFuncN::actionWithTarget(this, callfuncN_selector(CMonster::monsterAction)));
}

void CMonster::attackTower()
{
	m_sprite->PlayAnimation(1,1.5f,1,false,CCCallFuncN::actionWithTarget(this,callfuncN_selector(CMonster::monsterAction)));
}

void CMonster::attackDone(CCNode* sender)
{
	//monsterAction();
	m_spriteCoin->setVisible(true);
	m_spriteCoin->PlayAnimation(0,1.0f,1.75,false,CCCallFuncN::actionWithTarget(this,callfuncN_selector(CMonster::collectCoin)));
}

void CMonster::monsterDie()
{
	//typeMove = MOVE;
	m_sprite->PlayAnimation(3,1.0f,1,false,CCCallFuncN::actionWithTarget(this,callfuncN_selector(CMonster::attackDone)));
}

void CMonster::hitMonster()
{
	if(timeMove>getSpeed()){
		typeMove = ATTACK;
	}else{
		typeMove = MOVE;
	}
	m_sprite->PlayAnimation(2,0.3f,1,false,CCCallFuncN::actionWithTarget(this,callfuncN_selector(CMonster::monsterAction)));
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

void CMonster::monsterAction(CCNode* sender)
{
	switch(typeMove){
	case MOVE:
		moveMonster();
		break;
	case ATTACK:
		attackTower();
		break;
	case HIT:
		hitMonster();
		break;
	default:
		monsterDie();
		break;
	}
}


void CMonster::collectCoin( CCNode* sender )
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_sprite->setVisible(false);
	m_spriteCoin->runAction(CCSequence::create(
		CCMoveBy::create(1.0f,ccp(s.width/7-getPosition().x,s.height*6/7-getPosition().y)),
		CCCallFuncN::actionWithTarget(this,callfuncN_selector(CMonster::collectDone)),
		NULL));
}

void CMonster::collectDone( CCNode * sender )
{
	m_spriteCoin->setVisible(false);
}
