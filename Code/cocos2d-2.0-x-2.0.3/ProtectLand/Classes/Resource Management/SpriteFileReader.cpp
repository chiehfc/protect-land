#include "SpriteFileReader.h"
#define MAX_LENGTH_LINE 256
GeneralSpriteInfo getGeneralInfo(char* source, int &offsetBegin)
{
	char* pc_Begin = source;
	char pc_Line[MAX_LENGTH_LINE] = {0};
	int i_NextOffset = offsetBegin;
	int i_NumOfImages = 0;
	int i_NumOfModules = 0;
	int i_NumOfFrames = 0;
	int i_NumeOfAnims = 0;

	i_NextOffset = ReadLine(pc_Begin, pc_Line, i_NextOffset);
	sscanf(pc_Line, "    // Images:  %d", &i_NumOfImages);
	i_NextOffset = ReadLine(pc_Begin, pc_Line, i_NextOffset);
	sscanf(pc_Line, "    // Modules: %d", &i_NumOfModules);
	i_NextOffset = ReadLine(pc_Begin, pc_Line, i_NextOffset);
	sscanf(pc_Line, "    // Frames:  %d", &i_NumOfFrames);
	i_NextOffset = ReadLine(pc_Begin, pc_Line, i_NextOffset);
	sscanf(pc_Line, "    // Anims:   %d", &i_NumeOfAnims);
	offsetBegin = i_NextOffset;
	GeneralSpriteInfo info;
	//info.
	info.i_NumOfImages = i_NumOfImages;
	info.i_NumOfModules = i_NumOfModules;
	info.i_NumOfFrames = i_NumOfFrames;
	info.i_NumOfAnims = i_NumeOfAnims;

	return info;
}
int FindPositionStringApear_Current(char* source, int offset, const char* str)
{
	char pc_Line[MAX_LENGTH_LINE] = {0};
	int i_CurrOffset = offset;
	int i_NextOffset = offset;
	while(1)
	{
		i_CurrOffset = i_NextOffset;
		i_NextOffset = ReadLine(source, pc_Line, i_NextOffset);
		//offset = offsetNext;
		//pc_CurrentPos = (pc_CurrentPos+offsetNext);
		char * pch = NULL;
		pch = strstr (pc_Line,str);
		if(pch != NULL)
		{
			return i_CurrOffset;
		}
	}
}
int FindPositionStringApear_Next(char* source, int offset, const char* str)
{
	char pc_Line[MAX_LENGTH_LINE] = {0};
	int i_CurrOffset = offset;
	int i_NextOffset = offset;
	while(1)
	{
		i_CurrOffset = i_NextOffset;
		i_NextOffset = ReadLine(source, pc_Line, i_NextOffset);
		//offset = offsetNext;
		//pc_CurrentPos = (pc_CurrentPos+offsetNext);
		char * pch = NULL;
		pch = strstr (pc_Line,str);
		if(pch != NULL)
		{
			return i_NextOffset;
		}
	}
}
void getImageInfo(char* source, int &offset, ImageSpriteInfo *&info, int nImage)
{
	char pc_Line[MAX_LENGTH_LINE] ={0};
	char idImage[50] = {0};
	char PathImage[MAX_LENGTH_LINE] = {0};
	char Color[50] = {0};
	int indexImage = 0;
	int idPalet = 0;
	int iWidth = 0;
	int iHeight = 0;
	for(int i = 0; i < nImage; i++)
	{
		offset = ReadLine(source, pc_Line, offset);
		sscanf(pc_Line, "    IMAGE %s %s TRANSP %s // %d  size: %d x %d  palettes: %d", idImage, PathImage, Color, &indexImage, &iWidth, &iHeight, &idPalet );
		int iIdImageTemp = HexStringToInt(idImage);
		int iColorTemp = HexStringToInt(Color);
		
		int lengString = strlen(PathImage);
		PathImage[lengString-1] = '\0';
		
		info[i].i_IdImage = iIdImageTemp;
		info[i].i_color = iColorTemp;
		info[i].pc_NameImage = new char[lengString-1];
		strcpy(info[i].pc_NameImage , (PathImage+1));
		info[i].i_Width = iWidth;
		info[i].i_Height = iHeight;
	}
}
void getModuleInfo(char* source, int &offset, ModuleSpriteInfo *&info, int nModule)
{
	char pc_Line[MAX_LENGTH_LINE] ={0};
	char pc_idModule[50] = {0};
	int i_IdImage = 0;
	int i_Pos_X = 0;
	int i_Pos_Y = 0;
	int i_Width = 0;
	int i_Height = 0;
	for(int i = 0; i < nModule; i++)
	{
		offset = ReadLine(source, pc_Line, offset);
		sscanf(pc_Line, "        MD	%s	MD_IMAGE	%d	%d	%d	%d	%d", pc_idModule, &i_IdImage, &i_Pos_X, &i_Pos_Y, &i_Width, &i_Height );

		int iIdModuleTemp = HexStringToInt(pc_idModule);

		info[i].i_IdModule = iIdModuleTemp;
		info[i].i_IdImage = i_IdImage;
		info[i].i_BeginPos_X = i_Pos_X;
		info[i].i_BeginPos_Y = i_Pos_Y;
		info[i].i_Width = i_Width;
		info[i].i_Height = i_Height;
	}
}
void getFModuleInfo(char* source, int &offset, FModuleInfo *&info, int nFModule)
{
	char pc_Line[MAX_LENGTH_LINE] ={0};
	char* pc_Begin = source;
	int i_NextOffset = offset;
	char pc_IdFModule[99] = {0};
	for(int i = 0; i < nFModule; i ++)
	{
		int i_Pos_X = 0;
		int i_Pos_Y = 0;
		i_NextOffset = ReadLine(pc_Begin, pc_Line, i_NextOffset);
		sscanf(pc_Line, "        FM	%s	%d	%d", pc_IdFModule, &i_Pos_X, &i_Pos_Y );
		int i_IdFModule = HexStringToInt(pc_IdFModule);
		info[i].i_IdFModule = i_IdFModule;
		info[i].i_BeginPos_X = i_Pos_X;
		info[i].i_BeginPos_Y = i_Pos_Y;
	}

	offset = i_NextOffset;
}
void getFrameInfo(char* source, int &offset, FrameSpriteInfo *&info, int nFrame)
{
	char pc_Line[MAX_LENGTH_LINE] ={0};
	char pc_NameFrame[MAX_LENGTH_LINE]={0};
	char pc_IdFrameTemp[99] ={0};

	char* pc_Begin = source;
	int i_NextOffset = offset;

	for(int i = 0; i < nFrame; i++)
	{
		i_NextOffset = FindPositionStringApear_Current(pc_Begin, i_NextOffset, "    FRAME");
		i_NextOffset = ReadLine(pc_Begin, pc_Line, i_NextOffset);
		
		int i_FrameIndex = 0;
		int i_nFModule = 0;
		sscanf(pc_Line, "    FRAME %s // Index = %d, FModules = %d", pc_NameFrame, &i_FrameIndex, &i_nFModule );

		i_NextOffset = FindPositionStringApear_Next(pc_Begin, i_NextOffset, "    {");
		i_NextOffset = ReadLine(pc_Begin, pc_Line, i_NextOffset);
		sscanf(pc_Line, "        %s", pc_IdFrameTemp);

		int i_IdFrame = HexStringToInt(pc_IdFrameTemp);

		int lengString = strlen(pc_NameFrame);
		info[i].pc_NameOfFrame = new char[lengString+1];

		strcpy( info[i].pc_NameOfFrame, pc_NameFrame );
		info[i].i_IdOfFrame = i_IdFrame;
		info[i].i_nFModule = i_nFModule;

		info[i].s_FModules = new FModuleInfo[i_nFModule];
		getFModuleInfo(pc_Begin, i_NextOffset, info[i].s_FModules, i_nFModule);
		
	}
	offset = i_NextOffset;
}
void getAFrameInfo(char* source, int &offset, AFrameInfo *&info, int nAFrame)
{
	char pc_Line[MAX_LENGTH_LINE] ={0};
	char* pc_Begin = source;
	int i_NextOffset = offset;
	char pc_IdAFrame[99] = {0};
	for(int i = 0; i < nAFrame; i ++)
	{
		int i_Pos_X = 0;
		int i_Pos_Y = 0;
		int i_Time = 0;
		i_NextOffset = ReadLine(pc_Begin, pc_Line, i_NextOffset);
		sscanf(pc_Line, "        AF	%s	%d	%d	%d", pc_IdAFrame, &i_Time, &i_Pos_X, &i_Pos_Y );
		int i_IdFrame = HexStringToInt(pc_IdAFrame);
		info[i].i_IdFrame = i_IdFrame;
		info[i].i_Time = i_Time;
		info[i].i_BeginPos_X = i_Pos_X;
		info[i].i_BeginPos_Y = i_Pos_Y;
	}

	offset = i_NextOffset;
}
void getAnimInfo(char* source, int &offset, AnimSpriteInfo *&info, int nAnim)
{
	char pc_Line[MAX_LENGTH_LINE] ={0};
	char pc_NameAnim[MAX_LENGTH_LINE]={0};
	char pc_IdAnimTemp[99] ={0};

	char* pc_Begin = source;
	int i_NextOffset = offset;

	for(int i = 0; i < nAnim; i++)
	{
		i_NextOffset = FindPositionStringApear_Current(pc_Begin, i_NextOffset, "    ANIM");
		i_NextOffset = ReadLine(pc_Begin, pc_Line, i_NextOffset);

		int i_AnimIndex = 0;
		int i_nAFrame = 0;
		sscanf(pc_Line, "    ANIM %s // Index = %d, AFrames = %d", pc_NameAnim, &i_AnimIndex, &i_nAFrame );

		i_NextOffset = FindPositionStringApear_Next(pc_Begin, i_NextOffset, "    {");
		i_NextOffset = ReadLine(pc_Begin, pc_Line, i_NextOffset);
		sscanf(pc_Line, "        %s", pc_IdAnimTemp);

		int i_IdOfAnim = HexStringToInt(pc_IdAnimTemp);

		int lengString = strlen(pc_NameAnim);
		info[i].pc_NameOfAnim = new char[lengString+1];

		strcpy( info[i].pc_NameOfAnim, pc_NameAnim );
		info[i].i_IdOfAnim = i_IdOfAnim;
		info[i].i_nAFrame = i_nAFrame;

		info[i].s_AFrames = new AFrameInfo[i_nAFrame];
		getAFrameInfo(pc_Begin, i_NextOffset, info[i].s_AFrames, i_nAFrame);

	}
	offset = i_NextOffset;
}
void CSpriteFileReader::ReadFromFile( const char* cp_Path, SpriteTotalInformation* &totalInfo )
{
	//totalInfo = new SpriteTotalInformation;

	char* pc_FileContent;// = CFileManager::GetInstance()->GetFileContent(cp_Path);
	unsigned long sizeFile = 0;
	pc_FileContent = (char*)CCFileUtils::sharedFileUtils()->getFileData(cp_Path, "r",&sizeFile);
	//LOGE("%s",pc_FileContent);
	//////////////////////////////////////////////////////////////////////////
	char* pc_CurrentPos = pc_FileContent;
	char pc_Line[MAX_LENGTH_LINE] = {0};
	int i_CurrOffset = 0;
	int i_NextOffset = 0;
	//GeneralSpriteInfo s_GeneralInfo;
	
	i_NextOffset = FindPositionStringApear_Current(pc_CurrentPos, i_NextOffset,"Images");
	totalInfo->s_GeneralInfo = getGeneralInfo(pc_CurrentPos,i_NextOffset);

	int nImage = totalInfo->s_GeneralInfo.i_NumOfImages;
	totalInfo-> p_s_Images = new ImageSpriteInfo[nImage];
	i_NextOffset = FindPositionStringApear_Current(pc_CurrentPos, i_NextOffset,"    IMAGE");
	getImageInfo(pc_CurrentPos, i_NextOffset, totalInfo->p_s_Images, nImage);
	
	int nModule = totalInfo->s_GeneralInfo.i_NumOfModules;
	i_NextOffset = FindPositionStringApear_Next(pc_CurrentPos, i_NextOffset, "    MODULES");
	i_NextOffset = FindPositionStringApear_Next(pc_CurrentPos, i_NextOffset, "    {");
	totalInfo->p_s_Modules = new ModuleSpriteInfo[nModule];
	getModuleInfo(pc_CurrentPos, i_NextOffset, totalInfo->p_s_Modules, nModule);

	int nFrames = totalInfo->s_GeneralInfo.i_NumOfFrames;
	totalInfo->p_s_Frames = new FrameSpriteInfo[nFrames];

	getFrameInfo(pc_CurrentPos, i_NextOffset, totalInfo->p_s_Frames, nFrames);

	int nAnim = totalInfo->s_GeneralInfo.i_NumOfAnims;
	totalInfo->p_s_Anims = new AnimSpriteInfo[nAnim];

	getAnimInfo(pc_CurrentPos, i_NextOffset, totalInfo->p_s_Anims, nAnim);
	
	/*FindPositionStringApear_Current(pc_CurrentPos, i_NextOffset, "} // SPRITE");
	ReadLine(pc_CurrentPos, pc_Line, i_NextOffset);*/
	//////////////////////////////////////////////////////////////////////////
	//delete []pc_FileContent;
	/*delete []p_s_Frames;
	delete []p_s_Images;
	delete []p_s_Modules;
	delete []p_s_Anims;*/
}

