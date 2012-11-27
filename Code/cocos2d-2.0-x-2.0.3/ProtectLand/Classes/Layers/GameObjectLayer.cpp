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
		m_bIscol = false;
		m_bIsTouching = false;
		this->m_pObject = NULL;
		this->pMoveSprite = NULL;		

		this->pMenu->setEnabled(true);
	
		m_pBaseTower=CCSprite::spriteWithFile("Tower\\Data\\tower_11.png");
		m_pBaseTower->setPosition(ccp(LOCATION_X_TOWER,LOCATION_Y_TOWER));
		m_iCurrentBullet=FIRE_BULLET_0;
		this->addChild(m_pBaseTower);
		m_pTowerItem=new CMySprite("Tower\\tower.sprite");
		m_pTowerItem->setPosition(ccp(LOCATION_X_TOWER+10,LOCATION_Y_TOWER+20));
		this->addChild(m_pTowerItem);
		m_pTowerItem->PlayAnimation(FIRE_TOWER,0.4f, true, false);
		m_timeSkill=0;
		m_isClickSkill=false;
		m_isClickChangeBullet=false;
	    m_fSpeed=300;
		m_isFullEmergy=true;
		m_fTimeRetireBullet=0;
		m_TimeDelayBullet=0.5;
		
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
	
	creatMonster();
	attackTower();
	attackMonster();
	m_time = m_time + dt;
	m_fTimeRetireBullet+= dt;
	
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
			if(m_fTimeRetireBullet>m_TimeDelayBullet){
				addBullet(pTouch->getLocation());
				m_fTimeRetireBullet=0;
			}
	}
	return true;
}

void CGameObjectLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{	
	if(m_bIsTouching)
	{
		m_bIscol = false;
		if(m_fTimeRetireBullet>m_TimeDelayBullet){
			addBullet(pTouch->getLocation());
			m_fTimeRetireBullet=0;
		}
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
	CGamePlay::checkWin();
}
void CGameObjectLayer::changeBullet()
{	
	m_isClickChangeBullet=true;
	if(m_iCurrentBullet==FIRE_BULLET_0) {
		m_iCurrentBullet=WATER_BULLET_0;
		
	}
	else{
		if(m_iCurrentBullet==WATER_BULLET_0)
		m_iCurrentBullet=FIRE_BULLET_0;		
	}
	
}

void CGameObjectLayer::addBullet(CCPoint &p)
{
	char * path="";
	if(m_iCurrentBullet==FIRE_BULLET_0) path="Bullets\\data use\\bullets_01.png";
	else path="Bullets\\data use\\bullets_01.png";
	CCSprite* sp = CCSprite::create(path);
	sp->setPosition(ccp(0,0));
	//sp->setScale(30.0/240.0);
	Bullet *newBullet= new Bullet(m_iCurrentBullet,sp);
	newBullet->setType(m_iCurrentBullet);
	newBullet->setPosition(ccp(LOCATION_X_TOWER,LOCATION_Y_TOWER));
	//caculate Angle Rotate

	///////////////////////

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

float CGameObjectLayer::caculateAngle(CCPoint v,CCPoint v1,CCPoint v2)
{
	return 0.0f;
}
bool CGameObjectLayer::inAreaShoot(const CCPoint *p)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	return (p->x >= size.width/2 - AREA_SHOOT_BULLET_WIDTH/2) && (p->x <= size.width/2 + AREA_SHOOT_BULLET_WIDTH/2)
		&&(p->y >= 40 - AREA_SHOOT_BULLET_HEIGHT/2) && (p->y <= 40 + AREA_SHOOT_BULLET_HEIGHT/2);
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
void CGameObjectLayer::updateBullet()
{
	

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
	CCLOG("Click Skill");
	if(CCDirector::sharedDirector()->isPaused()) return;
	CCDirector::sharedDirector()->getTouchDispatcher()->removeAllDelegates();
	//this->setTouchEnabled(false);
	//CCDirector::sharedDirector()->pause();
	CCLayerColor *PBlurLayer = CCLayerColor::create();
	PBlurLayer->setOpacityModifyRGB(true);
	PBlurLayer->setColor(ccc3(0,0,0));
	PBlurLayer->setOpacity(150);
	CGamePlay::pSkillLayer = CSkillLayer::create();
	CGamePlay::pScene->addChild(CGamePlay::pSkillLayer, ZODER_GAMEPLAY_MENU_LAYER, TAG_GAMEPLAY_MENU_LAYER);
	CGamePlay::pScene->addChild(PBlurLayer, ZORDER_GAMEPLAY_COLOR_LAYER, TAG_GAMEPLAY_COLOR_LAYER);
	

}
void CGameObjectLayer::loadMap(){
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pSprite = CCSprite::create("Background\\background_package_level_1.png");
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
	for (int i = 0; i<20; i++)
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

void CGameObjectLayer::attackMonster()
{
	CCArray *monsterToDelete = new CCArray;
	//for(CCSprite *it in _projectiles){
	CCObject *it = new CMonster;
	CCObject *jt = new Bullet;
	//_projectiles = dynamic_cast<CCSprite*>(it);
	CCARRAY_FOREACH(m_arrMonster,it){
		CMonster *monsterD = (CMonster*) it;
		CCRect monsterRect = CCRectMake(monsterD->getPosition().x - monsterD->m_sprite->getContentSize().width*0.2/2,monsterD->getPosition().y-monsterD->m_sprite->getContentSize().height*0.2/2,monsterD->m_sprite->getContentSize().width*0.2,monsterD->m_sprite->getContentSize().height*0.2);
		CCArray *bulletsToDelete = new CCArray;
		CCARRAY_FOREACH(m_arrBullet,jt){
			Bullet *bulletD = (Bullet*)jt;
			CCRect bulletRect = CCRectMake(bulletD->getPosition().x- bulletD->m_sprite->getContentSize().width*30.0/128.0/2,bulletD->getPosition().y-bulletD->m_sprite->getContentSize().height*30.0/128.0/2,bulletD->m_sprite->getContentSize().width*30.0/128.0,bulletD->m_sprite->getContentSize().height*30.0/128.0);
			if(CCRect::CCRectIntersectsRect(monsterRect,bulletRect)){
				bulletsToDelete->addObject(bulletD);
			}
		}
		CCARRAY_FOREACH(bulletsToDelete,jt){
			Bullet *bulletD= (Bullet*)jt;
			m_arrBullet->removeObject(bulletD);
			this->removeChild(bulletD,true);
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
