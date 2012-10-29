#include "GameObjectLayer.h"
#include "GameConfig.h"
#include "MySprite.h"
#include "GameConfig.h"
#include "GamePlay.h"
#include "MenuLayer.h"

#include "WinScene.h"
#include "AudioManager.h"
#include "Bullet.h"
#if DEBUG_MODE
#include "MemoryManager.h"
#include "MemoryOperators.h"
#endif

enum {
	kTagTileMap = 1,
	kTagSpriteManager = 1,
	kTagAnimation1 = 1,
	kTagBitmapAtlas1 = 1,
	kTagBitmapAtlas2 = 2,
	kTagBitmapAtlas3 = 3,
};
//#define DEBUGMODE 1
USING_NS_CC;


bool CGameObjectLayer::init()
{
	if(!CCLayer::init())
	{  
#ifdef DEBUGMODE
		CCLOG("GameObjectLayer Init Parent fail..........................");
#endif // DEBUGMODE

		return false;
	}	
#ifdef DEBUGMODE
	CCLOG("GameObjectLayer Init..........................");
#endif // DEBUGMODE

	CCSize s = CCDirector::sharedDirector()->getWinSize();
	//init value
	{
		isAntTakeWater = false;
		isDeleteAround = false;
		isShowTip = false;
		m_bIsChooseKillThief = false;
		m_iNumWater = CGamePlay::getCurrentLevel()->getIntValue(LEVEL_ID_NUMWATER);
		this->m_pBeet = NULL;
		this->m_pTeleport = NULL;
		this->pTarget = NULL;
		this->pThief  = NULL;
		this->m_pSpriteWood = NULL;

	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();	



	sound_water_id =  new int(SOUND_WATER_1);
	sound_waterdrop_id =  new int(SOUND_ALARM_WATER_DROP_1);



	// create menu, it's an autorelease object
	{
		CCMenuItemImage *pSubMenu = CCMenuItemImage::create(
			"PauseGame.png",
			"PauseGameSelected.png",
			this,
			menu_selector(CGameObjectLayer::menuSubMenuCallback));
		//pSubMenu->setScaleX((float)size.width/WIDTH_SCREEN);
		//pSubMenu->setScaleY((float)size.height/HEIGHT_SCREEN);
		pSubMenu->setPosition( ccp(s.width -70 , s.height -40) );
		this->pMenu = CCMenu::create(pSubMenu, NULL);
		this->pMenu->setPosition( CCPointZero );	

		CCMenuItemImage *pReplay = CCMenuItemImage::create(
			"ReplayNormal.png",
			"ReplaySelected.png",
			this,
			menu_selector(CGameObjectLayer::menuReplayMenuCallback));
		/*pReplay->setScaleX((float)size.width/WIDTH_SCREEN);
		pReplay->setScaleY((float)size.height/HEIGHT_SCREEN);*/
		pReplay->setPosition( ccp(s.width -140, s.height -40) );
		this->pMenu->addChild(pReplay);

		const char* music;
		if(CAudioManager::instance()->GetSound() == SOUND_BG_EFF)
			music = "MusicOn.png";
		else if(CAudioManager::instance()->GetSound() == SOUND_EFF)
			music = "MusicBackGroundOff.png";
		else
			music = "Mute.png";
		pMute = CCMenuItemImage::create(
			music,
			music,
			this,
			menu_selector(CGameObjectLayer::menuMuteMenuCallback));
		/*pMute->setScaleX((float)size.width/WIDTH_SCREEN);
		pMute->setScaleY((float)size.height/HEIGHT_SCREEN);*/
		pMute->setPosition( ccp(s.width -210, s.height -40) );
		this->pMenu->addChild(pMute);
		eAstate = MUSIC_ON;
	}



	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, TOUCH_PRIORITY_MAIN_LAYER , true);
	this->setTouchEnabled(true);
	this->addChild(this->pMenu, ZODER_GAMEOBJECTLAYER_SPRITE_0, TAG_PMENU);


	//=======INIT VALUE=======//
	{
		m_iTouchedItem = NONITEM;
		m_pTouch = NULL;
		m_bIscol = false;
		m_bIsTouching = false;
		this->m_pObject = NULL;
		this->pMoveSprite = NULL;
		this->pSpriteTip = NULL;
		pTipText1 = NULL;
		m_bIsAllowTouchKillThief = false;
		m_bIsStopPlay = false;
		this->pMenu->setEnabled(true);

		m_pAreaShootFireBullet=CCSprite::spriteWithFile("AreaShootFireBullet.png",
			CCRectMake(0,0,AREA_SHOOT_BULLET_WIDTH,AREA_SHOOT_BULLET_HEIGHT));
		m_pAreaShootFireBullet->setPosition(ccp(size.width/2,AREA_SHOOT_BULLET_HEIGHT));
		m_pAreaShootFireBullet=CCSprite::spriteWithFile("AreaShootWaterBullet.png",
			CCRectMake(0,0,AREA_SHOOT_BULLET_WIDTH,AREA_SHOOT_BULLET_HEIGHT));
		m_pAreaShootFireBullet->setPosition(ccp(size.width/2,AREA_SHOOT_BULLET_HEIGHT));
		m_pAreaShootBullet=m_pAreaShootFireBullet;
		m_iCurrentBullet=FIRE_BULLET;
		this->addChild(m_pAreaShootBullet);
		m_vBullet = new vector<Bullet *>();
	}		



	CAudioManager::instance()->stopAllEff();
	CAudioManager::instance()->stopBGMusic();
	CAudioManager::instance()->playBGMusic(SOUND_GAMEPLAY_BAGROUND_1, true);
	scheduleUpdate();
	return true;
}

