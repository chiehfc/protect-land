#include "GameConfig.h"
#include "MenuLayer.h"
#include "GamePlay.h"
#include "MainMenuScene.h"
#include "SelectLevelScene.h"
#include "GameObjectLayer.h"
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
		"ContinueSub.png",
		"ContinueSubSelected.png",
		this,
		menu_selector(CMenuLayer::menuContinueCallback));

	pContinueItem->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pContinueItem->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	pContinueItem->setPosition( ccp(size.width/2 , size.height/2 + size.height*120/HEIGHT_SCREEN_STANDARD));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pContinueItem, NULL);
	pMenu->setPosition( CCPointZero );

	//Skip Button
	{
		CCMenuItemImage *pSkipItem;
			
				pSkipItem = CCMenuItemImage::create(
					"SkipLevelSub.png",
					"SkipLevelSubSelected.png",
					this,
					menu_selector(CMenuLayer::menuSkipLevelCallback));
				
			pSkipItem->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
			pSkipItem->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
			pSkipItem->setPosition( ccp(size.width/2, size.height/2 + size.height*40/HEIGHT_SCREEN_STANDARD));
			pMenu->addChild(pSkipItem);
	}
	


	CCMenuItemImage *pMainMenu = CCMenuItemImage::create(
		"LevelSelectSub.png",
		"LevelSelectSubSelected.png",
		this,
		menu_selector(CMenuLayer::menuLevelSelectCallback));
	pMainMenu->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pMainMenu->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	pMainMenu->setPosition(ccp(size.width/2,size.height/2 - size.height*40/HEIGHT_SCREEN_STANDARD));
	pMenu->addChild(pMainMenu);

	CCMenuItemImage *pMuteMenu = CCMenuItemImage::create(
		"MainMenuSub.png",
		"MainMenuSubSelected.png",
		this,
		menu_selector(CMenuLayer::menuMainMenuCallback));
	pMuteMenu->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pMuteMenu->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	pMuteMenu->setPosition(ccp(size.width/2, size.height/2 - size.height*120/HEIGHT_SCREEN_STANDARD));
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
	CAudioManager::instance()->playEff(SOUND_CLICK_1);
	CGamePlay::removeLayerByTag(TAG_GAMEPLAY_MENU_LAYER);
	CGamePlay::removeLayerByTag(TAG_GAMEPLAY_COLOR_LAYER);
	CCDirector::sharedDirector()->resume();
	CGamePlay::setEnableMenu(true);
}
void CMenuLayer::menuLevelSelectCallback(CCObject* pSender)
{	
	CAudioManager::instance()->stopAllEff();
	CAudioManager::instance()->stopBGMusic();
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_CLICK_1);
	CCDirector::sharedDirector()->resume();
	CGamePlay::removeLayerByTag(TAG_GAMEPLAY_COLOR_LAYER);
	CGamePlay::removeLayerByTag(TAG_GAMEPLAY_MENU_LAYER);	
	CCScene* selectLevel = CSelectLevelScene::scene();	
	CCScene* pScene = CCTransitionFade::create(TRANSITION_DURATION, selectLevel);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
	CGamePlay::destroy();
}
void CMenuLayer::menuSkipLevelCallback(CCObject* pSender)
{
	
}
void CMenuLayer::menuMainMenuCallback(CCObject* pSender)
{
	CAudioManager::instance()->stopAllEff();
	CAudioManager::instance()->stopBGMusic();
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_CLICK_1);
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

