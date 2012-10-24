#include "AboutScene.h"
#include "AudioManager.h"
USING_NS_CC;

CCScene* CAboutScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	CAboutScene *layer = CAboutScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool CAboutScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	this->m_runtime = 0;

	// add a "close" icon to exit the progress. it's an autorelease object
	
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"BackNormal.png",
		"BackSelected.png",
		this,
		menu_selector(CAboutScene::menuMainMenuCallback));
	pCloseItem->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pCloseItem->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	pCloseItem->setPosition( ccp(  pCloseItem->getContentSize().width/2+15*size.width/WIDTH_SCREEN_STANDARD,  pCloseItem->getContentSize().height/2+15*size.height/HEIGHT_SCREEN_STANDARD) );
	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu,1);
		
	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::create("about_background.png");
	pSprite->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pSprite->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	// position the sprite on the center of the screen
	pSprite->setPosition( ccp(size.width/2, size.height/2) );

	this->currentSprite = 0;
	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);

	
	this->pSprite_detail1 = CCSprite::create("about_detail1.png");
	this->pSprite_detail2 = CCSprite::create("about_detail2.png");
	this->pSprite_detail3 = CCSprite::create("about_detail3.png");
	this->pSprite_detail4 = CCSprite::create("about_detail4.png");
	this->pSprite_detail5 = CCSprite::create("about_detail5.png");

	this->addChild(pSprite_detail1,0);
	this->addChild(pSprite_detail2,0);
	this->addChild(pSprite_detail3,0);
	this->addChild(pSprite_detail4,0);
	this->addChild(pSprite_detail5,0);

	pSprite_detail1->setVisible(false);
	pSprite_detail2->setVisible(false);
	pSprite_detail3->setVisible(false);
	pSprite_detail4->setVisible(false);
	pSprite_detail5->setVisible(false);
	
	this->schedule(schedule_selector(CAboutScene::update));
	spriteMoveDone(this);
	return true;
}
void CAboutScene::update(float dt){

	/*this->m_runtime ++;
	char buf[20] = "Help scene: ";
	sprintf(&buf[12], "%d", this->m_runtime);
	this->_label->setString(buf);*/

}
void CAboutScene::render(){

}
void CAboutScene::exit(){

}

void CAboutScene::menuMainMenuCallback(CCObject* pSender)
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

void CAboutScene::spriteMoveDone( CCNode* sender )
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
}