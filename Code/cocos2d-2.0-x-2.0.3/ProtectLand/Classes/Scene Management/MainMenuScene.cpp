#include "MainMenuScene.h"

CCScene* CMainMenuScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	CMainMenuScene *layer = CMainMenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool CMainMenuScene::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	//New game menu item
	if((!CAudioManager::instance()->isBGMusicPlaying()) && CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playBGMusic(SOUND_BACKGROUND_MAIN, true);

	CCMenuItemImage *pPlayItem = CCMenuItemImage::create(
		"StartNormal.png",
		"StartSelected.png",
		this,
		menu_selector(CMainMenuScene::menuNewgameCallback));

	pPlayItem->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pPlayItem->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);

	pPlayItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width*330/WIDTH_SCREEN_STANDARD , CCDirector::sharedDirector()->getWinSize().height*300/HEIGHT_SCREEN_STANDARD) );

	//// create menu, it's an autorelease object
	m_pMenu = CCMenu::create(pPlayItem, NULL);
	m_pMenu->setPosition( CCPointZero );
	//
	////Continue menu item
	CCMenuItemImage *pContinueItem = CCMenuItemImage::create(
		"QuitNormal.png",
		"QuitSelected.png",
		this,
		menu_selector(CMainMenuScene::menuCloseCallback));

	pContinueItem->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pContinueItem->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);

	pContinueItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width*650/WIDTH_SCREEN_STANDARD, CCDirector::sharedDirector()->getWinSize().height*150/HEIGHT_SCREEN_STANDARD));
	m_pMenu->addChild(pContinueItem);
	//
	////About menu item
	CCMenuItemImage *pAboutItem = CCMenuItemImage::create(
		"AboutNormal.png",
		"AboutSelected.png",
		this,
		menu_selector(CMainMenuScene::menuAboutCallback));

	pAboutItem->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pAboutItem->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);

	pAboutItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width*400/WIDTH_SCREEN_STANDARD, CCDirector::sharedDirector()->getWinSize().height*180/HEIGHT_SCREEN_STANDARD));
	m_pMenu->addChild(pAboutItem);



	CCMenuItemImage *pOptionsItem = CCMenuItemImage::create(
		"OptionNormal.png",
		"OptionSelected.png",
		this,
		menu_selector(CMainMenuScene::menuOptionsCallback));

	pOptionsItem->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pOptionsItem->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);

	pOptionsItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width*570/WIDTH_SCREEN_STANDARD, CCDirector::sharedDirector()->getWinSize().height*280/HEIGHT_SCREEN_STANDARD));
	m_pMenu->addChild(pOptionsItem);
	//
	/*
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(CMainMenuScene::menuCloseCallback));
	pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
	pMenu->addChild(pCloseItem);
	*/
	//
	this->addChild(m_pMenu, 1);



	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::create("MainMenuBG.png");
	pSprite->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pSprite->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	// position the sprite on the center of the screen
	pSprite->setPosition( ccp(size.width/2, size.height/2) );

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);

	/************************************************************************/
	/* Pop up Menu                                                          */
	/************************************************************************/
	CCMenuItemImage *pYesItem = CCMenuItemImage::create(
		"icon_tick.png",
		"icon_tick_selected.png",
		this,
		menu_selector(CMainMenuScene::PopupYesCallback));
	CCMenuItemImage *pNoItem = CCMenuItemImage::create(
		"icon_x.png",
		"icon_x_selected.png",
		this,
		menu_selector(CMainMenuScene::PopupNoCallback));

	pYesItem->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pYesItem->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	pNoItem->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pNoItem->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	pYesItem->setPosition(MyChangePointScreen(130.0f, - 50.0f));
	pNoItem->setPosition(MyChangePointScreen(-130.0f,  - 50.0f));

	m_pBlurLayer = CCLayerColor::create();
	m_pBlurLayer->setOpacityModifyRGB(true);
	m_pBlurLayer->setColor(ccc3(0,0,0));
	m_pBlurLayer->setOpacity(150);
	this->addChild(m_pBlurLayer, ZORDER_GAMEPLAY_COLOR_LAYER, TAG_GAMEPLAY_COLOR_LAYER);
	
	//set position of Popup
	pPopupBackground = CCSprite::create("popup_quitgame.png");
	pPopupBackground->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pPopupBackground->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	pPopupBackground->setPosition(ccp( size.width/2, size.height/2 ));	
	this->addChild(pPopupBackground,ZORDER_GAMEPLAY_COLOR_LAYER + 1, TAG_GAMEPLAY_COLOR_LAYER + 1);

	m_pPopupMenu = CCMenu::create(pYesItem, NULL);
	m_pPopupMenu->addChild(pNoItem);	
	this->addChild(m_pPopupMenu,ZORDER_GAMEPLAY_COLOR_LAYER + 1, TAG_GAMEPLAY_COLOR_LAYER + 1);

	EnablePopupMenu(false);

	schedule(schedule_selector(CMainMenuScene::update));
	CCDirector::sharedDirector()->getTouchDispatcher()->removeAllDelegates();
	setTouchEnabled(false);
	return true;
}

