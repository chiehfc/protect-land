#include "Monster.h"
#include "cocos2d.h"
#include "PositionConfig.h"
#include "LevelManager.h"
//#include "GameObjectLayer.h"

CMonster::CMonster(TypeMonster type, MonsterLevel level, int height){
	timeMove = 0.0f;
	check1 = false;
	check2 = false;
	check3 = false;
	index = 1;
	setTimeAttackDelay(TIME_ATTACK_DELAY);
	setCurrentTime(0);
	setNumOfAttack(0);
	//settext("asd");
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
		setCointBonus(LEVEL1_MONSTER_COIN_BONUS);
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
		setCointBonus(LEVEL2_MONSTER_COIN_BONUS);
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
		setCointBonus(LEVEL3_MONSTER_COIN_BONUS);
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
	bloothOut1 = CCLabelTTF::labelWithString("","Arial",20);
	bloothOut2 = CCLabelTTF::labelWithString("","Arial",20);
	bloothOut3 = CCLabelTTF::labelWithString("","Arial",20);
	//CCLabelTTF * bloothOut = CCLabelTTF::labelWithString(gettext(),"Arial",20);
	addChild(bloothOut1);
	bloothOut1->setVisible(false);
	bloothOut1->setPosition(ccp(0,50));

	addChild(bloothOut2);
	bloothOut2->setVisible(false);
	bloothOut2->setPosition(ccp(0,50));

	addChild(bloothOut3);
	bloothOut3->setVisible(false);
	bloothOut3->setPosition(ccp(0,50));

	moveMonster();
	return true;
}

 

void CMonster::onExit()
{
	CCSprite::onExit();

}

void CMonster::moveMonster(){
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	timeMove = timeMove + getSpeed()/10.0f;
	if(getPosition().x<s.width/3.1f){
		typeMove = ATTACK;
	}
	//CCSize s = CCDirector::sharedDirector()->getWinSize();
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

void CMonster::monsterDie(int damage)
{
	//typeMove = MOVE;
	m_sprite->PlayAnimation(3,1.0f,1,false,CCCallFuncN::actionWithTarget(this,callfuncN_selector(CMonster::attackDone)));
	numberDamageIn(damage);
}

void CMonster::hitMonster(int damage)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	if(this->getPosition().x < s.width/3.1f){
		typeMove = ATTACK;
	}else{
		typeMove = MOVE;
	}
	m_sprite->stopAllActions();
	stopAllActions();
	m_sprite->PlayAnimation(2,0.3f,1,false,CCCallFuncN::actionWithTarget(this,callfuncN_selector(CMonster::monsterAction)));
	numberDamageIn(damage);
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
	/*case HIT:
		hitMonster();
		break;
	default:
		monsterDie();
		break;*/
	}
}


void CMonster::collectCoin( CCNode* sender )
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_sprite->setVisible(false);
	//m_spriteCoin->runAction(CCSequence::create(
	m_spriteCoin->PlayAnimationToPosition(LOCATION_COIN_ICON.x-getPosition().x, LOCATION_COIN_ICON.y-getPosition().y, 1.0f, 0, 0.2f, false, CCCallFuncN::actionWithTarget(this,callfuncN_selector(CMonster::collectDone)));
		//CCCallFuncN::actionWithTarget(this,callfuncN_selector(CMonster::collectDone)),
		//NULL));
	//m_spriteCoin->PlayAnimationToPosition(s.width/7-getPosition().x,s.height*6/7-getPosition().y,1.0f,0.2f,false,CCCallFuncN::actionWithTarget(this,callfuncN_selector(CMonster::collectDone)));
}

void CMonster::collectDone( CCNode * sender )
{
	m_spriteCoin->setVisible(false);
	CLevelManager::GetInstance()->GetLevelInformation()->m_iCoin += getCoin();
}

