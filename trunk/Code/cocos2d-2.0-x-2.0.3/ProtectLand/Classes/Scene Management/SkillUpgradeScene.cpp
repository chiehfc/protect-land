#include "SkillUpgradeScene.h"
#include "GamePlay.h"
#include "IncludeHelper.h"
#include "PositionConfig.h"
USING_NS_CC;

CCScene* CSkillUpgradeScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	CSkillUpgradeScene *layer = CSkillUpgradeScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool CSkillUpgradeScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	m_fTowerSpeed = 1.0f * pow(0.9, CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerSpeed - 1) ;
	m_iDameTowerCurrent = CLevelManager::GetInstance()->GetLevelInformation()->m_iDameTowerCurrent;
	m_iLevelTower = CLevelManager::GetInstance()->GetLevelInformation()->m_iLevelTower;
	m_iRateDoubleDamge = CLevelManager::GetInstance()->GetLevelInformation()->m_iRateDoubleDamge;
	pMenu = CCMenu::create(NULL, NULL);
	pMenu->setPosition( CCPointZero );	

	{
		
		//create button Play
		CCMenuItemImage *pPlay = CCMenuItemImage::create(
			"Button\\play_down.png",
			"Button\\play_up.png",
			this,
			menu_selector(CSkillUpgradeScene::menuPlayCallBack));	
		pPlay->setPosition(LOCATION_BUTTON_PLAY_SUG) ;
		pMenu->addChild(pPlay);

		//craete button Back
		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
			"Button\\back_down.png",
			"Button\\back_up.png",
			this,
			menu_selector(CSkillUpgradeScene::menuBackCallBack));
		pCloseItem->setPosition(LOCATION_BUTTON_BACK_SLS);
		pMenu->addChild(pCloseItem);
	}
	this->addChild(pMenu, 3);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, TOUCH_PRIORITY_MAIN_LAYER , true);
	this->setTouchEnabled(true);
	size = CCDirector::sharedDirector()->getWinSize();
	createLabelAndItem();

	return true;

}
void CSkillUpgradeScene::update(float dt){


}
void CSkillUpgradeScene::render(){

}
void CSkillUpgradeScene::exit(){

}

void CSkillUpgradeScene::menuPlayCallBack( CCObject* pSender )
{
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
	CAudioManager::instance()->playEff(SOUND_CLICK_1);	
	CCScene *gameplayScene = CGamePlay::scene();
	CCScene* pScene = CCTransitionCrossFade::create(TRANSITION_DURATION, gameplayScene);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	} 
}


bool CSkillUpgradeScene::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{

	CCLOG("ccp(%d, %d)",(int)pTouch->getLocation().x,(int)pTouch->getLocation().y);
	return true;
}
void CSkillUpgradeScene::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLOG("ccp(%d, %d)",(int)pTouch->getLocation().x,(int)pTouch->getLocation().y);

}
void CSkillUpgradeScene::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void CSkillUpgradeScene::addSpire(CCSprite **m_sprite, char* path, CCPoint &position, float scaleX,float scaleY)
{

	*m_sprite = CCSprite::spriteWithFile(path);
	(*m_sprite)->setScaleX(scaleX);
	(*m_sprite)->setScaleY(scaleY);
	(*m_sprite)->setPosition(position);
	this->addChild(*m_sprite);
}

void CSkillUpgradeScene::addLabel(CCLabelBMFont **pLabel, ccColor3B &color, int width, CCPoint &position,char* str,float scale)
{
	*pLabel = CCLabelBMFont::create(str, "fonts/myFont.fnt",width );

	(*pLabel)->setColor(color);
	(*pLabel)->setScale(scale);

	(*pLabel)->setAnchorPoint(ccp(0, 1));
	(*pLabel)->setPosition( position);
	this->addChild(*pLabel, 2);
}

