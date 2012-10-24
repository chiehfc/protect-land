#ifndef __CLEVEL_H__
#define __CLEVEL_H__
#include "cocos2d.h"
#include "IncludeHelper.h"

USING_NS_CC;
class CLevel
{

private:
	cocos2d::CCDictionary *m_LevelDict;
	sGameObject* m_pTargetList;
	sGameObject* m_pRockList;
	sGameObject* m_pThiefList;	
	int NumTarget;
	int NumRocks;
	int NumThiefs;
	int NumWaters;		
	int IsHaveTeleport;
	CCPoint m_BeetPos;	
	CCPoint m_StitchPos;
	CCPoint m_TeleportPosIn;
	CCPoint m_TeleportPosOut;

public:
	int			 getIntValue(int ID);
	sGameObject* getObjectList(int ID);
	CCPoint		 getCCPointValue(int ID);
	CLevel(int level);
	~CLevel(void);
};

#endif