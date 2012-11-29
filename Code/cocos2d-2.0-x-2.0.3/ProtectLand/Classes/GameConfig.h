#ifndef __GAMECONFIG_H__
#define __GAMECONFIG_H__
#include "cocos2d.h"

/************************************************************************/
/* MODE DEFINE                                                           */
/************************************************************************/
#define DEBUG_MODE				0

#define SCREEN_MODE_1280_800	1    //0 for 800 480


/************************************************************************/
/* TAG Definitions                                                      */
/************************************************************************/
#define  TAG_GAMEPLAY_SPRITE_LAYER		100
#define  TAG_GAMEPLAY_COLOR_LAYER		101
#define  TAG_GAMEPLAY_MENU_LAYER		102
#define  TAG_GAMEPLAY_PHYSICS_LAYER		103
#define  TAG_GAMEPLAY_BACKGROUND_LAYER	104
#define  TAG_GAMEPLAY_SPRITE_TEMP       105
#define  TAG_GAMEPLAY_SPRITE_FIXED      106
#define  TAG_WOOD_SPRITE	            107
#define  TAG_OPEN_BOX                   108   
#define  TAG_GAMEPLAY_WINLAYER          109
#define  TAG_SPRITE_COCONUT_1			110
#define  TAG_SPRITE_BEET				111
#define  TAG_GAMEOVER_SCENE             112
#define  TAG_GAMEPLAY_FRONTSPRITE_LAYER 113
#define  TAG_GAMEPLAY_GAME_OBJECT_LAYER 114
#define  TAG_GAMEOBJECT_TARGET			115
#define  TAG_GAMEOBJECT_THIEF			116
#define  TAG_PMENU						117
#define  TAG_STITCH_LOSE				118
#define  TAG_WOOD_MASS					119
#define  TAG_SPRITE_COCONUT_2			120
#define  TAG_SPRITE_STITCH_WIN			121
#define  TAG_GAMEPLAY_SKILL_LAYER		122
/************************************************************************/
/* Zoder Definitions                                                    */
/************************************************************************/

#define ZODER_GAMEPLAY_BACKGROUND_LAYER  0
#define ZODER_GAMEPLAY_GAME_OBJECT_LAYER 2
#define ZORDER_GAMEPLAY_COLOR_LAYER      3
#define ZODER_GAMEPLAY_MENU_LAYER        4
#define ZODER_GAMEPLAY_WIN_LAYER         5
#define ZODER_GAMEPLAY_SKILL_LAYER		 7
#define ZODER_GAMEOVER_SCENE			 6


#define ZODER_GAMEOBJECTLAYER_SPRITE_0		 0
#define ZODER_GAMEOBJECTLAYER_SPRITE_1		 1
#define ZODER_GAMEOBJECTLAYER_SPRITE_2		 2
#define ZODER_GAMEOBJECTLAYER_SPRITE_3		 3
#define ZODER_GAMEOBJECTLAYER_PHYSIC_0		 4
#define ZODER_GAMEOBJECTLAYER_PHYSIC_1		 5
#define ZODER_GAMEOBJECTLAYER_PHYSIC_2		 6
#define ZODER_GAMEOBJECTLAYER_PHYSIC_3		 7
#define ZODER_GAMEOBJECTLAYER_FRONT_0		 8
#define ZODER_GAMEOBJECTLAYER_FRONT_1		 9
#define ZODER_GAMEOBJECTLAYER_FRONT_2		 10

/************************************************************************/
/* LEVEL KEY DEFINE                                                     */
/************************************************************************/

