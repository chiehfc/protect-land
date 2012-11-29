#pragma once
#ifndef CAudioManager_H
#define CAudioManager_H

#include "SimpleAudioEngine.h"
#include "GameConfig.h"
#include "SoundConfig.h"

class CAudioManager
{
public:

	~CAudioManager();
	static CAudioManager* instance();
	CocosDenshion::SimpleAudioEngine* GetSManager();
	void preloadBGMusic(int AudioID);
	void playBGMusic(int AudioID, bool bLoop = false);
	void stopBGMusic(bool bReleaseData = false);
	void pauseBGMusic();
	void resumeBGMusic();
	void rewindBGMusic();
	bool willPlayBGdMusic();
	bool isBGMusicPlaying();
	float getBGMusicVolume();
	void setBGMusicVolume(float volume);
	float getEffVolume();
	void setEffVolume(float volume);
	unsigned int playEff(int AudioID, bool bLoop = false);
	void pauseEff(unsigned int nSoundId);
	void pauseAllEff();
	void resumeEff(unsigned int nSoundId);
	void resumeAllEff();
	void stopEff(unsigned int nSoundId);
	void stopAllEff();
	void preloadEff(int AudioID);
	void unloadEff(int AudioID);
	static void DestroyInstance();
	void initAudio();
	int GetSound() { return m_Sound; }
	void SetSound(int newSound) { m_Sound = newSound; }
	
private:
	void AudioChoice(int AudioID);

	static CAudioManager* m_instance;
	int m_Sound;
	CAudioManager();
	CocosDenshion::SimpleAudioEngine* m_SManager;
	char* m_pszFilePath;
};
#endif