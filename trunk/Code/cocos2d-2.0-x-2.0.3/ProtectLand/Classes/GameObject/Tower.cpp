#include "Tower.h"
#include "cocos2d.h"

CTower::CTower(int hp){
	m_iHp = hp;
	init();
	//m_sprite->setPosition(ccp(0,0));
	//m_sprite->setScale(0.4);
}

CTower::~CTower(){
	
}

bool CTower::init()
{
	if (!CCSprite::init())
	{
		return false;
	}
	//init here
	m_sprite = CCSprite::create("tower.png");
	//this->setScale(0.4);
	this->setPosition(ccp(900,505));
	addChild(m_sprite);
	return true;
}

void CTower::onExit()
{
	CCSprite::onExit();
	//m_sprite->release();
}
