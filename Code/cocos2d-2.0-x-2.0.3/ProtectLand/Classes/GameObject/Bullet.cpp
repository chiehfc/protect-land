#include "Bullet.h"


Bullet::Bullet(int type,CCSprite* p)
{
	m_iType = type;
	
	init(p);
	//setType(type);
	//setSprite(p);
}

Bullet::Bullet()
{

}

bool Bullet::init(CCSprite * p)
{
	if (!CCSprite::init())
	{
		return false;
	}
	//init here
	m_sprite = p;
	addChild(m_sprite);
	
	
	return true;
}

void Bullet::onExit()
{
	CCSprite::onExit();
}

Bullet::~Bullet()
{

}

void Bullet::draw()
{
	/*ccDrawColor4F(1.0f, 0.0f, 0.0f, 1.0f);
	CCRect rect = getRectCurrentOfBullet();
	ccDrawRect(rect.origin, ccpAdd(rect.origin, ccp(rect.size.width, rect.size.height)));
	ccDrawColor4F(1.0f, 1.0f, 1.0f, 1.0f);*/
}

cocos2d::CCRect Bullet::getRectCurrentOfBullet()
{
	//set rect for check collison
	return CCRectMake(m_sprite->getPosition().x - m_sprite->getContentSize().width/2.0f, m_sprite->getPosition().y - m_sprite->getContentSize().height/2.0f, m_sprite->getContentSize().width, m_sprite->getContentSize().height);
}
