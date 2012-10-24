#include "SelectLevelScene.h"
#include "MainMenuScene.h"
#include "GamePlay.h"
#include "AudioManager.h"
#include "IncludeHelper.h"
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
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	// add a "close" icon to exit the progress. it's an autorelease object
	
	char* strNameFile[32] = {"box1-0star.png", "box2-0star.png", "box3-0star.png", "box4-0star.png", "box5-0star.png", "box6-0star.png", "box7-0star.png", "box8-0star.png",
							"box1-1star.png", "box2-1star.png", "box3-1star.png", "box4-1star.png", "box5-1star.png", "box6-1star.png", "box7-1star.png", "box8-1star.png",
							"box1-2star.png", "box2-2star.png", "box3-2star.png", "box4-2star.png", "box5-2star.png", "box6-2star.png", "box7-2star.png", "box8-2star.png",
							"box1-3star.png", "box2-3star.png", "box3-3star.png", "box4-3star.png", "box5-3star.png", "box6-3star.png", "box7-3star.png", "box8-3star.png",
							};
	CLevelManager * levelmanager = CLevelManager::GetInstance();
	int numLevel = levelmanager->GetNumOfLevel();

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(NULL, NULL);
	pMenu->setPosition( CCPointZero );

	
	CCMenuItemImage *pLevel;
	for (int i=1; i<=numLevel; i++)
	{
		m_levelSelected = i;
		if (levelmanager->GetIsPass(i)) 
		{
			int temp = levelmanager->GetNumOfStar(i);
			switch (i)
			{
			case 1:
				pLevel = CCMenuItemImage::create(
					strNameFile[(i-1)+temp*8],
					strNameFile[(i-1)+temp*8],
					this,
					menu_selector(CSelectLevelScene::level1CallBack));
				break;
			case 2:
				pLevel = CCMenuItemImage::create(
					strNameFile[(i-1)+temp*8],
					strNameFile[(i-1)+temp*8],
					this,
					menu_selector(CSelectLevelScene::level2CallBack));
				break;
			case 3:
				pLevel = CCMenuItemImage::create(
					strNameFile[(i-1)+temp*8],
					strNameFile[(i-1)+temp*8],
					this,
					menu_selector(CSelectLevelScene::level3CallBack));
				break;
			case 4:
				pLevel = CCMenuItemImage::create(
					strNameFile[(i-1)+temp*8],
					strNameFile[(i-1)+temp*8],
					this,
					menu_selector(CSelectLevelScene::level4CallBack));
				break;
			case 5:
				pLevel = CCMenuItemImage::create(
					strNameFile[(i-1)+temp*8],
					strNameFile[(i-1)+temp*8],
					this,
					menu_selector(CSelectLevelScene::level5CallBack));
				break;
			case 6:
				pLevel = CCMenuItemImage::create(
					strNameFile[(i-1)+temp*8],
					strNameFile[(i-1)+temp*8],
					this,
					menu_selector(CSelectLevelScene::level6CallBack));
				break;
			case 7:
				pLevel = CCMenuItemImage::create(
					strNameFile[(i-1)+temp*8],
					strNameFile[(i-1)+temp*8],
					this,
					menu_selector(CSelectLevelScene::level7CallBack));
				break;
			case 8:
				pLevel = CCMenuItemImage::create(
					strNameFile[(i-1)+temp*8],
					strNameFile[(i-1)+temp*8],
					this,
					menu_selector(CSelectLevelScene::level8CallBack));
				break;
			}
						
		}	
		else 
		{
			pLevel = CCMenuItemImage::create(
				"lock.png",
				"lock.png",
				this,
				NULL);
		}
		if (i >= 5)
		{
			pLevel->setPosition(ccp((i%5 + 1)*s.width/5 , s.height/2 + 130 - 150*((int)(i/5)) ) );
		}
		else
		{
			pLevel->setPosition(ccp((i%5)*s.width/5 , s.height/2 + 130 - 150*((int)(i/5)) ) );
		}		
		pMenu->addChild(pLevel);
	}
	
	CCMenuItemImage *pBack = CCMenuItemImage::create(
		"BackNormal.png",
		"BackSelected.png",
		this,
		menu_selector(CSelectLevelScene::menuBackCallBack));
	pBack->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pBack->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	pBack->setPosition( ccp(  pBack->getContentSize().width/2+15*size.width/WIDTH_SCREEN_STANDARD,  pBack->getContentSize().height/2+15*size.height/HEIGHT_SCREEN_STANDARD)) ;
	pMenu->addChild(pBack);

	this->addChild(pMenu, 1);	


	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::create("MenuSelectBG.png");
	pSprite->setScaleX((float)size.width/WIDTH_SCREEN_STANDARD);
	pSprite->setScaleY((float)size.height/HEIGHT_SCREEN_STANDARD);
	// position the sprite on the center of the screen
	pSprite->setPosition( ccp(size.width/2, size.height/2) );

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);
	this->schedule(schedule_selector(CSelectLevelScene::update));
	return true;
}
void CSelectLevelScene::update(float dt){


}
void CSelectLevelScene::render(){

}
void CSelectLevelScene::exit(){

}

