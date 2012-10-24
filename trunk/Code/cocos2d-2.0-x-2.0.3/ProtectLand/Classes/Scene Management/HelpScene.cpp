#include "HelpScene.h"
#include "MainMenuScene.h"
#include "AudioManager.h"
#include "IncludeHelper.h"
USING_NS_CC;

CCScene* CHelpScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	CHelpScene *layer = CHelpScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool CHelpScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	this->m_runtime = 0;

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"MainMenuNormal.png",
		"MainMenuSelected.png",
		this,
		menu_selector(CHelpScene::menuMainMenuCallback));
	pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2) );

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu,1);
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	this->_label = CCLabelTTF::create("Help scene: 0.00000", "Arial", 24);
	this->_label->setPosition( ccp(size.width / 2, size.height - 50) );
	this->addChild(this->_label,1);



	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::create("BackGround.png");
	pSprite->setScaleX((float)size.width/WIDTH_SCREEN);
	pSprite->setScaleY((float)size.height/HEIGHT_SCREEN);
	// position the sprite on the center of the screen
	pSprite->setPosition( ccp(size.width/2, size.height/2) );

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);
	this->schedule(schedule_selector(CHelpScene::update));
	return true;
}
void CHelpScene::update(float dt){

	this->m_runtime ++;
	char buf[20] = "Help scene: ";
	sprintf(&buf[12], "%d", this->m_runtime);
	this->_label->setString(buf);
	
}
void CHelpScene::render(){

}
void CHelpScene::exit(){

}

void CHelpScene::menuMainMenuCallback(CCObject* pSender)
{
	CAudioManager::instance()->playEff(SOUND_CLICK_1);
	/*CCScene* mainmenuScene  = CMainMenuScene::scene();
	CCDirector::sharedDirector()->replaceScene(mainmenuScene);*/
	CCScene* mainmenuScene = CMainMenuScene::scene();
	CCScene* pScene = CCTransitionFade::create(TRANSITION_DURATION, mainmenuScene);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}  
}
