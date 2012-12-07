#include "HelpScene.h"
#include "MainMenuScene.h"
#include "AudioManager.h"
#include "PositionConfig.h"
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

	//insert menu
	CCMenu* m_pMenu = CCMenu::create(NULL, NULL);
	m_pMenu->setPosition( CCPointZero );

	//Button Back
	{
		CCMenuItemImage *pBackButton = CCMenuItemImage::create(
			"Button\\back_down.png",
			"Button\\back_up.png",
			this,
			menu_selector(CAboutScene::menuMainMenuCallback));
		pBackButton->setPosition(LOCATION_BUTTON_BACK);
		m_pMenu->addChild(pBackButton);
	}
	this->addChild(m_pMenu, 1);

	this->schedule(schedule_selector(CHelpScene::update));
	return true;
}
void CHelpScene::update(float dt){

}
void CHelpScene::render(){

}
void CHelpScene::exit(){

}

void CHelpScene::menuMainMenuCallback(CCObject* pSender)
{
	CAudioManager::instance()->playEff(SOUND_BUTTON);
	CCScene* mainmenuScene = CMainMenuScene::scene();
	CCScene* pScene = CCTransitionFade::create(TRANSITION_DURATION, mainmenuScene);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}  
}
