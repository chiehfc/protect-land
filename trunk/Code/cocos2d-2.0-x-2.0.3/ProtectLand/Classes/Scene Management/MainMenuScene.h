#ifndef __MAINMENUSCENE_H__
#define __MAINMENUSCENE_H__
#include "cocos2d.h"
#include "OptionScene.h"
#include "HelpScene.h"
#include "AboutScene.h"
#include "GamePlay.h"
#include "LoadingScene.h"
#include "GameConfig.h"
#include "WinScene.h"
#include "AudioManager.h"

USING_NS_CC;
class CMainMenuScene: public cocos2d::CCLayer
{
protected:
	CCMenu* m_pMenu;
	CCMenu* m_pPopupMenu;
	CCLayerColor* m_pBlurLayer;
	CCSprite* pPopupBackground;
	void EnablePopupMenu(bool value);
public:
	virtual bool init(); 
	virtual void destroy();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(CMainMenuScene);
	void menuAboutCallback(CCObject* pSender);
	void menuNewgameCallback(CCObject* pSender);
	void menuHelpCallback(CCObject* pSender);
	void menuContinueCallback(CCObject* pSender);
	void menuCloseCallback(CCObject* pSender);
	void menuOptionsCallback(CCObject* pSender);
	void PopupYesCallback(CCObject* pSender);
	void PopupNoCallback(CCObject* pSender);
};
#endif