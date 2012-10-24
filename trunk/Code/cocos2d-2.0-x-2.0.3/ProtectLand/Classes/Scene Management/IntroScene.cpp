#include "IntroScene.h"
#include "IntroSceneSecond.h"
#include "IncludeHelper.h"
#include "MainMenuScene.h"
USING_NS_CC;

CCScene* IntroScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	IntroScene *layer = IntroScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool IntroScene::init()
{

	
	
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	CAudioManager::instance()->initAudio();
	this->m_runtime = 0;
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0 , true);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	
	// add a "close" icon to exit the progress. it's an autorelease object
	m_bselected = true;

//-----------------------------MODIFY----------------------------------

	CAudioManager::instance()->playBGMusic(SOUND_INTRO); 
//---------------------------------------------------------------------
	// create menu, it's an autorelease object
	
	
	m_pMute = CCMenuItemImage::create(
		"MusicOn.png",
		"MusicOn.png",
		this,
		menu_selector(IntroScene::buttonMuteCallBack));
	m_pMute->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	m_pMute->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	m_pMute->setPosition( ccp(size.width - size.width*40/WIDTH_SCREEN_STANDARD, size.height - size.height*40/HEIGHT_SCREEN_STANDARD));
	CCMenu* pMenu = CCMenu::create(m_pMute, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu,1);
	

	//CCLabelTTF* pLabel = CCLabelTTF::create("Plash scene: 0.0s", "Arial", 24);
	/*this->_label = CCLabelTTF::create("Intro scene: 0.00000", "Arial", 24);
	this->_label->setPosition( ccp(size.width / 2, size.height - 50) );
	this->addChild(this->_label,1);

	CCLabelTTF* label = CCLabelTTF::create("Tap to skip", "Arial", 40);
	label->setPosition( ccp(size.width / 2, 100) );
	this->addChild(label,1);
*/

	// ask director the window size

	// add "HelloWorld" splash screen"
	//CCSprite* pSprite = CCSprite::create("Youwin2.png");
	// position the sprite on the center of the screen
	//pSprite->setPosition( ccp(size.width/2, size.height/2) );


	//CCSize size = CCDirector::sharedDirector()->getWinSize();
	/*CCParticleSystem* m_emitte = new CCParticleSystemQuad();
	m_emitte->initWithFile("l_par.plist");
	m_emitte->setBlendAdditive(false);
	this->addChild(m_emitte, 10);
	m_emitte->setPosition(size.width/2, size.height/2);
	*/
	CCSprite* pSprite = CCSprite::create("introBG.png");
	pSprite->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pSprite->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);

	// position the sprite on the center of the screen
	pSprite->setPosition( ccp(size.width/2, size.height/2) );

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);	



	Stitch = new CMySprite("StitchRun.sprite");
	Stitch->setPosition(CCPoint(size.width*100.0f/WIDTH_SCREEN_STANDARD, size.height*70.0f/HEIGHT_SCREEN_STANDARD));
	Stitch->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	Stitch->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	this->addChild(Stitch);
	//Stitch->PlayAnimation(2, 3.5f,false, false);
	//CCActionInterval* a2 =  CCMoveBy::create(4.0f, CCPoint(850.0f, 150.0f));
	//Stitch->PlayAnimationToPosition(520.0f,70.0f, 4.0f, 0, 0.2f, false, NULL);//CCCallFuncN::actionWithTarget(this, callfuncN_selector(IntroScene::spriteMoveDone)));
	//Stitch->stopAllActions();
	Stitch->PlayAnimation(2, 3.5f, 1, false, CCCallFuncN::actionWithTarget(this, callfuncN_selector(IntroScene::spriteMoveDone)));
	//Stitch->PlayAnimationTwoAction(4.0f,1,0,false);
	
	//CCAction* af = cocos2d::CCSequence::create(a1,a2,NULL);
	//Stitch->runAction(af);

	SimpSon = new CMySprite("SimpSonRun.sprite");
	SimpSon->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	SimpSon->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	SimpSon->setPosition(CCPoint(0.0f, size.height*110.0f/HEIGHT_SCREEN_STANDARD));
	this->addChild(SimpSon);
	//SimpSon->PlayAnimation(1, 0.1f,true, false);
	SimpSon->PlayAnimationToPosition(size.width*520.0f/WIDTH_SCREEN_STANDARD,size.height*110.0f/HEIGHT_SCREEN_STANDARD, 4.0f, 0, 0.4f, false,CCCallFuncN::actionWithTarget(this, callfuncN_selector(IntroScene::SimpSonMove)));

	arrow = new CMySprite("arrow.sprite");
	arrow->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	arrow->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	arrow->setPosition(CCPoint(size.width*0.0f, size.height*120.0f/HEIGHT_SCREEN_STANDARD));
	this->addChild(arrow,0);

	arrow1 = new CMySprite("arrow.sprite");
	arrow1->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	arrow1->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	arrow1->setPosition(CCPoint(size.width*40.0f/WIDTH_SCREEN_STANDARD, size.height*130.0f/HEIGHT_SCREEN_STANDARD));
	this->addChild(arrow1,0);
	arrow1->setVisible(false);

	arrow2 = new CMySprite("arrow.sprite");
	arrow2->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	arrow2->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	arrow2->setPosition(CCPoint(size.width*80.0f/WIDTH_SCREEN_STANDARD, size.height*111.0f/HEIGHT_SCREEN_STANDARD));
	this->addChild(arrow2,0);
	arrow2->setVisible(false);

	arrow3 = new CMySprite("arrow.sprite");
	arrow3->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	arrow3->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	arrow3->setPosition(CCPoint(size.width*130.0f/WIDTH_SCREEN_STANDARD, size.height*100.0f/HEIGHT_SCREEN_STANDARD));
	this->addChild(arrow3,0);
	arrow3->setVisible(false);

	arrow4 = new CMySprite("arrow.sprite");
	arrow4->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	arrow4->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	arrow4->setPosition(CCPoint(size.width*150.0f/WIDTH_SCREEN_STANDARD, size.height*145.0f/HEIGHT_SCREEN_STANDARD));
	this->addChild(arrow4,0);
	arrow4->setVisible(false);

	arrow5 = new CMySprite("arrow.sprite");
	arrow5->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	arrow5->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	arrow5->setPosition(CCPoint(size.width*200.0f/WIDTH_SCREEN_STANDARD, size.height*120.0f/HEIGHT_SCREEN_STANDARD));
	this->addChild(arrow5,0);
	arrow5->setVisible(false);

	arrow6 = new CMySprite("arrow.sprite");
	arrow6->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	arrow6->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	arrow6->setPosition(CCPoint(size.width*230.0f/WIDTH_SCREEN_STANDARD, size.height*150.0f/HEIGHT_SCREEN_STANDARD));
	this->addChild(arrow6,0);
	arrow6->setVisible(false);
	

	////////////////////////////////Test by HieuPhan//////////////////////////////////////////
	CLevelManager::GetInstance()->CreateFileFirstGame("LevelInfo.txt",8);

	this->schedule(schedule_selector(IntroScene::update));

	return true;
}
void IntroScene::update(float dt){
	if(m_runtime == 10)
		arrow->PlayAnimation(0, 0.3, 1, false,CCCallFuncN::actionWithTarget(this, callfuncN_selector(IntroScene::Arrowdone)));
	if(m_runtime == 260)
	{
		CCScene *IntroSecond = IntroSceneSecond::scene();
		CCScene* pScene = CCTransitionFade::create(TRANSITION_DURATION, IntroSecond);
		if (pScene)
		{
			CCDirector::sharedDirector()->replaceScene(pScene);
		}
		//this->destroy();
	}
	this->m_runtime ++;
	/*char buf[20] = "Intro scene: ";
	sprintf(&buf[13], "%d", this->m_runtime);
	this->_label->setString(buf);*/
}
void IntroScene::Arrowdone(CCNode* sender)
{

		arrow1->PlayAnimation(0, 0.35, 1, false, CCCallFuncN::actionWithTarget(this, callfuncN_selector(IntroScene::Arrowdone1)));
		//this->addChild(arrow1,0);
		arrow1->setVisible(true);
}
void IntroScene::Arrowdone1(CCNode* sender)
{
		arrow2->PlayAnimation(0, 0.35, 1, false, CCCallFuncN::actionWithTarget(this, callfuncN_selector(IntroScene::Arrowdone2)));
		//this->addChild(arrow2,0);
		arrow2->setVisible(true);
}
void IntroScene::Arrowdone2(CCNode* sender)
{
		arrow3->PlayAnimation(0, 0.35, 1, false, CCCallFuncN::actionWithTarget(this, callfuncN_selector(IntroScene::Arrowdone3)));
		//this->addChild(arrow3,0);
		arrow3->setVisible(true);
}
void IntroScene::Arrowdone3(CCNode* sender)
{
		arrow4->PlayAnimation(0, 0.35, 1, false, CCCallFuncN::actionWithTarget(this, callfuncN_selector(IntroScene::Arrowdone4)));
		//this->addChild(arrow4,0);
		arrow4->setVisible(true);
}
void IntroScene::Arrowdone4(CCNode* sender)
{
		arrow5->PlayAnimation(0, 0.35, 1, false, CCCallFuncN::actionWithTarget(this, callfuncN_selector(IntroScene::Arrowdone5)));
		//this->addChild(arrow4,0);
		arrow5->setVisible(true);
}

