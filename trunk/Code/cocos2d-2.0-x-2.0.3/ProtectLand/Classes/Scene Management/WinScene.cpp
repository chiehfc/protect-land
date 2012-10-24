#include "WinScene.h"
USING_NS_CC;

CCScene* CWinScene::scene(eStar star)
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	CWinScene *layer = CWinScene::create();
	layer->addStar(star);
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool CWinScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	countTotal = 0;
	countSocre = 0;
	countBonus = 0;
	m_pLabelScorce = CCLabelBMFont::create(" 0", "fonts/vni-whimsy.fnt", 35);
	//m_pLabelScorce->setScale(0.7f);
	m_pLabelScorce->setColor(ccc3(177, 89, 76));
	m_pLabelScorce->setScaleX(0.7f*SCREEN_WIDTH_RATIO_PORT);
	m_pLabelScorce->setScaleY(0.7f*SCREEN_HEIGHT_RATION_PORT);
	this->m_pLabelScorce->setPosition( ccp(size.width/2 + 120*SCREEN_WIDTH_RATIO_PORT, size.height/2 - 25*SCREEN_HEIGHT_RATION_PORT ) );
	this->addChild(m_pLabelScorce, 3);

	m_pLabelBonus = CCLabelBMFont::create(" 0", "fonts/vni-whimsy.fnt", 35);
	//m_pLabelBonus->setScale(0.7f);
	m_pLabelBonus->setColor(ccc3(177, 89, 76));
	m_pLabelBonus->setScaleX(0.7f*SCREEN_WIDTH_RATIO_PORT);
	m_pLabelBonus->setScaleY(0.7f*SCREEN_HEIGHT_RATION_PORT);
	this->m_pLabelBonus->setPosition( ccp(size.width/2 + 120*SCREEN_WIDTH_RATIO_PORT, size.height/2 - 70*SCREEN_HEIGHT_RATION_PORT) );
	this->addChild(m_pLabelBonus, 3);

	m_pLabelTotal = CCLabelBMFont::create(" 0", "fonts/vni-whimsy.fnt", 50);
	m_pLabelTotal->setScale(0.9f);
	m_pLabelTotal->setColor(ccc3(230, 30, 53));
	m_pLabelTotal->setVisible(false);
	m_pLabelTotal->setScaleX(0.9f*SCREEN_WIDTH_RATIO_PORT);
	m_pLabelTotal->setScaleY(0.9f*SCREEN_HEIGHT_RATION_PORT);
	this->m_pLabelTotal->setPosition( ccp(size.width/2 + 120*SCREEN_WIDTH_RATIO_PORT , size.height/2 - 120*SCREEN_HEIGHT_RATION_PORT) );
	this->addChild(m_pLabelTotal, 3);


	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pLevelSelect = CCMenuItemImage::create(
		"MainMenuWinNormal.png",
		"MainMenuWinSelected.png",
		this,
		menu_selector(CWinScene::menuLevelSelectCallback));
	pLevelSelect->setScaleX(SCREEN_WIDTH_RATIO_PORT);
	pLevelSelect->setScaleY(SCREEN_HEIGHT_RATION_PORT);
	pLevelSelect->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2 - 150*SCREEN_WIDTH_RATIO_PORT, CCDirector::sharedDirector()->getWinSize().height/2 -200*SCREEN_HEIGHT_RATION_PORT) );

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pLevelSelect, NULL);
	pMenu->setPosition( CCPointZero );

	CCMenuItemImage *pRestart = CCMenuItemImage::create(
		"ReplayWinNormal.png",
		"ReplayWinSelected.png",
		this,
		menu_selector(CWinScene::menuRestartCallback));
	pRestart->setScaleX(SCREEN_WIDTH_RATIO_PORT);
	pRestart->setScaleY(SCREEN_HEIGHT_RATION_PORT);
	pRestart->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2  , CCDirector::sharedDirector()->getWinSize().height/2 - 200*SCREEN_HEIGHT_RATION_PORT) );
	pMenu->addChild(pRestart);

	CCMenuItemImage *pNext = CCMenuItemImage::create(
		"NextWinNormal.png",
		"NextWinSelected.png",
		this,
		menu_selector(CWinScene::menuNextCallback));
	pNext->setScaleX(SCREEN_WIDTH_RATIO_PORT);
	pNext->setScaleY(SCREEN_HEIGHT_RATION_PORT);
	pNext->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2 + 150*SCREEN_WIDTH_RATIO_PORT , CCDirector::sharedDirector()->getWinSize().height/2 - 200*SCREEN_HEIGHT_RATION_PORT) );
	pMenu->addChild(pNext);


	this->addChild(pMenu,1);

	CCSprite* wSprite = CCSprite::create("GLBG.png");
	// position the sprite on the center of the screen
	wSprite->setScaleX(SCREEN_WIDTH_RATIO_PORT);
	wSprite->setScaleY(SCREEN_HEIGHT_RATION_PORT);
	wSprite->setPosition( ccp(size.width/2, size.height/2) );
	//wSprite->autorelease();
	this->addChild(wSprite, 0);

	CCSprite* wSprite1 = CCSprite::create("winBG.png");
	// position the sprite on the center of the screen
	wSprite1->setScaleX(SCREEN_WIDTH_RATIO_PORT);
	wSprite1->setScaleY(SCREEN_HEIGHT_RATION_PORT);
	wSprite1->setPosition( ccp(size.width/2, size.height/2) );
	//wSprite1->autorelease();
	this->addChild(wSprite1, 0);
	isPlayedScoreCount = false;
	isPlayedWin        = false;
	star_1_id = new int(SOUND_STAR_1);
	star_2_id = new int(SOUND_STAR_2);
	star_3_id = new int(SOUND_STAR_3);
	//////////////////////////////////////////////////////////////////////////
	//Stitch when win...Create by HieuPhan
	{
		m_pStitchFun = new CMySprite("stitch_fun.sprite", TYPE_SPRITE_SRITE);
		this->addChild(m_pStitchFun);
		m_pStitchFun->setVisible(true);
		m_pStitchFun->PlayAnimation(1, 1.0f, true, false);
#if SCREEN_MODE_1280_800
		m_pStitchFun->setPosition( ccp(size.width/2 + 300, size.height/2 + 150 ) );
#else
		m_pStitchFun->setPosition( ccp(size.width/2 + 200, size.height/2 + wSprite1->getContentSize().height/3 - 30) );
#endif
	}

	{
		m_pStitchFun = new CMySprite("stitch_fun.sprite", TYPE_SPRITE_SRITE);
		this->addChild(m_pStitchFun);
		m_pStitchFun->setVisible(true);
		m_pStitchFun->PlayAnimation(1, 1.0f, true, false);
#if SCREEN_MODE_1280_800
		m_pStitchFun->setPosition( ccp(size.width/2 - 300, size.height/2 + 150 ) );
#else
		m_pStitchFun->setPosition( ccp(size.width/2 - 200, size.height/2 + wSprite1->getContentSize().height/3 - 30) );
#endif
	}
	
	

	scheduleUpdate();
	CAudioManager::instance()->stopBGMusic();
	return true;
}
void CWinScene::update(float dt)
{	
	
	if(countSocre == CGamePlay::getValue(SCORE) && countBonus == CGamePlay::getValue(BONUS))
	{
		
		char bufTotal[50] = "";
		sprintf(bufTotal, " %d", CGamePlay::getValue(SCORE) + CGamePlay::getValue(BONUS));
		this->m_pLabelTotal->setString(bufTotal);
		m_pLabelTotal->setVisible(true);
		if(isPlayedWin == true) return;
		CAudioManager::instance()->stopAllEff();
		switch (numStar)
		{
			case 0:
				CAudioManager::instance()->playEff(SOUND_WIN_1);
				break;
			case 1:
				CAudioManager::instance()->playEff(SOUND_WIN_1);
				break;
			case 2:
				CAudioManager::instance()->playEff(SOUND_WIN_2);
				break;
			case 3:
				CAudioManager::instance()->playEff(SOUND_WIN_2);
				break;
		}
		isPlayedWin = true;
	}
	else
	{	
		
		if (countSocre <= CGamePlay::getValue(SCORE))
		{
			char bufScore[50] = "";
			//this->m_pLabelScorce->setString(bufScore);
			countSocre += 2;
			if (countSocre > CGamePlay::getValue(SCORE)) countSocre = CGamePlay::getValue(SCORE);	
			sprintf(bufScore, " %d", countSocre);
			this->m_pLabelScorce->setString(bufScore);
		}
		if (countBonus <= CGamePlay::getValue(BONUS))
		{
			char bufBonus[20] = "";
			//this->m_pLabelBonus->setString(bufBonus);
			countBonus++;
			if (countBonus > CGamePlay::getValue(BONUS)) countBonus = CGamePlay::getValue(BONUS);
			sprintf(bufBonus, " %d", countBonus);
			this->m_pLabelBonus->setString(bufBonus);
		}	
		if(isPlayedScoreCount == true) return;
		CAudioManager::instance()->playEff(SOUND_SCORE_COUNT, true);
		isPlayedScoreCount = true;
	}
}
void CWinScene::render(){

}
void CWinScene::exit(){

}
void CWinScene::menuLevelSelectCallback(CCObject* pSender)
{
	CAudioManager::instance()->playEff(SOUND_CLICK_1);
	CGamePlay::destroy();
	CCScene *levelSelectScene = CSelectLevelScene::scene();
	CCScene* pScene =CCTransitionFade::create(TRANSITION_DURATION, levelSelectScene, ccWHITE);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}
