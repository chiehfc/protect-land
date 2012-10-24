#include "MySprite.h"

int getIdModule( ModuleSpriteInfo* p_s_Modules, int nModule, int i_IdFModule );
int getIdFrame( FrameSpriteInfo* p_s_Frames, int nFrame, int i_IdAFrame );

int getIdModule( ModuleSpriteInfo* p_s_Modules, int nModule, int i_IdFModule ) 
{
	for(int i = 0; i < nModule; i ++)
	{
		if(p_s_Modules[i].i_IdModule == i_IdFModule)
			return i;
	}
	return -1;
}

int getIdFrame( FrameSpriteInfo* p_s_Frames, int nFrame, int i_IdAFrame ) 
{
	for(int i = 0; i < nFrame; i ++)
	{
		if(p_s_Frames[i].i_IdOfFrame == i_IdAFrame)
			return i;
	}
	return -1;
}


bool CMySprite::LoadMySpriteFromFile( const char* pPath )
{
	SpriteTotalInformation* info = new SpriteTotalInformation;
	

//#if DEBUG_MODE
//	const char * sdcard = "sdcard/resource/";
//	int sdcardLength = strlen(sdcard);
//	char* pszFullPath = new char[strlen(sdcard)+ strlen(pPath)+1];
//	strcpy(pszFullPath,sdcard);
//	strcat(pszFullPath,pPath);
//	/*LOGI("FULLPATH SPRITE=================================================");
//	LOGI(pszFullPath);
//	LOGI("FULLPATH SPRITE=================================================");*/
//#else
	const char* pszFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pPath);
	/*LOGI("FULLPATH SPRITE=================================================");
	LOGI(pszFullPath);
	LOGI("FULLPATH SPRITE=================================================");*/
