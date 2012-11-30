#include "GameObjectLayer.h"
#include "GameConfig.h"
#include "MySprite.h"
#include "GamePlay.h"
#include "MenuLayer.h"
#include "SkillLayer.h"
#include "PositionConfig.h"

#include "WinScene.h"
#include "AudioManager.h"
#include "Bullet.h"
#include "DebugConfig.h"


enum {
	kTagTileMap = 1,
	kTagSpriteManager = 1,
	kTagAnimation1 = 1,
	kTagBitmapAtlas1 = 1,
	kTagBitmapAtlas2 = 2,
	kTagBitmapAtlas3 = 3,
};
USING_NS_CC;

//DEBUG
CCLabelTTF *m_label;
char m_str[100];
//////////////////////////


bool CGameObjectLayer::init()
{
	if(!CCLayer::init())
	{  
		return false;
	}	

	

	size = CCDirector::sharedDirector()->getWinSize();
	//init value
	{
		check = false;
		m_checkLose = false;
		m_time = 0;
		m_arrMonster = new CCArray;
		m_arrMonsterToDelete = new CCArray;
		m_arrBullet = new CCArray;
		m_index = -1;
		setCheckWin(false);
		setCoinBonus(0);
		initMap();
	}
	
	loadMap();

	// create menu, it's an autorelease object
	{
		CCMenuItemImage *pSubMenu = CCMenuItemImage::create(
			"PauseGame.png",
			"PauseGameSelected.png",
			this,
			menu_selector(CGameObjectLayer::menuSubMenuCallback));
		pSubMenu->setPosition( ccp(size.width -70 , size.height -40) );
		this->pMenu = CCMenu::create(pSubMenu, NULL);
		this->pMenu->setPosition( CCPointZero );	

		CCMenuItemImage *pReplay = CCMenuItemImage::create(
			"ReplayNormal.png",
			"ReplaySelected.png",
			this,
			menu_selector(CGameObjectLayer::menuReplayMenuCallback));
		pReplay->setPosition( ccp(size.width -140, size.height -40) );
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
		pMute->setPosition( ccp(size.width -210, size.height -40) );
		this->pMenu->addChild(pMute);
		eAstate = MUSIC_ON;
	}



	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, TOUCH_PRIORITY_MAIN_LAYER , true);
	this->setTouchEnabled(true);

	this->addChild(this->pMenu, ZODER_GAMEOBJECTLAYER_SPRITE_0, TAG_PMENU);


	//=======INIT VALUE=======//
	{
		m_bIsFinshChooseSkill = false; // gan gia tri ban dau la false, tuc chua them skill
		m_bIscol = false;
		m_bIsTouching = false;
		this->m_pObject = NULL;
		this->pMoveSprite = NULL;		

		this->pMenu->setEnabled(true);

		/*
		m_pBaseTower=CCSprite::spriteWithFile("Tower\\Data\\tower_11.png");
		m_pBaseTower->setPosition(ccp(LOCATION_X_TOWER,LOCATION_Y_TOWER));
		this->addChild(m_pBaseTower);
		m_pTowerItem=new CMySprite("Tower\\tower.sprite");
		m_pTowerItem->setPosition(ccp(LOCATION_X_TOWER+10,LOCATION_Y_TOWER+20));
		this->addChild(m_pTowerItem);
		m_pTowerItem->PlayAnimation(FIRE_TOWER, 0.4f, true, false);
		*/
		
		m_isClickChangeBullet = false;
		m_fSpeed = 1000;
		m_bIsFullEmergy = true;
		m_fTimeRetireBullet = 0;
		m_TimeDelayBullet = 1.0f*pow(0.8,CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerSpeed);
		m_levelBullet = CLevelManager::GetInstance()->GetLevelInformation()->m_iLevelTower;
		if(rand()%2 == 0)
		{
			m_typeBullet = FIRE_BULLET;
		}
		else {
			m_typeBullet = WATER_BULLET;
		}

		m_iCurrentEnegy = 0;  // khoi tao enegy ban dau
		m_bToggle=false;
		addSkillButton();
		updateBullet(m_typeBullet,m_levelBullet);
	}

	// init tower:
	towerHp = CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerHp;
	m_activeHP = CCSprite::spriteWithFile("HPbar\\activeHP.png");
	m_inactiveHP = CCSprite::spriteWithFile("HPbar\\inactiveHP.png");
	m_inactiveHP->setScaleX(1.0f/4.2f);
	m_inactiveHP->setScaleY(1.0f/5.0f);
	m_activeHP->setScale(1.0f/4.0f);
	m_activeHP->setPosition(ccp(LOCATION_X_ACTIVE_HP_TOWER,LOCATION_Y_HP_TOWER));
	m_inactiveHP->setPosition(ccp(LOCATION_X_ACTIVE_HP_TOWER,LOCATION_Y_HP_TOWER));
	m_activeHP->setAnchorPoint(ccp(0,0));
	m_inactiveHP->setAnchorPoint(ccp(0,0));
	this->addChild(m_inactiveHP);
	this->addChild(m_activeHP);
	
	//add label coin and scene
	{
		//icon Coin
		CCSprite* pCoinSorite = CCSprite::spriteWithFile("PlayScene\\coin.png");
		pCoinSorite->setPosition(LOCATION_COIN_ICON);
		this->addChild(pCoinSorite);
		char * pNameIconScene[7] = {"PlayScene\\human.png",  "PlayScene\\elf.png", "PlayScene\\magi_icon.png", 
									"PlayScene\\dwarf.png", "PlayScene\\darkelf.png", "PlayScene\\undead.png", "PlayScene\\devil.png"};
		//icon Stage
		CCSprite* pSceneSorite = CCSprite::spriteWithFile(pNameIconScene[CLevelManager::GetInstance()->GetLevelInformation()->m_iMapCurrent -1]);
		pSceneSorite->setPosition(LOCATION_SCENE_ICON);
		this->addChild(pSceneSorite);

		//label coin
		m_pLabelCoinCollect = CCLabelBMFont::create("0", "fonts/myFont.fnt", 50);
		m_pLabelCoinCollect->setColor(ccc3(177, 89, 76));
		m_pLabelCoinCollect->setScale(1.5f);
		m_pLabelCoinCollect->setAnchorPoint(ccp(0.0f, 0.5f));
		m_pLabelCoinCollect->setPosition(LOCATION_LABEL_COIN);
		this->addChild(m_pLabelCoinCollect, zLabel);

		//label stage
		char strTemp[20] = "";
		sprintf(strTemp, "%d/5", CLevelManager::GetInstance()->GetLevelInformation()->m_iLevelCurrent);
		m_pLabelStageCurrent = CCLabelBMFont::create(strTemp, "fonts/myFont.fnt", 35);
		m_pLabelStageCurrent->setScale(1.5f);
		m_pLabelStageCurrent->setColor(ccc3(177, 89, 76));
		m_pLabelStageCurrent->setPosition(LOCATION_LABEL_SCENE);
		this->addChild(m_pLabelStageCurrent, zLabel);
	}

	
	
	CAudioManager::instance()->stopAllEff();
	CAudioManager::instance()->stopBGMusic();
	CAudioManager::instance()->playBGMusic(SOUND_GAMEPLAY_BAGROUND_1, true);
	scheduleUpdate();
	return true;
}

