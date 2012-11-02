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

//DEBUG
CCLabelTTF *m_label;
char m_str[100];
//////////////////////////


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
		m_checkLose = false;
		m_time = 0;
		m_arrMonster = new CCArray;
		m_arrBullet = new CCArray;
		m_index = -1;

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
	loadMap();



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
		m_pTouchbegin = NULL;
		m_pTouchend=NULL;
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
		//m_pAreaShootFireBullet->setRotation(90);
		m_pAreaShootFireBullet->setPosition(ccp(size.width/2,AREA_SHOOT_BULLET_HEIGHT/2.0));
		m_pAreaShootWaterBullet=CCSprite::spriteWithFile("AreaShootWaterBullet.png",
			CCRectMake(0,0,AREA_SHOOT_BULLET_WIDTH,AREA_SHOOT_BULLET_HEIGHT));
		m_pAreaShootWaterBullet->setPosition(ccp(size.width/2,AREA_SHOOT_BULLET_HEIGHT/2.0));
		m_pAreaShootBullet=m_pAreaShootFireBullet;
		m_iCurrentBullet=FIRE_BULLET_SMALL;
		this->addChild(m_pAreaShootBullet);
		//m_vBullet = new vector<Bullet *>();
		m_pTouchTemp = new CCPoint();
		
	}		
	//DEBUG 
	m_label = CCLabelTTF::labelWithString(m_str, "Arial", 24);

	m_label->setPosition( ccp(size.width/2,size.height/2) );
	this->addChild( m_label );
	/////////////////


	CAudioManager::instance()->stopAllEff();
	CAudioManager::instance()->stopBGMusic();
	CAudioManager::instance()->playBGMusic(SOUND_GAMEPLAY_BAGROUND_1, true);
	scheduleUpdate();
	return true;
}

void CGameObjectLayer::update(float dt)
{
	if(m_bIsTouching) {
		if(inAreaShoot(&m_pBulletTemp->getPosition())) m_fTimeFire+=dt;
		if(m_fTimeFire>1) {
			updateBullet();
		}
		
		
		//sprintf(m_str,"%f",m_fTimeFire);
		m_label->setString( m_str );
		
	}
	creatMonster();
	attackTower();
	m_time = m_time + dt;
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

		if(inAreaShoot(&pTouch->getLocation()))
		{
			m_bIsTouching = true;
			m_fTimeFire=0;
			length=0;
			m_pTouchbegin = new CCPoint(pTouch->getLocation().x,pTouch->getLocation().y);
			m_pTouchend = new CCPoint(pTouch->getLocation().x,pTouch->getLocation().y);
			addBullet(pTouch->getLocation());
			
		}
	}



	return true;
}

void CGameObjectLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{	
	if(m_bIsTouching)
	{
		m_pTouchTemp->setPoint(pTouch->getLocation().x,pTouch->getLocation().y);	

		m_fTimeFire=0;
		m_bIscol = false;
		//CCPoint direction;
		//CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());


		float x1=m_pTouchend->x;
		float x2=pTouch->getLocation().x;
		float y1=m_pTouchend->y;
		float y2=pTouch->getLocation().y;
		float d= sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
		if(d>20){
			length+=d;
			m_pTouchbegin->setPoint(m_pTouchend->x,m_pTouchend->y);
			m_pTouchend->setPoint(pTouch->getLocation().x,pTouch->getLocation().y);
			if(length>MAX_LENGTH_MOVE){
				m_bIsTouching=false;
				shootBullet();
			}
			
		}

		//CCSprite* t_bullet= m_pBulletTemp;
		m_pBulletTemp->setPosition(*m_pTouchTemp);

		//this->removeChild(
	}

}

void CGameObjectLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{	
	if(m_bIsTouching){

		m_bIsTouching = false;	
		shootBullet();
	}
	
	
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
	//labelTarget->setVisible(false);
	Bullet *sprite = (Bullet *)sender;
	this->removeChild(sprite, true);
	m_arrBullet->removeObject(sprite);
	
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
	if(m_iCurrentBullet==FIRE_BULLET_SMALL) {
		m_iCurrentBullet=WATER_BULLET_SMALL;
		m_pAreaShootBullet=m_pAreaShootWaterBullet;
	}
	else{
		m_iCurrentBullet=FIRE_BULLET_SMALL;
		m_pAreaShootBullet=m_pAreaShootFireBullet;
	}
	this->addChild(m_pAreaShootBullet);
}