void CSelectLevelScene::level1CallBack( CCObject* pSender )
{
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_CLICK_1);
	CGamePlay::setLevel(1);
	/*CCScene *gameplayScene = CGamePlay::scene();		
	CCDirector::sharedDirector()->replaceScene(gameplayScene);*/
	CCScene *gameplayScene = CGamePlay::scene();
	CCScene* pScene = CCTransitionCrossFade::create(TRANSITION_DURATION, gameplayScene);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	} 	
}

void CSelectLevelScene::level2CallBack( CCObject* pSender )
{
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_CLICK_1);
	CGamePlay::setLevel(2);
	CCScene *gameplayScene = CGamePlay::scene();
	CCScene* pScene = CCTransitionCrossFade::create(TRANSITION_DURATION, gameplayScene);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
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

void CSelectLevelScene::level3CallBack( CCObject* pSender )
{
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_CLICK_1);
	CGamePlay::setLevel(3);
	CCScene *gameplayScene = CGamePlay::scene();
	CCScene* pScene = CCTransitionCrossFade::create(TRANSITION_DURATION, gameplayScene);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	} 
}

void CSelectLevelScene::level4CallBack( CCObject* pSender )
{
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_CLICK_1);
	CGamePlay::setLevel(4);
	CCScene *gameplayScene = CGamePlay::scene();
	CCScene* pScene = CCTransitionCrossFade::create(TRANSITION_DURATION, gameplayScene);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	} 
}

void CSelectLevelScene::level5CallBack( CCObject* pSender )
{
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_CLICK_1);
	CGamePlay::setLevel(5);
	CCScene *gameplayScene = CGamePlay::scene();
	CCScene* pScene = CCTransitionCrossFade::create(TRANSITION_DURATION, gameplayScene);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	} 
}

void CSelectLevelScene::level6CallBack( CCObject* pSender )
{
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_CLICK_1);
	CGamePlay::setLevel(6);
	CCScene *gameplayScene = CGamePlay::scene();
	CCScene* pScene = CCTransitionCrossFade::create(TRANSITION_DURATION, gameplayScene);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	} 
}

void CSelectLevelScene::level7CallBack( CCObject* pSender )
{
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_CLICK_1);
	CGamePlay::setLevel(7);
	CCScene *gameplayScene = CGamePlay::scene();
	CCScene* pScene = CCTransitionCrossFade::create(TRANSITION_DURATION, gameplayScene);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	} 
}

void CSelectLevelScene::level8CallBack( CCObject* pSender )
{
	//if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
		CAudioManager::instance()->playEff(SOUND_CLICK_1);
	CGamePlay::setLevel(8);
	CCScene *gameplayScene = CGamePlay::scene();
	CCScene* pScene = CCTransitionCrossFade::create(TRANSITION_DURATION, gameplayScene);
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	} 
}