void CGameObjectLayer::update(float dt)
{
	if(indexTime == 6 && m_arrMonster->count()==0){
		setCheckWin(true);
	}
	addDeleteMonster();
	//CCLOG("%f",m_fTimeRetireBullet);

	m_fTimeRetireBullet += dt;
	if(m_bIsTouching){
		if(m_fTimeRetireBullet>m_TimeDelayBullet){
			addBullets(m_pCurrentPoint);
			m_fTimeRetireBullet=0;
		}
	}
	processLabelCoin();
	creatMonster();
	attackMonster();
	attackTower();
	
	m_time = m_time + dt;

	if (m_bIsFinshChooseSkill)
	{
		addSkillAnimation(m_iTypeSkillReturn);
		m_bIsFinshChooseSkill = false;
	}

	if(m_bToggle){
		this->removeChild(m_pSkill,true);
		m_pSkill = CCSprite::spriteWithFile("Skill\\Skill1_2.png");
		m_pSkill->setPosition(ccp(LOCATION_X_SKILL,LOCATION_Y_SKILL));
		this->addChild(m_pSkill);
		m_bToggle=false;
	}
	
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
	CCLOG("%f %f",pTouch->getLocation().x,pTouch->getLocation().y);
	if(CCDirector::sharedDirector()->isPaused()) return false;
	if(m_bIsTouching)
	{
		return false;
	}
	else
	{
		m_bIsTouching = true;
		m_pCurrentPoint = pTouch->getLocation();
	}
	if(m_bIsFullEmergy && isClickSkill(pTouch->getLocation()))
	{
		m_bIsTouching = false;
		addStarSkill();		
	}

	return true;
}

void CGameObjectLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{	
	if(m_bIsTouching)
	{
		m_bIscol = false;
		m_pCurrentPoint=pTouch->getLocation();

	}
}

void CGameObjectLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{	
	if(m_bIsTouching){

		m_bIsTouching = false;	

	}


}

void CGameObjectLayer::draw()
{
#if DEBUG_DRAW_RECT_ENABLE
	ccDrawColor4F(0.0f, 1.0f, 0.0f, 1.0f);
	CCObject *it = new CMonster;
	CCObject *jt = new Bullet;
	CCARRAY_FOREACH(m_arrMonster,it){
		CMonster *monsterD = (CMonster*) it;
		CCRect monsterRect = getRectMonsterFire(monsterD);
		ccDrawRect(monsterRect.origin, ccpAdd(monsterRect.origin, ccp(monsterRect.size.width, monsterRect.size.height)));
	}
	CCARRAY_FOREACH(m_arrBullet,jt){
		Bullet *bulletD = (Bullet*)jt;
		CCRect bulletRect = getRectBulletFire(bulletD);			
		ccDrawColor4F(0.0f, 1.0f, 0.0f, 1.0f);
		ccDrawRect(bulletRect.origin, ccpAdd(bulletRect.origin, ccp(bulletRect.size.width, bulletRect.size.height)));
	}	
	ccDrawColor4F(1.0f, 1.0f, 1.0f, 1.0f);
#endif	
}