//#endif
	CSpriteFileReader::ReadFromFile(pszFullPath, info);
	//LOGE("*************************MySprite.cpp_LoadMySpriteFromFile******************************");
	int nImage = info->s_GeneralInfo.i_NumOfImages;
	int lengPath = strlen(pszFullPath);
	char* path = new char[lengPath+1];
	strcpy(path, pszFullPath);
	//LOGI("Path before: %s",path);
	for(int i = 0; i < lengPath+1; i++)
		path[i] = tolower(path[i]);
	char* posTemp = strstr(path,".sprite");
	int pos = (posTemp - path)/sizeof(char);
	//LOGI("%d",pos);
	for(; pos >= 0 ; pos--)
	{
		if (path[pos] == '\\' || path[pos] == '/')
		{
			break;
		}
	}
	path[pos+1] ='\0';
	//LOGI("Path after: %s",path);
	//CCTexture2D * texture = new CCTexture2D[nImage];
	CCArray * textures = CCArray::createWithCapacity(nImage);
	//textures->retain();
	//
	/*LOGE("__________________+++++++++++++++++______________");
	LOGE("%d",info->s_GeneralInfo.i_NumOfImages);
	LOGE("%d",info->s_GeneralInfo.i_NumOfModules);
	LOGE("%d",info->s_GeneralInfo.i_NumOfFrames);
	LOGE("%d",info->s_GeneralInfo.i_NumOfAnims);
	LOGE("___________________ENd Reader______________");
	LOGE("*************************MySprite.cpp_LoadMySpriteFromFile******************************Begin for %d-%d",nImage,pos);*/
	for(int i = 0; i < nImage; i ++)
	{
		if (pos >= 0)
		{
			char* FileName = info->p_s_Images[i].pc_NameImage;
			int lengFileName = strlen(FileName);
			char* FullPath = new char[pos+ lengFileName ];
			strcpy(FullPath,path);
			strcat (FullPath,FileName+2);
			//LOGE("%s : Pos:%d  Filename: %d  Total: %d _ %d",FullPath,pos,lengFileName,pos+ lengFileName,strlen(FullPath));
			////strcpy_s(FullPath+pos,lengFileName,FileName);
			//LOGE("*************************MySprite.cpp_LoadMySpriteFromFile*****************If True*************11111");
			CCTexture2D* textureTemp = CCTextureCache::sharedTextureCache()->addImage(FullPath);
			//LOGE("%s",FileName+2);
			/*if (textureTemp ==  NULL)
			{
				LOGE("sd;fkljso;fjpo;sdgfj;dzfsjgfjesgrjesjtghjdortyjO:drtjoyh;l';yhdrjhortyhjdrtfyhjdr");
			}*/
			//LOGE("*************************MySprite.cpp_LoadMySpriteFromFile******************************222222");
			textures->addObject(textureTemp);
			//LOGE("*************************MySprite.cpp_LoadMySpriteFromFile******************************33333333");

			CC_SAFE_DELETE_ARRAY(FullPath);
		}
		else{
			//LOGE("*************************MySprite.cpp_LoadMySpriteFromFile*****************If False*************11111");
			textures->addObject(CCTextureCache::sharedTextureCache()->addImage(info->p_s_Images[i].pc_NameImage+2));
		}
	}
	//LOGE("*************************MySprite.cpp_LoadMySpriteFromFile******************************End For");
	delete path;


	int nFrame = info->s_GeneralInfo.i_NumOfFrames;
	int nModule = info->s_GeneralInfo.i_NumOfModules;


	int nAnim = info->s_GeneralInfo.i_NumOfAnims;
	m_iNumOfAnimation = nAnim;
	m_pAnimationArray = CCArray::createWithCapacity(nAnim);
	m_pAnimationArray->retain();
	//LOGE("*************************MySprite.cpp_LoadMySpriteFromFile******************************3333333333");
	for (int i = 0; i < nAnim; i ++)
	{
		AnimSpriteInfo* AnimSprite = (info->p_s_Anims+i);
		int nAFrame = AnimSprite->i_nAFrame;
		CCArray* frameArray = CCArray::createWithCapacity(nAFrame);
		frameArray->retain();
		for(int j = 0; j < nAFrame; j ++)
		{
			AFrameInfo AFrame = AnimSprite->s_AFrames[j];
			int i_idFrame = getIdFrame(info->p_s_Frames,nFrame, AFrame.i_IdFrame);
			FrameSpriteInfo* frameInfo = (info->p_s_Frames+i_idFrame);

			int nFModule = frameInfo->i_nFModule;
			for (int k = 0; k < nFModule; k ++)
			{
				FModuleInfo* fModule = (frameInfo->s_FModules+k);
				int i_idModule = getIdModule(info->p_s_Modules, nModule, fModule->i_IdFModule);
				ModuleSpriteInfo* Module = (info->p_s_Modules+i_idModule);
				CCTexture2D* txt = (CCTexture2D* )textures->objectAtIndex(Module->i_IdImage);
				if (Module->i_Width > 0 && Module->i_Height > 0)
				{
					CCSpriteFrame* FrameSprite = CCSpriteFrame::createWithTexture(txt,CCRectMake(Module->i_BeginPos_X, Module->i_BeginPos_Y, Module->i_Width, Module->i_Height));
					//FrameSprite->retain();
					FrameSprite->setOffset(ccp(
						(AFrame.i_BeginPos_X+fModule->i_BeginPos_X),
						-(AFrame.i_BeginPos_Y+fModule->i_BeginPos_Y)
						));
					frameArray->addObject(FrameSprite);
				}
			}

			//AFrame.i_BeginPos_X
		}
		m_pAnimationArray->addObject(frameArray);
	}
	//LOGE("*************************MySprite.cpp_LoadMySpriteFromFile******************************44444444444444");
	CC_SAFE_DELETE(info);
	//LOGE("*************************MySprite.cpp_LoadMySpriteFromFile_21/08/2012******************************");
	if (nAnim > 0)
	{
		for(int i = 0; i < nAnim; i ++)
		{
			CCArray* anim = (CCArray*)m_pAnimationArray->objectAtIndex(i);
			if (anim->count() > 0)
			{
				CCSpriteFrame* frame = (CCSpriteFrame*)anim->objectAtIndex(0);

				//FIX ME:
				//FROM COCOS

				bool bRet = initWithTexture(frame->getTexture(), frame->getRect());
				setDisplayFrame(frame);
				if (bRet)
				{
					this->autorelease();

					return true;
				}
				CCAssert(frame != NULL, "");

				return false;

				//END FIX ME
				//	break;
			}
		}
	}
	return true;
}