void CSkillUpgradeScene::createLabelAndItem()
{
	addSpire(&m_pBackground,"SkillScreen\\background2.png",ccp(size.width/2.0f,size.height/2.0f),1.0f,1.0f);
	addSpire(&m_pBackground,"SkillScreen\\background.png",LOCATION_BACKGROUND,SCALE_BACKROUND,SCALE_BACKROUND);
	m_pLogoSelect = CCSprite::spriteWithFile("SkillScreen\\logo_select.png");
	m_pLogoSelect->setScale(SCALE_ITEM);
	m_pLogoSelect->setPosition(LOCATION_WALL_ITEM);
	this->addChild(m_pLogoSelect,10);



	CCMenu* pMenu = CCMenu::create();
	addSpire(&m_pLine,"SkillScreen\\line.png", LOCATION_LINE, SCALE_BACKROUND, SCALE_BACKROUND);
	m_pWall = CCMenuItemImage::create(
		"SkillScreen\\wall.png",
		"SkillScreen\\wall.png",
		this,
		menu_selector(CSkillUpgradeScene::buttonWallCallback));
	setButton(m_pWall, LOCATION_WALL_ITEM, SCALE_ITEM);
	pMenu->addChild(m_pWall);
	addSpire(&m_pBorder,"SkillScreen\\border_item.png", LOCATION_WALL_ITEM, SCALE_ITEM, SCALE_ITEM);

	m_pLevel = CCMenuItemImage::create(
		"SkillScreen\\level.png",
		"SkillScreen\\level.png",
		this,
		menu_selector(CSkillUpgradeScene::buttonLevelCallback));
	setButton(m_pLevel, LOCATION_LEVEL_ITEM, SCALE_ITEM);
	pMenu->addChild(m_pLevel);
	addSpire(&m_pBorder,"SkillScreen\\border_item.png",LOCATION_LEVEL_ITEM,SCALE_ITEM,SCALE_ITEM);

	m_pSpeed = CCMenuItemImage::create(
		"SkillScreen\\speed.png",
		"SkillScreen\\speed.png",
		this,
		menu_selector(CSkillUpgradeScene::buttonSpeedCallback));
	setButton(m_pSpeed, LOCATION_SPEED_ITEM, SCALE_ITEM);
	pMenu->addChild(m_pSpeed);
	addSpire(&m_pBorder,"SkillScreen\\border_item.png",LOCATION_SPEED_ITEM,SCALE_ITEM,SCALE_ITEM);

	m_pDamage = CCMenuItemImage::create(
		"SkillScreen\\damage.png",
		"SkillScreen\\damage.png",
		this,
		menu_selector(CSkillUpgradeScene::buttonDamageCallback));
	setButton(m_pDamage, LOCATION_DAME_ITEM, SCALE_ITEM);
	pMenu->addChild(m_pDamage);
	addSpire(&m_pBorder,"SkillScreen\\border_item.png",LOCATION_DAME_ITEM,SCALE_ITEM,SCALE_ITEM);

	m_pRateDamage = CCMenuItemImage::create(
		"SkillScreen\\rateDamage.png",
		"SkillScreen\\rateDamage.png",
		this,
		menu_selector(CSkillUpgradeScene::buttonRateCallback));
	setButton(m_pRateDamage, LOCATION_RATEDAME_ITEM, SCALE_ITEM);
	pMenu->addChild(m_pRateDamage);
	addSpire(&m_pBorder,"SkillScreen\\border_item.png",LOCATION_RATEDAME_ITEM,SCALE_ITEM,SCALE_ITEM);
	m_pBorder = NULL;
	m_pBuy = CCMenuItemImage::create(
		"Button\\upgrade_down.png",
		"Button\\upgrade_down.png",
		this,
		menu_selector(CSkillUpgradeScene::buttonBuyCallback));
	m_pBuy->setPosition(LOCATION_UPGRADE);
	m_pBuy->setScaleX(SCALE_ITEM*0.5);
	m_pBuy->setScaleY(SCALE_ITEM*0.5);
	pMenu->addChild(m_pBuy);


	pMenu->setPosition(ccp(0,0));
	this->addChild(pMenu);
	addLabel(&m_lable1,ccc3(255,255,0),200,LOCATION_NAME_LABEL,"Wall Protect",1.0);
	addLabel(&m_lable2,ccc3(255,255,255),250,LOCATION_DETAIL_LABEL,"Can cause double the damage at certain probability",0.7);
	addLabel(&m_lable3,ccc3(255,126,0),100,LOCATION_CURRENT_LABEL,"Current Probability:",0.7);
	char buf[30];
	sprintf(buf,"%d",CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerHp);
	addLabel(&m_lable4,ccc3(0,255,0),100,LOCATION_CURRENTVALUE_LABEL,"24:",0.7);
	addLabel(&m_lable5,ccc3(255,126,0),100,LOCATION_NEXT_LABEL,"Next level:",0.7);
	sprintf(buf,"%d",CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerHp + HP_UPDATE);
	addLabel(&m_lable6,ccc3(0,255,0),100,LOCATION_NEXTVALUE_LABEL,buf,0.7);
	sprintf(buf,"%d",((CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerHp - INIT_TOWER_HP +10)/10)*50);//num of coin to buy
	addLabel(&m_lable7,ccc3(255,255,0),100,LOCATION_COIN2_LABEL,buf,1.3);
	sprintf(buf,"%d",CLevelManager::GetInstance()->GetLevelInformation()->m_iCoin);
	addLabel(&m_lable8,ccc3(255,255,0),100,LOCATION_COIN_LABEL,buf,1.3);
	int t1=((CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerHp - INIT_TOWER_HP +10)/10)*50;
	int t2=CLevelManager::GetInstance()->GetLevelInformation()->m_iCoin;
	if(t2 >= t1) addSpire(&m_pBorder,"SkillScreen\\buy2.png",LOCATION_UPGRADE_BORDER,SCALE_ITEM*0.75,SCALE_ITEM*0.5);
	m_iCoinToBuy = t1;
	m_iCurentItemSelect = WALL_ITEM;
	char buf1[20] = "";
	sprintf(buf1, " %d", CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerHp);
	char buf2[20] = "";
	sprintf(buf2, " %d", CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerHp + HP_UPDATE);
	m_lable1->setString("Wall Protect");
	m_lable2->setString("Increase your HP");
	m_lable3->setString("Current HP:");
	m_lable4->setString(buf1);
	m_lable5->setString("Next level:");
	m_lable6->setString(buf2);
	addSpire(&m_pCoin,"SkillScreen\\current_coin.png", LOCATION_COIN, SCALE_ITEM, SCALE_ITEM);
	addSpire(&m_pCoin2,"SkillScreen\\coin.png", LOCATION_COIN2, 1.0f, 1.0f);

}

