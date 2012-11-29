#ifndef __LEVEL_MANAGER_H__
#define __LEVEL_MANAGER_H__
#include "FileManager.h"
#include "cocos2d.h"
#include "Utils.h"
#include "IncludeHelper.h"

using namespace cocos2d;

#define INIT_DAMGE_TOWER		24
#define INIT_TOWER_SPEED		1.0f
#define INIT_TOWER_HP			100
#define INIT_RATE_DOUBLE_DAMGE	5
#define INIT_SHOW_LEVEL_SPEED	1

enum Mapcurrent {
	human,
	elves,
	magi,
	dwarf,
	darkelves,
	undead,
	devils,
	max_map,
};


struct SLevelInfomation
{
	int m_iMapCurrent;
	int m_iLevelCurrent;
	int m_iCoin;
	int m_iLevelTower;
	int m_iDameTowerCurrent;
	int m_iTowerSpeed;
	int m_iShowTowerSpeed;
	int m_iTowerHp;
	int m_iRateDoubleDamge;
	SLevelInfomation()
	{
		m_iMapCurrent = human;
		m_iLevelCurrent = 1;
		m_iCoin = 0;
		m_iLevelTower = 1;
		m_iDameTowerCurrent = INIT_DAMGE_TOWER;
		m_iTowerSpeed = 1;
		m_iTowerHp = INIT_TOWER_HP;
		m_iRateDoubleDamge = INIT_RATE_DOUBLE_DAMGE;
	}
};
class CLevelManager{
protected:
	SLevelInfomation* m_psLevelInfo;
	int m_iNumOfLevel;
	CLevelManager();
	CLevelManager(const CLevelManager &);
	~CLevelManager();
	bool ResetLevelInfo();
	void ResetLevelInfo(int NumOfLevel);
	static CLevelManager* s_Instance;
public:
	static CLevelManager* GetInstance();
	static void DestroyInstance();
	int GetNumOfLevel();
	/************************************************************************/
	/* Public Function                                                      */
	/************************************************************************/
	bool LoadLevelFromFile(const char* pszPath);
	bool SaveLevelToFile(const char* pszPath);
	SLevelInfomation* GetLevelInformation();
	SLevelInfomation* GetListLevel(int& NumOfLevel);
	bool ResetLevel(const char* pszPath, int iNumOfLevel);
	bool ResetLevel(const char* pszPath);
	bool SetLevelInfo(int iMapCurrent, int iLevelCurrent, int iCoin, int iLevelTower, int iDameTowerCurrent, int iTowerSpeed, int iTowerHp, int iRateDoubleDamge);
	
	
	bool CreateFileFirstGame(const char* pc_FileName, int iNumOfLevel);
};
#endif