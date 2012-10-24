#include "LevelManager.h"
#include "IncludeHelper.h"
CLevelManager* CLevelManager::s_Instance = NULL;
CLevelManager::CLevelManager()
{
	m_psLevelInfo = NULL;
	m_iNumOfLevel = 0;
}

CLevelManager::~CLevelManager()
{
	CC_SAFE_DELETE_ARRAY(m_psLevelInfo);
	m_iNumOfLevel = 0;
}

CLevelManager* CLevelManager::GetInstance()
{
	if (!s_Instance)
		s_Instance = new CLevelManager();
	return s_Instance;
}

void CLevelManager::DestroyInstance()
{
	CC_SAFE_DELETE(s_Instance);
}

bool CLevelManager::LoadLevelFromFile( const char* pszPath )
{
	#if ANDROID
	string pathWriteable = CCFileUtils::sharedFileUtils()->getWriteablePath();
	char pszFullPath[256] = {0};
	strcpy(pszFullPath, pathWriteable.c_str());
	strcat(pszFullPath, pszPath);
	/*const char * sdcard = PATH_EXTERNAL;
	int sdcardLength = strlen(sdcard);
	char* pszFullPath = new char[strlen(sdcard)+ strlen(pszPath)+1];
	strcpy(pszFullPath,sdcard);
	strcat(pszFullPath,pszPath);*/
	/*LOGI("FULLPATH Level Inf=================================================");
	LOGI(pszFullPath);
	LOGI("FULLPATH Level Inf=================================================");*/
#else
	const char *pszFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pszPath);
	//LOGI("FULLPATH Level Info=================================================");
	//LOGI(pszFullPath);
	//LOGI("FULLPATH Level Inf=================================================");
#endif
	//Bat dau Load
	
	/*char* psContentFile = NULL;
	unsigned long bufferSize = 0;
	psContentFile =(char*) CCFileUtils::sharedFileUtils()->getFileData(pszFullPath, "r", &bufferSize);
	psContentFile[bufferSize] = '\0';*/
	char* psContentFile = CFileManager::GetInstance()->GetFileContent(pszFullPath);
	/*LOGE("****************content File**********");
	if(psContentFile == NULL) LOGE("FFFFFFFFFFFFFFFFFFFFFFFFFF");
	else LOGE(psContentFile);*/
	if (!psContentFile)
	{
		return false;
	}
	//Neu da load roi
	if (m_iNumOfLevel != 0)
	{
		m_iNumOfLevel = 0;
		CC_SAFE_DELETE(m_psLevelInfo);
	}
	int iNumOfLevel  = 0;
	char pc_Line[999];
	int currentOffset = 0;
	currentOffset = ReadLine(psContentFile, pc_Line, currentOffset);
	sscanf(pc_Line, "%d", &iNumOfLevel);
	this->m_iNumOfLevel = iNumOfLevel;
	this->m_psLevelInfo = new SLevelInfomation[m_iNumOfLevel];
	for(int i = 0; i < iNumOfLevel; i ++)
	{
		currentOffset = ReadLine(psContentFile, pc_Line, currentOffset);
		int idLevel = i;
		int iNumOfStar = 0;
		int iHighScore = 0;
		int isPass = 0;
		sscanf(pc_Line, "%d %d %d %d", &idLevel, &iNumOfStar, &iHighScore, &isPass);
		m_psLevelInfo[i].m_iLevel = idLevel;
		m_psLevelInfo[i].m_NumOfStar = iNumOfStar;
		m_psLevelInfo[i].m_iHighScore = iHighScore;
		m_psLevelInfo[i].m_bIsPass = (isPass == 1 ? 1 : 0);
	}
	CC_SAFE_DELETE_ARRAY(psContentFile);
	return true;
}

bool CLevelManager::SaveLevelToFile( const char* pszPath )
{
	if (!m_iNumOfLevel || !m_psLevelInfo)
	{
		return false;
	}
	#if ANDROID
	string pathWriteable = CCFileUtils::sharedFileUtils()->getWriteablePath();
	char pszFullPath[256] = {0};
	strcpy(pszFullPath, pathWriteable.c_str());
	strcat(pszFullPath, pszPath);
	/*const char * sdcard = PATH_EXTERNAL;
	int sdcardLength = strlen(sdcard);
	char* pszFullPath = new char[strlen(sdcard)+ strlen(pszPath)+1];
	strcpy(pszFullPath,sdcard);
	strcat(pszFullPath,pszPath);*/
	/*LOGI("FULLPATH Level Inf=================================================");
	LOGI(pszFullPath);
	LOGI("FULLPATH Level Inf=================================================");*/
#else
	const char *pszFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pszPath);
	//LOGI("FULLPATH Level Info=================================================");
	//LOGI(pszFullPath);
	//LOGI("FULLPATH Level Inf=================================================");