void CSkillUpgradeScene::setButton( CCMenuItemImage *m_button,CCPoint &position, float scale )
{
	m_button->setPosition(position);
	m_button->setScale(scale);
}

void CSkillUpgradeScene::buttonWallCallback( CCObject* pSender )
{
	m_pLogoSelect->setPosition(LOCATION_WALL_ITEM);
	this->removeChild(m_pBorder,true);
	char buf[10] = "";

	int t1=((CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerHp - INIT_TOWER_HP +10)/10)*50;//num of coin to buy
	int t2=CLevelManager::GetInstance()->GetLevelInformation()->m_iCoin;
	if(t2 >= t1) addSpire(&m_pBorder,"SkillScreen\\buy2.png",LOCATION_UPGRADE_BORDER,SCALE_ITEM*0.75,SCALE_ITEM*0.5);
	m_iCoinToBuy = t1;
	m_iCurentItemSelect = WALL_ITEM;
	m_lable1->setString("Wall Protect");
	m_lable2->setString("Increase your HP");
	m_lable3->setString("Current HP:");
	sprintf(buf, " %d", CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerHp);
	m_lable4->setString(buf);
	m_lable5->setString("Next level:");
	sprintf(buf, " %d", CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerHp + HP_UPDATE);
	m_lable6->setString(buf);
	sprintf(buf,"%d",((CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerHp - INIT_TOWER_HP +10)/10)*50);
	m_lable7->setString(buf);	

}