CMySprite::CMySprite():CCSprite()
{
	m_iNumOfAnimation = 0;
	m_pAnimationArray = NULL;
}

bool CMySprite::LoadMySpriteFromInformation( const char* pPath, SpriteTotalInformation* info )
{
	const char* pszFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pPath);

	int nImage = info->s_GeneralInfo.i_NumOfImages;
	int lengPath = strlen(pszFullPath);
	char* path = new char[lengPath+1];
	strcpy(path, pszFullPath);
	for(int i = 0; i < lengPath+1; i++)
		path[i] = tolower(path[i]);
	char* posTemp = strstr(path,".sprite");
	int pos = (posTemp - path)/sizeof(char);
	for(; pos >= 0 ; pos--)
	{
		if (path[pos] == '\\' || path[pos] == '/')
		{
			break;
		}
	}
	path[pos+1] ='\0';
	//CCTexture2D * texture = new CCTexture2D[nImage];
	CCArray * textures = CCArray::createWithCapacity(nImage);
	//textures->retain();
	//
	for(int i = 0; i < nImage; i ++)
	{
		if (pos >= 0)
		{
			char* FileName = info->p_s_Images[i].pc_NameImage;
			int lengFileName = strlen(FileName);
			char* FullPath = new char[pos+ lengFileName ];
			strcpy(FullPath,path);
			strcat (FullPath,FileName+2);
			//LOGE("*************************MySprite.cpp_LoadMySpriteFromFile*****************If True*************11111");
			CCTexture2D* textureTemp = CCTextureCache::sharedTextureCache()->addImage(FullPath);
			//LOGE("*************************MySprite.cpp_LoadMySpriteFromFile******************************222222");
			textures->addObject(textureTemp);
			//LOGE("*************************MySprite.cpp_LoadMySpriteFromFile******************************33333333");

			CC_SAFE_DELETE_ARRAY(FullPath);
		}
		else{
			//LOGE("*************************MySprite.cpp_LoadMySpriteFromFile*****************If False*************11111");
			textures->addObject(CCTextureCache::sharedTextureCache()->addImage(info->p_s_Images[i].pc_NameImage+2));
		}
	}
	//LOGE("*************************MySprite.cpp_LoadMySpriteFromFile******************************End For");
	delete path;


	int nFrame = info->s_GeneralInfo.i_NumOfFrames;
	int nModule = info->s_GeneralInfo.i_NumOfModules;


	int nAnim = info->s_GeneralInfo.i_NumOfAnims;
	m_iNumOfAnimation = nAnim;
	m_pAnimationArray = CCArray::createWithCapacity(nAnim);
	m_pAnimationArray->retain();
	//LOGE("*************************MySprite.cpp_LoadMySpriteFromFile******************************3333333333");
	for (int i = 0; i < nAnim; i ++)
	{
		AnimSpriteInfo* AnimSprite = (info->p_s_Anims+i);
		int nAFrame = AnimSprite->i_nAFrame;
		CCArray* frameArray = CCArray::createWithCapacity(nAFrame);
		frameArray->retain();
		for(int j = 0; j < nAFrame; j ++)
		{
			AFrameInfo AFrame = AnimSprite->s_AFrames[j];
			int i_idFrame = getIdFrame(info->p_s_Frames,nFrame, AFrame.i_IdFrame);
			FrameSpriteInfo* frameInfo = (info->p_s_Frames+i_idFrame);

			int nFModule = frameInfo->i_nFModule;
			for (int k = 0; k < nFModule; k ++)
			{
				FModuleInfo* fModule = (frameInfo->s_FModules+k);
				int i_idModule = getIdModule(info->p_s_Modules, nModule, fModule->i_IdFModule);
				ModuleSpriteInfo* Module = (info->p_s_Modules+i_idModule);
				CCTexture2D* txt = (CCTexture2D* )textures->objectAtIndex(Module->i_IdImage);
				if (Module->i_Width > 0 && Module->i_Height > 0)
				{
					CCSpriteFrame* FrameSprite = CCSpriteFrame::createWithTexture(txt,CCRectMake(Module->i_BeginPos_X, Module->i_BeginPos_Y, Module->i_Width, Module->i_Height));
					//FrameSprite->retain();
					FrameSprite->setOffset(ccp(
						(AFrame.i_BeginPos_X+fModule->i_BeginPos_X),
						-(AFrame.i_BeginPos_Y+fModule->i_BeginPos_Y)
						));
					frameArray->addObject(FrameSprite);
				}
			}

			//AFrame.i_BeginPos_X
		}
		m_pAnimationArray->addObject(frameArray);
	}
	//LOGE("*************************MySprite.cpp_LoadMySpriteFromFile******************************44444444444444");
	//CC_SAFE_DELETE(info);
	//LOGE("*************************MySprite.cpp_LoadMySpriteFromFile_21/08/2012******************************");
	if (nAnim > 0)
	{
		for(int i = 0; i < nAnim; i ++)
		{
			CCArray* anim = (CCArray*)m_pAnimationArray->objectAtIndex(i);
			if (anim->count() > 0)
			{
				CCSpriteFrame* frame = (CCSpriteFrame*)anim->objectAtIndex(0);

				//FIX ME:
				//FROM COCOS

				bool bRet = initWithTexture(frame->getTexture(), frame->getRect());
				setDisplayFrame(frame);
				if (bRet)
				{
					this->autorelease();

					return true;
				}
				CCAssert(frame != NULL, "");

				return false;

				//END FIX ME
				//	break;
			}
		}
	}
	return true;
}
void CMySprite::PlayAnimation( int idAnimation, float DurationTime, bool isRunForever, bool isReverse )
{
	if (idAnimation < 0 || idAnimation >= m_iNumOfAnimation)
	{
		return;
	}
	CCArray* arrAnim = (CCArray*)m_pAnimationArray->objectAtIndex(idAnimation);
	float numOfFrame = arrAnim->count();
	CCAnimation *anima = CCAnimation::create(arrAnim, DurationTime/numOfFrame);
	CCActionInterval* seq = (CCActionInterval*) CCAnimate::create(anima);
	if(isReverse)
		seq = seq->reverse();
	if (isRunForever)
	{
		this->stopAllActions();
		this->runAction(CCRepeatForever::create( seq ) );
	}else{
		this->stopAllActions();
		this->runAction(seq);
	}
}