void CGameObjectLayer::addBullet(CCPoint &p)
{
	char * path="";
	if(m_iCurrentBullet==FIRE_BULLET_SMALL) path="FireBulletSmall.png";
	else path="WaterBulletSmall.png";
	CCSprite* sp = CCSprite::create(path);
	sp->setPosition(ccp(0,0));
	sp->setScale(30.0/128.0);
	Bullet *b= new Bullet(m_iCurrentBullet,sp);
	b->setType(m_iCurrentBullet);

	m_pBulletTemp=b;
	m_pBulletTemp->setPosition(CCPoint(p));
	this->addChild(m_pBulletTemp);


}

bool CGameObjectLayer::inAreaShoot(const CCPoint *p)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	return (p->x >= size.width/2 - AREA_SHOOT_BULLET_WIDTH/2) && (p->x <= size.width/2 + AREA_SHOOT_BULLET_WIDTH/2)
		&&(p->y >= 40 - AREA_SHOOT_BULLET_HEIGHT/2) && (p->y <= 40 + AREA_SHOOT_BULLET_HEIGHT/2);
}

CCPoint CGameObjectLayer::getRealDest(float X1,float Y1, float X2, float Y2)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	float t;
	if(X2-X1!= 0) t= 50/(X2-X1);
	else t= 50/(Y2-Y1);
	if(t<0) t=-t;
	float Vx=t*(X2-X1);
	float Vy=t*(Y2-Y1);
	float DestX=X1;
	float DestY=Y1;
	
	do{

		DestX+= Vx;
		DestY+= Vy;
		if(DestX < -20 || DestX > (size.width +20) || DestY<-20 || DestY > (size.height+20)) break;
	}
	while(1);
	return ccp(DestX,DestY);

}
void CGameObjectLayer::updateBullet()
{
	Bullet *oldBullet= m_pBulletTemp;
	char * path="";
	if(m_iCurrentBullet==FIRE_BULLET_SMALL) {
		m_iCurrentBullet=FIRE_BULLET_BIG;
		path="FireBulletBig.png";
	}
	else {
		m_iCurrentBullet=WATER_BULLET_BIG;
		path="WaterBulletBig.png";
	}
	CCSprite* newBullet = CCSprite::create(path);

	newBullet->setScale(50.0/128.0);
	newBullet->setPosition(ccp(0,0));
	Bullet* b= new Bullet(m_iCurrentBullet,newBullet);
	b->setPosition(m_pBulletTemp->getPosition());
	this->removeChild(m_pBulletTemp,true);
	m_pBulletTemp=b;
	this->addChild(m_pBulletTemp);
	if(m_iCurrentBullet==FIRE_BULLET_BIG) {
		m_iCurrentBullet=FIRE_BULLET_SMALL;
		
	}
	else {
		m_iCurrentBullet=WATER_BULLET_SMALL;
		
	}
	

}
void CGameObjectLayer::shootBullet(){
	float X1=m_pTouchbegin->x;
	float Y1=m_pTouchbegin->y;	
	float X2=m_pTouchend->x;
	float Y2=m_pTouchend->y;

	float Dx=X2-X1;
	float Dy=Y2-Y1;
	// Determine speed of the target
	length += sqrt(Dx*Dx+Dy*Dy);

	if(length>20) 
	{	
		//m_vBullet->push_back(m_pBulletTemp);// add Bullet to vector
		m_arrBullet->addObject(m_pBulletTemp);
		//float velocity= length/m_fTimeFire;
		float realMoveDuration= 100/length;
		if(realMoveDuration<0.5) realMoveDuration=0.5;
		if(realMoveDuration>1.5) realMoveDuration=1.5;
		sprintf(m_str,"Time:%f",realMoveDuration);
		CCPoint realDest = getRealDest(X1,Y1,X2,Y2);

		m_pBulletTemp->runAction( CCSequence::actions(
			CCMoveTo::actionWithDuration(realMoveDuration, realDest),
			CCCallFuncN::actionWithTarget(this,
			callfuncN_selector(CGameObjectLayer::spriteMoveDone)), 
			NULL) );
	}else{
		this->removeChild(m_pBulletTemp,true);
	}
}

void CGameObjectLayer::ccTouchesBegan(CCSet* touch, CCEvent* touchEvent)  
{  
	// Initialization.  
	

	// Verify whether "UP" keyboard key is pressed or not  
	if(GetKeyState(VK_UP))  
	{  
		
	}

	// Verify whether "DOWN" keyboard key is pressed or not  
	if(GetKeyState(VK_DOWN))  
	{  
		
	}  
} 

