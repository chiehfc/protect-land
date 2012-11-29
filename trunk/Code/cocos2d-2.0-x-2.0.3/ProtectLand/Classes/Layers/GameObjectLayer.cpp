#include "GameObjectLayer.h"
#include "GameConfig.h"
#include "MySprite.h"
#include "GameConfig.h"
#include "GamePlay.h"
#include "MenuLayer.h"
#include "SkillLayer.h"

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


	CCSize s = CCDirector::sharedDirector()->getWinSize();
	//init value
	{
		oneMonster = false;
		m_checkLose = false;
		m_time = 0;
		m_arrMonster = new CCArray;
		m_arrBullet = new CCArray;
		m_index = -1;	

	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();	
	loadMap();



	// create menu, it's an autorelease object
	{
		CCMenuItemImage *pSubMenu = CCMenuItemImage::create(
			"PauseGame.png",
			"PauseGameSelected.png",
			this,
			menu_selector(CGameObjectLayer::menuSubMenuCallback));
		pSubMenu->setPosition( ccp(s.width -70 , s.height -40) );
		this->pMenu = CCMenu::create(pSubMenu, NULL);
		this->pMenu->setPosition( CCPointZero );	

		CCMenuItemImage *pReplay = CCMenuItemImage::create(
			"ReplayNormal.png",
			"ReplaySelected.png",
			this,
			menu_selector(CGameObjectLayer::menuReplayMenuCallback));
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
		m_bIsFinshChooseSkill = false; // gan gia tri ban dau la false, tuc chua them skill
		m_bIscol = false;
		m_bIsTouching = false;
		this->m_pObject = NULL;
		this->pMoveSprite = NULL;		

		this->pMenu->setEnabled(true);

		m_pBaseTower=CCSprite::spriteWithFile("Tower\\Data\\tower_11.png");
		m_pBaseTower->setPosition(ccp(LOCATION_X_TOWER,LOCATION_Y_TOWER));
		this->addChild(m_pBaseTower);
		m_pTowerItem=new CMySprite("Tower\\tower.sprite");
		m_pTowerItem->setPosition(ccp(LOCATION_X_TOWER+10,LOCATION_Y_TOWER+20));
		this->addChild(m_pTowerItem);
		m_pTowerItem->PlayAnimation(FIRE_TOWER, 0.4f, true, false);
		m_timeSkill = 0;
		m_isClickSkill = false;
		m_isClickChangeBullet = false;
		m_fSpeed = 1000;
		m_isFullEmergy = true;
		m_fTimeRetireBullet = 0;
		m_TimeDelayBullet = CLevelManager::GetInstance()->GetLevelInformation()->m_fTowerSpeed;
		m_levelBullet = CLevelManager::GetInstance()->GetLevelInformation()->m_iLevelTower;
	}		

	
	// TEST
	// them layskill nhan du kien touch
	addStarSkill();


	

	CAudioManager::instance()->stopAllEff();
	CAudioManager::instance()->stopBGMusic();
	CAudioManager::instance()->playBGMusic(SOUND_GAMEPLAY_BAGROUND_1, true);
	scheduleUpdate();
	return true;
}

void CGameObjectLayer::update(float dt)
{
	//CCLOG("%f",m_fTimeRetireBullet);

	m_fTimeRetireBullet += dt;
	if(m_bIsTouching){
		if(m_fTimeRetireBullet>m_TimeDelayBullet){
			addBullets(m_pCurrentPoint);
			m_fTimeRetireBullet=0;
		}
	}

	if(!oneMonster){
		if(m_time >4 && m_time <4.1){
			creatMonster();
			oneMonster = true;
		}
	}
	//attackTower();
	attackMonster();
	m_time = m_time + dt;

	if ()
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
		m_pCurrentPoint = pTouch->getLocation();
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
	CCSize size= CCDirector::sharedDirector()->getWinSize();
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
bool CGameObjectLayer::isSelectSkill(CCPoint *p)
{
	if(m_isFullEmergy){
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		int xLeft=size.width/2.0 + AREA_SHOOT_BULLET_WIDTH/2 +10;
		int xRight=xLeft+60;
		int yMin= 10;
		int yMax= yMin+60;
		int realX = p->x;
		int realY = p->y;
		if(realY>= yMin && realY<=yMax && realX>=xLeft && realX<=xRight){
			return true;
		}
		return false;
	}
	return false;

}

void  CGameObjectLayer::addStarSkill(){
	//CCLOG("Click Skill");
	if(CCDirector::sharedDirector()->isPaused()) return;
	CCDirector::sharedDirector()->getTouchDispatcher()->removeAllDelegates();
	CCLayerColor *PBlurLayer = CCLayerColor::create();
	PBlurLayer->setOpacityModifyRGB(true);
	PBlurLayer->setColor(ccc3(0,0,0));
	PBlurLayer->setOpacity(150);
	CGamePlay::pSkillLayer = CSkillLayer::create();
	CGamePlay::pScene->addChild(CGamePlay::pSkillLayer, ZODER_GAMEPLAY_SKILL_LAYER, TAG_GAMEPLAY_SKILL_LAYER);
	CGamePlay::pScene->addChild(PBlurLayer, ZORDER_GAMEPLAY_COLOR_LAYER, TAG_GAMEPLAY_COLOR_LAYER);


}
void CGameObjectLayer::loadMap(){
	CCSize size = CCDirector::sharedDirector()->getWinSize();	

}

void CGameObjectLayer::creatMonster(){
	CMonster * newMonster = new CMonster(FIRE_MONSTER,LEVEL1_MONSTER);
	this->addChild(newMonster);
	m_arrMonster->addObject(newMonster);
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
	CCArray *monsterToDelete = new CCArray;
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
			monsterToDelete->addObject(monsterD);
		}
		bulletsToDelete->release();
	}
	CCARRAY_FOREACH(monsterToDelete,it){
		CMonster* monsterD = (CMonster*)it;
		m_arrMonster->removeObject(monsterD);
		this->removeChild(monsterD,true);
	}
	monsterToDelete->release();
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

void CGameObjectLayer::addSkillAnimation( int typeSkill )
{
	//TEST insert demo skill
	for (int i=0; i<3; i++)
	{
		CMySprite* pSprite = new CMySprite("SkillAnimation\\skill_explode_earth.sprite");
		pSprite->setPosition(ccp(pTouch->getLocation().x + i*200.0f, pTouch->getLocation().y + 100.0f));
		pSprite->setScale(2.5f);
		this->addChild(pSprite);
		pSprite->PlayAnimation(0, 3.0f, 1, false);
	}
}
