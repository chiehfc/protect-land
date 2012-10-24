#include "AudioManager.h"
#include "IncludeHelper.h"
CAudioManager* CAudioManager::m_instance = 0;
CAudioManager* CAudioManager::instance()
{
	if(!m_instance)
	{
		m_instance = new CAudioManager();
	}

	return m_instance;
}

CAudioManager::CAudioManager()
{
	m_SManager = CocosDenshion::SimpleAudioEngine::sharedEngine();
	initAudio();
}

CocosDenshion::SimpleAudioEngine* CAudioManager::GetSManager()
{
	return this->m_SManager;
}

void CAudioManager::preloadBGMusic(int AudioId)
{
	m_SManager->preloadBackgroundMusic(m_pszFilePath);
}
void CAudioManager::playBGMusic(int AudioID, bool bLoop)
{
	if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF)
	{
		AudioChoice(AudioID);
		m_SManager->playBackgroundMusic(m_pszFilePath, bLoop);
	}
}

void CAudioManager::stopBGMusic(bool bReleaseData)
{
	m_SManager->stopBackgroundMusic(bReleaseData);
}

void CAudioManager::pauseBGMusic()
{
	m_SManager->pauseBackgroundMusic();
}

void CAudioManager::resumeBGMusic()
{
	m_SManager->resumeBackgroundMusic();
}

void CAudioManager::rewindBGMusic()
{
	m_SManager->rewindBackgroundMusic();
}

bool CAudioManager::willPlayBGdMusic()
{
	return m_SManager->willPlayBackgroundMusic();
}

bool CAudioManager::isBGMusicPlaying()
{
	return m_SManager->isBackgroundMusicPlaying();
}

float CAudioManager::getBGMusicVolume()
{
	return m_SManager->getBackgroundMusicVolume();
}

void CAudioManager::setBGMusicVolume(float volume)
{
	m_SManager->setBackgroundMusicVolume(volume);
}

float CAudioManager::getEffVolume()
{
	return m_SManager->getEffectsVolume();
}


void CAudioManager::setEffVolume(float volume)
{
	m_SManager->setEffectsVolume(volume);
}

unsigned int CAudioManager::playEff(int AudioID, bool bLoop)
{
	AudioChoice(AudioID);
	if(CAudioManager::instance()->GetSound()==SOUND_BG_EFF || CAudioManager::instance()->GetSound()==SOUND_EFF )
		return m_SManager->playEffect(m_pszFilePath, bLoop);
	return 0;
}

void CAudioManager::pauseEff(unsigned int nSoundId)
{
	m_SManager->pauseEffect(nSoundId);
}

void CAudioManager::pauseAllEff()
{
	
	m_SManager->pauseAllEffects();
}

void CAudioManager::resumeEff(unsigned int nSoundId)
{
	m_SManager->resumeEffect(nSoundId);
}

void CAudioManager::resumeAllEff()
{
	m_SManager->resumeAllEffects();
}

void CAudioManager::stopEff(unsigned int nSoundId)
{
	m_SManager->stopEffect(nSoundId);
}

void CAudioManager::stopAllEff()
{
	m_SManager->stopAllEffects();
}

void CAudioManager::preloadEff(int AudioID)
{
	m_SManager->preloadEffect(m_pszFilePath);
}

void CAudioManager::unloadEff(int AudioID)
{
	m_SManager->unloadEffect(m_pszFilePath);
}

void CAudioManager::AudioChoice(int AudioID)
{
	switch(AudioID)
	{
	case SOUND_WIN_1:
		m_pszFilePath = "Sounds/Win1.ogg";
		break;
	case SOUND_WIN_2:
		m_pszFilePath = "Sounds/Win2.ogg";
		break;
	case SOUND_WATER_1:
		m_pszFilePath = "Sounds/Water1.ogg";
		break;
	case SOUND_WATER_2:
		m_pszFilePath = "Sounds/Water2.ogg";
		break;
	case SOUND_WATER_3:
		m_pszFilePath = "Sounds/Water3.ogg";
		break;
	case SOUND_SCORE_COUNT:
		m_pszFilePath = "Sounds/Score_Count1.ogg" ;
		break;
	case SOUND_ALARM_WATER_DROP_1:
		m_pszFilePath = "Sounds/Alarm_Water_Drop.ogg";
		break;
	case SOUND_CLICK_1:
		m_pszFilePath = "Sounds/click.ogg";
		break;
	case SOUND_BACKGROUND:
		m_pszFilePath = "Sounds/BgMusic.ogg";
		break;
	case SOUND_STAR_1:
		m_pszFilePath = "Sounds/star_1.ogg";
		break;
	case SOUND_STAR_2:
		m_pszFilePath = "Sounds/star_2.ogg";
		break;
	case SOUND_STAR_3:
		m_pszFilePath = "Sounds/star_3.ogg";
		break;
	case SOUND_GAMEPLAY_BAGROUND_1:
		m_pszFilePath = "Sounds/GamePlayBackGround_1.ogg";
		break;
	case SOUND_ENABLE_BUTTON:
		m_pszFilePath = "Sounds/EnableButton.ogg";
		break;
	case SOUND_ANT_MOVE:
		m_pszFilePath = "Sounds/AntMove.ogg";
		break;
	case SOUND_ANT_DEAD:
		m_pszFilePath = "Sounds/AntDead.ogg";
		break;
	case SOUND_INTRO:
		m_pszFilePath = "Sounds/Sound564.ogg";
		break;
	case SOUND_MAINMENU:
		m_pszFilePath = "Sounds/Sound647.ogg";
		break;
	default:
		m_pszFilePath = "";
		break;
	}
}

void CAudioManager::initAudio()
{
	m_Sound = SOUND_BG_EFF;
	m_SManager->preloadEffect("Sounds/Win1.ogg");
	m_SManager->preloadEffect("Sounds/Win2.ogg");
	m_SManager->preloadEffect("Sounds/Water1.ogg");
	m_SManager->preloadEffect("Sounds/Water2.ogg");
	m_SManager->preloadEffect("Sounds/Water3.ogg");
	m_SManager->preloadEffect("Sounds/Score_Count1.ogg");
	m_SManager->preloadEffect("Sounds/click.ogg");
	m_SManager->preloadEffect("Sounds/star_1.ogg");
	m_SManager->preloadEffect("Sounds/star_2.ogg");
	m_SManager->preloadEffect("Sounds/star_3.ogg");
	m_SManager->preloadEffect("Sounds/AntMove.ogg");
	m_SManager->preloadEffect("Sounds/AntDead.ogg");
	m_SManager->preloadEffect("Sounds/EnableButton.ogg");
	m_SManager->preloadEffect("Sounds/Alarm_Water_Drop.ogg");
	m_SManager->preloadBackgroundMusic("Sounds/BgMusic.ogg");
	m_SManager->preloadBackgroundMusic("Sounds/Sound564.ogg");
	m_SManager->preloadBackgroundMusic("Sounds/Sound647.ogg");
}
void CAudioManager::DestroyInstance()
{
	CC_SAFE_DELETE(m_instance);
}

CAudioManager::~CAudioManager()
{

}