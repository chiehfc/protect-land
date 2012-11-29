#include "WinScene.h"
USING_NS_CC;

CCScene* CWinScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	CWinScene *layer = CWinScene::create();	
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool CWinScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	
	

	scheduleUpdate();
	CAudioManager::instance()->stopBGMusic();
	return true;
}
void CWinScene::update(float dt)
{
	
}
void CWinScene::render(){

}
void CWinScene::exit(){

}
void CWinScene::menuLevelSelectCallback(CCObject* pSender)
{
	CAudioManager::instance()->playEff(SOUND_CLICK_1);
	CGamePlay::destroy();
	CCScene *levelSelectScene = CSelectLevelScene::scene();
	CCScene* pScene =CCTransitionFade::create(TRANSITION_DURATION, levelSelectScene, ccWHITE);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}
void CWinScene::menuNextCallback( CCObject* pSender )
{
	CAudioManager::instance()->playEff(SOUND_CLICK_1);
	CGamePlay::destroy();	
	CCScene *gameSkillUpgradeScene = CSkillUpgradeScene::scene();
	CCScene* pScene = CCTransitionSlideInR::create(0.7f, gameSkillUpgradeScene);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	} 
}

void CWinScene::menuRestartCallback( CCObject* pSender )
{
	CAudioManager::instance()->playEff(SOUND_CLICK_1);
	CGamePlay::destroy();
	CCScene *gamePlay = CGamePlay::scene();
	CCDirector::sharedDirector()->replaceScene(gamePlay);
}

void CWinScene::playSound(CCNode* sender, void* data)
{
	CAudioManager::instance()->playEff(*((int*)data));
}