void CGameObjectLayer::menuReplayMenuCallback( CCObject* pSender )
{   
	if(CCDirector::sharedDirector()->isPaused()) return;
	CAudioManager::instance()->playEff(SOUND_CLICK_1);
	//this->removeAllChildrenWithCleanup(true);	
	CGamePlay::removeLayerByTag(TAG_GAMEPLAY_FRONTSPRITE_LAYER);
	CGamePlay::removeLayerByTag(TAG_GAMEPLAY_GAME_OBJECT_LAYER);
	CGamePlay::destroy();
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

void CGameObjectLayer::onExit()
{

}

void CGameObjectLayer::spriteMoveDone( CCNode* sender )
{
	Bullet *sprite = (Bullet *)sender;
	this->removeChild(sprite, true);
	m_arrBullet->removeObject(sprite);

}

void CGameObjectLayer::playSound( CCNode* sender, void* data )
{
	if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF || CAudioManager::instance()->GetSound()==SOUND_EFF )
		CAudioManager::instance()->playEff(*(int*)data);
}		



void CGameObjectLayer::delayWinScene( float dt )
{
	
}


void CGameObjectLayer::addBullets(CCPoint &centerPoint)
{	
	//CCLOG("Shoot: %f",m_fTimeRetireBullet);
	float angle = -caculateAngle(ccp(LOCATION_X_TOWER,LOCATION_Y_TOWER),centerPoint);
	int a=2;
	float dx,dy;
	dx=centerPoint.x - LOCATION_X_TOWER;
	if(angle>-88 && angle <88 &&dx>0){
		switch(m_levelBullet){
		case BULLET_LEVEL_1:
			addOneBullet(centerPoint,-angle);
			break;
		case BULLET_LEVEL_2:

			dy= dx*tan((angle+a)/(180/PI));
			addOneBullet(ccp(centerPoint.x, LOCATION_Y_TOWER + dy),-(angle+a/2));
			dy= dx*tan((angle-a)/(180/PI));
			addOneBullet(ccp(centerPoint.x, LOCATION_Y_TOWER + dy),-(angle-a/2));
			break;
		case BULLET_LEVEL_3:
			dx=centerPoint.x - LOCATION_X_TOWER;
			addOneBullet(centerPoint, -angle);
			dy= dx*tan((angle+a)/(180/PI));
			addOneBullet(ccp(centerPoint.x, LOCATION_Y_TOWER + dy),-(angle+a));
			dy= dx*tan((angle-a)/(180/PI));
			addOneBullet(ccp(centerPoint.x, LOCATION_Y_TOWER + dy),-(angle-a));
			break;
		}
	}
}

void CGameObjectLayer::addOneBullet(CCPoint &p,float angle)
{
	char * path="";
	if(m_typeBullet==FIRE_BULLET) path="Bullets\\data use\\bullets_01.png";
	else path="Bullets\\data use\\bullets_01.png";
	switch(m_typeBullet){
	case FIRE_BULLET:
		switch(m_levelBullet){
		case BULLET_LEVEL_1:
			path="Bullets\\data use\\bullets_01.png";
			break;
		case BULLET_LEVEL_2:
			path="Bullets\\data use\\bullets_02.png";
			break;
		case BULLET_LEVEL_3:
			path="Bullets\\data use\\bullets_03.png";
			break;

		}
		m_pTowerItem->PlayAnimation(FIRE_TOWER,0.4f, true, false);
		break;
	case WATER_BULLET:
		switch(m_levelBullet){
		case BULLET_LEVEL_1:
			path="Bullets\\data use\\bullets_05.png";
			break;
		case BULLET_LEVEL_2:
			path="Bullets\\data use\\bullets_06.png";
			break;
		case BULLET_LEVEL_3:
			path="Bullets\\data use\\bullets_07.png";
			break;

		}
		m_pTowerItem->PlayAnimation(WATER_TOWER,0.4f, true, false);
		break;
	}
	CCSprite* sp = CCSprite::create(path);
	sp->setPosition(ccp(0,0));
	//sp->setScale(30.0/240.0);
	Bullet *newBullet= new Bullet(m_typeBullet,sp);
	newBullet->setType(m_typeBullet);
	newBullet->setPosition(ccp(LOCATION_X_TOWER + 15,LOCATION_Y_TOWER+30));
	newBullet->setRotation(angle);
	this->addChild(newBullet);
	m_arrBullet->addObject(newBullet);
	CCPoint realDest = getDestination(p.x,p.y);
	float dx=realDest.x-LOCATION_X_TOWER;
	float dy=realDest.y-LOCATION_Y_TOWER;
	float s=sqrt(dx*dx+dy*dy);
	float timeMoveDuration= s/m_fSpeed;
	newBullet->runAction( CCSequence::actions(
		CCMoveTo::actionWithDuration(timeMoveDuration, realDest),
		CCCallFuncN::actionWithTarget(this,
		callfuncN_selector(CGameObjectLayer::spriteMoveDone)), 
		NULL));

}

float CGameObjectLayer::caculateAngle(CCPoint v,CCPoint v1)
{

	float dx=v1.x - v.x;
	float dy=v1.y - v.y;

	float angle=-atan(dy/dx);
	angle = angle/(PI/180);
	return angle;
}

