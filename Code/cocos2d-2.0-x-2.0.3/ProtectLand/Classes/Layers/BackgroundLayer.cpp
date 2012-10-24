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
	CCSprite* pSprite = CCSprite::create("GLBG.png");
	pSprite->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pSprite->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	pSprite->setPosition( ccp(size.width/2, size.height/2) );
	this->addChild(pSprite, 0);
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