#endif
	FILE * pFile =  NULL;
	pFile = fopen(pszFullPath, "w+");
	if (pFile != NULL)
	{
		fprintf(pFile,"%d\n",m_iNumOfLevel);
		for (int i = 0; i < m_iNumOfLevel; i ++)
		{
			fprintf(pFile,"%d %d %d %d\n",m_psLevelInfo[i].m_iLevel, m_psLevelInfo[i].m_NumOfStar, 
				m_psLevelInfo[i].m_iHighScore, m_psLevelInfo[i].m_bIsPass);
		}

		fclose(pFile);
	}

	return true;
}

SLevelInfomation* CLevelManager::GetLevelInformation( int idx )
{
	idx--;
	if ( ( idx < 0 && idx >= m_iNumOfLevel )|| !m_psLevelInfo)
	{
		return NULL;
	}
	return (m_psLevelInfo+idx);
}

SLevelInfomation* CLevelManager::GetListLevel( int& NumOfLevel )
{
	NumOfLevel = m_iNumOfLevel;
	return m_psLevelInfo;
}

bool CLevelManager::ResetLevel( const char* pszPath, int iNumOfLevel )
{
	
	#if ANDROID
	string pathWriteable = CCFileUtils::sharedFileUtils()->getWriteablePath();
	char pszFullPath[256] = {0};
	strcpy(pszFullPath, pathWriteable.c_str());
	strcat(pszFullPath, pszPath);
	/*const char * sdcard = PATH_EXTERNAL;
	int sdcardLength = strlen(sdcard);
	char* pszFullPath = new char[strlen(sdcard)+ strlen(pszPath)+1];
	strcpy(pszFullPath,sdcard);
	strcat(pszFullPath,pszPath);*/
	/*LOGI("FULLPATH Level Inf=================================================");
	LOGI(pszFullPath);
	LOGI("FULLPATH Level Inf=================================================");*/
#else
	const char *pszFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pszPath);
	//LOGI("FULLPATH Level Info=================================================");
	//LOGI(pszFullPath);
	//LOGI("FULLPATH Level Inf=================================================");
#endif
	FILE * pFile =  NULL;
	pFile = fopen(pszFullPath, "w+");
	if (pFile != NULL)
	{
		fprintf(pFile,"%d\n",iNumOfLevel);
		for (int i = 0; i < iNumOfLevel; i ++)
		{
			if (i==0) 
			{
				fprintf(pFile,"%d 0 0 1\n", (i+1) );
			}
			else
			{
				fprintf(pFile,"%d 0 0 0\n", (i+1) );
			}
		}

		fclose(pFile);
		//ResetLevelInfo(iNumOfLevel);
		return true;
	}
	return false;
}

bool CLevelManager::ResetLevel( const char* pszPath )
{
	int iNumOfLevel  = 0;
	#if ANDROID
	string pathWriteable = CCFileUtils::sharedFileUtils()->getWriteablePath();
	char pszFullPath[256] = {0};
	strcpy(pszFullPath, pathWriteable.c_str());
	strcat(pszFullPath, pszPath);
	/*const char * sdcard = PATH_EXTERNAL;
	int sdcardLength = strlen(sdcard);
	char* pszFullPath = new char[strlen(sdcard)+ strlen(pszPath)+1];
	strcpy(pszFullPath,sdcard);
	strcat(pszFullPath,pszPath);*/
	/*LOGI("FULLPATH Level Inf=================================================");
	LOGI(pszFullPath);
	LOGI("FULLPATH Level Inf=================================================");*/
#else
	const char *pszFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pszPath);
	//LOGI("FULLPATH Level Info=================================================");
	//LOGI(pszFullPath);
	//LOGI("FULLPATH Level Inf=================================================");
#endif
	//Neu chua load level
	if (m_iNumOfLevel == 0 || m_psLevelInfo == NULL)
	{
		char* psContentFile = CFileManager::GetInstance()->GetFileContent(pszFullPath);
		char pc_Line[99];
		if ( psContentFile == NULL)
		{
			//Neu chua ton tai file do'
			return false;
		}
		//Da ton tai file lay so luong phan tu trong do' ra
		ReadLine(psContentFile, pc_Line, 0);
		sscanf(pc_Line, "%d", &iNumOfLevel);
		CC_SAFE_DELETE_ARRAY(psContentFile);
	}
	else
	{
		//Da load file
		iNumOfLevel = m_iNumOfLevel;
	}
	//Ghi file
	FILE * pFile =  NULL;
	pFile = fopen(pszPath, "wb+");
	if (pFile != NULL)
	{
		fprintf(pFile,"%d\n",iNumOfLevel);
		for (int i = 0; i < iNumOfLevel; i ++)
		{
			fprintf(pFile,"%d 0 0 0\n", (i+1) );
		}

		fclose(pFile);
		ResetLevelInfo();
	}
	return true;
}

bool CLevelManager::ResetLevelInfo()
{
	if (!m_iNumOfLevel || !m_psLevelInfo)
	{
		return false;
	}
	for(int i = 0; i < m_iNumOfLevel; i ++)
	{
		m_psLevelInfo[i].m_NumOfStar = 0;
		m_psLevelInfo[i].m_iHighScore = 0;
		m_psLevelInfo[i].m_bIsPass = false;
	}
	return true;
}

