#include "AudioManager.h"
#include "IncludeHelper.h"
#include "SoundConfig.h"
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
	case SOUND_BACKGROUND_ACADEMY:
		m_pszFilePath = "SoundBackground/academy_bg.mp3";
		break;
	case SOUND_BACKGROUND_BOSS:
		m_pszFilePath = "SoundBackground/boss_bg.mp3";
		break;
	case SOUND_BACKGROUND_DARKELF:
		m_pszFilePath = "SoundBackground/darkelf_bg.mp3";
		break;
	case SOUND_BACKGROUND_DEVIL:
		m_pszFilePath = "SoundBackground/devil_bg.mp3";
		break;
	case SOUND_BACKGROUND_DWARF:
		m_pszFilePath = "SoundBackground/dwarf_bg.mp3";
		break;
	case SOUND_BACKGROUND_ELF:
		m_pszFilePath = "SoundBackground/elf_bg.mp3" ;
		break;
	case SOUND_BACKGROUND_FAIL:
		m_pszFilePath = "SoundBackground/fail.mp3";
		break;
	case SOUND_BACKGROUND_HUMAN:
		m_pszFilePath = "SoundBackground/human_bg.mp3";
		break;
	case SOUND_BACKGROUND_MAIN:
		m_pszFilePath = "SoundBackground/main_bg.mp3";
		break;
	case SOUND_BACKGROUND_SUCCEED:
		m_pszFilePath = "SoundBackground/succeed.mp3";
		break;
	case SOUND_BACKGROUND_UNDEAD:
		m_pszFilePath = "SoundBackground/undead_bg.mp3";
		break;
	case SOUND_BUTTON:
		m_pszFilePath = "SoundEffect/01_button.mp3";
		break;
	case SOUND_EQUIP_UPGRADE:
		m_pszFilePath = "SoundEffect/02_equip_or_upgrade.mp3";
		break;
	case SOUND_NORMAL_TOWER:
		m_pszFilePath = "SoundEffect/03_normal_tower.mp3";
		break;
	case SOUND_FIRE_TOWER:
		m_pszFilePath = "SoundEffect/04_fire_tower.mp3";
		break;
	case SOUND_ICE_TOWER:
		m_pszFilePath = "SoundEffect/05_ice_tower.mp3";
		break;
	case SOUND_ELECT_TOWER:
		m_pszFilePath = "SoundEffect/06_elect_tower.mp3";
		break;
	case SOUND_BOSS_ALERT:
		m_pszFilePath = "SoundEffect/07_boss_alert.mp3";
		break;
	case SOUND_MONSTER_ALERT:
		m_pszFilePath = "SoundEffect/08_monster_alert.mp3";
		break;
	case SOUND_WALL_BEHIT:
		m_pszFilePath = "SoundEffect/09_wall_behit.mp3";
		break;
	case SOUND_WALL_BEHIT_BLAST:
		m_pszFilePath = "SoundEffect/09_wall_behit_blast.mp3";
		break;
	case SOUND_MONSTER_BEHIT:
		m_pszFilePath = "SoundEffect/10_monster_behit.mp3";
		break;
	case SOUND_FIRE_MAGIC:
		m_pszFilePath = "SoundEffect/11_fire_magic.mp3";
		break;
	case SOUND_ICE_MAGIC:
		m_pszFilePath = "SoundEffect/12_ice_magic.mp3";
		break;
	case SOUND_WIND_MAGIC:
		m_pszFilePath = "SoundEffect/13_wind_magic.mp3";
		break;
	case SOUND_SUPER_MAGIC:
		m_pszFilePath = "SoundEffect/14_super_magic.mp3";
		break;
	case SOUND_MAGIC_WAIT_FINISH:
		m_pszFilePath = "SoundEffect/15_magic_wait_finish.mp3";
		break;
	case SOUND_MAIN_LOGO_EFFECT_FLY:
		m_pszFilePath = "SoundEffect/17_main_logo_effect_fly.mp3";
		break;
	case SOUND_MAIN_LOGO_EFFECT_HIT:
		m_pszFilePath = "SoundEffect/17_main_logo_effect_hit.mp3";
		break;
	default:
		m_pszFilePath = "";
		break;
	}
}

void CAudioManager::initAudio()
{
	m_Sound = SOUND_BG_EFF;
	m_SManager->preloadBackgroundMusic("SoundBackground/academy_bg.mp3");
	m_SManager->preloadBackgroundMusic("SoundBackground/boss_bg.mp3");
	m_SManager->preloadBackgroundMusic("SoundBackground/darkelf_bg.mp3");
	m_SManager->preloadBackgroundMusic("SoundBackground/devil_bg.mp3");
	m_SManager->preloadBackgroundMusic("SoundBackground/dwarf_bg.mp3");
	m_SManager->preloadBackgroundMusic("SoundBackground/elf_bg.mp3");
	m_SManager->preloadBackgroundMusic("SoundBackground/fail.mp3");
	m_SManager->preloadBackgroundMusic("SoundBackground/human_bg.mp3");
	m_SManager->preloadBackgroundMusic("SoundBackground/main_bg.mp3");
	m_SManager->preloadBackgroundMusic("SoundBackground/succeed.mp3");
	m_SManager->preloadBackgroundMusic("SoundBackground/undead_bg.mp3");
	m_SManager->preloadEffect("SoundEffect/01_button.mp3");
	m_SManager->preloadEffect("SoundEffect/02_equip_or_upgrade.mp3");
	m_SManager->preloadEffect("SoundEffect/03_normal_tower.mp3");
	m_SManager->preloadEffect("SoundEffect/04_fire_tower.mp3");
	m_SManager->preloadEffect("SoundEffect/05_ice_tower.mp3");
	m_SManager->preloadEffect("SoundEffect/06_elect_tower.mp3");
	m_SManager->preloadEffect("SoundEffect/08_monster_alert.mp3");
	m_SManager->preloadEffect("SoundEffect/09_wall_behit.mp3");
	m_SManager->preloadEffect("SoundEffect/09_wall_behit_blast.mp3");
	m_SManager->preloadEffect("SoundEffect/10_monster_behit.mp3");
	m_SManager->preloadEffect("SoundEffect/11_fire_magic.mp3");
	m_SManager->preloadEffect("SoundEffect/12_ice_magic.mp3");
	m_SManager->preloadEffect("SoundEffect/13_wind_magic.mp3");
	m_SManager->preloadEffect("SoundEffect/14_super_magic.mp3");
	m_SManager->preloadEffect("SoundEffect/15_magic_wait_finish.mp3");
	m_SManager->preloadEffect("SoundEffect/17_main_logo_effect_fly.mp3");
	m_SManager->preloadEffect("SoundEffect/17_main_logo_effect_hit.mp3");
	
}
void CAudioManager::DestroyInstance()
{
	CC_SAFE_DELETE(m_instance);
}

CAudioManager::~CAudioManager()
{

}