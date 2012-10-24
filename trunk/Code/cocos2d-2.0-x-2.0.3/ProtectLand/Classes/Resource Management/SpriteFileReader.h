#ifndef __SPRITE_FILE_READER_H__
#define __SPRITE_FILE_READER_H__
#include "cocos2d.h"
#include "FileManager.h"
#include "Utils.h"
#include "GameConfig.h"
USING_NS_CC;

struct GeneralSpriteInfo
{
	int i_NumOfImages;
	int i_NumOfModules;
	int i_NumOfFrames;
	int i_NumOfAnims;
};
struct ImageSpriteInfo
{
	int i_IdImage;
	char* pc_NameImage;
	int i_Width;
	int i_Height;
	int i_color;
	ImageSpriteInfo(){ pc_NameImage = NULL;}
	~ImageSpriteInfo(){
		CC_SAFE_DELETE_ARRAY(pc_NameImage);}
};
struct ModuleSpriteInfo
{
	int i_IdModule;
	int i_IdImage;
	int i_BeginPos_X;
	int i_BeginPos_Y;
	int i_Width;
	int i_Height;
};
struct FModuleInfo
{
	int i_IdFModule;
	int i_BeginPos_X;
	int i_BeginPos_Y;
};
struct FrameSpriteInfo
{
	char* pc_NameOfFrame;
	int i_IdOfFrame;
	int i_nFModule;
	FModuleInfo* s_FModules;
	FrameSpriteInfo(){
		i_nFModule = 0;
		pc_NameOfFrame = NULL;
		s_FModules = NULL;
	}
	~FrameSpriteInfo(){
		CC_SAFE_DELETE_ARRAY(pc_NameOfFrame);
		CC_SAFE_DELETE_ARRAY(s_FModules);
	}
};
struct AFrameInfo
{
	int i_IdFrame;
	int i_Time;
	int i_BeginPos_X;
	int i_BeginPos_Y;
};
struct AnimSpriteInfo
{
	char* pc_NameOfAnim;
	int i_IdOfAnim;
	int i_nAFrame;
	AFrameInfo* s_AFrames;
	AnimSpriteInfo(){
		i_nAFrame = 0;
		pc_NameOfAnim = NULL;
		s_AFrames = NULL;
	}
	~AnimSpriteInfo(){
		CC_SAFE_DELETE_ARRAY(pc_NameOfAnim);
		CC_SAFE_DELETE_ARRAY(s_AFrames);
	}
};
struct SpriteTotalInformation{
	GeneralSpriteInfo s_GeneralInfo;
	ImageSpriteInfo* p_s_Images;
	ModuleSpriteInfo* p_s_Modules;
	FrameSpriteInfo* p_s_Frames;
	AnimSpriteInfo* p_s_Anims;
	SpriteTotalInformation(){
		p_s_Images = NULL;
		p_s_Modules = NULL;
		p_s_Frames = NULL;
		p_s_Anims = NULL;
	}
	~SpriteTotalInformation(){
		CC_SAFE_DELETE_ARRAY(p_s_Images);
		CC_SAFE_DELETE_ARRAY(p_s_Modules);
		CC_SAFE_DELETE_ARRAY(p_s_Frames);
		CC_SAFE_DELETE_ARRAY(p_s_Anims);
	}
};
class CSpriteFileReader
{

public:
	static CSpriteFileReader* instance;
	CSpriteFileReader(){}
	//CSpriteFileReader(const &CSpriteFileReader reader){}
	~CSpriteFileReader(){}
public:
	static void ReadFromFile( const char* cp_Path, SpriteTotalInformation* &totalInfo );
	CSpriteFileReader* getInstance();

};
#endif