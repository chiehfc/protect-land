#include "SkillUpgradeScene.h"
#include "GamePlay.h"
#include "IncludeHelper.h"
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

	pMenu = CCMenu::create(NULL, NULL);
	pMenu->setPosition( CCPointZero );	

	{
		//FOR TEST
		//create button Play
		CCMenuItemImage *pPlay = CCMenuItemImage::create(
			"BackNormal.png",
			"BackSelected.png",
			this,
			menu_selector(CSkillUpgradeScene::menuPlayCallBack));	
		pPlay->setPosition( ccp(pPlay->getContentSize().width/2.0f + 15,  pPlay->getContentSize().height/2 + 15)) ;
		pMenu->addChild(pPlay);
	}
	this->addChild(pMenu);
	
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


