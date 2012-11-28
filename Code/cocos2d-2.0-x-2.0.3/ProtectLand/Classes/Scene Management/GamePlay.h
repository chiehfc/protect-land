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
	static void		setEnableMenu(bool value);

	/************************************************************************/
	/* Static members                                                       */
	/* pScene, pMenuLayer, pMainLayer are autorelease                       */
	/************************************************************************/
	static cocos2d::CCScene* pScene;
	static cocos2d::CCLayer* pMenuLayer;
	static cocos2d::CCLayer* pBackgroundLayer;
	static cocos2d::CCLayer* pGameObjectLayer;
	static cocos2d::CCLayer* pSkillLayer;

	static CLevel* m_pCurrentLevel;
	static bool s_bisRunning;   

	static cocos2d::CCScene* scene();	
	static void destroy();
	static void removeLayerByTag(int TAG);
	void AnimationDone(CCNode* sender);

};
#endif