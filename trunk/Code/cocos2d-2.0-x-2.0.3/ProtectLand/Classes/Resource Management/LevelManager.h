#ifndef __LEVEL_MANAGER_H__
#define __LEVEL_MANAGER_H__
#include "FileManager.h"
#include "cocos2d.h"
#include "Utils.h"
#include "IncludeHelper.h"

using namespace cocos2d;

struct SLevelInfomation
{
	int m_iLevel;
	int m_iHighScore;
	bool m_bIsPass;
	int m_NumOfStar;
	SLevelInfomation()
	{
		this->m_iLevel = -1;
		m_iHighScore = 0;
		m_bIsPass = false;
		m_NumOfStar = 0;
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
	SLevelInfomation* GetLevelInformation(int idx);
	SLevelInfomation* GetListLevel(int& NumOfLevel);
	bool ResetLevel(const char* pszPath, int iNumOfLevel);
	bool ResetLevel(const char* pszPath);
	bool SetLevelInfo(int idLevel, int NumOfStar, int HightScore, bool IsPass);
	int GetNumOfStar(int idLevel);
	int GetHighScore(int idLevel);
	bool GetIsPass(int idLevel);
	bool SetHighScore(int idLevel, int highScore);
	bool SetNumStar(int idLevel, int numStar);
	void SetPassable(int idLevel, bool isPass);
	bool CreateFileFirstGame(const char* pc_FileName, int iNumOfLevel);
};
#endif