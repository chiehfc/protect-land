#include "MainMenuScene.h"
#include "GameOverScene.h"
#include "GamePlay.h"
#include "GameConfig.h"
#include "MySprite.h"
USING_NS_CC;


CCScene* CGameOverScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	CGameOverScene *layer = CGameOverScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
// on "init" you need to initialize your instance
bool CGameOverScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	// youlose animation

	this->m_runtime = 0;

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"MainMenuNormal.png",
		"MainMenuSelected.png",
		this,
		menu_selector(CGameOverScene::menuMainMenuCallback));
	pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2) );

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );

	CCMenuItemImage *pRestart = CCMenuItemImage::create(
		"RestartNormal.png",
		"RestartSelected.png",
		this,
		menu_selector(CGameOverScene::menuRestartCallback));
	pRestart->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2 - 100 , CCDirector::sharedDirector()->getWinSize().height/2) );
	pMenu->addChild(pRestart);

	CCMenuItemImage *pNext = CCMenuItemImage::create(
		"NextNormal.png",
		"NextSelected.png",
		this,
		menu_selector(CGameOverScene::menuNextCallback));
	pNext->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2 + 100 , CCDirector::sharedDirector()->getWinSize().height/2) );
	pMenu->addChild(pNext);


	this->addChild(pMenu,1);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	this->_label = CCLabelTTF::create("You Lose (~_~)", "Arial", 40);
	this->_label->setPosition( ccp(size.width / 2, size.height - 100) );
	this->addChild(this->_label,1);
	this->schedule(schedule_selector(CGameOverScene::update));
	
	CCSprite* pSprite = CCSprite::create("youloseBG.png");
	// position the sprite on the center of the screen
	pSprite->setPosition( ccp(size.width/2, size.height/2) );
	this->addChild(pSprite, 0);




	return true;
}
void CGameOverScene::update(float dt)
{



}
void CGameOverScene::render(){

}
void CGameOverScene::exit(){

}
void CGameOverScene::menuMainMenuCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->resume();
	CGamePlay::removeLayerByTag(TAG_GAMEPLAY_COLOR_LAYER);
	CGamePlay::removeLayerByTag(TAG_GAMEPLAY_WINLAYER);
	CGamePlay::destroy();
	CCScene *mainmenuScene = CMainMenuScene::scene();
	CCDirector::sharedDirector()->replaceScene(mainmenuScene);

}
void CGameOverScene::menuNextCallback( CCObject* pSender )
{

}
void CGameOverScene::menuRestartCallback( CCObject* pSender )
{
	CCDirector::sharedDirector()->resume();
	CGamePlay::destroy();
	CGamePlay::setLevel(CGamePlay::getLevel());
	CCScene *gamePlay = CGamePlay::scene();
	CCDirector::sharedDirector()->replaceScene(gamePlay);
}
