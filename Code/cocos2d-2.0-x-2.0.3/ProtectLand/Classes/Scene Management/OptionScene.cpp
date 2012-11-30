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
	pCloseItem->setPosition( ccp( pCloseItem->getContentSize().width/2+15*size.width/WIDTH_SCREEN_STANDARD,  pCloseItem->getContentSize().height/2+15*size.height/HEIGHT_SCREEN_STANDARD) );
	//pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2) );

	// create menu, it's an autorelease object
	pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu,1);

	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::create("GLBG.png");
	pSprite->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pSprite->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	// position the sprite on the center of the screen
	pSprite->setPosition( ccp(size.width/2, size.height/2) );

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);
	CCSprite* pOptionName = CCSprite::create("option_name.png");
	CCSize sizeOptionName = pOptionName->getContentSize();
	pOptionName->setPosition(ccp(sizeOptionName.width/2*SCREEN_WIDTH_RATIO_PORT, size.height - sizeOptionName.height/2*SCREEN_HEIGHT_RATION_PORT));
	this->addChild(pOptionName);
	//////////////////////////////////////////////////////////////////////////
	pSoundItemOn = CCMenuItemImage::create(
		"option_soundon.png",
		"option_soundon_selected.png",
		this,
		menu_selector(COptionScene::soundOnCallback));
	pSoundItemOn->setPosition( ccp(size.width/2 , size.height/2) );
	//////////////////////////////////////////////////////////////////////////
	pSoundItemOff = CCMenuItemImage::create(
		"option_soundoff.png",
		"option_soundoff_selected.png",
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
		"option_resetlevel.png",
		"option_resetlevel_selected.png",
		this,
		menu_selector(COptionScene::resetLevelCallback));
	pResetLevelItem->setPosition(ccp(size.width/2 , size.height/2 - pSoundItemOn->getContentSize().height/2 - pResetLevelItem->getContentSize().height/2 - 50*SCREEN_HEIGHT_RATION_PORT) );
	pMenu->addChild(pResetLevelItem);

	
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
	
}

void COptionScene::PopupYesCallback( CCObject* pSender )
{
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_CLICK_1);
}

void COptionScene::PopupNoCallback( CCObject* pSender )
{
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_CLICK_1);
	this->pMenu->setEnabled(true);
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