CCPoint CGameObjectLayer::getDestination(float X,float Y)
{
	
	float t;
	if(X-LOCATION_X_TOWER!= 0) t= 50/(X-LOCATION_X_TOWER);
	else t= 50/(Y-LOCATION_Y_TOWER);
	if(t<0) t=-t;
	float Vx=t*(X-LOCATION_X_TOWER);
	float Vy=t*(Y-LOCATION_Y_TOWER);
	float DestX=X;
	float DestY=Y;

	do{

		DestX+= Vx;
		DestY+= Vy;
		if(DestX < -20 || DestX > (size.width +20) || DestY<-20 || DestY > (size.height+20)) break;
	}
	while(1);
	return ccp(DestX,DestY);

}
void CGameObjectLayer::updateBullet(int type, int level)
{
	m_typeBullet = type;
	m_levelBullet = level;
	switch(m_typeBullet){
	case FIRE_BULLET:
		switch(m_levelBullet){
		case BULLET_LEVEL_1:
			loadTower("Tower\\Data\\tower_11.png","Tower\\tower.sprite");
			break;
		case BULLET_LEVEL_2:
			loadTower("Tower\\Data\\tower_12.png","Tower\\tower.sprite");
			break;
		case BULLET_LEVEL_3:
			loadTower("Tower\\Data\\tower_13.png","Tower\\tower.sprite");
			break;
			
		}
		m_pTowerItem->PlayAnimation(FIRE_TOWER,0.4f, true, false);
		break;
	case WATER_BULLET:
		switch(m_levelBullet){
		case BULLET_LEVEL_1:
			loadTower("Tower\\Data\\tower_08.png","Tower\\tower.sprite");
			break;
		case BULLET_LEVEL_2:
			loadTower("Tower\\Data\\tower_09.png","Tower\\tower.sprite");
			break;
		case BULLET_LEVEL_3:
			loadTower("Tower\\Data\\tower_10.png","Tower\\tower.sprite");
			break;

		}
		m_pTowerItem->PlayAnimation(WATER_TOWER,0.4f, true, false);
		break;
	}
	

}
void CGameObjectLayer::loadTower(char * base, char * item)
{
	this->removeChild(m_pBaseTower,true);
	m_pBaseTower=CCSprite::spriteWithFile(base);
	m_pBaseTower->setPosition(ccp(LOCATION_X_TOWER,LOCATION_Y_TOWER));
	this->addChild(m_pBaseTower);
	this->removeChild(m_pTowerItem,true);
	m_pTowerItem=new CMySprite(item);
	m_pTowerItem->setPosition(ccp(LOCATION_X_TOWER + 5,LOCATION_Y_TOWER+40));
	this->addChild(m_pTowerItem);

}
bool CGameObjectLayer::isClickSkill(CCPoint &p)
{
	
	return ((p.x>=LOCATION_X_SKILL - 30) && (p.x<= LOCATION_X_SKILL + 30) && (p.y>= LOCATION_Y_SKILL-30) && (p.y <= LOCATION_Y_SKILL+30));

}

void  CGameObjectLayer::addStarSkill(){
	//CCLOG("Click Skill");
	if(CCDirector::sharedDirector()->isPaused()) return;
	//CCDirector::sharedDirector()->getTouchDispatcher()->removeAllDelegates();
	CCLayerColor *PBlurLayer = CCLayerColor::create();
	PBlurLayer->setOpacityModifyRGB(true);
	PBlurLayer->setColor(ccc3(0,0,0));
	PBlurLayer->setOpacity(150);	
	CGamePlay::pSkillLayer = CSkillLayer::create();
	CGamePlay::pScene->addChild(CGamePlay::pSkillLayer, ZODER_GAMEPLAY_SKILL_LAYER, TAG_GAMEPLAY_SKILL_LAYER);
	CGamePlay::pScene->addChild(PBlurLayer, ZORDER_GAMEPLAY_COLOR_LAYER, TAG_GAMEPLAY_COLOR_LAYER);
	
}

void CGameObjectLayer::loadMap(){
	

}

void CGameObjectLayer::creatMonster(){
	if (m_time < m_totalTimeEachWay[0])
	{
		if (m_time<=m_totalTimeEachWay[0] - timeDelay)
		{
			indexTime = 0;
		}else{
			indexTime = 7;
		}
	}else if (m_time < m_totalTimeEachWay[1])
	{
		if (m_time<=m_totalTimeEachWay[1] - timeDelay)
		{
			indexTime = 1;
		}else{
			indexTime = 7;
		}
	}else if (m_time < m_totalTimeEachWay[2])
	{
		if (m_time<=m_totalTimeEachWay[2] - timeDelay)
		{
			indexTime = 2;
		}else{
			indexTime = 7;
		}
	}else if (m_time < m_totalTimeEachWay[3])
	{
		if (m_time<=m_totalTimeEachWay[3] - timeDelay)
		{
			indexTime = 3;
		}else{
			indexTime = 7;
		}
	}else if (m_time < m_totalTimeEachWay[4])
	{
		if (m_time<=m_totalTimeEachWay[4] - timeDelay)
		{
			indexTime = 4;
		}else{
			indexTime = 7;
		}
	}else if (m_time < m_totalTimeEachWay[5])
	{
			indexTime = 5;
	}else{
		indexTime = 6;
	}

	if (indexTime <6){
		switch (typeOfAppear[indexTime]){
		case 0:
			appearInOneRow();
			break;
		case 1:
			appearInTwoRows();
			break;
		case 2:
			appearInThreeRows();
			break;
		default:
			appearInMixture();
			break;
		}
	}
}

