#ifndef __SUBMENULAYER_H__
#define __SUBMENULAYER_H__
#include "cocos2d.h"
class CMenuLayer: public cocos2d::CCLayer
{
public:
	virtual bool init();
	virtual void onExit();

	/************************************************************************/
	/* Menu call back funtions                                              */
	/************************************************************************/
	//Save game menu call back
	void menuSkipLevelCallback(CCObject* pSender);

	//Continue menu call back
	void menuContinueCallback(CCObject* pSender);

	//Main menu call back
	void menuSkillUpgradeCallback(CCObject* pSender);
	
	//Mute call back
	void menuMainMenuCallback(CCObject* pSender);

	CREATE_FUNC(CMenuLayer);
};
#endif