void CGameObjectLayer::loadMap(){
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pSprite = CCSprite::create("map.png");
	//pSprite->getContentSize().width;
	pSprite->setScaleX((float)size.width/pSprite->getContentSize().width);
	pSprite->setScaleY((float)size.height/pSprite->getContentSize().height);
	// position the sprite on the center of the screen
	pSprite->setPosition( ccp(size.width/2, size.height/2) );

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);

	CCPointArray *array1 = CCPointArray::create(20);
	array1->addControlPoint(ccp(0,0));
	array1->addControlPoint(ccp(25, 150));
	array1->addControlPoint(ccp(50, 200));
	array1->addControlPoint(ccp(100, 250));
	array1->addControlPoint(ccp(150, 270));
	array1->addControlPoint(ccp(200, 300));
	array1->addControlPoint(ccp(250, 320));
	array1->addControlPoint(ccp(300, 331));
	array1->addControlPoint(ccp(350, 334));
	array1->addControlPoint(ccp(400, 335));
	array1->addControlPoint(ccp(450, 335));
	array1->addControlPoint(ccp(500, 340));
	array1->addControlPoint(ccp(550, 351));
	array1->addControlPoint(ccp(600, 375));
	array1->addControlPoint(ccp(650, 410));
	array1->addControlPoint(ccp(700, 440));
	array1->addControlPoint(ccp(750, 450));
	array1->addControlPoint(ccp(800, 455));
	array1->addControlPoint(ccp(850, 455));
	m_array1 = array1;
	m_array1->retain();


	CCPointArray *array2 = CCPointArray::create(20);
	array2->addControlPoint(ccp(0,0));
	array2->addControlPoint(ccp(50, 20));
	array2->addControlPoint(ccp(100, 50));
	array2->addControlPoint(ccp(150, 80));
	array2->addControlPoint(ccp(200, 95));
	array2->addControlPoint(ccp(250, 100));
	array2->addControlPoint(ccp(300, 105));
	array2->addControlPoint(ccp(350, 115));
	array2->addControlPoint(ccp(400, 130));
	array2->addControlPoint(ccp(450, 150));
	array2->addControlPoint(ccp(500, 170));
	array2->addControlPoint(ccp(550, 210));
	array2->addControlPoint(ccp(600, 250));
	array2->addControlPoint(ccp(650, 330));
	array2->addControlPoint(ccp(675, 380));
	array2->addControlPoint(ccp(700, 440));
	array2->addControlPoint(ccp(750, 450));
	array2->addControlPoint(ccp(800, 455));
	array2->addControlPoint(ccp(850, 455));
	m_array2 = array2;
	m_array2->retain();

	CCPointArray *array3 = CCPointArray::create(20);
	array3->addControlPoint(ccp(-70,300));
	array3->addControlPoint(ccp(0,290));
	//array3->addControlPoint(ccp(25, 300));
	array3->addControlPoint(ccp(50, 300));
	array3->addControlPoint(ccp(100, 310));
	array3->addControlPoint(ccp(150, 320));
	array3->addControlPoint(ccp(200, 350));
	array3->addControlPoint(ccp(250, 390));
	array3->addControlPoint(ccp(300, 420));
	array3->addControlPoint(ccp(350, 450));
	array3->addControlPoint(ccp(400, 470));
	array3->addControlPoint(ccp(450, 480));
	array3->addControlPoint(ccp(500, 490));
	array3->addControlPoint(ccp(550, 490));
	array3->addControlPoint(ccp(600, 480));
	array3->addControlPoint(ccp(650, 470));
	array3->addControlPoint(ccp(700, 440));
	array3->addControlPoint(ccp(750, 450));
	array3->addControlPoint(ccp(800, 455));
	array3->addControlPoint(ccp(850, 455));
	m_array3 = array3;
	m_array3->retain();

	CCPointArray *array4 = CCPointArray::create(20);
	array4->addControlPoint(ccp(400, -70));
	array4->addControlPoint(ccp(450, -30));
	array4->addControlPoint(ccp(500, 0));
	array4->addControlPoint(ccp(550, 20));
	array4->addControlPoint(ccp(600, 80));
	array4->addControlPoint(ccp(650, 160));
	array4->addControlPoint(ccp(675, 260));
	array4->addControlPoint(ccp(700, 320));
	array4->addControlPoint(ccp(725, 360));
	array4->addControlPoint(ccp(750, 400));
	array4->addControlPoint(ccp(800, 440));
	array4->addControlPoint(ccp(850, 455));
	m_array4 = array4;
	m_array4->retain();


	m_tower = new CTower(30);
	m_tower->setPosition(ccp(950,525));
	this->addChild(m_tower);
}