#define LEVEL_KEY_WINSCORE			"WinScore"
#define LEVEL_KEY_NUMWOOD			"NumWood"
#define LEVEL_KEY_NUMKILLTHIEFS		"NumKillThief"
#define LEVEL_KEY_NUMTARGET			"NumTarget"
#define LEVEL_KEY_TARGETLIST		"Targets"
#define LEVEL_KEY_NUMROCK			"NumRock"
#define LEVEL_KEY_ROCKLIST			"Rocks"
#define LEVEL_KEY_NUMTHIEF			"NumThief"
#define LEVEL_KEY_THIEFLIST			"Thiefs"
#define LEVEL_KEY_THIEF_DURATION	"Duration"
#define LEVEL_KEY_THIEF_DIECTION_X	"DirectionX"
#define LEVEL_KEY_THIEF_DIECTION_Y	"DirectionY"
#define LEVEL_KEY_THIEF_BEFORE		"Before"
#define LEVEL_KEY_THIEF_AFTER		"After"
#define LEVEL_KEY_THIEF_HEALTH		"Health"
#define LEVEL_KEY_NUM_WATER			"NumWater"
#define LEVEL_KEY_1STAR			    "1Star"
#define LEVEL_KEY_2STAR				"2Star"
#define LEVEL_KEY_3STAR				"3Star"
#define LEVEL_KEY_BEET_POS_X		"BeetPosX"
#define LEVEL_KEY_BEET_POS_Y		"BeetPosY"
#define LEVEL_KEY_NUMTELEPORT		"NumTeleport"
#define LEVEL_KEY_TELEPORT_IN_X		"TeleportInX"
#define LEVEL_KEY_TELEPORT_IN_Y		"TeleportInY"
#define LEVEL_KEY_TELEPORT_OUT_X	"TeleportOutX"
#define LEVEL_KEY_TELEPORT_OUT_Y	"TeleportOutY"
#define LEVEL_KEY_TARGET_DIRECTION_X "DirectionX"
#define LEVEL_KEY_TARGET_DIRECTION_Y "DirectionY"
#define LEVEL_KEY_TARGET_DURATION	"Duration"
#define LEVEL_KEY_TARGET_TYPEMOVE	"TypeMove"
#define LEVEL_KEY_TIME_START_WATER	"TimeWater"
#define LEVEL_KEY_TIME_OPEN_BOX		"TimeOpenBox"
#define LEVEL_KEY_STITCH_POS_X		"StitchPosX"
#define LEVEL_KEY_STITCH_POS_Y		"StitchPosY"

/************************************************************************/
/* LEVEL ID DEFINE                                                      */
/************************************************************************/

#define LEVEL_ID_WINSCORE			10000
#define LEVEL_ID_NUMWOOD			10001
#define LEVEL_ID_NUMTARGET			10002
#define LEVEL_ID_NUMROCK			10003
#define LEVEL_ID_TARGETLIST			10004
#define LEVEL_ID_ROCK_LIST			10005
#define LEVEL_ID_NUMTHIEF			10006
#define LEVEL_ID_THIEFLIST			10007
#define LEVEL_ID_NUMWATER			10008
#define LEVEL_ID_1STAR				10009
#define LEVEL_ID_2STAR				10010
#define LEVEL_ID_3STAR				10011
#define LEVEL_ID_NUMKILLTHIEF		10012
#define LEVEL_ID_BEET_POS			10013
#define LEVEL_ID_TELEPORT_POS_IN	10014
#define LEVEL_ID_TELEPORT_POS_OUT	10015
#define LEVEL_ID_NUMTELEPORT		10016
#define LEVEL_ID_TIME_START_WATER	10017
#define LEVEL_ID_TIME_OPEN_BOX		10018
#define LEVEL_ID_STITCH_POS			10019



/************************************************************************/
/* LEVEL DATA FILE NAME                                                 */
/************************************************************************/

#define NUMBER_LEVEL	8
#define LEVEL1_FILENAME "level1.plist"
#define LEVEL2_FILENAME "level2.plist"
#define LEVEL3_FILENAME "level3.plist"
#define LEVEL4_FILENAME "level4.plist"
#define LEVEL5_FILENAME "level5.plist"
#define LEVEL6_FILENAME "level6.plist"
#define LEVEL7_FILENAME "level7.plist"
#define LEVEL8_FILENAME "level8.plist"

#define FILE_LEVEL_INFO		"LevelInfo.txt"

enum eSpriteIDPic
{
	SPRITE_ID_TARGET_FRONT, SPRITE_ID_TARGET_BACK,
	SPRITE_ID_WOOD,
	SPRITE_ID_ROCK,
	SPRITE_ID_PICTURE_MAX,
	//////////////////////////////////////////////////////////////////////////
	SPRITE_ID_THIEF = SPRITE_ID_PICTURE_MAX
};
enum eGameObjectType
{
	GAMEOBJECT_TYPE_TARGET,
	GAMEOBJECT_TYPE_ROCK,
	GAMEOBJECT_TYPE_THIEF,
};

enum eAudioState
{
	MUSIC_ON,
	MUSIC_BACKGROUND_OFF,
	MUSIC_OFF,
	
};

