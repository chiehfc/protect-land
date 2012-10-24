#include "LoadingScene.h"

int CLoadingScene::MODE = 0;
USING_NS_CC;
CCScene* CLoadingScene::scene(int MODE)
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	CLoadingScene::MODE = MODE;
	// 'layer' is an autorelease object
	CLoadingScene *layer = CLoadingScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool CLoadingScene::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0 , true);
	m_iNumOfStep = (CSpriteManager::GetInstance())->LoadFileResource("Resource1.txt");
	//CSpriteManager::GetInstance()->LoadFileResource("Resource1.txt");
	if (!m_iNumOfStep)
	{
		CCAssert(true, "Khong ton tai file Resource");
		return false;
	}
	m_iCurrentStep = 0;
	this->m_runtime  = 0;
	isTap = false;

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	this->_label = CCLabelTTF::create("", "Arial", 24);
	_label->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	_label->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	this->_label->setPosition( ccp(size.width / 2, size.height - 50*SCREEN_HEIGHT_RATION_PORT) );
	this->addChild(this->_label,1);
	
	m_pLoadingBar = new CMySprite("WaterDrop.sprite",TYPE_SPRITE_SRITE);
	addChild(m_pLoadingBar);
	//m_pLoadingBar->PlayAnimation(0, 1.0f, 1, false);
	m_pLoadingBar->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	m_pLoadingBar->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	m_pLoadingBar->setPosition(ccp(size.width/2,size.height/2));
	m_pLoadingBar->SetFrame(0,0);
	schedule(schedule_selector(CLoadingScene::update));
	return true;
}

void CLoadingScene::update(float dt)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if(true)//m_runtime % 20 == 0)
	{
		m_runtime = 0;
		if(!isTap && CLoadingScene::MODE == MODE_CONTINUE)
		{
			//this->m_runtime ++;
			char buf[50] = "Continue Loading scene: ";
			m_iCurrentStep = CSpriteManager::GetInstance()->LoadResourceByStep("", m_iCurrentStep);
			int percent = 100.0f * m_iCurrentStep / m_iNumOfStep;
			sprintf(&buf[24], "%d", percent);
			this->_label->setString(buf);
			m_pLoadingBar->SetFrame(0,percent/10);
		}
		else if(!isTap && CLoadingScene::MODE == MODE_NEWGAME)
		{
			//this->m_runtime ++;
			char buf[50] = "New Game Loading scene: ";
			m_iCurrentStep = CSpriteManager::GetInstance()->LoadResourceByStep("", m_iCurrentStep);
			int percent = 100.0f * m_iCurrentStep / m_iNumOfStep;
			sprintf(&buf[24], "%d", percent);
			this->_label->setString(buf);
			m_pLoadingBar->SetFrame(0,percent/10);

		}

		if(!isTap && m_iCurrentStep > m_iNumOfStep )
		{
			CCFadeOut *fadeOut = CCFadeOut::create(1.0f);
			CCFadeIn *fadeIn = CCFadeIn::create(0.3f);
			CCFiniteTimeAction *seq = CCSequence::create(fadeOut, fadeIn, NULL);
			CCRepeatForever *forever = CCRepeatForever::create((CCActionInterval *)seq);
			this->_label->setFontSize(24);
			this->_label->setPosition(ccp(size.width/2, size.height/2 - m_pLoadingBar->getContentSize().height / 2 * SCREEN_HEIGHT_RATION_PORT - 10*SCREEN_HEIGHT_RATION_PORT));
			this->_label->setString("Tap to continue...");
			//this->_label->runAction(forever);
			this->m_pLoadingBar->runAction(forever);
			isTap = true;
			////////////////////////////////////////////////////////////////////////////
			//CCLabelTTF *label1 = CCLabelTTF::create("Testing A8 Format", "Arial", 48);
			//addChild(label1);
			//label1->setColor(ccRED);
			//label1->setPosition(ccp(WIDTH_SCREEN/2, HEIGHT_SCREEN/2));

			///*CCFadeOut *fadeOut = CCFadeOut::create(2);
			//CCFadeIn *fadeIn = CCFadeIn::create(2);
			//CCFiniteTimeAction *seq = CCSequence::create(fadeOut, fadeIn, NULL);
			//CCRepeatForever *forever = CCRepeatForever::create((CCActionInterval *)seq);
			//*/
			//label1->runAction(forever);
			////////////////////////////////////////////////////////////////////////////
			CLevelManager* levelManager = CLevelManager::GetInstance();
			levelManager->LoadLevelFromFile("LevelInfo.txt");
		}
	}
	m_runtime ++;
}
void CLoadingScene::render()
{

}
void CLoadingScene::exit()
{

}

void CLoadingScene::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	if( isTap )
	{		
		CCScene* selectLevel = CSelectLevelScene::scene();	
		CCScene* pScene = CCTransitionFade::create(TRANSITION_DURATION, selectLevel);
		if (pScene)
		{
			CCDirector::sharedDirector()->replaceScene(pScene);
		} 
		CCDirector::sharedDirector()->getTouchDispatcher()->removeAllDelegates();
	}
}

bool CLoadingScene::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void CLoadingScene::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void CLoadingScene::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{

}