//
//void CMainMenuScene::exit()
//{
//	this->removeAllChildrenWithCleanup(true);
//}

void CMainMenuScene::menuAboutCallback(CCObject* pSender)
{
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
	CAudioManager::instance()->playEff(SOUND_BUTTON);
	/*CCScene* aboutscene = CAboutScene::scene();
	CCDirector::sharedDirector()->replaceScene(aboutscene);*/
	CCScene* aboutscene = CAboutScene::scene();
	CCScene* pScene = CCTransitionCrossFade::create(TRANSITION_DURATION, aboutscene);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}  
	
}

void CMainMenuScene::menuContinueCallback(CCObject* pSender)
{
	//Error
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_BUTTON);
	CCScene *loadingScene = CLoadingScene::scene(MODE_CONTINUE);
	CCDirector::sharedDirector()->replaceScene(loadingScene);
}

void CMainMenuScene::menuHelpCallback(CCObject* pSender)
{
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_BUTTON);
	/*CCScene* helpscene = CHelpScene::scene();
	CCDirector::sharedDirector()->replaceScene(helpscene);*/
	CCScene* helpscene = CHelpScene::scene();	
	CCScene* pScene = CCTransitionCrossFade::create(TRANSITION_DURATION, helpscene);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

void CMainMenuScene::menuNewgameCallback(CCObject* pSender)
{
    //Error
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
	CAudioManager::instance()->playEff(SOUND_BUTTON);
	CCScene *loadingScene = CLoadingScene::scene(MODE_NEWGAME);
	CCDirector::sharedDirector()->replaceScene(loadingScene);

}

void CMainMenuScene::menuCloseCallback(CCObject* pSender)
{
	CAudioManager::instance()->playEff(SOUND_BUTTON);
	EnablePopupMenu(true);
	
}

void CMainMenuScene::menuOptionsCallback( CCObject* pSender )
{
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_BUTTON);
	CCScene* optionscene = COptionScene::scene();	
	CCScene* pScene = CCTransitionCrossFade::create(TRANSITION_DURATION, optionscene);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

void CMainMenuScene::EnablePopupMenu( bool value )
{
	m_pMenu->setEnabled(!value);
	m_pBlurLayer->setVisible(value);
	pPopupBackground->setVisible(value);
	m_pPopupMenu->setVisible(value);
	m_pPopupMenu->setEnabled(value);
}

void CMainMenuScene::PopupYesCallback( CCObject* pSender )
{
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_BUTTON);

	CGamePlay::destroy();
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void CMainMenuScene::PopupNoCallback( CCObject* pSender )
{
	CAudioManager::instance()->playEff(SOUND_BUTTON);
	EnablePopupMenu(false);
}

void CMainMenuScene::destroy()
{
	this->removeAllChildrenWithCleanup(true);
}