void CGameObjectLayer::update(float dt)
{

}

void CGameObjectLayer::menuSubMenuCallback( CCObject* pSender )
{

	if(CCDirector::sharedDirector()->isPaused()) return;
	CAudioManager::instance()->playEff(SOUND_CLICK_1);
	this->pMenu->setEnabled(false);
	CCDirector::sharedDirector()->pause();
	CCLayerColor *PBlurLayer = CCLayerColor::create();
	PBlurLayer->setOpacityModifyRGB(true);
	PBlurLayer->setColor(ccc3(0,0,0));
	PBlurLayer->setOpacity(150);
	CGamePlay::pMenuLayer = CMenuLayer::create();
	CGamePlay::pScene->addChild(CGamePlay::pMenuLayer, ZODER_GAMEPLAY_MENU_LAYER, TAG_GAMEPLAY_MENU_LAYER);
	CGamePlay::pScene->addChild(PBlurLayer, ZORDER_GAMEPLAY_COLOR_LAYER, TAG_GAMEPLAY_COLOR_LAYER);
}

bool CGameObjectLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent)
{

	if(CCDirector::sharedDirector()->isPaused()) return false;
	if(m_bIsTouching)
	{
		return false;
	}
	else
	{
		m_bIsTouching = true;
		if(inAreaShoot(&pTouch->getLocation()))
		{
			addBullet(pTouch->getLocation());
		}
	}



	return true;
}

void CGameObjectLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{	
	m_bIscol = false;
	CCPoint direction;
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());
}

void CGameObjectLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{	
	m_bIsTouching = false;	
	float posX;
	float posY;	
}

void CGameObjectLayer::draw()
{

}