void CGameObjectLayer::attackTower(){
	if (towerHp>0)
	{
		CCObject *it = new CMonster;
		CCARRAY_FOREACH(m_arrMonster,it){
			CMonster * monsterD = (CMonster *)it;
			//m_activeHP->setScaleX((towerHp - monsterD->attackTowerWithDamage(m_time))/towerHp);
			towerHp = towerHp - monsterD->attackTowerWithDamage(m_time);
			if (towerHp>0)
			{
				m_activeHP->setScaleX(towerHp/(4.0f*CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerHp));
			}else{
				this->removeChild(m_activeHP,false);
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

void CGameObjectLayer::attackMonster()
{
	//CCArray *monsterToDelete = new CCArray;
	//for(CCSprite *it in _projectiles){
	CCObject *it = new CMonster;
	CCObject *jt = new Bullet;
	//_projectiles = dynamic_cast<CCSprite*>(it);
	CCARRAY_FOREACH(m_arrMonster,it){
		CMonster *monsterD = (CMonster*) it;
		CCRect monsterRect = getRectMonsterFire(monsterD);
		
		CCArray *bulletsToDelete = new CCArray;
		CCARRAY_FOREACH(m_arrBullet,jt){
			Bullet *bulletD = (Bullet*)jt;
			CCRect bulletRect = getRectBulletFire(bulletD);				
			if(CCRect::CCRectIntersectsRect(monsterRect, bulletRect)){
				bulletsToDelete->addObject(bulletD);
			}
		}
		CCARRAY_FOREACH(bulletsToDelete,jt){
			Bullet *bulletD= (Bullet*)jt;
			m_arrBullet->removeObject(bulletD);
			this->removeChild(bulletD, true);
		}
		if(bulletsToDelete->count() > 0)
		{
			//monsterToDelete->addObject(monsterD);
			if(monsterD->getType() == m_typeBullet){
				hitMonster(monsterD, CLevelManager::GetInstance()->GetLevelInformation()->m_iDameTowerCurrent);
			}else{
				int damage = (int)(CLevelManager::GetInstance()->GetLevelInformation()->m_iDameTowerCurrent * 0.75f);
				hitMonster(monsterD,damage);
			}
		bulletsToDelete->release();
	}
}
}

void CGameObjectLayer::initMap()
{
	int level = CLevelManager::GetInstance()->GetLevelInformation()->m_iLevelCurrent;
	int mapLevel = CLevelManager::GetInstance()->GetLevelInformation()->m_iMapCurrent;
	switch(level){
	case 1:
		timeDelay = 3.0f;
		numOfTime = 6;
		typeMonster = 1;
		numOfMonsterPTime = new int[6];
		typeOfAppear = new int[6];
		timeOfMonsterPerTime = new float[6];
		m_totalTimeEachWay = new float[6];
		timeForOneRow = new float[6];
		mixtureTime = new int[6];
		//typeOfAppear[i] = i;
		//timeOfMonsterPerTime[i] = 5.0f;

		numOfMonsterPTime[0] = 3;
		numOfMonsterPTime[1] = 4;
		numOfMonsterPTime[2] = 6;
		numOfMonsterPTime[3] = 6;
		numOfMonsterPTime[4] = 7;
		numOfMonsterPTime[5] = 9;


		typeOfAppear[0] = 0;
		typeOfAppear[1] = 0;
		typeOfAppear[2] = 0;
		typeOfAppear[3] = 1;
		typeOfAppear[4] = 1;
		typeOfAppear[5] = 2;

		timeOfMonsterPerTime[0] = 7.0f;
		timeOfMonsterPerTime[1] = 7.0f;
		timeOfMonsterPerTime[2] = 7.0f;
		timeOfMonsterPerTime[3] = 7.0f;
		timeOfMonsterPerTime[4] = 7.0f;
		timeOfMonsterPerTime[5] = 7.0f;

		break;
	case 2:
		timeDelay = 2.0f;
		numOfTime = 6;
		typeMonster = 1;
		numOfMonsterPTime = new int[6];
		typeOfAppear = new int[6];
		timeOfMonsterPerTime = new float[6];
		m_totalTimeEachWay = new float[6];
		timeForOneRow = new float[6];
		mixtureTime = new int[6];
		//typeOfAppear[i] = i;
		//timeOfMonsterPerTime[i] = 5.0f;

		numOfMonsterPTime[0] = 4;
		numOfMonsterPTime[1] = 5;
		numOfMonsterPTime[2] = 6;
		numOfMonsterPTime[3] = 8;
		numOfMonsterPTime[4] = 8;
		numOfMonsterPTime[5] = 8;


		typeOfAppear[0] = 0;
		typeOfAppear[1] = 0;
		typeOfAppear[2] = 1;
		typeOfAppear[3] = 1;
		typeOfAppear[4] = 2;
		typeOfAppear[5] = 2;

		timeOfMonsterPerTime[0] = 6.0f;
		timeOfMonsterPerTime[1] = 6.0f;
		timeOfMonsterPerTime[2] = 6.0f;
		timeOfMonsterPerTime[3] = 6.0f;
		timeOfMonsterPerTime[4] = 6.0f;
		timeOfMonsterPerTime[5] = 6.0f;

		break;
	default:
		timeDelay = 1.5f;
		numOfTime = 6;
		typeMonster = 1;
		numOfMonsterPTime = new int[6];
		typeOfAppear = new int[6];
		timeOfMonsterPerTime = new float[6];
		m_totalTimeEachWay = new float[6];
		timeForOneRow = new float[6];
		mixtureTime = new int[6];
		//typeOfAppear[i] = i;
		//timeOfMonsterPerTime[i] = 5.0f;

		numOfMonsterPTime[0] = 5;
		numOfMonsterPTime[1] = 6;
		numOfMonsterPTime[2] = 8;
		numOfMonsterPTime[3] = 9;
		numOfMonsterPTime[4] = 8;
		numOfMonsterPTime[5] = 8;


		typeOfAppear[0] = 0;
		typeOfAppear[1] = 0;
		typeOfAppear[2] = 1;
		typeOfAppear[3] = 2;
		typeOfAppear[4] = 3;
		typeOfAppear[5] = 3;

		timeOfMonsterPerTime[0] = 5.0f;
		timeOfMonsterPerTime[1] = 5.0f;
		timeOfMonsterPerTime[2] = 5.0f;
		timeOfMonsterPerTime[3] = 5.0f;
		timeOfMonsterPerTime[4] = 5.0f;
		timeOfMonsterPerTime[5] = 5.0f;

		break;
	}

	m_totalTimeEachWay[0] = timeOfMonsterPerTime[0] + timeDelay;
	m_totalTimeEachWay[1] = m_totalTimeEachWay[0] + timeOfMonsterPerTime[1] + timeDelay;
	m_totalTimeEachWay[2] = m_totalTimeEachWay[1] + timeOfMonsterPerTime[2] + timeDelay;
	m_totalTimeEachWay[3] = m_totalTimeEachWay[2] + timeOfMonsterPerTime[3] + timeDelay;
	m_totalTimeEachWay[4] = m_totalTimeEachWay[3] + timeOfMonsterPerTime[4] + timeDelay;
	m_totalTimeEachWay[5] = m_totalTimeEachWay[4] + timeOfMonsterPerTime[5];

	timeForOneRow[0] = 0;
	timeForOneRow[1] = m_totalTimeEachWay[0];
	timeForOneRow[2] = m_totalTimeEachWay[1];
	timeForOneRow[3] = m_totalTimeEachWay[2];
	timeForOneRow[4] = m_totalTimeEachWay[3];
	timeForOneRow[5] = m_totalTimeEachWay[4];

	for(int i = 0; i < 6 ; i++){
		mixtureTime[i] = 0;
	}

	indexTime = 0;
	timeForMixtureTime = 0.0f;
}

void CGameObjectLayer::appearInOneRow()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	float timeBetween = timeOfMonsterPerTime[indexTime]/(numOfMonsterPTime[indexTime]);
	if (timeForOneRow[indexTime] <= m_time)
	{
		TypeMonster type = (TypeMonster)randomTypeMonster();
		MonsterLevel level = (MonsterLevel)randomLevelMonster();
		int height = randomPosition((int)s.height/4, (int)s.height*3/4);
		CMonster * monster = new CMonster(type,level,height);
		this->addChild(monster, zBulletAndMonster);
		m_arrMonster->addObject(monster);
		timeForOneRow[indexTime] = timeForOneRow[indexTime] + timeBetween;
	}
	
}

void CGameObjectLayer::appearInTwoRows()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	float timeBetween = timeOfMonsterPerTime[indexTime] / (numOfMonsterPTime[indexTime]/2);
	if (timeForOneRow[indexTime] <= m_time)
	{
		//first monster
		TypeMonster type1 = (TypeMonster)randomTypeMonster();
		MonsterLevel level1 = (MonsterLevel)randomLevelMonster();
		int height1 = randomPosition((int)s.height/2+20,(int)s.height*3/4);
		//while(abs(height1 - (int)s.height/2) < 30){
			//height1 = randomPosition();
		//}
		CMonster * monster1 = new CMonster(type1,level1,height1);
		this->addChild(monster1, zBulletAndMonster);
		m_arrMonster->addObject(monster1);


		//second monster
		TypeMonster type2 = (TypeMonster)randomTypeMonster();
		MonsterLevel level2 = (MonsterLevel)randomLevelMonster();
		int height2 = randomPosition((int)s.width/4,height1 - 20);
		CMonster * monster2 = new CMonster(type2,level2,height2);
		this->addChild(monster2, zBulletAndMonster);
		m_arrMonster->addObject(monster2);

		timeForOneRow[indexTime] = timeForOneRow[indexTime] + timeBetween;
	}
}

void CGameObjectLayer::appearInThreeRows()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	float timeBetween = timeOfMonsterPerTime[indexTime] / (numOfMonsterPTime[indexTime]/3);
	if (timeForOneRow[indexTime] <= m_time)
	{
		//first monster
		TypeMonster type1 = (TypeMonster)randomTypeMonster();
		MonsterLevel level1 = (MonsterLevel)randomLevelMonster();
		int height1 = randomPosition((int)s.height/2+50,(int)s.height*3/4);
		CMonster * monster1 = new CMonster(type1,level1,height1);
		this->addChild(monster1, zBulletAndMonster);
		m_arrMonster->addObject(monster1);


		//second monster
		TypeMonster type2 = (TypeMonster)randomTypeMonster();
		MonsterLevel level2 = (MonsterLevel)randomLevelMonster();
		int height2 = (int)s.height-height1;
		CMonster * monster2 = new CMonster(type2,level2,height2);


		//third monster
		TypeMonster type3 = (TypeMonster)randomTypeMonster();
		MonsterLevel level3 = (MonsterLevel)randomLevelMonster();
		int height3 = randomPosition(height2+20,height1-20);
		CMonster * monster3 = new CMonster(type3,level3,height3);
		this->addChild(monster3, zBulletAndMonster);
		m_arrMonster->addObject(monster3);

		//add second monster
		this->addChild(monster2, zBulletAndMonster);
		m_arrMonster->addObject(monster2);

		timeForOneRow[indexTime] = timeForOneRow[indexTime] + timeBetween;
	}
}

void CGameObjectLayer::appearInMixture()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	int numOfMonster = (int)numOfMonsterPTime[indexTime]/2;
	if(m_time>=timeForMixtureTime){
		if(mixtureTime[indexTime]<2){
			for(int i = (int)s.height*3/4;i>=(int)s.height/4;i=i-(int)s.height/(numOfMonster*2)){
				if(mixtureTime[indexTime]==0){
					TypeMonster type = (TypeMonster)randomTypeMonster();
					MonsterLevel level = (MonsterLevel)randomLevelMonster();
					int height = i;
					CMonster * monster = new CMonster(type,level,height);
					this->addChild(monster, zBulletAndMonster);
					m_arrMonster->addObject(monster);
					timeForMixtureTime = m_time;
				}else{
					TypeMonster type = (TypeMonster)randomTypeMonster();
					MonsterLevel level = (MonsterLevel)randomLevelMonster();
					int height = i+10;
					CMonster * monster = new CMonster(type,level,height);
					this->addChild(monster, zBulletAndMonster);
					m_arrMonster->addObject(monster);
				}
			}
			mixtureTime[indexTime]++;
			timeForMixtureTime = timeForMixtureTime + 1.0f;
		}

	}
}

