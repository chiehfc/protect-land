#include "GameConfig.h"
#include "MenuLayer.h"
#include "GamePlay.h"
#include "MainMenuScene.h"
#include "SelectLevelScene.h"
#include "GameObjectLayer.h"
#include "SkillUpgradeScene.h"
#include "AudioManager.h"
//#include "SpritesLayer.h"
#include "IncludeHelper.h"
USING_NS_CC;
bool CMenuLayer::init()
{
	
	if(!CCLayer::init())
	{
		return false;
	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCMenuItemImage *pContinueItem = CCMenuItemImage::create(
		"Button\\button_play_down.png",
		"Button\\button_home_up.png",
		this,
		menu_selector(CMenuLayer::menuContinueCallback));
	pContinueItem->setPosition( ccp(size.width/2 , size.height/2 + size.height*120/HEIGHT_SCREEN_STANDARD));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pContinueItem, NULL);
	pMenu->setPosition( CCPointZero );

	CCMenuItemImage *pMainMenu = CCMenuItemImage::create(
		"Button\\button_return_down.png",
		"Button\\button_return_up.png",
		this,
		menu_selector(CMenuLayer::menuSkillUpgradeCallback));
	pMainMenu->setPosition(ccp(size.width/2, size.height/2 + size.height*40/HEIGHT_SCREEN_STANDARD));
	pMenu->addChild(pMainMenu);

	CCMenuItemImage *pMuteMenu = CCMenuItemImage::create(
		"Button\\button_home_down.png",
		"Button\\button_home_up.png",
		this,
		menu_selector(CMenuLayer::menuMainMenuCallback));
	pMuteMenu->setPosition(ccp(size.width/2, size.height/2 - size.height*40/HEIGHT_SCREEN_STANDARD));
	pMenu->addChild(pMuteMenu);
	this->addChild(pMenu);	
	return true;
}

/************************************************************************/
/* Menu call back funtions                                              */
/************************************************************************/

void CMenuLayer::menuContinueCallback(CCObject* pSender)
{
	/*CAudioManager::instance()->stopAllEff();
	CAudioManager::instance()->stopBGMusic();*/
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
	CAudioManager::instance()->playEff(SOUND_BUTTON);
	CGamePlay::removeLayerByTag(TAG_GAMEPLAY_MENU_LAYER);
	CGamePlay::removeLayerByTag(TAG_GAMEPLAY_COLOR_LAYER);
	CCDirector::sharedDirector()->resume();
	CGamePlay::setEnableMenu(true);
}
void CMenuLayer::menuSkillUpgradeCallback(CCObject* pSender)
{	
	CAudioManager::instance()->stopAllEff();
	CAudioManager::instance()->stopBGMusic();
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
	CAudioManager::instance()->playEff(SOUND_BUTTON);
	CCDirector::sharedDirector()->resume();
	CGamePlay::removeLayerByTag(TAG_GAMEPLAY_COLOR_LAYER);
	CGamePlay::removeLayerByTag(TAG_GAMEPLAY_MENU_LAYER);	
	CCScene* selectLevel = CSkillUpgradeScene::scene();	
	CCScene* pScene = CCTransitionFade::create(TRANSITION_DURATION, selectLevel);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
	CGamePlay::destroy();
}

void CMenuLayer::menuMainMenuCallback(CCObject* pSender)
{
	CAudioManager::instance()->stopAllEff();
	CAudioManager::instance()->stopBGMusic();
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_BUTTON);
	CCDirector::sharedDirector()->resume();
	CGamePlay::removeLayerByTag(TAG_GAMEPLAY_COLOR_LAYER);
	CGamePlay::removeLayerByTag(TAG_GAMEPLAY_MENU_LAYER);
	CGamePlay::destroy();
	CCScene *mainmenuScene = CMainMenuScene::scene();
	CCScene* pScene =CCTransitionFade::create(TRANSITION_DURATION, mainmenuScene, ccWHITE);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

void CMenuLayer::onExit()
{
	this->removeAllChildrenWithCleanup(true);
}