void CGameObjectLayer::gameLogic( float dt )
{

	index += (int) m_iNumWater/3;
	if (index == m_iNumWater)
	{
		if(CGamePlay::getCurrentLevel()->getIntValue(LEVEL_ID_NUMTHIEF) > 0)
		{
			if (!m_bIsAllowTouchKillThief) {
				m_bIsAllowTouchKillThief = true;
				CAudioManager::instance()->playEff(SOUND_ENABLE_BUTTON);
			}
			if (CGamePlay::getLevel() == 2 && !isShowTip)
			{
				isShowTip = true;
				//show hand
				{
					CCSprite * pSprite = CCSprite::create("hand_mode_choose.png");
					pSprite->setPosition( ccp(m_pSpriteKillThief->getPositionX() , m_pSpriteKillThief->getPositionY() - 40 ));
					pSprite->setScale(0.6f);
					addChild(pSprite, ZODER_GAMEOBJECTLAYER_FRONT_0);
					pSprite->setOpacity(0);
					CCActionInterval*  a1 = CCFadeIn::create(1.5f);
					CCActionInterval* fade_out = CCFadeOut::create(1.0f);
					CCAction*  action2;
					action2 = CCSequence::create(a1,fade_out, NULL);	
					pSprite->runAction(action2);
				}
				//show text
				{
					pTipText1 = CCSprite::create("tipTextKillThief2.png");
					pTipText1->setPosition( ccp(m_pSpriteKillThief->getPositionX() - 230 , m_pSpriteKillThief->getPositionY() + 50));
					pTipText1->setScale(0.7f);
					addChild(pTipText1, ZODER_GAMEOBJECTLAYER_FRONT_0);
					pTipText1->setOpacity(0);
					CCActionInterval*  a1 = CCFadeIn::create(1.5f);
					CCActionInterval* fade_out = CCFadeOut::create(1.0f);
					CCAction*  action2;
					action2 = CCSequence::create(a1,fade_out, NULL);
					pTipText1->runAction(action2);
				}				
			}
		}
	}
	CCDelayTime *delayAction = CCDelayTime::actionWithDuration(2.0f);
	cocos2d::CCCallFuncND* callFunc = CCCallFuncND::actionWithTarget(this, callfuncND_selector(CWinScene::playSound) ,(void*) sound_water_id);
	this->runAction(CCSequence::actions(delayAction, callFunc, NULL));
}

void CGameObjectLayer::openBox( float dt )
{
	CAudioManager::instance()->stopAllEff();
}

void CGameObjectLayer::addElement()
{

}

bool CGameObjectLayer::checkColision(CCTouch* pTouch, int ID )
{
	switch(ID)
	{
	case MENU_ITEM_WOOD:
		if(CCDirector::sharedDirector()->convertToGL(pTouch->locationInView()).x >= MENU_BODER_LEFT*SCREEN_WIDTH_RATIO_PORT
			&& CCDirector::sharedDirector()->convertToGL(pTouch->locationInView()).y >= MENU_BODER_BOTTOM*SCREEN_HEIGHT_RATION_PORT)
		{
			return true;
		}	

		for(int i = 0; i < CGamePlay::getCurrentLevel()->getIntValue(LEVEL_ID_NUMTARGET); i++)
		{
			CCRect touchRec = CCRectMake((CCDirector::sharedDirector()->convertToGL(pTouch->locationInView())).x - WOOD_BOUNDINGBOX_WIDTH/2.0f , (CCDirector::sharedDirector()->convertToGL(pTouch->locationInView())).y - WOOD_BOUNDINGBOX_HEIGHT/2.0f , WOOD_BOUNDINGBOX_WIDTH, WOOD_BOUNDINGBOX_HEIGHT);
			CCRect objRec   = CCRectMake((CGamePlay::getCurrentLevel()->getObjectList(LEVEL_ID_TARGETLIST)[i].position).x - COCONUT_WIDTH/2.0f , (CGamePlay::getCurrentLevel()->getObjectList(LEVEL_ID_TARGETLIST)[i].position).y - COCONUT_WIDTH/2.0f, COCONUT_WIDTH, COCONUT_HEIGHT);

			if(CCRect::CCRectIntersectsRect(touchRec, objRec))
			{			
				return true;
			}
		}

		for(int i = 0; i < CGamePlay::getCurrentLevel()->getIntValue(LEVEL_ID_NUMROCK); i++)
		{
			CCRect touchRec = CCRectMake((CCDirector::sharedDirector()->convertToGL(pTouch->locationInView())).x - WOOD_BOUNDINGBOX_WIDTH/2.0f , (CCDirector::sharedDirector()->convertToGL(pTouch->locationInView())).y - WOOD_BOUNDINGBOX_HEIGHT/2.0f , WOOD_BOUNDINGBOX_WIDTH, WOOD_BOUNDINGBOX_HEIGHT);
			CCRect objRec   = CCRectMake((CGamePlay::getCurrentLevel()->getObjectList(LEVEL_ID_ROCK_LIST)[i].position).x - ROCK_WIDTH/2.0f , (CGamePlay::getCurrentLevel()->getObjectList(LEVEL_ID_ROCK_LIST)[i].position).y - ROCK_HEIGHT/2.0f, ROCK_WIDTH, ROCK_HEIGHT);

			if(CCRect::CCRectIntersectsRect(touchRec, objRec))
			{
				return true;
			}
		}
		break;
	default:
		break;
	}
	return false;
}

