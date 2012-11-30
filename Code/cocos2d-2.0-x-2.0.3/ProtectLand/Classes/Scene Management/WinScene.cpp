#include "WinScene.h"
USING_NS_CC;


cocos2d::CCScene* CWinScene::scene( int coinBonus, int HpTowerRemind )
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	CWinScene *layer = CWinScene::create();	
	// add layer as a child to scene
	layer->m_iCoinBonus = coinBonus;
	layer->m_iHpTowerRemind = HpTowerRemind;
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
	int totalCoin=0;
	addSpire(&m_pTemp,"WinScreen\\stats_bg.png",ccp(size.width/2.0f,size.height/2.0f), 1.0f,1.0f);
	addSpire(&m_pTemp,"WinScreen\\boss1.png",LOCATION_MONTER1, 2.0f,2.0f);
	addSpire(&m_pTemp,"WinScreen\\monster1.png",LOCATION_MONTER2, 1.2f,1.2f);
	addSpire(&m_pTemp,"WinScreen\\monster3.png",LOCATION_MONTER3, 1.2f,1.2f);
	addSpire(&m_pTemp,"WinScreen\\monster6.png",LOCATION_MONTER4, -1.2f,1.2f);
	addSpire(&m_pTemp,"WinScreen\\monster5.png",LOCATION_MONTER5, -1.2f,1.2f);
	sprintf(buf,"STAGE  %d",CLevelManager::GetInstance()->GetLevelInformation()->m_iMapCurrent);
	addLabel(&m_pLabel, ccc3(255, 255, 255), 400, LOCATION_TITLE ,buf, 2.0f);
	int fullHP = CLevelManager::GetInstance()->GetLevelInformation()->m_iTowerHp;
	float rate = (m_iHpTowerRemind - fullHP)/fullHP;
	sprintf(buf,"HP         %d %%",rate);
	addLabel(&m_pLabel, ccc3(255, 255, 255), 300, LOCATION_HP,buf, 1.2f);
	int coinBonus = m_iHpTowerRemind;
	totalCoin += coinBonus;
	int nCoin = coinBonus % 100;
	int nDiamond = coinBonus/100;
	sprintf(buf,"%d",nCoin);
	addLabel(&m_pLabel, ccc3(255, 255, 255), 300, LOCATION_HP_VALUE,buf, 1.2f);
	sprintf(buf,"%d",nDiamond);
	addLabel(&m_pLabel, ccc3(255, 255, 255), 300, LOCATION_HP_VALUE2,buf, 1.2f);

	sprintf(buf,"STAGE");
	addLabel(&m_pLabel, ccc3(255, 255, 255), 300, LOCATION_STAGE,buf, 1.2f);
	coinBonus =(int) pow(1.3f,CLevelManager::GetInstance()->GetLevelInformation()->m_iMapCurrent - 1)*50;
	totalCoin += coinBonus;
	nCoin = coinBonus % 100;
	nDiamond = coinBonus/100;
	sprintf(buf,"%d",nCoin);
	addLabel(&m_pLabel, ccc3(255, 255, 255), 300, LOCATION_STAGE_VALUE,buf, 1.2f);
	sprintf(buf,"%d",nDiamond);
	addLabel(&m_pLabel, ccc3(255, 255, 255), 300, LOCATION_STAGE_VALUE2,buf, 1.2f);

	coinBonus = m_iCoinBonus;
	totalCoin += coinBonus;
	nCoin = coinBonus % 100;
	nDiamond = coinBonus/100;
	sprintf(buf,"KILL");
	addLabel(&m_pLabel, ccc3(255, 255, 255), 300, LOCATION_KILL,buf, 1.2f);
	sprintf(buf,"%d",nCoin);
	addLabel(&m_pLabel, ccc3(255, 255, 255), 300, LOCATION_KILL_VALUE,buf, 1.2f);
	sprintf(buf,"%d",nDiamond);
	addLabel(&m_pLabel, ccc3(255, 255, 255), 300, LOCATION_KILL_VALUE2,buf, 1.2f);
	
	nCoin = totalCoin % 100;
	nDiamond = totalCoin/100;
	sprintf(buf,"TOTAL");
	addLabel(&m_pLabel, ccc3(255, 255, 255), 300, LOCATION_TOTAL,buf, 1.2f);
	sprintf(buf,"%d",nCoin);
	addLabel(&m_pLabel, ccc3(255, 255, 255), 300, LOCATION_TOTAL_VALUE,buf, 1.2f);
	sprintf(buf,"%d",nDiamond);
	addLabel(&m_pLabel, ccc3(255, 255, 255), 300, LOCATION_TOTAL_VALUE2,buf, 1.2f);

	CLevelManager::GetInstance()->GetLevelInformation()->m_iCoin += totalCoin;
	CLevelManager::GetInstance()->SaveLevelToFile("LevelInfo.txt");

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, TOUCH_PRIORITY_MAIN_LAYER , true);
	this->setTouchEnabled(true);
	CCMenu *pMenu= CCMenu::create();
	CCMenuItemImage *pNextItem = CCMenuItemImage::create(
		"Button\\next_down.png",
		"Button\\next_up.png",
		this,
		menu_selector(CWinScene::menuNextCallback));
	pNextItem->setPosition(LOCATION_BUTTON_NEXT_SLS);
	pMenu->addChild(pNextItem);
	CCMenuItemImage *pResetItem = CCMenuItemImage::create(
		"Button\\reset_down.png",
		"Button\\reset_up.png",
		this,
		menu_selector(CWinScene::menuRestartCallback));
	pResetItem->setPosition(ccp(100,100));
	pMenu->addChild(pResetItem);
	CCMenuItemImage *pSelecLevelItem = CCMenuItemImage::create(
		"Button\\back_down.png",
		"Button\\back_up.png",
		this,
		menu_selector(CWinScene::menuLevelSelectCallback));
	pSelecLevelItem->setPosition(ccp(100,100));
	pMenu->addChild(pSelecLevelItem);
	this->addChild(pMenu);


	scheduleUpdate();
	CAudioManager::instance()->stopBGMusic();
	return true;
}
void CWinScene::update(float dt)
{
	
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
	CCScene *gameSkillUpgradeScene = CSkillUpgradeScene::scene();
	CCScene* pScene = CCTransitionSlideInR::create(0.7f, gameSkillUpgradeScene);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	} 
}


