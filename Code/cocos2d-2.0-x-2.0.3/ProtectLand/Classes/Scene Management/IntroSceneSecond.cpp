#include "IntroSceneSecond.h"
#include "IncludeHelper.h"
#include "MainMenuScene.h"

USING_NS_CC;
CCScene* IntroSceneSecond::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	IntroSceneSecond *layer = IntroSceneSecond::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool IntroSceneSecond::init()
{
	//
	//
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	this->m_runtime = 0;
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0 , false);
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	// add a "close" icon to exit the progress. it's an autorelease object
	m_bselected = true;
	char* msg;
	if(CAudioManager::instance()->GetSound() ==SOUND_BG_EFF)
		msg = "MusicOn.png";
	else
		msg = "Mute.png";
	m_pMute = CCMenuItemImage::create(
		msg,
		msg,
		this,
		menu_selector(IntroSceneSecond::buttonMuteCallBack));
	m_pMute->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	m_pMute->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	m_pMute->setPosition( ccp(size.width - size.width*40/WIDTH_SCREEN_STANDARD, size.height - size.height*40/HEIGHT_SCREEN_STANDARD) );
	CCMenu* pMenu = CCMenu::create(m_pMute, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu,1);
	

	//CCLabelTTF* pLabel = CCLabelTTF::create("Plash scene: 0.0s", "Arial", 24);
	/*this->_label = CCLabelTTF::create("IntroSecond scene: 0.00000", "Arial", 24);
	this->_label->setPosition( ccp(size.width / 2, size.height - 50) );
	this->addChild(this->_label,1);
*/
	/*CCLabelTTF* label = CCLabelTTF::create("Tap to skip", "Arial", 40);
	label->setPosition( ccp(size.width / 2, 100) );
	this->addChild(label,1);*/

	pSprite = CCSprite::create("IntroSecondBG.png");
	pSprite->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pSprite->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	// position the sprite on the center of the screen
	pSprite->setPosition( ccp(size.width/2, size.height/2) );

	pSprite2 = CCSprite::create("Intro3.png");
	pSprite2->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pSprite2->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	pSprite2->setPosition( ccp(size.width/2, size.height/2) );
	// add the sprite as a child to this layer
	this->addChild(pSprite2, 0);	
	this->addChild(pSprite, 0);	

	this->schedule(schedule_selector(IntroSceneSecond::update));
	return true;
}
void IntroSceneSecond::destroy()
{
	this->removeAllChildrenWithCleanup(true);
	CCDirector::sharedDirector()->getTouchDispatcher()->removeAllDelegates();
}
void IntroSceneSecond::update(float dt){
	if(m_runtime == 140)
	{
		this->removeChild(pSprite,true);
		
	}
	if(m_runtime == 280)
	{
		CAudioManager::instance()->stopBGMusic(SOUND_BACKGROUND);
		CCScene *splashsccene = CMainMenuScene::scene();
		CCScene* pScene = CCTransitionFade::create(TRANSITION_DURATION, splashsccene);
		if (pScene)
		{
			CCDirector::sharedDirector()->replaceScene(pScene);
		}

		this->destroy();
	}
	this->m_runtime ++;
	//char buf[20] = "IntroSecond scene: ";
	//sprintf(&buf[13], "%d", this->m_runtime);
	//this->_label->setString(buf);
}
void IntroSceneSecond::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CAudioManager::instance()->stopBGMusic(SOUND_BACKGROUND);
	CCScene *splashsccene = CSPlashScene::scene();
	CCScene* pScene = CCTransitionFade::create(TRANSITION_DURATION, splashsccene);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
	this->destroy();
}
void IntroSceneSecond::buttonMuteCallBack(CCObject* pSender)
{
	CAudioManager::instance()->playEff(SOUND_CLICK_1);
	if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
	{
		CAudioManager::instance()->resumeBGMusic();
		m_bselected = !m_bselected;
		m_pMute->setNormalImage(CCSprite::create("Mute.png"));
		m_pMute->setSelectedImage(CCSprite::create("Mute.png"));
		CAudioManager::instance()->SetSound(SOUND_OFF);
	}
	else
	{
		CAudioManager::instance()->pauseBGMusic();
		m_bselected = !m_bselected;
		m_pMute->setNormalImage(CCSprite::create("MusicOn.png"));
		m_pMute->setSelectedImage(CCSprite::create("MusicOn.png"));
		CAudioManager::instance()->SetSound(SOUND_BG_EFF);
	}
}
bool IntroSceneSecond::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}
