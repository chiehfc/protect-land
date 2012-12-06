#include "OptionScene.h"
#include "IncludeHelper.h"
USING_NS_CC;

CCScene* COptionScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	COptionScene *layer = COptionScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool COptionScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	this->m_runtime = 0;

	// add a "close" icon to exit the progress. it's an autorelease object
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"Button\\back_down.png",
		"Button\\back_up.png",
		this,
		menu_selector(COptionScene::menuMainMenuCallback));
	pCloseItem->setPosition( ccp( pCloseItem->getContentSize().width/2 + 15*size.width/WIDTH_SCREEN_STANDARD,  pCloseItem->getContentSize().height/2+15*size.height/HEIGHT_SCREEN_STANDARD) );
	//pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2) );

	// create menu, it's an autorelease object
	pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu,1);

	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::create("OptionScene\\option-screen1.png");
	// position the sprite on the center of the screen
	pSprite->setPosition( ccp(size.width/2, size.height/2) );

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);
	CCSprite* pOptionName = CCSprite::create("OptionScene\\option.png");
	CCSize sizeOptionName = pOptionName->getContentSize();
	pOptionName->setPosition(ccp(sizeOptionName.width/2*SCREEN_WIDTH_RATIO_PORT, size.height - sizeOptionName.height/2*SCREEN_HEIGHT_RATION_PORT));
	this->addChild(pOptionName);
	//////////////////////////////////////////////////////////////////////////
	pSoundItemOn = CCMenuItemImage::create(
		"OptionScene\\sound_on1.png",
		"OptionScene\\sound-on.png",
		this,
		menu_selector(COptionScene::soundOnCallback));
	pSoundItemOn->setPosition( ccp(size.width/2 , size.height/2) );
	//////////////////////////////////////////////////////////////////////////
	pSoundItemOff = CCMenuItemImage::create(
		"OptionScene\\sound_off2.png",
		"OptionScene\\sound_off.png",
		this,
		menu_selector(COptionScene::soundOffCallback));
	pSoundItemOff->setPosition( ccp(size.width/2 , size.height/2) );
	
	pMenu->addChild(pSoundItemOn);
	pMenu->addChild(pSoundItemOff);
	//////////////////////////////////NEED MODIFY////////////////////////////////////////
	if(CAudioManager::instance()->GetSound() == SOUND_BG_EFF)
	{
		SetStateSoundButton(true);
		pSoundItemOff->setVisible(false);
	}
	else
	{
		SetStateSoundButton(false);
		pSoundItemOff->setVisible(true);
	}

	pResetLevelItem = CCMenuItemImage::create(
		"OptionScene\\reset-level1.png",
		"OptionScene\\reset-level.png",
		this,
		menu_selector(COptionScene::resetLevelCallback));
	pResetLevelItem->setPosition(ccp(size.width/2 , size.height/2 - pSoundItemOn->getContentSize().height/2 - pResetLevelItem->getContentSize().height/2 - 50) );
	pMenu->addChild(pResetLevelItem);

	CCMenuItemImage *pYesItem = CCMenuItemImage::create(
		"Button\\yes-down.png",
		"Button\\yes-up.png",
		this,
		menu_selector(COptionScene::PopupYesCallback));
	CCMenuItemImage *pNoItem = CCMenuItemImage::create(
		"Button\\no-down.png",
		"Button\\no-up.png",
		this,
		menu_selector(COptionScene::PopupNoCallback));
	
	pYesItem->setPosition(220.0f, 0.0f);
	pNoItem->setPosition(380.0f, 0.0f);

	m_pBlurLayer = CCLayerColor::create();
	m_pBlurLayer->setOpacityModifyRGB(true);
	m_pBlurLayer->setColor(ccc3(0,0,0));
	m_pBlurLayer->setOpacity(150);
	this->addChild(m_pBlurLayer, ZORDER_GAMEPLAY_COLOR_LAYER, TAG_GAMEPLAY_COLOR_LAYER);
	m_pBlurLayer->setVisible(false);
	//set position of Popup
	pPopupBackground = CCSprite::create("Button\\popup1.png");
	pPopupBackground->setPosition(ccp( size.width/2, size.height/2 ));
	pPopupBackground->setVisible(false);
	this->addChild(pPopupBackground,ZORDER_GAMEPLAY_COLOR_LAYER + 1, TAG_GAMEPLAY_COLOR_LAYER + 1);

	pPopupMenu = CCMenu::create(pYesItem, NULL);
	pPopupMenu->addChild(pNoItem);
	pPopupMenu->setVisible(false);
	pPopupMenu->setEnabled(false);
	this->addChild(pPopupMenu,ZORDER_GAMEPLAY_COLOR_LAYER + 1, TAG_GAMEPLAY_COLOR_LAYER + 1);

	this->schedule(schedule_selector(COptionScene::update));
	return true;
}
void COptionScene::update(float dt){

	/*this->m_runtime ++;
	char buf[20] = "Help scene: ";
	sprintf(&buf[12], "%d", this->m_runtime);
	this->_label->setString(buf);*/
	
}
void COptionScene::render(){

}
void COptionScene::exit(){

}

void COptionScene::menuMainMenuCallback(CCObject* pSender)
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

void COptionScene::soundOnCallback( CCObject* pSender )
{
	CAudioManager::instance()->stopBGMusic();
	CAudioManager::instance()->SetSound(SOUND_OFF);

	SetStateSoundButton(false);
}

void COptionScene::soundOffCallback( CCObject* pSender )
{
	CAudioManager::instance()->SetSound(SOUND_BG_EFF);
	CAudioManager::instance()->playBGMusic(SOUND_MAINMENU);

	SetStateSoundButton(true);
}

void COptionScene::resetLevelCallback( CCObject* pSender )
{
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_CLICK_1);
	pPopupMenu->setEnabled(true);
	this->pMenu->setEnabled(false);
	
	m_pBlurLayer->setVisible(true);
	pPopupMenu->setVisible(true);
	pPopupBackground->setVisible(true);
}

void COptionScene::PopupYesCallback( CCObject* pSender )
{
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_CLICK_1);
	pPopupMenu->setEnabled(false);
	this->pMenu->setEnabled(true);
	m_pBlurLayer->setVisible(false);
	pPopupMenu->setVisible(false);
	pPopupBackground->setVisible(false);
	CLevelManager::GetInstance()->ResetLevel("LevelInfo.txt");
}

void COptionScene::PopupNoCallback( CCObject* pSender )
{
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_CLICK_1);
	pPopupMenu->setEnabled(false);
	this->pMenu->setEnabled(true);
	m_pBlurLayer->setVisible(false);
	pPopupMenu->setVisible(false);
	pPopupBackground->setVisible(false);
}

void COptionScene::SetStateSoundButton( bool isSoundOn )
{
	if (isSoundOn != false)
	{
		//CAudioManager::instance()->playEff(SOUND_CLICK_1);
	}
	pSoundItemOn->setVisible(isSoundOn);
	pSoundItemOff->setVisible(!isSoundOn);
	
}