int CGameObjectLayer::randomLevelMonster()
{
	//if(typeMonster != 1){
		int minDuration = 0;
		int maxDuration = typeMonster;
		int rangeDuration = maxDuration - minDuration;
		//srand(time(NULL));
		//CCRANDOM_0_1()
		int actualDuration = (rand()%rangeDuration) + minDuration;
		return actualDuration;
	//}
	//return 0;
}

int CGameObjectLayer::randomTypeMonster()
{
	int minDuration = 0;
	int maxDuration = 2;
	int rangeDuration = maxDuration - minDuration;
	//srand(time(NULL));
	//CCRANDOM_0_1()
	int actualDuration = (rand()%rangeDuration) + minDuration;
	return actualDuration;
}

int CGameObjectLayer::randomPosition(int firstPos, int secondPos)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	int minDuration = firstPos;
	int maxDuration = secondPos;
	int rangeDuration = maxDuration - minDuration;
	//srand(time(NULL));
	//CCRANDOM_0_1()
	int actualDuration = (rand()%rangeDuration) + minDuration;
	return actualDuration;
}

void CGameObjectLayer::addMonsterToDelete( CMonster * monster, int damage )
{
	setCoinBonus(getCoinBonus()+monster->getCointBonus());
	monster->setDelayTimeDie(m_time);
	monster->monsterDie(monster->getHP());
	//cong tien them khi quai bi kill
	//CLevelManager::GetInstance()->GetLevelInformation()->m_iCoin += monster->getCoin();
	m_arrMonster->removeObject(monster);
	m_arrMonsterToDelete->addObject(monster);
}

