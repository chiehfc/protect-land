#include "Monster.h"
#include "cocos2d.h"
//#include "GameObjectLayer.h"

CMonster::CMonster(MonsterType type, int level, float timemove, CCPointArray*array){	
	m_iType = type;
	switch (level)
	{
		case 1:
			m_iHp = 2;
			break;
		case 2:
			m_iHp = 4;
			break;
		case 3:
			m_iHp = 6;
			break;
	}
	m_fTimeMove = timemove;
	m_arrPath = array;
	init();
	}
CMonster::CMonster(){
}
void CMonster::moveMonster(){
	CCCatmullRomBy *action = CCCatmullRomBy::create(m_fTimeMove, m_arrPath);
	
    CCFiniteTimeAction *seq = CCSequence::create(action,NULL);
	this->setScale(0.2);
	// position the sprite on the center of the screen
	this->setPosition( ccp(50,50) );
	this->runAction(seq);
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

	//init here
	m_sprite = CMonster::create("images.jpg");
	m_sprite->setPosition(ccp(0, 0));
	addChild(m_sprite);
	return true;
}

void CMonster::onExit()
{
	CCSprite::onExit();
	
}