void CGameObjectLayer::creatMonster(){
	for (int i = 0;i<50;i++)
	{
		if(i*4<m_time && i>m_index){
			int minDuration = (int)0.0;
			int maxDuration = (int)4.0;
			int rangeDuration = maxDuration - minDuration;
			//srand(TimgetTicks())
			int actualDuration = (rand()%rangeDuration) + minDuration;
			if (actualDuration==1)
			{
				CMonster * monsterObj = new CMonster(MONSTER_FIRE,1,12,m_array2);
				monsterObj->moveMonster();
				//this->addChild(monsterObj->m_sprite);
				//monsterObj->setScale(0.2);
				m_arrMonster->addObject(monsterObj);
				//monster[i] = new CMonster(MONSTER_FIRE,1,12,m_array);
				//monster[i]->moveMonster();
				//this->addChild(monster[i]->m_sprite);
				this->addChild(monsterObj);
			}else if(actualDuration==2){
				CMonster * monsterObj = new CMonster(MONSTER_FIRE,1,12,m_array1);
				monsterObj->moveMonster();
				//this->addChild(monsterObj->m_sprite);
				//monsterObj->setScale(0.2);
				m_arrMonster->addObject(monsterObj);
				//monster[i] = new CMonster(MONSTER_FIRE,1,12,m_array);
				//monster[i]->moveMonster();
				//this->addChild(monster[i]->m_sprite);
				this->addChild(monsterObj);
			}else if(actualDuration==3){
				CMonster * monsterObj = new CMonster(MONSTER_FIRE,1,12,m_array4);
				monsterObj->moveMonster();
				//this->addChild(monsterObj->m_sprite);
				//monsterObj->setScale(0.2);
				m_arrMonster->addObject(monsterObj);
				//monster[i] = new CMonster(MONSTER_FIRE,1,12,m_array);
				//monster[i]->moveMonster();
				//this->addChild(monster[i]->m_sprite);
				this->addChild(monsterObj);
			}else {
				CMonster * monsterObj = new CMonster(MONSTER_FIRE,1,12,m_array3);
				monsterObj->moveMonster();
				//this->addChild(monsterObj->m_sprite);
				//monsterObj->setScale(0.2);
				m_arrMonster->addObject(monsterObj);
				//monster[i] = new CMonster(MONSTER_FIRE,1,12,m_array);
				//monster[i]->moveMonster();
				//this->addChild(monster[i]->m_sprite);
				this->addChild(monsterObj);
			}
			m_index = i;
		}
	}
}

void CGameObjectLayer::attackTower(){
	if(!m_checkLose){
		bool check =false;
		CCRect towerRect = CCRectMake(m_tower->getPosition().x - m_tower->m_sprite->getContentSize().width/2,
			m_tower->getPosition().y - m_tower->m_sprite->getContentSize().height/2,
			m_tower->m_sprite->getContentSize().width,m_tower->m_sprite->getContentSize().height);
		CCObject *it = new CMonster;
		CMonster *monsterToDele = new CMonster;
		CCARRAY_FOREACH(m_arrMonster,it){
			CMonster*jt = (CMonster*)it;
			CCRect monsterRect = CCRectMake(jt->getPosition().x - jt->getContentSize().width/2,
				jt->getPosition().y-jt->getContentSize().height/2,
				jt->getContentSize().width,jt->getContentSize().height);
			if(CCRect::CCRectIntersectsRect(towerRect,monsterRect)){
				monsterToDele = jt;
				actionKillMonster( monsterToDele );
				//break;
			}
		}
	}
}

void CGameObjectLayer::actionKillMonster( CMonster* pMonster )
{
	m_tower->setHP(m_tower->getHP()-pMonster->getHP());
	actionDestroyTower();
	m_arrMonster->removeObject(pMonster);
	this->removeChild(pMonster, true);
}

void CGameObjectLayer::actionDestroyTower()
{
	if(m_tower->getHP()<=0){
		this->removeChild(m_tower, true);
		m_tower->release();
		m_checkLose = true;
	}
}