void CGameObjectLayer::addDeleteMonster()
{
	CCObject *it = new CMonster();
	CCARRAY_FOREACH(m_arrMonsterToDelete,it){
		CMonster *monsterD = (CMonster*) it;
		if(monsterD->getDelayTimeDie()+10.0f<=m_time){
			//m_arrMonster->removeObject(monsterD);
			this->removeChild(monsterD,false);
		}
	}
}

cocos2d::CCRect CGameObjectLayer::getRectBulletFire( Bullet* pBullet )
{
	
	float angle = - (pBullet->getRotation());
	CCLOG("Angle = %f", angle);
	float orginX = pBullet->getPosition().x ;
	float orginY = pBullet->getPosition().y ;
	float orginWidth = pBullet->m_sprite->getContentSize().width;
	float orginHeight = pBullet->m_sprite->getContentSize().height;
	float asixX, asixY, width, height;
	if (angle >45.0f)
	{
		asixX = orginX ;
		asixY = orginY ;
		width = orginWidth/4.0f;
		height = orginHeight;
		return CCRectMake(asixX, asixY, width, height);
	}
	if ( angle > 30.0f )
	{
		asixX = orginX ;
		asixY = orginY ;
		width = orginWidth/2.0f - 5.0f;
		height = orginHeight - 5.0f;
		return CCRectMake(asixX, asixY, width, height);
	}
	if ( angle > 10.0f )
	{
		asixX = orginX ;
		asixY = orginY - orginHeight/2.0f + 10.0f;
		width = orginWidth/2.0f;
		height = orginHeight - 10.0f;
		return CCRectMake(asixX, asixY, width, height);
	}
	if (angle >= 0.0f )
	{
		asixX = orginX ;
		asixY = orginY - orginHeight/2.0f + 5.0f;
		width = orginWidth/2.0f;
		height = orginHeight - 10.0f;
		return CCRectMake(asixX, asixY, width, height);
	}
	if (angle < -45.0f)
	{
		asixX = orginX  ;
		asixY = orginY - orginHeight/2 - 10.0f;
		width = orginWidth/4.0f;
		height = orginHeight;
		return CCRectMake(asixX, asixY, width, height);
	}
	if (angle < -30.0f)
	{
		asixX = orginX ;
		asixY = orginY - orginHeight/2 - 5.0f;
		width = orginWidth/2.0f - 5.0f;
		height = orginHeight - 10.0f;
		return CCRectMake(asixX, asixY, width, height);
	}
	if (angle < 0.0f)
	{
		asixX = orginX ;
		asixY = orginY - orginHeight/2.0f - 5.0f ;
		width = orginWidth/2.0f;
		height = orginHeight - 5.0f;
		return CCRectMake(asixX, asixY, width, height);
	}				
	
}