void CMonster::numberDamageIn(int damage)
{
	
	if(!check1){
		//index = 2;
		check1 = true;
		char text[250];
		sprintf(text,"-%d",damage);
		bloothOut1->setVisible(true);
		bloothOut1->setColor(ccRED);
		//bloothOut->sets
		bloothOut1->setString(text);
		bloothOut1->runAction(CCMoveBy::create(TIME_BLOOD_MOVE_SCALE,ccp(0,30)));
		bloothOut1->runAction(CCScaleBy::create(TIME_BLOOD_MOVE_SCALE,1.3f,1.3f));
		bloothOut1->runAction(CCSequence::create(CCFadeIn::create(TIME_BLOOD_FADE),CCFadeOut::create(TIME_BLOOD_FADE),CCCallFuncN::actionWithTarget(this,callfuncN_selector(CMonster::hurtDone1)),NULL));
	}else if(!check2){
		//index = 3;
		check2 = true;
		char text[250];
		sprintf(text,"-%d",damage);
		bloothOut2->setVisible(true);
		bloothOut2->setColor(ccRED);
		//bloothOut->sets
		bloothOut2->setString(text);
		bloothOut2->runAction(CCMoveBy::create(TIME_BLOOD_MOVE_SCALE,ccp(0,30)));
		bloothOut2->runAction(CCScaleBy::create(TIME_BLOOD_MOVE_SCALE,1.3f,1.3f));
		bloothOut2->runAction(CCSequence::create(CCFadeIn::create(TIME_BLOOD_FADE),CCFadeOut::create(TIME_BLOOD_FADE),CCCallFuncN::actionWithTarget(this,callfuncN_selector(CMonster::hurtDone2)),NULL));
	}else if(!check3){
		////index = 1;
		check3 = true;
		char text[250];
		sprintf(text,"-%d",damage);
		bloothOut3->setVisible(true);
		bloothOut3->setColor(ccRED);
		//bloothOut->sets
		bloothOut3->setString(text);
		bloothOut3->runAction(CCMoveBy::create(TIME_BLOOD_MOVE_SCALE,ccp(0,30)));
		bloothOut3->runAction(CCScaleBy::create(TIME_BLOOD_MOVE_SCALE,1.3f,1.3f));
		bloothOut3->runAction(CCSequence::create(CCFadeIn::create(TIME_BLOOD_FADE),CCFadeOut::create(TIME_BLOOD_FADE),CCCallFuncN::actionWithTarget(this,callfuncN_selector(CMonster::hurtDone3)),NULL));
	}
}

void CMonster::hurtDone1( CCNode* sender )
{
	check1=false;
	bloothOut1->setVisible(false);
	bloothOut1->runAction(CCMoveBy::create(0.1f,ccp(0,-30)));
	bloothOut1->runAction(CCScaleBy::create(0.1f,1.0f/1.3f,1.0f/1.3f));
}

void CMonster::hurtDone2( CCNode* sender )
{
	check2=false;
	bloothOut2->setVisible(false);
	bloothOut2->runAction(CCMoveBy::create(0.1f,ccp(0,-30)));
	bloothOut2->runAction(CCScaleBy::create(0.1f,1.0f/1.3f,1.0f/1.3f));
}

void CMonster::hurtDone3( CCNode* sender )
{
	check3=false;
	bloothOut3->setVisible(false);
	bloothOut3->runAction(CCMoveBy::create(0.1f,ccp(0,-30)));
	bloothOut3->runAction(CCScaleBy::create(0.1f,1.0f/1.3f,1.0f/1.3f));
}

int CMonster::attackTowerWithDamage(float m_time)
{
	if (typeMove == ATTACK)
	{
		if(getNumOfAttack()==0){
			setNumOfAttack(1);
			setCurrentTime(m_time);
			return getDamage();
		}else{
			if (m_time>=getCurrentTime()+getNumOfAttack()*getTimeAttackDelay())
			{
				setNumOfAttack(getNumOfAttack()+1);
				return getDamage();
			}
		}
	}
	return 0;
}