void CWinScene::menuNextCallback( CCObject* pSender )
{
	CAudioManager::instance()->playEff(SOUND_CLICK_1);
	CGamePlay::destroy();
	CGamePlay::setLevel(CGamePlay::getLevel() + 1);
	CCScene *gameplayScene = CGamePlay::scene();
	CCScene* pScene = CCTransitionSlideInR::create(0.7f, gameplayScene);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	} 
	

}
void CWinScene::menuRestartCallback( CCObject* pSender )
{
	CAudioManager::instance()->playEff(SOUND_CLICK_1);
	CGamePlay::destroy();
	CGamePlay::setLevel(CGamePlay::getLevel());
	CCScene *gamePlay = CGamePlay::scene();
	CCDirector::sharedDirector()->replaceScene(gamePlay);
}

void CWinScene::addStar( eStar star )
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pSprite = NULL;
	CMySprite * starSpriteAnimation = new CMySprite("star.sprite", TYPE_SPRITE_SRITE);
	starSpriteAnimation->setScaleX(SCREEN_WIDTH_RATIO_PORT);
	starSpriteAnimation->setScaleY(SCREEN_HEIGHT_RATION_PORT);
	starSpriteAnimation->setPosition(ccp(size.width/2 , size.height/2 + 50*SCREEN_HEIGHT_RATION_PORT ));
	this->addChild(starSpriteAnimation, 3);
	starSpriteAnimation->PlayAnimation(0, 2, 1, false);	
	CCDelayTime *delayAction =NULL;
	cocos2d::CCCallFunc *callSelectorAction = NULL;
	cocos2d::CCCallFuncND *callFunc = NULL;
	switch(star)
	{
		case STAR0:
			pSprite = CCSprite::create("passableText.png");
			pSprite->setScaleX(SCREEN_WIDTH_RATIO_PORT);
			pSprite->setScaleY(SCREEN_HEIGHT_RATION_PORT);
			pSprite->setPosition(ccp(size.width/2 , size.height/2 + 130*SCREEN_HEIGHT_RATION_PORT ));
			this->addChild(pSprite, 3);
			numStar = 0;
			break;
		case STAR1:

			pSprite = CCSprite::create("goodText.png");
			pSprite->setScaleX(SCREEN_WIDTH_RATIO_PORT);
			pSprite->setScaleY(SCREEN_HEIGHT_RATION_PORT);
			pSprite->setPosition(ccp(size.width/2, size.height/2 + 130*SCREEN_HEIGHT_RATION_PORT ));
			this->addChild(pSprite, 3);
			numStar = 1;
			delayAction = CCDelayTime::actionWithDuration(0.5f);
			//callSelectorAction = CCCallFunc::actionWithTarget(this, callfunc_selector(CWinScene::playSound1Star));
			callFunc = CCCallFuncND::actionWithTarget(this, callfuncND_selector(CWinScene::playSound) ,(void*) star_1_id);
			this->runAction(CCSequence::actions(delayAction, callFunc, NULL));

			starSpriteAnimation->PlayAnimation(1, 1.5, 1, false, CCCallFuncN::actionWithTarget(this, callfuncN_selector(CWinScene::particeStar)));
			break;
		case STAR2:
			pSprite = CCSprite::create("greatText.png");
			pSprite->setScaleX(SCREEN_WIDTH_RATIO_PORT);
			pSprite->setScaleY(SCREEN_HEIGHT_RATION_PORT);
			pSprite->setPosition(ccp(size.width/2 , size.height/2 + 130*SCREEN_HEIGHT_RATION_PORT));
			this->addChild(pSprite, 3);
			numStar = 2;
			delayAction = CCDelayTime::actionWithDuration(0.5f);
			//callSelectorAction = CCCallFunc::actionWithTarget(this, callfunc_selector(CWinScene::playSound1Star));
			callFunc = CCCallFuncND::actionWithTarget(this, callfuncND_selector(CWinScene::playSound) ,(void*) star_1_id);
			this->runAction(CCSequence::actions(delayAction, callFunc, NULL));

			delayAction = CCDelayTime::actionWithDuration(1.0f);
			//callSelectorAction = CCCallFunc::actionWithTarget(this, callfunc_selector(CWinScene::playSound2Star));
			callFunc = CCCallFuncND::actionWithTarget(this, callfuncND_selector(CWinScene::playSound) ,(void*) star_2_id);
			
			this->runAction(CCSequence::actions(delayAction, callFunc, NULL));

			starSpriteAnimation->PlayAnimation(2, 2, 1, false, CCCallFuncN::actionWithTarget(this, callfuncN_selector(CWinScene::particeStar)));
			break;
		case STAR3:
			
			pSprite = CCSprite::create("excellentText.png");
			pSprite->setScaleX(SCREEN_WIDTH_RATIO_PORT);
			pSprite->setScaleY(SCREEN_HEIGHT_RATION_PORT);
			pSprite->setPosition(ccp(size.width/2, size.height/2 + 130*SCREEN_HEIGHT_RATION_PORT));
			this->addChild(pSprite, 3);
			numStar = 3;
			delayAction = CCDelayTime::actionWithDuration(0.5f);
			//callSelectorAction = CCCallFunc::actionWithTarget(this, callfunc_selector(CWinScene::playSound1Star));
			callFunc = CCCallFuncND::actionWithTarget(this, callfuncND_selector(CWinScene::playSound) ,(void*) star_1_id);
			this->runAction(CCSequence::actions(delayAction, callFunc, NULL));

			delayAction = CCDelayTime::actionWithDuration(1.0f);
			//callSelectorAction = CCCallFunc::actionWithTarget(this, callfunc_selector(CWinScene::playSound2Star));
			callFunc = CCCallFuncND::actionWithTarget(this, callfuncND_selector(CWinScene::playSound) ,(void*) star_2_id);
			this->runAction(CCSequence::actions(delayAction, callFunc, NULL));

			delayAction = CCDelayTime::actionWithDuration(1.5f);
			//callSelectorAction = CCCallFunc::actionWithTarget(this, callfunc_selector(CWinScene::playSound3Star));
			callFunc = CCCallFuncND::actionWithTarget(this, callfuncND_selector(CWinScene::playSound) ,(void*) star_3_id);
			this->runAction(CCSequence::actions(delayAction, callFunc, NULL));

			starSpriteAnimation->PlayAnimation(3, 2, 1, false, CCCallFuncN::actionWithTarget(this, callfuncN_selector(CWinScene::particeStar)));
			break;
		default:
			break;
	}
}

