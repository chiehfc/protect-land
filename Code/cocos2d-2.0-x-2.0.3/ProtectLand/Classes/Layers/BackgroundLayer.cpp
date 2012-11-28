#include "GameConfig.h"
#include "BackgroundLayer.h"
#include "IncludeHelper.h"
USING_NS_CC;
bool CBackgroundLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pSprite = CCSprite::create("Background\\background_package_level_1.png");
	pSprite->setPosition( ccp(size.width/2, size.height/2) );
	this->addChild(pSprite, 0);
	return true;
}

void CBackgroundLayer::update(float dt)
{

}

void CBackgroundLayer::render()
{

}

void CBackgroundLayer::exit()
{

}