void CSkillUpgradeScene::buttonLevelCallback( CCObject* pSender )
{
	m_pLogoSelect->setPosition(LOCATION_LEVEL_ITEM);
	this->removeChild(m_pBorder,true);
	char buf1[20] = "";
	sprintf(buf1, " %d", CLevelManager::GetInstance()->GetLevelInformation()->m_iLevelTower);
	char buf2[20] = "";
	if(CLevelManager::GetInstance()->GetLevelInformation()->m_iLevelTower>=3){
		sprintf(buf2, "Max");
		m_iCoinToBuy = -1;
	}
	else{
		sprintf(buf2, " %d", CLevelManager::GetInstance()->GetLevelInformation()->m_iLevelTower + LEVEL_UPDATE);
		int t1=(CLevelManager::GetInstance()->GetLevelInformation()->m_iLevelTower)*3*50;//num of coin to buy
		int t2=CLevelManager::GetInstance()->GetLevelInformation()->m_iCoin;
		if(t2 >= t1) addSpire(&m_pBorder,"SkillScreen\\buy2.png",LOCATION_UPGRADE_BORDER,SCALE_ITEM*0.75,SCALE_ITEM*0.5);
		m_iCoinToBuy = t1;
	}

	m_iCurentItemSelect = LEVEL_ITEM;


	m_lable1->setString("Level Tower");
	m_lable2->setString("Increase number of bullets");
	m_lable3->setString("Current level:");
	m_lable4->setString(buf1);
	m_lable5->setString("Next level:");
	m_lable6->setString(buf2);
	sprintf(buf2,"%d",(CLevelManager::GetInstance()->GetLevelInformation()->m_iLevelTower)*3*50);
	m_lable7->setString(buf2);	


}

void CSkillUpgradeScene::buttonSpeedCallback( CCObject* pSender )
{
	m_pLogoSelect->setPosition(LOCATION_SPEED_ITEM);
	this->removeChild(m_pBorder,true);
	
	char buf1[20] = "";
	sprintf(buf1, " %d", CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerSpeed);
	char buf2[20] = "";
	sprintf(buf2, " %d", CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerSpeed + SPEED_UPDATE);


	m_lable1->setString("Speed Tower");
	m_lable2->setString("Increase number of bullets perhap second");
	m_lable3->setString("Current level:");
	m_lable4->setString(buf1);
	m_lable5->setString("Next level:");
	m_lable6->setString(buf2);
	sprintf(buf2,"%d",(CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerSpeed)*50);
	m_lable7->setString(buf2);	

	int t1=(CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerSpeed)*50;//num of coin to buy
	int t2=CLevelManager::GetInstance()->GetLevelInformation()->m_iCoin;
	if(t2 >= t1) addSpire(&m_pBorder,"SkillScreen\\buy2.png", LOCATION_UPGRADE_BORDER, SCALE_ITEM*0.75, SCALE_ITEM*0.5);
	m_iCoinToBuy = t1;
	m_iCurentItemSelect = SPEED_ITEM;
}

void CSkillUpgradeScene::buttonDamageCallback( CCObject* pSender )
{
	m_pLogoSelect->setPosition(LOCATION_DAME_ITEM);
	this->removeChild(m_pBorder,true);
	char buf1[10] = "";
	sprintf(buf1, " %d", CLevelManager::GetInstance()->GetLevelInformation()->m_iDameTowerCurrent);
	char buf2[10] = "";
	sprintf(buf2, " %d", CLevelManager::GetInstance()->GetLevelInformation()->m_iDameTowerCurrent + DAMAGE_UPDATE);
	m_lable1->setString("Damage");
	m_lable2->setString("Increase damage of tower");
	m_lable3->setString("Current damage:");
	m_lable4->setString(buf1);
	m_lable5->setString("Next level:");
	m_lable6->setString(buf2);
	sprintf(buf2,"%d",((CLevelManager::GetInstance()->GetLevelInformation()->m_iDameTowerCurrent - INIT_DAMGE_TOWER +10)/10)*50);
	m_lable7->setString(buf2);	

	int t1=((CLevelManager::GetInstance()->GetLevelInformation()->m_iDameTowerCurrent - INIT_DAMGE_TOWER +10)/10)*50;//num of coin to buy
	int t2=CLevelManager::GetInstance()->GetLevelInformation()->m_iCoin;
	if(t2 >= t1) addSpire(&m_pBorder,"SkillScreen\\buy2.png", LOCATION_UPGRADE_BORDER, SCALE_ITEM*0.75, SCALE_ITEM*0.5);
	m_iCoinToBuy = t1;
	m_iCurentItemSelect = DAMAGE_ITEM;

}

