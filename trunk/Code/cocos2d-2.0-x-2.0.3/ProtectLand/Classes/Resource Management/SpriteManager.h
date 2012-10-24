#ifndef __SPRITE_MANAGER_H__
#define __SPRITE_MANAGER_H__
#include "MySprite.h"
#include "FileManager.h"
#include "IncludeHelper.h"

#include "cocos2d.h"
struct SpriteInformation{
	int m_iId;
	char* m_pcFileName;
	CCRect m_rRect;
	E_TYPE_SPRITE m_eType;
	SpriteTotalInformation* m_sAnimationInfo;
	SpriteInformation(){
		m_iId = -1;
		m_pcFileName = NULL;
		m_sAnimationInfo = NULL;
	}
	~SpriteInformation(){
		CC_SAFE_DELETE_ARRAY(m_pcFileName);
		CC_SAFE_DELETE(m_sAnimationInfo);
	}

};
/*
class SpriteInformation{
protected:
	int m_iId;
	char* m_pcFileName;
public:
	SpriteInformation(){
		m_iId = -1;
		m_pcFileName = NULL;
	}
	~SpriteInformation(){
		CC_SAFE_DELETE_ARRAY(m_pcFileName);
	}
	int GetId()
	{
		return this->m_iId;
	}
	void SetId(int id)
	{
		this->m_iId = id;
	}
	char* GetFileName()
	{
		return this->m_pcFileName;
	}
	void SetFileName(char* name)
	{
		if (!name)
		{
			int length = strlen(name);
			if (!m_pcFileName)
			{
				CC_SAFE_DELETE_ARRAY(m_pcFileName);
			}
			m_pcFileName = new char[length+1];
			strcpy_s(m_pcFileName,length+1,name);
		}
	}
	void init(int id, char* name)
	{
		SetId(id);
		SetFileName(name);
	}
};
class ImageSpriteInformation : public SpriteInformation
{
protected:
	CCRect rect;
public:
	ImageSpriteInformation():SpriteInformation()
	{

	}
	CCRect GetRect()
	{
		return this->rect;
	}
	void SetRect(float x, float y, float width, float height)
	{
		this->rect.setRect(x,y,width,height);
	}
};
class SpriteFileInformation: public SpriteInformation
{
protected:
	SpriteTotalInformation* m_sAnimaInfo;
public:
	SpriteFileInformation():SpriteInformation()
	{
		m_sAnimaInfo = NULL;
	}
	~SpriteFileInformation()
	{
		CC_SAFE_DELETE(m_sAnimaInfo);
	}
};
*/
class CSpriteManager
{
protected:
	static CSpriteManager* s_Instance;
	CSpriteManager();
	CSpriteManager(const CSpriteManager &);
	virtual ~CSpriteManager();
	//Variable
	SpriteInformation* m_sSpriteInfo;
	int m_iNumOfSprite;
	cocos2d::CCArray * m_pContentArray;
public:
	static CSpriteManager* GetInstance();
	static void DestroyInstance();
	//MySprite* LoadSpriteFromFile
	void LoadResource(const char* pszPlist);
	int LoadFileResource(const char* pszPlist);
	int LoadResourceByStep(const char* pszNameResoure, int step);
	CMySprite* GetSpriteByID(eSpriteIDPic id);
};

#endif