void IntroScene::Arrowdone5(CCNode* sender)
{
		arrow6->PlayAnimation(0, 0.35, 1, false, CCCallFuncN::actionWithTarget(this, callfuncN_selector(IntroScene::Arrowdone6)));
		//this->addChild(arrow4,0);
		arrow6->setVisible(true);
}

void IntroScene::Arrowdone6(CCNode* sender)
{
}

void IntroScene::buttonMuteCallBack(CCObject* pSender)
{
	CAudioManager::instance()->playEff(SOUND_CLICK_1);
	if(m_bselected)
	{
		CAudioManager::instance()->pauseBGMusic();
		m_bselected = !m_bselected;
		m_pMute->setNormalImage(CCSprite::create("Mute.png"));
		m_pMute->setSelectedImage(CCSprite::create("Mute.png"));
		CAudioManager::instance()->SetSound(SOUND_OFF);
	}
	else
	{
		CAudioManager::instance()->resumeBGMusic();
		m_bselected = !m_bselected;
		m_pMute->setNormalImage(CCSprite::create("MusicOn.png"));
		m_pMute->setSelectedImage(CCSprite::create("MusicOn.png"));
		CAudioManager::instance()->SetSound(SOUND_BG_EFF);
	}
}

void IntroScene::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CAudioManager::instance()->stopBGMusic(SOUND_BACKGROUND);
	CCScene *splash = CMainMenuScene::scene();
	CCScene* pScene = CCTransitionFade::create(TRANSITION_DURATION, splash);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
	//this->destroy();
}


void IntroScene::destroy()
{
	this->removeChild(SimpSon, true);
	CCDirector::sharedDirector()->getTouchDispatcher()->removeAllDelegates();
}

void IntroScene::spriteMoveDone( CCNode* sender )
{
	this->removeChild(Stitch, true);
}

void IntroScene::SimpSonMove(CCNode* sender)
{
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	this->removeChild(SimpSon, false);
	SimpSonHit = new CMySprite("SimpSonR.sprite");
	SimpSonHit->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	SimpSonHit->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	SimpSonHit->setPosition(CCPoint(size.width*520.0f/WIDTH_SCREEN_STANDARD, size.height*110.0f/HEIGHT_SCREEN_STANDARD));
	this->addChild(SimpSonHit);
	SimpSonHit->PlayAnimation(0, 1.1f, 5, false, CCCallFuncN::actionWithTarget(this, callfuncN_selector(IntroScene::SimpSonMoveDone)));
}

void IntroScene::SimpSonMoveDone(CCNode* sender)
{
	this->removeChild(SimpSonHit, true);
}

bool IntroScene::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}