void CMySprite::PlayAnimation( int idAnimation, float DurationTime, int NumOfRepeat, bool isReverse )
{
	if (idAnimation < 0 || idAnimation > m_iNumOfAnimation)
	{
		return;
	}
	CCArray* arrAnim = (CCArray*)m_pAnimationArray->objectAtIndex(idAnimation);
	float numOfFrame = arrAnim->count();
	CCAnimation *anima = CCAnimation::create(arrAnim, DurationTime/numOfFrame);
	CCActionInterval* seq = (CCActionInterval*) CCAnimate::create(anima);
	if(isReverse)
		seq = seq->reverse();
	CCArray* AnimArray = CCArray::createWithCapacity(NumOfRepeat);
	for(int i = 0; i < NumOfRepeat; i ++)
	{
		AnimArray->addObject(seq);
	}
	this->runAction(CCSequence::actionWithArray(AnimArray));
	/*if (isRepeat)
	{
		sprite->runAction(CCRepeatForever::create( seq ) );
	}else{
		sprite->runAction(seq);
	}*/
}

bool CMySprite::PlayAnimation( float TimeDuration, ... )
{
	va_list ap;
	int idx = 0;
	bool isPlayable = true;
	CCArray* arrayOfAction = CCArray::create();

	/*CCArray* arrAnim = (CCArray*)m_pAnimationArray->objectAtIndex(idAnimation);
	float numOfFrame = arrAnim->count();
	CCAnimation *anima = CCAnimation::create(arrAnim, DurationTime/numOfFrame);
	CCActionInterval* seq = (CCActionInterval*) CCAnimate::create(anima);
	if(isReverse)
		seq = seq->reverse();
	CCArray* AnimArray = CCArray::create(NumOfRepeat);
	for(int i = 0; i < NumOfRepeat; i ++)
	{
		AnimArray->addObject(seq);
	}
	this->runAction(CCSequence::actionWithArray(AnimArray));*/

	CCArray* arrAnim;
	CCAnimation *anima;
	CCActionInterval* seq;
	va_start(ap, TimeDuration);

	idx = va_arg(ap,int);
	do 
	{
		if ( idx < 0 || idx > m_iNumOfAnimation)
		{
			isPlayable = false;
			break;
		}
		arrAnim = (CCArray*)m_pAnimationArray->objectAtIndex(idx);
		int nFrame = arrAnim->count();

		anima = CCAnimation::create(arrAnim, TimeDuration/nFrame);

		seq = (CCActionInterval*) CCAnimate::create(anima);
		arrayOfAction->addObject(seq);

		idx = va_arg(ap, int);
	} while (idx >= 0);

	va_end(ap);

	if (!isPlayable)
	{
		arrayOfAction->removeAllObjects();
	}
	else
	{
		this->stopAllActions();
		this->runAction(CCSequence::actionWithArray(arrayOfAction));
	}
	return isPlayable;
}