void CWinScene::particeStar( CCNode* sender )
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCParticleSystem* m_emitte = NULL;
	switch (numStar) 
	{
	case 1:
		m_emitte = new CCParticleSystemQuad();
		m_emitte->initWithFile("demo.plist");
		m_emitte->setBlendAdditive(false);
		this->addChild(m_emitte, 4);
		m_emitte->setPosition(ccp(size.width/2 - 100*SCREEN_WIDTH_RATIO_PORT , size.height/2 + 50*SCREEN_HEIGHT_RATION_PORT ));
		break;
	case 2:
		m_emitte = new CCParticleSystemQuad();
		m_emitte->initWithFile("demo.plist");
		m_emitte->setBlendAdditive(false);
		this->addChild(m_emitte, 4);
		m_emitte->setPosition(ccp(size.width/2 - 100*SCREEN_WIDTH_RATIO_PORT , size.height/2 + 50*SCREEN_HEIGHT_RATION_PORT));

		m_emitte = new CCParticleSystemQuad();
		m_emitte->initWithFile("demo.plist");
		m_emitte->setBlendAdditive(false);
		this->addChild(m_emitte, 4);
		m_emitte->setPosition(ccp(size.width/2, size.height/2 + 50*SCREEN_HEIGHT_RATION_PORT));
		break;
	case 3:

		m_emitte = new CCParticleSystemQuad();
		m_emitte->initWithFile("demo.plist");
		m_emitte->setBlendAdditive(false);
		this->addChild(m_emitte, 4);
		m_emitte->setPosition(ccp(size.width/2 - 100*SCREEN_WIDTH_RATIO_PORT, size.height/2 + 50*SCREEN_HEIGHT_RATION_PORT));

		m_emitte = new CCParticleSystemQuad();
		m_emitte->initWithFile("demo.plist");
		m_emitte->setBlendAdditive(false);
		this->addChild(m_emitte, 4);
		m_emitte->setPosition(ccp(size.width/2 , size.height/2 + 50*SCREEN_HEIGHT_RATION_PORT));


		m_emitte = new CCParticleSystemQuad();
		m_emitte->initWithFile("demo.plist");
		m_emitte->setBlendAdditive(false);
		this->addChild(m_emitte, 4);
		m_emitte->setPosition(ccp(size.width/2 + 100*SCREEN_WIDTH_RATIO_PORT, size.height/2 + 50*SCREEN_HEIGHT_RATION_PORT));
		break;

	}
}

void CWinScene::playSound(CCNode* sender, void* data)
{
	CAudioManager::instance()->playEff(*((int*)data));
}

void CWinScene::StitchMoveDone( CCNode* sender )
{
	m_pStitchFun->PlayAnimation(2, 3.0f, true, false);
}
