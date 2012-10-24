#include "Level.h"
#include "GameConfig.h"
USING_NS_CC;

CLevel::CLevel(int level)
{
	switch(level)
	{
		case 1:
			m_LevelDict = CCDictionary::createWithContentsOfFile(LEVEL1_FILENAME);
			break;
		case 2:
		   m_LevelDict = CCDictionary::createWithContentsOfFile(LEVEL2_FILENAME);
		   break;
		case 3:
			m_LevelDict = CCDictionary::createWithContentsOfFile(LEVEL3_FILENAME);
			break;
		case 4:
			m_LevelDict = CCDictionary::createWithContentsOfFile(LEVEL4_FILENAME);
			break;	
		case 5:
			m_LevelDict = CCDictionary::createWithContentsOfFile(LEVEL5_FILENAME);
			break;
		case 6:
			m_LevelDict = CCDictionary::createWithContentsOfFile(LEVEL6_FILENAME);
			break;
		case 7:
			m_LevelDict = CCDictionary::createWithContentsOfFile(LEVEL7_FILENAME);
			break;
		case 8:
			m_LevelDict = CCDictionary::createWithContentsOfFile(LEVEL8_FILENAME);
			break;	
		default:
			m_LevelDict = CCDictionary::createWithContentsOfFile(LEVEL1_FILENAME);
			break;
	}
	//water
	this->NumWaters = m_LevelDict->valueForKey(LEVEL_KEY_NUM_WATER)->intValue();

	//Teleport
	this->IsHaveTeleport = m_LevelDict->valueForKey(LEVEL_KEY_NUMTELEPORT)->intValue();
	this->m_TeleportPosIn = MyChangePointScreen(m_LevelDict->valueForKey(LEVEL_KEY_TELEPORT_IN_X)->intValue(), m_LevelDict->valueForKey(LEVEL_KEY_TELEPORT_IN_Y)->intValue());
	this->m_TeleportPosOut = MyChangePointScreen(m_LevelDict->valueForKey(LEVEL_KEY_TELEPORT_OUT_X)->intValue(), m_LevelDict->valueForKey(LEVEL_KEY_TELEPORT_OUT_Y)->intValue());

	//Beet
	this->m_BeetPos = MyChangePointScreen(m_LevelDict->valueForKey(LEVEL_KEY_BEET_POS_X)->intValue(), m_LevelDict->valueForKey(LEVEL_KEY_BEET_POS_Y)->intValue());
	
	//Stitch Loose Pos
	this->m_StitchPos = MyChangePointScreen(m_LevelDict->valueForKey(LEVEL_KEY_STITCH_POS_X)->intValue(), m_LevelDict->valueForKey(LEVEL_KEY_STITCH_POS_Y)->intValue());

	//Target init
	CCArray* points = (CCArray*) m_LevelDict->objectForKey(LEVEL_KEY_TARGETLIST);
	this->NumTarget = m_LevelDict->valueForKey(LEVEL_KEY_NUMTARGET)->intValue();
	if(this->NumTarget > 0)
	{
		m_pTargetList = new sGameObject[this->NumTarget];
		for(int i = 0; i < this->NumTarget; i++)
		{
			m_pTargetList[i].SpriteID   =  SPRITE_ID_TARGET_FRONT;
			m_pTargetList[i].Type = GAMEOBJECT_TYPE_TARGET;
			m_pTargetList[i].position.x = ((CCDictionary*) points->objectAtIndex(i))->valueForKey("X")->floatValue()*SCREEN_WIDTH_RATIO_PORT;
			m_pTargetList[i].position.y = ((CCDictionary*) points->objectAtIndex(i))->valueForKey("Y")->floatValue()*SCREEN_HEIGHT_RATION_PORT;
			m_pTargetList[i].direction.x = ((CCDictionary*) points->objectAtIndex(i))->valueForKey(LEVEL_KEY_TARGET_DIRECTION_X)->floatValue()*SCREEN_WIDTH_RATIO_PORT;
			m_pTargetList[i].direction.y = ((CCDictionary*) points->objectAtIndex(i))->valueForKey(LEVEL_KEY_TARGET_DIRECTION_Y)->floatValue()*SCREEN_HEIGHT_RATION_PORT;
			m_pTargetList[i].typeMove = ((CCDictionary*) points->objectAtIndex(i))->valueForKey(LEVEL_KEY_TARGET_TYPEMOVE)->intValue();
			m_pTargetList[i].duration = ((CCDictionary*) points->objectAtIndex(i))->valueForKey(LEVEL_KEY_TARGET_DURATION)->floatValue()*SCREEN_HEIGHT_RATION_PORT;
		}
	}
	points->release();
	m_LevelDict->retain();

	// Rocks innit
	points = (CCArray*) m_LevelDict->objectForKey(LEVEL_KEY_ROCKLIST);
	this->NumRocks = m_LevelDict->valueForKey(LEVEL_KEY_NUMROCK)->intValue();
	if(this->NumRocks > 0)
	{
		m_pRockList = new sGameObject[this->NumRocks];
		for(int i = 0; i < this->NumRocks; i++)
		{
			m_pRockList[i].SpriteID   =  SPRITE_ID_ROCK;
			m_pRockList[i].Type = GAMEOBJECT_TYPE_ROCK;
			m_pRockList[i].position.x = ((CCDictionary*) points->objectAtIndex(i))->valueForKey("X")->floatValue()*SCREEN_WIDTH_RATIO_PORT;
			m_pRockList[i].position.y = ((CCDictionary*) points->objectAtIndex(i))->valueForKey("Y")->floatValue()*SCREEN_HEIGHT_RATION_PORT;
		}
	}
	points->release();

	//Thief init
	points = (CCArray*) m_LevelDict->objectForKey(LEVEL_KEY_THIEFLIST);
	this->NumThiefs = m_LevelDict->valueForKey(LEVEL_KEY_NUMTHIEF)->intValue();
	if(this->NumThiefs > 0)
	{
		m_pThiefList = new sGameObject[this->NumThiefs];
		for(int i = 0; i < this->NumThiefs; i++)
		{
			m_pThiefList[i].SpriteID   =  SPRITE_ID_THIEF;
			m_pThiefList[i].Type = GAMEOBJECT_TYPE_THIEF;
			m_pThiefList[i].position.x = ((CCDictionary*) points->objectAtIndex(i))->valueForKey("X")->floatValue()*SCREEN_WIDTH_RATIO_PORT;
			m_pThiefList[i].position.y = ((CCDictionary*) points->objectAtIndex(i))->valueForKey("Y")->floatValue()*SCREEN_HEIGHT_RATION_PORT;
			m_pThiefList[i].duration   = ((CCDictionary*) points->objectAtIndex(i))->valueForKey(LEVEL_KEY_THIEF_DURATION)->floatValue();
			m_pThiefList[i].direction.x   = ((CCDictionary*) points->objectAtIndex(i))->valueForKey(LEVEL_KEY_THIEF_DIECTION_X)->floatValue()*SCREEN_WIDTH_RATIO_PORT;
			m_pThiefList[i].direction.y   = ((CCDictionary*) points->objectAtIndex(i))->valueForKey(LEVEL_KEY_THIEF_DIECTION_Y)->floatValue()*SCREEN_HEIGHT_RATION_PORT;
			m_pThiefList[i].before		  = ((CCDictionary*) points->objectAtIndex(i))->valueForKey(LEVEL_KEY_THIEF_BEFORE)->intValue();
			m_pThiefList[i].after		  = ((CCDictionary*) points->objectAtIndex(i))->valueForKey(LEVEL_KEY_THIEF_AFTER)->intValue();
			m_pThiefList[i].health		  = ((CCDictionary*) points->objectAtIndex(i))->valueForKey(LEVEL_KEY_THIEF_HEALTH)->intValue();
		}
	}
	points->release();
}

