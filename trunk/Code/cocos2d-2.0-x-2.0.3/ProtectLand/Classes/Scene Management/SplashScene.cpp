#include "SplashScene.h"
#include "MainMenuScene.h"
#include "IncludeHelper.h"
USING_NS_CC;
CCScene* CSPlashScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	CSPlashScene *layer = CSPlashScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool CSPlashScene::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	this->m_runtime  = 0;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	//this->_label = CCLabelTTF::create("Splash scene: 0.00000", "Arial", 24);
	//this->_label->setPosition( ccp(size.width / 2, size.height - 50) );
	//this->addChild(this->_label,1);

// Loading Animation 
//--------------------------------------------------------------------------------------------
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pSprite = CCSprite::create("SplashBG.png");
	//pSprite->setScale(0.6f);
	// position the sprite on the center of the screen
	pSprite->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pSprite->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	pSprite->setPosition( ccp(size.width/2, size.height/2) );

	// add the sprite as a child to this layer
	this->addChild(pSprite, -1);
	CCDirector::sharedDirector()->getTouchDispatcher()->removeAllDelegates();
	setTouchEnabled(false);
//--------------------------------------------------------------------------------------------
	schedule(schedule_selector(CSPlashScene::update));
	return true;
}
void CSPlashScene::update(float dt)
{
	this->m_runtime ++;
	/*char buf[20] = "Splash scene: ";
	sprintf(&buf[14], "%d", this->m_runtime);
	this->_label->setString(buf);*/
	if(this->m_runtime == 100)
	{
		CCScene* mainmenuScene = CMainMenuScene::scene();
		CCScene* pScene = CCTransitionFade::create(TRANSITION_DURATION, mainmenuScene);
		if (pScene)
		{
			CCDirector::sharedDirector()->replaceScene(pScene);
		}
		this->removeAllChildrenWithCleanup(true);
		CCDirector::sharedDirector()->getTouchDispatcher()->removeAllDelegates();
		//this->onExit();
		//this->release();
	}
	m_runtime++;
}
