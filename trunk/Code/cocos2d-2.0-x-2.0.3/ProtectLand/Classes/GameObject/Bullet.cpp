#include "Bullet.h"


Bullet::Bullet(int type,CCSprite* p)
{
	m_iType = type;
	
	init(p);
	//setType(type);
	//setSprite(p);
}

bool Bullet::init(CCSprite * p)
{
	if (!CCSprite::init())
	{
		return false;
	}
	//init here
	
	//m_pSprite->setPosition(ccp(0,0));
	//this->setPosition(m_pSprite->getPosition());
	addChild(p);
	return true;
}

void Bullet::onExit()
{
	CCSprite::onExit();
}

Bullet::~Bullet()
{

}
