#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__
#define TAG_MENU_LAYER 1000
#define TAG_MAIN_LAYER 2000
#include "cocos2d.h"
#include "Level.h"
#include "IncludeHelper.h"
#include "MainMenuScene.h"
#include "MenuLayer.h"
#include "BackgroundLayer.h"
#include "WinScene.h"
#include "GameOverScene.h"
#include "GameObjectLayer.h"
#include "LevelManager.h"
class CGamePlay: public cocos2d::CCScene
{

public:

	virtual bool	init(); 
	static void		initGameState();
	static void		addValue(int ID, int value);
	static int		getValue(int ID);
	static bool		checkWin();
	static eStar	checkStars();
	static void		setLevel(int level);
	static CLevel*	getCurrentLevel();
	static int      getLevel();
	static void		setEnableMenu(bool value);

	/************************************************************************/
	/* Static members                                                       */
	/* pScene, pMenuLayer, pMainLayer are autorelease                       */
	/************************************************************************/
	static cocos2d::CCScene* pScene;
	//static cocos2d::CCLayer* pSpriteLayer;
	static cocos2d::CCLayer* pMenuLayer;
	//static cocos2d::CCLayer* pPhysicsLayer;
	static cocos2d::CCLayer* pBackgroundLayer;
	//static cocos2d::CCLayer* pFrontSpriteLayer;
	static cocos2d::CCLayer* pGameObjectLayer;

	static CLevel* m_pCurrentLevel;
	static int  m_iLevel;
	static int  s_iScore;
	static int  s_iNumWoods;
	static int  s_iNumKillThiefTimes;
	static int  s_iWinScores;
	static int  s_iBonus;
	static int  s_i1StarScores;
	static int  s_i2StarScores;
	static int  s_i3StarScores;
	static bool s_bisRunning;   

	static cocos2d::CCScene* scene();	
	static void destroy();
	static void removeLayerByTag(int TAG);
	void AnimationDone(CCNode* sender);

};
#endif