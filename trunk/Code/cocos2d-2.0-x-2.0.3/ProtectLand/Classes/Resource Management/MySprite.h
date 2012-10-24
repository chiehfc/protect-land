#ifndef __MY_SPRITE_H__
#define __MY_SPRITE_H__
#include "cocos2d.h"
using namespace cocos2d;
#include "CCPlatformDefine.h"
#include "GameConfig.h"
#include "SpriteFileReader.h"
#include "stdio.h"
#include "stdarg.h"

class CMySprite : public cocos2d::CCSprite
{
	/*CC_PROPERTY(cocos2d::CCSprite*, _sprite, Sprite)
	CC_PROPERTY(cocos2d::CCAnimation*, _animations, Anim)
	CC_PROPERTY(int, _nAnimation, nAnimation)
	CC_PROPERTY(int, _iAnimation, iAnimation)*/
	//CCSprite* sprite;
	int m_iNumOfAnimation;
	CCArray* m_pAnimationArray;

public:
	CCArray* getAnimationArray()
	{
		return m_pAnimationArray;
	}
	/*CCSprite* getSprite()
	{
		return sprite;
	}
	void setSprite(CCSprite * s)
	{
		sprite = s;
	}*/
	
	int getNumOfAnimation(){return m_iNumOfAnimation;}
	void setNumOfAnimation(int n){ m_iNumOfAnimation = n;}
	/*Constructor*/
	CMySprite();

	CMySprite(const char* pPath):CCSprite(){
		m_iNumOfAnimation = 0;
		m_pAnimationArray = NULL;
		bool res = this->LoadMySpriteFromFile(pPath);
		CCAssert( res == true, "can't load sprite from file \"" + pPath +"\"");
	}
	CMySprite(const char* pPath, E_TYPE_SPRITE type):CCSprite(){
		m_iNumOfAnimation = 0;
		m_pAnimationArray = NULL;

		switch(type)
		{
		case TYPE_SPRITE_SRITE:
			{
				bool res = this->LoadMySpriteFromFile(pPath);
				CCAssert( res == true, "can't load sprite from file \"" + pPath +"\"");
				break;
			}
		case TYPE_SPRITE_PICTURE:
			{
				CCAssert(pPath != NULL, "Invalid filename for sprite");

				CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(pPath);
				if (pTexture)
				{
					CCRect rect = CCRectZero;
					rect.size = pTexture->getContentSize();
					bool isInitTexture =  initWithTexture(pTexture, rect);
					CCAssert(isInitTexture == true, "can't create sprite from file \"" + pPath +"\"");
				}
				else
				{
					CCAssert(true, "can't create sprite from file \"" + pPath +"\"");
				}
				break;
			}
		default:
			CCAssert(true, "Wrong SPRITE_TYPE");
			break;
		}
		/*CCSize size = this->getContentSize();
		m_CollisionBox.setRect(0,0,size.width, size.height);*/
	}

	CMySprite(const char* pPath, E_TYPE_SPRITE type,SpriteTotalInformation* AnimationInfo, CCRect rect):CCSprite(){
		m_iNumOfAnimation = 0;
		m_pAnimationArray = NULL;

		switch(type)
		{
		case TYPE_SPRITE_SRITE:
			{
				bool res = this->LoadMySpriteFromInformation(pPath, AnimationInfo);
				CCAssert( res == true, "can't load sprite from file \"" + pPath +"\"");
				break;
			}
		case TYPE_SPRITE_PICTURE:
			{
				CCAssert(pPath != NULL, "Invalid filename for sprite");

				CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(pPath);
				if (pTexture)
				{
					CCRect rectangle = CCRectZero;
					rectangle.size = pTexture->getContentSize();
					bool isInitTexture =  initWithTexture(pTexture, rectangle);
					CCAssert(isInitTexture == true, "can't create sprite from file \"" + pPath +"\"");
				}
				else
				{
					CCAssert(true, "can't create sprite from file \"" + pPath +"\"");
				}
				break;
			}
		default:
			CCAssert(true, "Wrong SPRITE_TYPE");
			break;
		}

	}
	
	~CMySprite(){

		for(int i = 0; i < m_iNumOfAnimation; i ++)
		{
			CCArray* array = (CCArray*)m_pAnimationArray->objectAtIndex(i);
			array->removeAllObjects();
			array->release();
		}
		//AnimationArray->removeAllObjects();
		CC_SAFE_RELEASE( m_pAnimationArray);
	}
	bool LoadMySpriteFromFile(const char* pPath);
	bool LoadMySpriteFromInformation(const char* pPath, SpriteTotalInformation* info);
	
	bool init(const char *pPath, E_TYPE_SPRITE type, const CCRect& rect)
	{
		switch(type)
		{
		case TYPE_SPRITE_SRITE:
			{
				bool res = this->LoadMySpriteFromFile(pPath);
				CCAssert( res == true, "can't load sprite from file \"" + pPath +"\"");
				return res;
				break;
			}
		case TYPE_SPRITE_PICTURE:
			{
				CCAssert(pPath != NULL, "Invalid filename for sprite");

				CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(pPath);
				if (pTexture)
				{
					bool isInitTexture =  initWithTexture(pTexture, rect);
					CCAssert(isInitTexture == true, "can't create sprite from file \"" + pPath +"\"");
					if (isInitTexture)
					{
						//this->autorelease();
					}
					return isInitTexture;
				}
				else
				{
					CCAssert(true, "can't create sprite from file \"" + pPath +"\"");
					return false;
				}
				break;
			}
		default:
			CCAssert(true, "Wrong SPRITE_TYPE");
			return false;
			break;
		}
	}
	static CMySprite* CreateInstance(const char* pPath, E_TYPE_SPRITE type, CCRect rect)
	{
		CMySprite* result = new CMySprite(pPath, type);
		if (result != NULL)
		{
			result->retain();
			result->release();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(result);
		}
		return result;
	}
	static CMySprite* CreateInstance(const char* pPath, E_TYPE_SPRITE type,SpriteTotalInformation* AnimationInfo, CCRect rect)
	{
		CMySprite* result = new CMySprite(pPath, type, AnimationInfo, rect);
		if (result != NULL)
		{
			result->retain();
			result->release();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(result);
		}
		return result;
	}
	/*Chay 1 action trong khoang thoi gian*/
	void PlayAnimation( int idAnimation, float DurationTime, bool isRunForever, bool isReverse );
	/*Chạy 1 action với n lần*/
	void PlayAnimation (int idAnimation, float DurationTime, int NumOfRepeat, bool isReverse );
	/**/
	void PlayAnimationTwoAction( float DurationTime, int idx, int jdx , bool isForever );
	void PlayAnimationToPosition( float x, float y, float time );
	void PlayAnimationToPosition( float x, float y, float TimeToMove, int idAnimation, float DurationTime,
		bool isReverse, CCFiniteTimeAction* actionMoveDone  );
	void PlayAnimationToPosition( float x, float y, float TimeToMove, float DurationTime,
		bool isReverse);
	bool PlayAnimation( float TimeDuration, ... );
	bool PlayAnimation( float TimeDuration, bool isReverse, CCFiniteTimeAction* actionMoveDone, ... );
	/*Play animation with Duration Time */
	void PlayAnimation( int idAnimation, float DurationTime, int NumOfRepeat, bool isReverse, CCFiniteTimeAction* actionMoveDone );
	bool SetFrame(int idAnimation, int FrameIdx);
};
#endif