struct  sGameObject
{
	eSpriteIDPic SpriteID;
	eGameObjectType Type;
	cocos2d::CCPoint position;
	cocos2d::CCPoint direction;
	float duration;
	int typeMove;
	int before;
	int after;
	int health;

};


enum E_TYPE_SPRITE{
	TYPE_SPRITE_PICTURE,
	TYPE_SPRITE_SRITE
};

enum eStar
{
	STAR0,
	STAR1,
	STAR2,
	STAR3,
};

/************************************************************************/
/* Menu Item                                                            */
/************************************************************************/
#define MENU_ITEM_WOOD		  50000
#define MENU_ITEM_KILLTHIEF	  50001
#define NONITEM	             -1

/************************************************************************/
/* Constants Definitions                                                */
/************************************************************************/

#define MODE_NEWGAME  1000
#define MODE_CONTINUE 1001
#define SCORE         1002
#define BONUS         1003
#define MAX_NUM_ITEM_PHYSIC 10
#define ROTATE_FACTOR  1.0

/************************************************************************/
/* Object Item  ID                                                      */
/************************************************************************/
#define OBJECT_ITEM_WOOD		 70000
#define OBJECT_ITEM_KILLTHIEF	 70001

/************************************************************************/
/* Touch priority                                                       */
/************************************************************************/

#define TOUCH_PRIORITY_MAIN_LAYER 0




/************************************************************************/
/* TC Define                                                            */
/************************************************************************/

#define PI      3.14159265358979323846f
#define DEGTORAD(a)     (a*PI/180.0f)
#define RADTODEG(a)     (a*180.0f/PI)
#define DEG2RAD         (PI/180.0f)


/************************************************************************/
/* SCREEN SIZE                                                          */
/************************************************************************/
#define WIDTH_SCREEN_STANDARD	800
#define HEIGHT_SCREEN_STANDARD	480

#if SCREEN_MODE_1280_800
	#define WIDTH_SCREEN		1024
	#define HEIGHT_SCREEN		700

#else
	#define WIDTH_SCREEN		800
	#define HEIGHT_SCREEN		480
	
#endif

/************************************************************************/
/* Object Size                                                          */
/************************************************************************/

#define ROCK_WIDTH  100.0f
#define ROCK_HEIGHT 45.0f
#define WOOD_WIDTH  180.0f
#define WOOD_HEIGHT 50.0f
#define WOOD_BOUNDINGBOX_WIDTH  135.0f
#define WOOD_BOUNDINGBOX_HEIGHT 21.0f
#define COCONUT_WIDTH  70.0f
#define COCONUT_HEIGHT 70.0f
#define MENU_BODER_LEFT  700.0f
#define MENU_BODER_BOTTOM 200.0f

/************************************************************************/
/* Audio ID                                                             */
/************************************************************************/
#define SOUND_WIN_1						10000
#define SOUND_WIN_2						20000
#define SOUND_WIN_3                     30000
#define SOUND_WATER_1					40000
#define SOUND_ALARM_WATER_DROP_1		50000
#define SOUND_SCORE_COUNT				60000
#define SOUND_BACKGROUND	            70000
#define SOUND_CLICK_1                   80000
#define SOUND_STAR_1					90000
#define SOUND_STAR_2					100000
#define SOUND_STAR_3					110000
#define SOUND_WATER_2					120000
#define SOUND_WATER_3					130000
#define SOUND_GAMEPLAY_BAGROUND_1       140000
#define SOUND_ENABLE_BUTTON             150000
#define SOUND_ANT_MOVE                  160000
#define SOUND_ANT_DEAD					170000
#define SOUND_INTRO						180000
#define SOUND_MAINMENU					190000

/************************************************************************/
/* TYPE MOVE		                                                     */
/************************************************************************/
#define TYPE_MOVE_TARGET_LINE	1
#define TYPE_MOVE_TARGET_BOX	2

#define SOUND_BG_EFF 100
#define	SOUND_EFF 200
#define SOUND_OFF 300

/************************************************************************/
/* TRANSITION SCENE DEFINE                                               */
/************************************************************************/
#define TRANSITION_DURATION 0.7f

/************************************************************************/
/* PHYSICS CONFIG                                                       */
/************************************************************************/
#if SCREEN_MODE_1280_800
	#define PTM_RATIO 30
#else
	#define PTM_RATIO 32
#endif




