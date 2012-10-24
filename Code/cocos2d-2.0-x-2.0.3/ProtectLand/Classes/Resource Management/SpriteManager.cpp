#include "SpriteManager.h"
#include "IncludeHelper.h"
CSpriteManager* CSpriteManager::s_Instance = NULL;
void LoadResource_Sprite(CCArray* spriteDict, CCArray*& spriteArray, int nSprite);
void LoadResource_Sprite(CCArray* spriteDict, SpriteInformation* & sprite, int nSprite);
void LoadResource_SpriteByStep(CCDictionary* spriteInfoDict, SpriteInformation* & spriteInfo, int idx);
CSpriteManager::CSpriteManager()
{
	this->m_iNumOfSprite = 0;
	this->m_sSpriteInfo = NULL;
	this->m_pContentArray = NULL;
}

CSpriteManager::CSpriteManager( const CSpriteManager & )
{

}

CSpriteManager::~CSpriteManager()
{
	//CC_SAFE_RELEASE(this->FrameButtonArray);
	this->m_iNumOfSprite = 0;
	CC_SAFE_DELETE_ARRAY(this->m_sSpriteInfo);
	CC_SAFE_RELEASE_NULL(this->m_pContentArray);
	//this->SpriteArray;
}

void CSpriteManager::DestroyInstance()
{
	CC_SAFE_DELETE(s_Instance);
}

CSpriteManager* CSpriteManager::GetInstance()
{
	if (!s_Instance)
		s_Instance = new CSpriteManager();
	return s_Instance;
}
void LoadResource_Sprite(CCArray* spriteDict, CCArray*& spriteArray, int nSprite)
{
	for (int i = 0; i < nSprite; i ++)
	{
		CCDictionary* spriteInfo = (CCDictionary*)spriteDict->objectAtIndex(i);
		int id = spriteInfo->valueForKey("Id")->intValue();
		int Type = spriteInfo->valueForKey("Type")->intValue();
		int Pos_X = spriteInfo->valueForKey("Pos_X")->intValue();
		int Pos_Y = spriteInfo->valueForKey("Pos_Y")->intValue();
		const char* nameFile = spriteInfo->valueForKey("Filename")->getCString();
		//std::string nameFile("");
		//nameFile = ((CCString*)NameFileArr->objectAtIndex(0))->getCString();
		CMySprite* mySprite = NULL;
		const char *pszPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(nameFile);
		if (Type == TYPE_SPRITE_PICTURE)
		{
			

			CCDictionary* Dic_Rect = (CCDictionary*)spriteInfo->valueForKey("Rect");
			int x = Dic_Rect->valueForKey("X")->intValue();
			int y = Dic_Rect->valueForKey("Y")->intValue();
			int width = Dic_Rect->valueForKey("Width")->intValue();
			int height = Dic_Rect->valueForKey("Height")->intValue();

			// * frame = CC::create(pszPath ,CCRectMake(x,y,width,height));
			//CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(pszPath);
			if ( width > 0 && height > 0)
			{
				mySprite = CMySprite::CreateInstance(pszPath, TYPE_SPRITE_PICTURE,CCRectMake(x,y,width,height));//new MySprite(pszPath, TYPE_SPRITE_PICTURE,CCRectMake(x,y,width,height));
				if (mySprite != NULL)
				{
					//mySprite->autorelease();
					mySprite->retain();
					spriteArray->addObject(mySprite);
				}
			}
		}
		else if(TYPE_SPRITE_SRITE)
		{
			//const char *pszPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pszPath);
			mySprite = CMySprite::CreateInstance(pszPath, TYPE_SPRITE_SRITE,CCRectMake(0,0,10,10));
			mySprite->retain();
			//mySprite->autorelease();
			spriteArray->addObject(mySprite);
		}
		else{

		}
		if (mySprite)
		{
			mySprite->setPosition(ccp(Pos_X, Pos_Y));
		}
	}
}
void LoadResource_Sprite(CCArray* spriteDict, SpriteInformation* & spriteInfo, int nSprite)
{
	for (int i = 0; i < nSprite; i ++)
	{
		CCDictionary* spriteInfoDict = (CCDictionary*)spriteDict->objectAtIndex(i);
		int id = spriteInfoDict->valueForKey("Id")->intValue();
		int Type = spriteInfoDict->valueForKey("Type")->intValue();
		int Pos_X = spriteInfoDict->valueForKey("Pos_X")->intValue();
		int Pos_Y = spriteInfoDict->valueForKey("Pos_Y")->intValue();
		const char* nameFile = spriteInfoDict->valueForKey("Filename")->getCString();
		//std::string nameFile("");
		//nameFile = ((CCString*)NameFileArr->objectAtIndex(0))->getCString();
		//MySprite* mySprite = NULL;
		const char *pszPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(nameFile);
		
		spriteInfo[i].m_iId = id;
		int lengFileName = strlen(pszPath);
		spriteInfo[i].m_pcFileName = new char[lengFileName+1];
		strcpy(spriteInfo[i].m_pcFileName, pszPath);
		if (Type == TYPE_SPRITE_PICTURE)
		{

			spriteInfo[i].m_eType = TYPE_SPRITE_PICTURE;
			CCDictionary* Dic_Rect = (CCDictionary*)spriteInfoDict->valueForKey("Rect");
			int x = Dic_Rect->valueForKey("X")->intValue();
			int y = Dic_Rect->valueForKey("Y")->intValue();
			int width = Dic_Rect->valueForKey("Width")->intValue();
			int height = Dic_Rect->valueForKey("Height")->intValue();

			// * frame = CC::create(pszPath ,CCRectMake(x,y,width,height));
			//CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(pszPath);
			if ( width > 0 && height > 0)
			{
				spriteInfo[i].m_rRect.setRect(x,y,width,height);
			}
		}
		else if(TYPE_SPRITE_SRITE)
		{
			spriteInfo[i].m_eType = TYPE_SPRITE_SRITE;
			spriteInfo[i].m_sAnimationInfo = new SpriteTotalInformation;
			CSpriteFileReader::ReadFromFile(pszPath, spriteInfo[i].m_sAnimationInfo);
			
		}
		else{

		}
		
	}
}
void LoadResource_SpriteByStep(CCDictionary* spriteInfoDict, SpriteInformation* & spriteInfo, int idx)
{
	int id = spriteInfoDict->valueForKey("Id")->intValue();
	int Type = spriteInfoDict->valueForKey("Type")->intValue();
	int Pos_X = spriteInfoDict->valueForKey("Pos_X")->intValue();
	int Pos_Y = spriteInfoDict->valueForKey("Pos_Y")->intValue();
	const char* nameFile = spriteInfoDict->valueForKey("Filename")->getCString();
	//std::string nameFile("");
	//nameFile = ((CCString*)NameFileArr->objectAtIndex(0))->getCString();
	//MySprite* mySprite = NULL;
	const char *pszPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(nameFile);

	spriteInfo[idx].m_iId = id;
	int lengFileName = strlen(pszPath);
	spriteInfo[idx].m_pcFileName = new char[lengFileName+1];
	strcpy(spriteInfo[idx].m_pcFileName, pszPath);
	if (Type == TYPE_SPRITE_PICTURE)
	{

		spriteInfo[idx].m_eType = TYPE_SPRITE_PICTURE;
		CCDictionary* Dic_Rect = (CCDictionary*)spriteInfoDict->valueForKey("Rect");
		int x = Dic_Rect->valueForKey("X")->intValue();
		int y = Dic_Rect->valueForKey("Y")->intValue();
		int width = Dic_Rect->valueForKey("Width")->intValue();
		int height = Dic_Rect->valueForKey("Height")->intValue();

		// * frame = CC::create(pszPath ,CCRectMake(x,y,width,height));
		//CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(pszPath);
		if ( width > 0 && height > 0)
		{
			spriteInfo[idx].m_rRect.setRect(x,y,width,height);
		}
	}
	else if(TYPE_SPRITE_SRITE)
	{
		spriteInfo[idx].m_eType = TYPE_SPRITE_SRITE;
		spriteInfo[idx].m_sAnimationInfo = new SpriteTotalInformation;
		CSpriteFileReader::ReadFromFile(pszPath, spriteInfo[idx].m_sAnimationInfo);

	}
	else{

	}

}
void CSpriteManager::LoadResource( const char* pszPlist )
{
	const char *pszPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pszPlist);
	CCDictionary *dict = CCDictionary::createWithContentsOfFileThreadSafe(pszPath);

	CCArray* spriteDict = (CCArray*)dict->valueForKey("Sprites");//objectForKey("Resources");
	m_iNumOfSprite = spriteDict->count();
	//LoadResource_Sprite(spriteDict, SpriteArray, m_iNumOfSprite);
	m_sSpriteInfo = new SpriteInformation[m_iNumOfSprite];
	LoadResource_Sprite(spriteDict, m_sSpriteInfo, m_iNumOfSprite);

	CCArray* buttonDict = (CCArray*)dict->valueForKey("Buttons");

	//string texturePath("");
	//if (spriteDict)
	//{
	//	// try to read  texture file name from meta data
	//	//texturePath = metadataDict->valueForKey("textureFileName")->getCString();
	//}
}