void CSkillUpgradeScene::buttonRateCallback( CCObject* pSender )
{
	this->removeChild(m_pBorder,true);
	m_pLogoSelect->setPosition(LOCATION_RATEDAME_ITEM);
	//this->removeChild(m_pLogoSelect,true);
	//addSpire(&m_pLogoSelect,"SkillScreen\\logo_select.png", LOCATION_RATEDAME_ITEM, SCALE_ITEM,SCALE_ITEM);
	char buf1[10] = "";
	sprintf(buf1, " %d %%", CLevelManager::GetInstance()->GetLevelInformation()->m_iRateDoubleDamge);
	char buf2[10] = "";
	if(CLevelManager::GetInstance()->GetLevelInformation()->m_iRateDoubleDamge >= 100)
	{
		sprintf(buf2, " Max");
		m_iCoinToBuy = -1;
	}
	else{
		sprintf(buf2, " %d %%", CLevelManager::GetInstance()->GetLevelInformation()->m_iRateDoubleDamge + RATEDAMAGE_UPDATE);
		int t1=((CLevelManager::GetInstance()->GetLevelInformation()->m_iRateDoubleDamge - INIT_RATE_DOUBLE_DAMGE +5)/5)*50;//num of coin to buy
		int t2=CLevelManager::GetInstance()->GetLevelInformation()->m_iCoin;
		if(t2 >= t1) addSpire(&m_pBorder,"SkillScreen\\buy2.png", LOCATION_UPGRADE_BORDER, SCALE_ITEM*0.75, SCALE_ITEM*0.5);
		m_iCoinToBuy = t1;
	}

	m_iCurentItemSelect = DAMAGE_ITEM;

	m_lable1->setString("Rate Damage");
	m_lable2->setString("Can cause double the damage at certain probability");
	m_lable3->setString("Current rate:");
	m_lable4->setString(buf1);
	m_lable5->setString("Next level:");
	m_lable6->setString(buf2);
	sprintf(buf2,"%d",((CLevelManager::GetInstance()->GetLevelInformation()->m_iRateDoubleDamge - INIT_RATE_DOUBLE_DAMGE +5)/5)*50);
	m_lable7->setString(buf2);	


}

void CSkillUpgradeScene::buttonBuyCallback( CCObject* pSender )
{
	if(m_iCoinToBuy > -1)
	{
		if(CLevelManager::GetInstance()->GetLevelInformation()->m_iCoin >= m_iCoinToBuy)
		{	

			char buf[10]="";
			CLevelManager::GetInstance()->GetLevelInformation()->m_iCoin -= m_iCoinToBuy;
			sprintf(buf,"%d",CLevelManager::GetInstance()->GetLevelInformation()->m_iCoin);
			m_lable8->setString(buf);
			switch(m_iCurentItemSelect){
			case WALL_ITEM:
				CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerHp += HP_UPDATE;
				buttonWallCallback(NULL);
				break;
			case LEVEL_ITEM:
				CLevelManager::GetInstance()->GetLevelInformation()->m_iLevelTower += 1;
				buttonLevelCallback(NULL);
				break;
			case SPEED_ITEM:
				CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerSpeed += 1;
				buttonSpeedCallback(NULL);
				break;
			case DAMAGE_ITEM:
				CLevelManager::GetInstance()->GetLevelInformation()->m_iDameTowerCurrent += HP_UPDATE;
				buttonDamageCallback(NULL);	
				break;
			case RATEDAMAGE_ITEM:
				CLevelManager::GetInstance()->GetLevelInformation()->m_iRateDoubleDamge += HP_UPDATE;
				buttonRateCallback(NULL);	
				break;
			}
			CLevelManager::GetInstance()->SaveLevelToFile( "LevelInfo.txt" );

		}

	}
}

void CSkillUpgradeScene::menuBackCallBack( CCObject* pSender )
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