void CMySprite::PlayAnimation( int idAnimation, float DurationTime, int NumOfRepeat, bool isReverse, CCFiniteTimeAction* actionMoveDone )
{
	if (idAnimation < 0 || idAnimation > m_iNumOfAnimation)
	{
		return;
	}
	CCArray* arrAnim = (CCArray*) m_pAnimationArray->objectAtIndex(idAnimation);
	float numOfFrame = arrAnim->count();
	CCAnimation *anima = CCAnimation::createWithSpriteFrames(arrAnim, DurationTime/numOfFrame);
	CCActionInterval* seq = (CCActionInterval*) CCAnimate::create(anima);
	if(isReverse)
		seq = seq->reverse();
	CCArray* AnimArray = CCArray::createWithCapacity(NumOfRepeat);
	for(int i = 0; i < NumOfRepeat; i ++)
	{
		AnimArray->addObject(seq);
	}
	if (actionMoveDone != NULL)
	{
		AnimArray->addObject(actionMoveDone);
	}
	this->stopAllActions();
	this->runAction(CCSequence::actionWithArray(AnimArray));
}

bool CMySprite::PlayAnimation( float TimeDuration, bool isReverse, CCFiniteTimeAction* actionDone, ... )
{
	va_list ap;
	int idx = 0;
	bool isPlayable = true;
	CCArray* arrayOfAction = CCArray::create();

	/*CCArray* arrAnim = (CCArray*)m_pAnimationArray->objectAtIndex(idAnimation);
	float numOfFrame = arrAnim->count();
	CCAnimation *anima = CCAnimation::create(arrAnim, DurationTime/numOfFrame);
	CCActionInterval* seq = (CCActionInterval*) CCAnimate::create(anima);
	if(isReverse)
		seq = seq->reverse();
	CCArray* AnimArray = CCArray::create(NumOfRepeat);
	for(int i = 0; i < NumOfRepeat; i ++)
	{
		AnimArray->addObject(seq);
	}
	this->runAction(CCSequence::actionWithArray(AnimArray));*/

	CCArray* arrAnim;
	CCAnimation *anima;
	CCActionInterval* seq;
	va_start(ap, actionDone);

	idx = va_arg(ap,int);
	do 
	{
		if ( idx < 0 || idx > m_iNumOfAnimation)
		{
			isPlayable = false;
			break;
		}
		arrAnim = (CCArray*)m_pAnimationArray->objectAtIndex(idx);
		int nFrame = arrAnim->count();

		anima = CCAnimation::create(arrAnim, TimeDuration/nFrame);

		seq = (CCActionInterval*) CCAnimate::create(anima);
		if (isReverse)
		{
			seq = seq->reverse();
		}
		arrayOfAction->addObject(seq);

		idx = va_arg(ap, int);
	} while (idx >= 0);

	va_end(ap);

	if (!isPlayable)
	{
		arrayOfAction->removeAllObjects();
	}
	else
	{
		if (actionDone != NULL)
		{
			arrayOfAction->addObject(actionDone);
		}
		this->stopAllActions();
		this->runAction(CCSequence::actionWithArray(arrayOfAction));
	}
	return isPlayable;
}