cocos2d::CCRect CGameObjectLayer::getRectMonsterFire( CMonster* pMonster )
{
	return CCRectMake(pMonster->getPosition().x + 28.0f - pMonster->m_sprite->getContentSize().width/2.0f, 
		pMonster->getPosition().y - pMonster->m_sprite->getContentSize().height/2 + 5.0f,
		pMonster->m_sprite->getContentSize().width,
		pMonster->m_sprite->getContentSize().height - 5.0f);
}

void CGameObjectLayer::addSkillAnimation( int typeSkill)
{
	//TEST insert demo skill
	for (int i=0; i<3; i++)
	{
		CMySprite* pSprite = new CMySprite("SkillAnimation\\skill_explode_earth.sprite");
		pSprite->setPosition(ccp(size.width/2.0f + i*200.0f, size.height/2.0f + 100.0f));
		pSprite->setScale(2.5f);
		this->addChild(pSprite, zSkill);
		pSprite->PlayAnimation(0, 3.0f, 1, false);
	}
}

void CGameObjectLayer::processWhenMonsterDie( CMonster* pMonster )
{
	// cong them nang luon
	m_iCurrentEnegy += pMonster->getPower();
	//playAnimation Monster Die
	
	if(m_iCurrentEnegy >= MAX_ENEGY )
	{
		m_bIsFullEmergy = true;
		m_bToggle=true;
	}
	

}



void CGameObjectLayer::hitMonster( CMonster * monster, int damage )
{
	if(monster->getHP() > damage){
		hurtMonster(monster, damage);
	}else {
	//CLevelManager::GetInstance()->GetLevelInformation()->m_iDameTowerCurrent;
		addMonsterToDelete(monster, damage);
	}
}

void CGameObjectLayer::hurtMonster( CMonster *monster, int damage )
{
	monster->setHP(monster->getHP()-damage);
	monster->hitMonster(damage);
}

void CGameObjectLayer::processLabelCoin()
{
	char bufTem[20] = "";
	sprintf(bufTem, "%d", CLevelManager::GetInstance()->GetLevelInformation()->m_iCoin);
	m_pLabelCoinCollect->setString(bufTem);
}

void CGameObjectLayer::addSkillButton()
{
	this->removeChild(m_pSkill,true);
	char* path="";
	if(m_typeBullet == FIRE_BULLET)
	{
		switch(m_levelBullet){
		case BULLET_LEVEL_1:
			path = "Skill\\magic_button_fire1.png";
			break;
		case BULLET_LEVEL_2:
			path = "Skill\\magic_button_fire2.png";
			break;
		case BULLET_LEVEL_3:
			path = "Skill\\magic_button_fire3.png";
			break;
		}
		
	}
	else
	{
		switch(m_levelBullet){
		case BULLET_LEVEL_1:
			path = "Skill\\magic_button_ice1.png";
			break;
		case BULLET_LEVEL_2:
			path = "Skill\\magic_button_ice2.png";
			break;
		case BULLET_LEVEL_3:
			path = "Skill\\magic_button_ice3.png";
			break;
		}
	}
	m_pSkill = CCSprite::spriteWithFile(path);
	m_pSkill->setPosition(ccp(LOCATION_X_SKILL, LOCATION_Y_SKILL));
	this->addChild(m_pSkill);
}