void CLevelManager::ResetLevelInfo( int NumOfLevel )
{
	if (m_iNumOfLevel != 0 || m_psLevelInfo != NULL)
	{
		if (m_iNumOfLevel != NumOfLevel)
		{
			m_iNumOfLevel = NumOfLevel;
			CC_SAFE_DELETE_ARRAY(m_psLevelInfo);
			m_psLevelInfo = new SLevelInfomation[m_iNumOfLevel];
		}
	}
	for (int i = 0; i < NumOfLevel; i ++)
	{
		m_psLevelInfo[i].m_iLevel = i+1;
		m_psLevelInfo[i].m_NumOfStar = 0;
		m_psLevelInfo[i].m_iHighScore = 0;
		m_psLevelInfo[i].m_bIsPass = false;
	}
}

bool CLevelManager::SetLevelInfo( int idLevel, int NumOfStar, int HightScore, bool IsPass )
{
	if ( m_iNumOfLevel <= 0 || m_psLevelInfo == NULL 
		|| idLevel < 0 || idLevel >= m_iNumOfLevel)
	{
		return false;
	}
	if (NumOfStar > m_psLevelInfo[idLevel].m_NumOfStar)
	{
		m_psLevelInfo[idLevel].m_NumOfStar = NumOfStar;
	}
	if (HightScore > m_psLevelInfo[idLevel].m_iHighScore)
	{
		m_psLevelInfo[idLevel].m_iHighScore = HightScore;
	}
	if (m_psLevelInfo[idLevel].m_bIsPass == false)
	{
		m_psLevelInfo[idLevel].m_bIsPass = IsPass;
	}
	return true;
}
int CLevelManager::GetNumOfStar( int idLevel )
{
	SLevelInfomation * level = NULL;
	level = GetLevelInformation(idLevel);
	if ( level != NULL)
	{
		return level->m_NumOfStar;
	}
	return -1;
}

int CLevelManager::GetHighScore( int idLevel )
{
	SLevelInfomation * level = NULL;
	level = GetLevelInformation(idLevel);
	if ( level != NULL)
	{
		return level->m_iHighScore;
	}
	return -1;
}

bool CLevelManager::GetIsPass( int idLevel )
{
	SLevelInfomation * level = NULL;
	level = GetLevelInformation(idLevel);
	if ( level != NULL)
	{
		return level->m_bIsPass;
	}
	return false;
}

int CLevelManager::GetNumOfLevel()
{
	if(m_iNumOfLevel <= 0 || m_psLevelInfo == NULL)
		return 0;
	return m_iNumOfLevel;
}

bool CLevelManager::SetHighScore( int idLevel, int highScore )
{
	SLevelInfomation * level = NULL;
	level = GetLevelInformation(idLevel);
	if ( level != NULL)
	{
		if (level->m_iHighScore < highScore)
		{
			level->m_iHighScore = highScore;
			SetPassable(idLevel, true);
			return true;
		}
		return false;
	}
	return false;
}

bool CLevelManager::SetNumStar( int idLevel, int numStar )
{
	SLevelInfomation * level = NULL;
	level = GetLevelInformation(idLevel);
	if ( level != NULL)
	{
		if (level->m_NumOfStar < numStar)
		{
			level->m_NumOfStar = numStar;
			SetPassable(idLevel, true);
			return true;
		}
		return false;
	}
	return false;
}

void CLevelManager::SetPassable( int idLevel, bool isPass )
{
	SLevelInfomation * level = NULL;
	level = GetLevelInformation(idLevel);
	if ( level != NULL)
	{
		level->m_bIsPass = isPass;
	}
}

bool CLevelManager::CreateFileFirstGame( const char* pc_FileName, int iNumOfLevel )
{

	bool result = true;
	
	string pathTest = CCFileUtils::sharedFileUtils()->getWriteablePath();
	
#if ANDROID
	char FullPath[256] = {0};
	strcpy(FullPath,pathTest.c_str());
	strcat(FullPath,"LevelInfo.txt");
	FILE* pFile;
	pFile = fopen(FullPath,"r");
	if (pFile != NULL)
	{
		result = false;
		
		fclose(pFile);
	}
	else
	{
		result = true;
		
		pFile = fopen(FullPath,"w+");
		
		if (pFile != NULL)
		{
			fprintf(pFile,"%d\n",iNumOfLevel);
			for (int i = 0; i < iNumOfLevel; i ++)
			{
				if (i <= 5) 
				{
					fprintf(pFile,"%d 0 0 1\n", (i+1) );
				}
				else
				{
					fprintf(pFile,"%d 0 0 0\n", (i+1) );
				}
			}

			fclose(pFile);
			//ResetLevelInfo(iNumOfLevel);
			return true;
		}
		else
		{
			CCMessageBox("Create first file failed","Error");
		}
	}
	
#endif
	return result;
}