void CGameObjectLayer::checkScore()
{
	int scores = 0;
	int countLiqiudToStop = 0;		

	if(CGamePlay::getValue(SCORE)%20 == 0 && scores >  CGamePlay::getValue(SCORE))
	{
		CAudioManager::instance()->playEff(SOUND_WATER_3);
	}
	CGamePlay::addValue(SCORE,scores - CGamePlay::getValue(SCORE));	

	if(countLiqiudToStop == m_iNumWater && !m_bIsStopPlay) 
	{
		CAudioManager::instance()->stopAllEff();
		m_bIsStopPlay = true;
		int valueItemRemain = CGamePlay::getValue(OBJECT_ITEM_KILLTHIEF)*SCORE_BONUS_KILLTHIEF + CGamePlay::getValue(OBJECT_ITEM_WOOD)*SCORE_BONUS_WOOD;
		CGamePlay::addValue(BONUS,valueItemRemain );
		this->schedule(schedule_selector(CGameObjectLayer::delayWinScene), 1.5f, 0, 0); //, 0,  CGamePlay::getCurrentLevel()->getIntValue(LEVEL_ID_TIME_OPEN_BOX));
	}
}

void CGameObjectLayer::menuReplayMenuCallback( CCObject* pSender )
{   
	if(CCDirector::sharedDirector()->isPaused()) return;
	CAudioManager::instance()->playEff(SOUND_CLICK_1);
	//this->removeAllChildrenWithCleanup(true);	
	CGamePlay::removeLayerByTag(TAG_GAMEPLAY_FRONTSPRITE_LAYER);
	CGamePlay::removeLayerByTag(TAG_GAMEPLAY_GAME_OBJECT_LAYER);
	CGamePlay::destroy();
	CGamePlay::setLevel(CGamePlay::getLevel());
	CCScene *gamePlay = CGamePlay::scene();
	CCDirector::sharedDirector()->replaceScene(gamePlay);
}

void CGameObjectLayer::menuMuteMenuCallback( CCObject* pSender )
{
	if(CCDirector::sharedDirector()->isPaused()) return;
	switch(CAudioManager::instance()->GetSound())
	{
	case SOUND_BG_EFF:
		//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_CLICK_1);
		pMute->setNormalImage(CCSprite::create("MusicBackGroundOff.png"));
		pMute->setSelectedImage(CCSprite::create("MusicBackGroundOff.png"));
		//CAudioManager::instance()->setBGMusicVolume(0.0f);
		CAudioManager::instance()->pauseBGMusic();
		CAudioManager::instance()->SetSound(SOUND_EFF);
		break;
	case SOUND_EFF:
		//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_CLICK_1);
		pMute->setNormalImage(CCSprite::create("Mute.png"));
		pMute->setSelectedImage(CCSprite::create("Mute.png"));
		//CAudioManager::instance()->setEffVolume(0.0f);
		CAudioManager::instance()->pauseAllEff();
		CAudioManager::instance()->SetSound(SOUND_OFF);
		break;
	case SOUND_OFF:
		//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_CLICK_1);
		pMute->setNormalImage(CCSprite::create("MusicOn.png"));
		pMute->setSelectedImage(CCSprite::create("MusicOn.png"));
		//CAudioManager::instance()->setBGMusicVolume(1.0f);
		//CAudioManager::instance()->setEffVolume(1.0f);
		CAudioManager::instance()->resumeBGMusic();
		CAudioManager::instance()->SetSound(SOUND_BG_EFF);
		break;
	default:
		break;
	}
}

