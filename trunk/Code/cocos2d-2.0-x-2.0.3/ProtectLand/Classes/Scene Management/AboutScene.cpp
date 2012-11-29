#include "AboutScene.h"
#include "AudioManager.h"
#include "PositionConfig.h"
USING_NS_CC;

CCScene* CAboutScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	CAboutScene *layer = CAboutScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool CAboutScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//insert background
	CCSprite* pBackGround = CCSprite::spriteWithFile("Background\\about-screen.png");
	pBackGround->setPosition(ccp(size.width/2.0f, size.height/2.0f));
	this->addChild(pBackGround, 0);
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

	
	this->schedule(schedule_selector(CAboutScene::update));	
	return true;
}
void CAboutScene::update(float dt){

}
void CAboutScene::render(){

}
void CAboutScene::exit(){

}

void CAboutScene::menuMainMenuCallback(CCObject* pSender)
{
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_CLICK_1);
	CCScene* mainmenuScene = CMainMenuScene::scene();
	CCScene* pScene = CCTransitionFade::create(TRANSITION_DURATION, mainmenuScene);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}   
}

