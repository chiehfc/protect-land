#include "SelectLevelScene.h"
#include "MainMenuScene.h"
#include "SkillUpgradeScene.h"
#include "AudioManager.h"
#include "IncludeHelper.h"
#include "PositionConfig.h"
#include "MainConfig.h"
USING_NS_CC;

 

CCScene* CSelectLevelScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	CSelectLevelScene *layer = CSelectLevelScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool CSelectLevelScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	this->m_runtime = 0;
	CCSize sizeScr = CCDirector::sharedDirector()->getWinSize();
	
	//file name of map match level
	char* strNameFile[8] = {"MapScene\\human_map_unlock.png", "MapScene\\map_elves_unlock.png", "MapScene\\map_magi_unlock.png", "MapScene\\map_dwarf_unlock.png",
								"MapScene\\map_darkelf_unlock.png", "MapScene\\map_undead_unlock.png", "MapScene\\map_devil_unlock.png", "MapScene\\map_full_over.png"
							};
	CLevelManager * levelmanager = CLevelManager::GetInstance();	

	CCSprite* pSprite = CCSprite::create(strNameFile[levelmanager->GetLevelInformation()->m_iMapCurrent - 1]);	
	pSprite->setPosition( ccp(sizeScr.width/2, sizeScr.height/2) );
	this->addChild(pSprite);

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(NULL, NULL);
	pMenu->setPosition( CCPointZero );	

	//create button Back
	CCMenuItemImage *pBack = CCMenuItemImage::create(
		"Button\\back_down.png",
		"Button\\back_up.png",
		this,
		menu_selector(CSelectLevelScene::menuBackCallBack));	
	pBack->setPosition(LOCATION_BUTTON_BACK_SLS) ;
	pMenu->addChild(pBack);
	

	//create button Next
	CCMenuItemImage *pNext = CCMenuItemImage::create(
		"Button\\next_down.png",
		"Button\\next_up.png",
		this,
		menu_selector(CSelectLevelScene::menuNextCallBack));	
	pNext->setPosition(LOCATION_BUTTON_NEXT_SLS) ;
	pMenu->addChild(pNext);

	//add Menu vao layer
	this->addChild(pMenu, 1);



	
	this->schedule(schedule_selector(CSelectLevelScene::update));
	return true;
}
void CSelectLevelScene::update(float dt){

}
void CSelectLevelScene::render(){

}
void CSelectLevelScene::exit(){

}


void CSelectLevelScene::menuBackCallBack( CCObject* pSender )
{
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_CLICK_1);;
	CCScene *mainmenuScene = CMainMenuScene::scene();
	CCScene* pScene =CCTransitionFade::create(TRANSITION_DURATION, mainmenuScene, ccWHITE);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

void CSelectLevelScene::menuNextCallBack( CCObject* pSender )
{
	//chuyen den skillUpgradeScene
	CCScene * pSkillUpgradeScene = CSkillUpgradeScene::scene();
	CCScene* pScene =CCTransitionFade::create(TRANSITION_DURATION, pSkillUpgradeScene, ccWHITE);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}

	
}