void CGameObjectLayer::shakeBeet( float dt )
{
	if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF || CAudioManager::instance()->GetSound()==SOUND_EFF )
		CAudioManager::instance()->playEff(SOUND_ALARM_WATER_DROP_1,true);

}

void CGameObjectLayer::onExit()
{
#ifdef DEBUGMODE
	CCLOG("Exit Gameobject Layer");
#endif // DEBUGMODE

	if(this->pThief != NULL)
		CC_SAFE_DELETE(this->pThief);

	delete sound_water_id;
	delete sound_waterdrop_id;
	//m_pSpriteList->removeAllObjects();
	//this->removeAllChildrenWithCleanup(true);
	//m_pSpriteList->release();

}

void CGameObjectLayer::spriteMoveDone( CCNode* sender )
{
	//labelTarget->stopAllActions();
	labelTarget->setVisible(false);
	//labelTarget->release();
}

void CGameObjectLayer::playSound( CCNode* sender, void* data )
{
	if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF || CAudioManager::instance()->GetSound()==SOUND_EFF )
		CAudioManager::instance()->playEff(*(int*)data);
}		

void CGameObjectLayer::tipTextSpriteDone( CCNode* sender )
{


	//show text
	{
		pTipText1->setVisible(false);
		CCSprite* pSprite = CCSprite::create("tipTextKillThief3.png");
		pSprite->setPosition( ccp(m_pSpriteKillThief->getPositionX() - 230 , m_pSpriteKillThief->getPositionY() + 10));
		pSprite->setScale(0.7f);
		addChild(pSprite, ZODER_GAMEOBJECTLAYER_FRONT_0);	
		CCActionInterval*  a1 = CCFadeIn::create(0.7f);
		CCActionInterval*  a2 = CCMoveBy::create(1.0f, ccp(0, 0));
		CCActionInterval* fade_out = CCFadeOut::create(1.0f);
		CCAction*  action2;
		action2 = CCRepeat::create(CCSequence::create(a1, a2, fade_out, NULL), 1);	
		pSprite->runAction(action2);
	}
}

void CGameObjectLayer::delayWinScene( float dt )
{
	CGamePlay::checkWin();
}

void CGameObjectLayer::changeBullet()
{	
	this->removeChild(m_pAreaShootBullet, false);
	if(m_iCurrentBullet==FIRE_BULLET) {
		m_iCurrentBullet=WATER_BULLET;
		m_pAreaShootBullet=m_pAreaShootWaterBullet;
	}
	else{
		m_iCurrentBullet=FIRE_BULLET;
		m_pAreaShootBullet=m_pAreaShootFireBullet;
	}
	this->addChild(m_pAreaShootBullet);
}

void CGameObjectLayer::addBullet(CCPoint &p)
{
	char * path="";
	if(m_iCurrentBullet==FIRE_BULLET) path="FireBullet.png";
	else path="WaterBullet.png";
	CCSprite* sp = CCSprite::create(path);
	
	sp->setScale(20.0/128.0);
	sp->setPosition(CCPoint(p));
	Bullet *b= new Bullet(m_iCurrentBullet,sp);
	b->setType(m_iCurrentBullet);
	m_vBullet->push_back(b);
	this->addChild(sp);
	
}

bool CGameObjectLayer::inAreaShoot(CCPoint *p)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	return (p->x >= size.width/2 - AREA_SHOOT_BULLET_WIDTH/2) && (p->x <= size.width/2 + AREA_SHOOT_BULLET_WIDTH/2)
		&&(p->y >= 40 - AREA_SHOOT_BULLET_HEIGHT/2) && (p->y <= 40 + AREA_SHOOT_BULLET_HEIGHT/2);
}
