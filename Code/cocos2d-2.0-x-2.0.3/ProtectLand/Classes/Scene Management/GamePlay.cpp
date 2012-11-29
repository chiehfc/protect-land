#include "GamePlay.h"


USING_NS_CC;
CCScene* CGamePlay::pScene					 = NULL;
CCLayer* CGamePlay::pMenuLayer				 = NULL;
CCLayer* CGamePlay::pBackgroundLayer         = NULL;
CCLayer* CGamePlay::pGameObjectLayer		 = NULL;
CCLayer* CGamePlay::pSkillLayer              = NULL;
CLevel*  CGamePlay::m_pCurrentLevel          = NULL;
bool     CGamePlay::s_bisRunning             = true;


CCScene* CGamePlay::scene()
{
	CGamePlay::s_bisRunning  = true;
	if(CGamePlay::pScene == NULL)
	{
		// 'scene' is an autorelease object
		CGamePlay::pScene		    = CGamePlay::create();
		// 'layer' is an autorelease object
		
		CGamePlay::pBackgroundLayer = CBackgroundLayer::create();
		
		CGamePlay::pGameObjectLayer = CGameObjectLayer::create();
		    	// add layer as a child to scene
		CGamePlay::pScene->addChild(CGamePlay::pBackgroundLayer, ZODER_GAMEPLAY_BACKGROUND_LAYER, TAG_GAMEPLAY_BACKGROUND_LAYER);
		CGamePlay::pScene->addChild(CGamePlay::pGameObjectLayer, ZODER_GAMEPLAY_GAME_OBJECT_LAYER, TAG_GAMEPLAY_GAME_OBJECT_LAYER);			

		return CGamePlay::pScene;
	}
	else
	{
		return CGamePlay::pScene;
	}
}



bool CGamePlay::init()
{
	return true;
}
void CGamePlay::destroy()
{
	if(CGamePlay::pScene != NULL)
		CGamePlay::pScene->removeAllChildrenWithCleanup(true);
	CGamePlay::pScene		    = NULL;
	CGamePlay::pMenuLayer	    = NULL;
    CGamePlay::pGameObjectLayer = NULL;	
	CGamePlay::pBackgroundLayer = NULL;
	CC_SAFE_DELETE(CGamePlay::m_pCurrentLevel);
	
}

/************************************************************************/
/* Remove layers by it's TAG with and clean up it                       */
/************************************************************************/
void CGamePlay::removeLayerByTag(int TAG)
{
	switch(TAG)
	{
		case TAG_GAMEPLAY_MENU_LAYER:
			CGamePlay::pMenuLayer = NULL;
			CGamePlay::pScene->removeChildByTag(TAG_GAMEPLAY_MENU_LAYER, true);
			break;
		case TAG_GAMEPLAY_GAME_OBJECT_LAYER:
			CGamePlay::pGameObjectLayer = NULL;
			CGamePlay::pScene->removeChildByTag(TAG_GAMEPLAY_GAME_OBJECT_LAYER, true);
			break;
		case TAG_GAMEPLAY_COLOR_LAYER:
			CGamePlay::pScene->removeChildByTag(TAG_GAMEPLAY_COLOR_LAYER, true);
			break;
		default:
			CGamePlay::pScene->removeChildByTag(TAG, true);
			break;
	}

}


void CGamePlay::setEnableMenu( bool value )
{
	((CCMenu*) ((CGameObjectLayer*) pGameObjectLayer->getChildByTag(TAG_PMENU)))->setEnabled(value);
}

void CGamePlay::AnimationDone( CCNode* sender )
{
	CAudioManager::instance()->stopAllEff();
	CGamePlay::destroy();	
	CCScene *gamePlay = CGamePlay::scene();
	CCDirector::sharedDirector()->replaceScene(gamePlay);
}