void CWinScene::menuRestartCallback( CCObject* pSender )
{
	CAudioManager::instance()->playEff(SOUND_CLICK_1);
	CGamePlay::destroy();
	CCScene *gamePlay = CGamePlay::scene();
	CCDirector::sharedDirector()->replaceScene(gamePlay);
}


void CWinScene::playSound(CCNode* sender, void* data)
{
	CAudioManager::instance()->playEff(*((int*)data));
}

void CWinScene::addSpire(CCSprite **m_sprite, char* path, CCPoint &position, float scaleX,float scaleY)
{

	*m_sprite = CCSprite::spriteWithFile(path);
	(*m_sprite)->setScaleX(scaleX);
	(*m_sprite)->setScaleY(scaleY);
	(*m_sprite)->setPosition(position);
	this->addChild(*m_sprite);
}

void CWinScene::addLabel(CCLabelBMFont **pLabel, ccColor3B &color, int width, CCPoint &position,char* str,float scale)
{
	*pLabel = CCLabelBMFont::create(str, "fonts/myFont.fnt",width );

	(*pLabel)->setColor(color);
	(*pLabel)->setScale(scale);

	(*pLabel)->setAnchorPoint(ccp(0, 0));
	(*pLabel)->setPosition( position);
	this->addChild(*pLabel, 2);

}

bool CWinScene::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	
	return true;
}

void CWinScene::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	
}