CLevel::~CLevel(void)
{
	if(this->NumTarget > 0)
		delete[] this->m_pTargetList;
	if(this->NumRocks > 0)
		delete[] this->m_pRockList;
	if(this->NumThiefs > 0)
		delete[] this->m_pThiefList;

}

int CLevel::getIntValue(int ID )
{
	
	switch(ID)
	{
		case LEVEL_ID_WINSCORE:
			return m_LevelDict->valueForKey(LEVEL_KEY_WINSCORE)->intValue();
			break;
		case LEVEL_ID_NUMWOOD:
			return m_LevelDict->valueForKey(LEVEL_KEY_NUMWOOD)->intValue();
			break;
		case LEVEL_ID_NUMKILLTHIEF:
			return m_LevelDict->valueForKey(LEVEL_KEY_NUMKILLTHIEFS)->intValue();
			break;
		case LEVEL_ID_NUMTARGET:
			return this->NumTarget;
		case LEVEL_ID_NUMROCK:
			return this->NumRocks;
		case LEVEL_ID_NUMTHIEF:
			return this->NumThiefs;
		case LEVEL_ID_NUMWATER:
			return this->NumWaters;			
		case LEVEL_ID_1STAR:
			return m_LevelDict->valueForKey(LEVEL_KEY_1STAR)->intValue();
		case LEVEL_ID_2STAR:
		    return m_LevelDict->valueForKey(LEVEL_KEY_2STAR)->intValue();
		case LEVEL_ID_3STAR:
		    return m_LevelDict->valueForKey(LEVEL_KEY_3STAR)->intValue();
		case LEVEL_ID_NUMTELEPORT:
			return m_LevelDict->valueForKey(LEVEL_KEY_NUMTELEPORT)->intValue();
		case LEVEL_ID_TIME_START_WATER:
			return m_LevelDict->valueForKey(LEVEL_KEY_TIME_START_WATER)->floatValue();
		case LEVEL_ID_TIME_OPEN_BOX:
			return m_LevelDict->valueForKey(LEVEL_KEY_TIME_OPEN_BOX)->floatValue();
		default:
			return 0;
	}
}

CCPoint CLevel::getCCPointValue(int ID )
{
	switch(ID)
	{	
	case LEVEL_ID_BEET_POS:
		return this->m_BeetPos;		
	case LEVEL_ID_TELEPORT_POS_IN:
		return this->m_TeleportPosIn;
	case LEVEL_ID_TELEPORT_POS_OUT:
		return this->m_TeleportPosOut;
	case LEVEL_ID_STITCH_POS:
		return this->m_StitchPos;
	default:
		return MyChangePointScreen(-10, -10);
	}
}

sGameObject* CLevel::getObjectList( int ID )
{
	switch(ID)
	{
	case LEVEL_ID_TARGETLIST:
		return this->m_pTargetList;
		break;
	case LEVEL_ID_ROCK_LIST:
		return this->m_pRockList;
	case LEVEL_ID_THIEFLIST:
		return this->m_pThiefList;
		break;
	default:
		return NULL;
	}
	
}

