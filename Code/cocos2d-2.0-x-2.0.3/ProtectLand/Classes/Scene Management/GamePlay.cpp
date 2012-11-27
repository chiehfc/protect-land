#include "GamePlay.h"


USING_NS_CC;
CCScene* CGamePlay::pScene					 = NULL;
CCLayer* CGamePlay::pMenuLayer				 = NULL;
CCLayer* CGamePlay::pBackgroundLayer         = NULL;
CCLayer* CGamePlay::pGameObjectLayer		 = NULL;
CCLayer* CGamePlay::pSkillLayer              = NULL;
CLevel*  CGamePlay::m_pCurrentLevel          = NULL;
int      CGamePlay::s_iNumWoods				 = 0;
int		 CGamePlay::s_iNumKillThiefTimes	 = 0;
int		 CGamePlay::s_iScore				 = 0;
int      CGamePlay::s_iWinScores             = 0;
int      CGamePlay::m_iLevel                 = 1;
int      CGamePlay::s_i1StarScores			 = 0;
int      CGamePlay::s_i2StarScores			 = 0;
int      CGamePlay::s_i3StarScores			 = 0;
int		 CGamePlay::s_iBonus                 = 0;
bool     CGamePlay::s_bisRunning             = true;


CCScene* CGamePlay::scene()
{
	CGamePlay::s_bisRunning  = true;
	CGamePlay::initGameState();	
	if(CGamePlay::pScene == NULL)
	{
		// 'scene' is an autorelease object
		CGamePlay::pScene		    = CGamePlay::create();
		// 'layer' is an autorelease object
		//CGamePlay::pBackgroundLayer = CBackgroundLayer::create();
		CGamePlay::pGameObjectLayer = CGameObjectLayer::create();
    	// add layer as a child to scene
		//CGamePlay::pScene->addChild(CGamePlay::pBackgroundLayer, ZODER_GAMEPLAY_BACKGROUND_LAYER, TAG_GAMEPLAY_BACKGROUND_LAYER);
		CGamePlay::pScene->addChild(CGamePlay::pGameObjectLayer, ZODER_GAMEPLAY_GAME_OBJECT_LAYER, TAG_GAMEPLAY_GAME_OBJECT_LAYER);
		((CGameObjectLayer* )CGamePlay::pGameObjectLayer)->addElement();
		CMySprite *m_sprite = new CMySprite("stitch_lose.sprite");
		CGamePlay::pGameObjectLayer->addChild(m_sprite,ZODER_GAMEOBJECTLAYER_FRONT_2, TAG_STITCH_LOSE);
		m_sprite->setVisible(false);

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
void CGamePlay::initGameState()
{
	CGamePlay::s_iNumWoods			= CGamePlay::getCurrentLevel()->getIntValue(LEVEL_ID_NUMWOOD);
	CGamePlay::s_iNumKillThiefTimes = CGamePlay::getCurrentLevel()->getIntValue(LEVEL_ID_NUMKILLTHIEF);
	CGamePlay::s_iWinScores			= CGamePlay::getCurrentLevel()->getIntValue(LEVEL_ID_WINSCORE);
	CGamePlay::s_i1StarScores		= CGamePlay::getCurrentLevel()->getIntValue(LEVEL_ID_1STAR);
	CGamePlay::s_i2StarScores		= CGamePlay::getCurrentLevel()->getIntValue(LEVEL_ID_2STAR);
	CGamePlay::s_i3StarScores		= CGamePlay::getCurrentLevel()->getIntValue(LEVEL_ID_3STAR);
	CGamePlay::s_iScore = 0;
	CGamePlay::s_iBonus = 0;

}
void CGamePlay::addValue( int ID, int value )
{
	switch(ID)
	{
		case OBJECT_ITEM_WOOD:
			CGamePlay::s_iNumWoods += value;
			break;
		case OBJECT_ITEM_KILLTHIEF:
			CGamePlay::s_iNumKillThiefTimes += value;
			break;
		case SCORE:
			CGamePlay::s_iScore += value;
			break;
		case BONUS:
			CGamePlay::s_iBonus += value;
			break;
		default:
			break;
	}
}
int CGamePlay::getValue( int ID )
{
	switch(ID)
	{
		case OBJECT_ITEM_WOOD:
			return s_iNumWoods;
		case OBJECT_ITEM_KILLTHIEF:
			return s_iNumKillThiefTimes;
		case SCORE:
			return s_iScore;
		case BONUS:
			return s_iBonus;
		default:
			return 0;
	}
}
bool CGamePlay::checkWin()
{
	if(CGamePlay::pScene != NULL && CGamePlay::s_iScore >= CGamePlay::s_iWinScores )
	{
		CGamePlay::destroy();
		CLevelManager * levelmanager = CLevelManager::GetInstance();
		eStar numStars = CGamePlay::checkStars(); 
		// Thuc hien luu du lieu
		bool check = false;
		if (levelmanager->SetHighScore(m_iLevel, s_iScore) )
		{
			check = true;
		}
		if ( levelmanager->SetNumStar(m_iLevel, numStars))
		{
			check = true;
		}
		if (!levelmanager->GetIsPass((m_iLevel+1)%(NUMBER_LEVEL + 1)))
		{
			check = true;
			levelmanager->SetPassable((m_iLevel+1)%(NUMBER_LEVEL + 1), true);
		}
		if (check == true)
		{
			levelmanager->SaveLevelToFile(FILE_LEVEL_INFO);
		}
		CCDirector::sharedDirector()->getTouchDispatcher()->removeAllDelegates();
		CCScene *pWinScene = CWinScene::scene(numStars);
		CCDirector::sharedDirector()->replaceScene(pWinScene);
		return true;
	}
	else
	{
		CCDirector::sharedDirector()->getTouchDispatcher()->removeAllDelegates();
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		CMySprite*  pSpriteLose =(CMySprite*)  CGamePlay::pGameObjectLayer->getChildByTag(TAG_STITCH_LOSE);
		pSpriteLose->setPosition(CGamePlay::getCurrentLevel()->getCCPointValue(LEVEL_ID_STITCH_POS));
		pSpriteLose->PlayAnimation(0, 5.0f, 1, false,CCCallFuncN::actionWithTarget(CGamePlay::pScene, callfuncN_selector(CGamePlay::AnimationDone)));
		pSpriteLose->setOpacity(0);
		pSpriteLose->runAction(CCFadeIn::create(0.5f));
		pSpriteLose->setVisible(true);
		/**/
		return false;
	}
	
}
void CGamePlay::setLevel( int level )
{
	CGamePlay::m_iLevel = level;
	if(CGamePlay::m_pCurrentLevel != NULL)
		CC_SAFE_DELETE(CGamePlay::m_pCurrentLevel);
	CGamePlay::m_pCurrentLevel = NULL;

	if(level > 0)
	{
		CGamePlay::m_pCurrentLevel = new CLevel(level);	
	}

}
CLevel* CGamePlay::getCurrentLevel()
{
	return CGamePlay::m_pCurrentLevel;
}
int CGamePlay::getLevel()
{
	return CGamePlay::m_iLevel;
}
eStar CGamePlay::checkStars()
{
	if(CGamePlay::s_iScore >= CGamePlay::s_iWinScores)
	{
		if(CGamePlay::s_iScore + CGamePlay::s_iBonus >= CGamePlay::s_i3StarScores)
		{
			return STAR3;
		}
		else if(CGamePlay::s_iScore + CGamePlay::s_iBonus>= CGamePlay::s_i2StarScores)
		{
			return STAR2;
		}
		else if(CGamePlay::s_iScore + CGamePlay::s_iBonus >= CGamePlay::s_i1StarScores)
		{
			return STAR1;
		}
		else 
		{
			return STAR0;
		}
	}
	return STAR0;

}
void CGamePlay::setEnableMenu( bool value )
{
	((CCMenu*) ((CGameObjectLayer*) pGameObjectLayer->getChildByTag(TAG_PMENU)))->setEnabled(value);
}

void CGamePlay::AnimationDone( CCNode* sender )
{
	CAudioManager::instance()->stopAllEff();
	CGamePlay::destroy();
	CGamePlay::setLevel(CGamePlay::getLevel());
	CCScene *gamePlay = CGamePlay::scene();
	CCDirector::sharedDirector()->replaceScene(gamePlay);
}