void CMySprite::PlayAnimationTwoAction( float timeDuration, int idx, int jdx , bool isForever)
{
	if (idx < 0 || idx > m_iNumOfAnimation ||
		jdx < 0 || jdx > m_iNumOfAnimation)
	{
		return;
	}
	CCArray* arrAnim1 = (CCArray*)m_pAnimationArray->objectAtIndex(idx);
	CCArray* arrAnim2 = (CCArray*)m_pAnimationArray->objectAtIndex(jdx);
	
	int nFrame1 = arrAnim1->count();
	int nFrame2 = arrAnim2->count();

	CCAnimation *anima1 = CCAnimation::create(arrAnim1, timeDuration/nFrame1);
	CCAnimation *anima2 = CCAnimation::create(arrAnim2, timeDuration/nFrame2);

	CCActionInterval* seq1 = (CCActionInterval*) CCAnimate::create(anima1);
	CCActionInterval* seq2 = (CCActionInterval*) CCAnimate::create(anima2);

	this->stopAllActions();
	if (isForever)
	{
		this->runAction(CCRepeatForever::create(CCSequence::actionOneTwo(seq1,seq2)));
	}
	else{
		this->runAction(CCSequence::actionOneTwo(seq1,seq2));
	}
	/*if (isRepeat)
	{
		sprite->runAction(CCRepeatForever::create( seq ) );
	}else{
		sprite->runAction(seq);
	}*/
}

void CMySprite::PlayAnimationToPosition(float x, float y, float time)
{
	this->runAction(CCMoveTo::actionWithDuration( time, 
		ccp(x,y) ));
}
void CMySprite::PlayAnimationToPosition( float x, float y, float TimeToMove, float DurationTime, 
	bool isReverse)
{
	CCArray* arrAnim = (CCArray*)m_pAnimationArray->objectAtIndex(0);
	CCArray* arrAnim1 = (CCArray*)m_pAnimationArray->objectAtIndex(1);
	float numOfFrame = arrAnim->count();
	CCAnimation *anima = CCAnimation::create(arrAnim, DurationTime/numOfFrame);
	CCActionInterval* seq = (CCActionInterval*) CCAnimate::create(anima);
	if(isReverse)
		seq = seq->reverse();
	this->stopAllActions();
	this->runAction(CCRepeatForever::create(seq));


}
void CMySprite::PlayAnimationToPosition( float x, float y, float TimeToMove, int idAnimation, float DurationTime, 
	bool isReverse, CCFiniteTimeAction* actionMoveDone )
{
	if (idAnimation < 0 || idAnimation > m_iNumOfAnimation)
	{
		return;
	}
	CCArray* arrAnim = (CCArray*)m_pAnimationArray->objectAtIndex(idAnimation);
	float numOfFrame = arrAnim->count();
	CCAnimation *anima = CCAnimation::createWithSpriteFrames(arrAnim, DurationTime/numOfFrame);
	CCActionInterval* seq = (CCActionInterval*) CCAnimate::create(anima);
	if(isReverse)
		seq = seq->reverse();
	this->stopAllActions();
	this->runAction(CCRepeatForever::create(seq));
	if (actionMoveDone)
	{
		this->runAction(CCSequence::actionOneTwo(CCMoveTo::actionWithDuration( TimeToMove, ccp(x,y) ),actionMoveDone));
	}
	else
	{
		this->runAction(CCMoveTo::actionWithDuration( TimeToMove, ccp(x,y) ));
	}
}


bool CMySprite::SetFrame( int idAnimation, int FrameIdx )
{
	if (idAnimation < 0 || idAnimation > m_iNumOfAnimation)
	{
		return false;
	}
	CCArray* arrAnim = (CCArray*)m_pAnimationArray->objectAtIndex(idAnimation);
	float numOfFrame = arrAnim->count();
	if (FrameIdx < 0 || FrameIdx > numOfFrame)
	{
		return false;
	}
	CCSpriteFrame* frame = (CCSpriteFrame*)arrAnim->objectAtIndex(FrameIdx);
	this->setDisplayFrame(frame);
	return true;
}
