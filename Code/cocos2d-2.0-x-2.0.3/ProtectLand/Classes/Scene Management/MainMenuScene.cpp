#include "MainMenuScene.h"
#include "PositionConfig.h"

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
	//create menu
	m_pMenu = CCMenu::create(NULL, NULL);
	m_pMenu->setPosition( CCPointZero );

	//Button play
	{
		CCMenuItemImage *pPlayButton = CCMenuItemImage::create(
			"MainMenuScene\\play1.png",
			"MainMenuScene\\play2.png",
			this,
			menu_selector(CMainMenuScene::menuNewgameCallback));
		pPlayButton->setPosition(LOCATION_BUTTON_PLAY);
		m_pMenu->addChild(pPlayButton);
	}

	////Button Exit
	{
		CCMenuItemImage *pExitButton = CCMenuItemImage::create(
			"MainMenuScene\\exit1.png",
			"MainMenuScene\\exit2.png",
			this,
			menu_selector(CMainMenuScene::menuCloseCallback));
		pExitButton->setPosition(LOCATION_BUTTON_EXIT);
		m_pMenu->addChild(pExitButton);
	}
	
	//BUtton About
	{
		CCMenuItemImage *pAboutButton = CCMenuItemImage::create(
			"MainMenuScene\\about1.png",
			"MainMenuScene\\about2.png",
			this,
			menu_selector(CMainMenuScene::menuAboutCallback));
		pAboutButton->setPosition(LOCATION_BUTTON_ABOUT);
		m_pMenu->addChild(pAboutButton);
	}

	//Button Option
	{
		CCMenuItemImage *pOptionsButton = CCMenuItemImage::create(
			"MainMenuScene\\option1.png",
			"MainMenuScene\\option2.png",
			this,
			menu_selector(CMainMenuScene::menuOptionsCallback));
		pOptionsButton->setPosition(LOCATION_BUTTON_OPTION);
		m_pMenu->addChild(pOptionsButton);
	}

	//Button Help
	{
		CCMenuItemImage *pHelpButton = CCMenuItemImage::create(
			"MainMenuScene\\help1.png",
			"MainMenuScene\\help2.png",
			this,
			menu_selector(CMainMenuScene::menuHelpCallback));
		pHelpButton->setPosition(LOCATION_BUTTON_HELP);
		m_pMenu->addChild(pHelpButton);
	}
	
	this->addChild(m_pMenu, 1);



	//Background
	CCSprite* pSprite = CCSprite::create("MainMenuScene\\protectlane.png");
	pSprite->setPosition( ccp(size.width/2, size.height/2) );
	this->addChild(pSprite, 0);

	//Animation Fire
	CMySprite* pAnimFire=new CMySprite("Tower\\tower.sprite");
	pAnimFire->setPosition(LOCATION_ANIM_FIRE);
	pAnimFire->setScale(1.5f);
	this->addChild(pAnimFire);
	pAnimFire->PlayAnimation(FIRE_TOWER, 0.4f, true, false);


	/************************************************************************/
	/* Pop up Menu                                                          */
	/************************************************************************/
	CCMenuItemImage *pYesItem = CCMenuItemImage::create(
		"Button\\yes-down.png",
		"Button\\yes-up.png",
		this,
		menu_selector(CMainMenuScene::PopupYesCallback));
	CCMenuItemImage *pNoItem = CCMenuItemImage::create(
		"Button\\no-down.png",
		"Button\\no-up.png",
		this,
		menu_selector(CMainMenuScene::PopupNoCallback));

	pYesItem->setPosition(MyChangePointScreen(130.0f, - 50.0f));
	pNoItem->setPosition(MyChangePointScreen(-130.0f,  - 50.0f));

	m_pBlurLayer = CCLayerColor::create();
	m_pBlurLayer->setOpacityModifyRGB(true);
	m_pBlurLayer->setColor(ccc3(0,0,0));
	m_pBlurLayer->setOpacity(150);
	this->addChild(m_pBlurLayer, ZORDER_GAMEPLAY_COLOR_LAYER, TAG_GAMEPLAY_COLOR_LAYER);
	
	//set position of Popup
	pPopupBackground = CCSprite::create("Button\\popup1.png");
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