/************************************************************************/
/* SCORE BONUS CONFIG                                                   */
/************************************************************************/
#define SCORE_BONUS_WOOD		30
#define SCORE_BONUS_KILLTHIEF	10



/************************************************************************/
/* WATER  CONFIG                                                       */
/************************************************************************/
#define    B2_FLT_MAX        FLT_MAX
#define    B2_FLT_EPSILON    FLT_EPSILON
#define	RAND_LIMIT	32767
// MAGIC NUMBERS
#define N_PARTICLES  300
#define MAX_NUM_PER_TIME 100
#define TIME_PER_TIME 1.0f
#define TOTAL_MASS  10.0f
#define BOX_WIDTH  2.0f
#define BOX_HEIGHT  20.0f

#define FLUID_MIN_X  0.0f
#define FLUID_MAX_X  WIDTH_SCREEN /PTM_RATIO
#define FLUID_MIN_Y  0.0f
#define FLUID_MAX_Y  HEIGHT_SCREEN /PTM_RATIO

#define RAD 0.4f
#define RADIUS_CIRCLE  2.5f/PTM_RATIO
#define VISC  0.005f

#define HASH_WIDTH  40
#define HASH_HEIGHT 40


#if ANDROID
#include <android/log.h>
#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#else
#define  LOGI CCLOG
#define  LOGE CCLOG
#endif






/************************************************************************/
/* DEFINE MACRO                                                         */
/************************************************************************/
#define MyChangePointScreen(__X__, __Y__) cocos2d::CCPointMake((float)(__X__)*WIDTH_SCREEN/WIDTH_SCREEN_STANDARD, (float)(__Y__)*HEIGHT_SCREEN/HEIGHT_SCREEN_STANDARD)
#define SCREEN_WIDTH_RATIO_PORT		(float)(WIDTH_SCREEN/((float)WIDTH_SCREEN_STANDARD))
#define SCREEN_HEIGHT_RATION_PORT	(float)(HEIGHT_SCREEN/((float)HEIGHT_SCREEN_STANDARD))

/*
DEFINE	AREA SHOOT SIZE

#define AREA_SHOOT_BULLET_WIDTH 240
#define AREA_SHOOT_BULLET_HEIGHT 128
*/

/*
SKILL
*/

/*
TOWER
*/




/*
MONSTER
*/

//texture:
#define LEVEL1_WATER_MONSTER_TEXTURE "Monster/Water_lv1/water_monster_lv1.sprite"
#define LEVEL1_FIRE_MONSTER_TEXTURE	 "Monster/Fire_lv1/monster_fire_level1.sprite"
#define LEVEL2_WATER_MONSTER_TEXTURE ""
#define LEVEL2_FIRE_MONSTER_TEXTURE ""
#define LEVEL3_WATER_MONSTER_TEXTURE ""
#define LEVEL3_FIRE_MONSTER_TEXTURE ""
#define COIN "Coin/coin.sprite"

//hp
#define LEVEL1_MONSTER_HP 60
#define LEVEL2_MONSTER_HP 80
#define LEVEL3_MONSTER_HP 100

//speed
#define LEVEL1_MONSTER_SPEED 6
#define LEVEL2_MONSTER_SPEED 4
#define LEVEL3_MONSTER_SPEED 2

//power
#define LEVEL1_MONSTER_POWER 10
#define LEVEL2_MONSTER_POWER 20
#define LEVEL3_MONSTER_POWER 30

//damage
#define LEVEL1_MONSTER_DAMAGE 2
#define LEVEL2_MONSTER_DAMAGE 4
#define LEVEL3_MONSTER_DAMAGE 6

//coin
#define LEVEL1_MONSTER_COIN 5
#define LEVEL2_MONSTER_COIN 7
#define LEVEL3_MONSTER_COIN 9

//type
enum TypeMonster
{
	FIRE_MONSTER,
	WATER_MONSTER,
	MAX_MONSTER,
};

//level
enum MonsterLevel
{
	LEVEL1_MONSTER,
	LEVEL2_MONSTER,
	LEVEL3_MONSTER,
	LEVEL_MAX,
};

enum typeMove
{
	MOVE,
	ATTACK,
	HIT,
	DIE,
	MAX,
};

#define TIME_COIN 0.5f

#define TIME_BLOOD_MOVE_SCALE 1.0f

#define TIME_BLOOD_FADE 0.5f

#define TIME_ATTACK_DELAY 2.0f

#endif