CMySprite* CSpriteManager::GetSpriteByID( eSpriteIDPic id )
{
	if (id < 0 || id > m_iNumOfSprite)
	{
		return NULL;
	}
	return CMySprite::CreateInstance(m_sSpriteInfo[id].m_pcFileName, m_sSpriteInfo[id].m_eType, m_sSpriteInfo[id].m_sAnimationInfo, m_sSpriteInfo[id].m_rRect);
}

int CSpriteManager::LoadFileResource( const char* pszPlist )
{
	const char *pszPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pszPlist);
	CCDictionary* content = NULL;
	content = CCDictionary::createWithContentsOfFileThreadSafe(pszPath);
	if (content == NULL)
	{
		return 0;
	}
	CC_SAFE_RELEASE_NULL(m_pContentArray);
	m_pContentArray = (CCArray*)content->valueForKey("Sprites");
	m_iNumOfSprite = m_pContentArray->count();
	CC_SAFE_DELETE_ARRAY(m_sSpriteInfo);
	m_sSpriteInfo = new SpriteInformation[m_iNumOfSprite];
	m_pContentArray->retain();
	return m_iNumOfSprite;
}

int CSpriteManager::LoadResourceByStep( const char* pszNameResoure, int step )
{
	if (m_pContentArray)
	{
		//CCArray* resoureDict = (CCArray*)m_pContentDict->valueForKey(pszNameResoure);
		if (step >= m_iNumOfSprite)
		{
			return ++step;
		}
		else
		{
			LoadResource_SpriteByStep((CCDictionary*)m_pContentArray->objectAtIndex(step), m_sSpriteInfo, step);
			step++;
			return step;
		}
	}
	else
	{
		return -1;
	}
}