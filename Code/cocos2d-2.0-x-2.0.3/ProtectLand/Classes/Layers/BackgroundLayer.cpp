#include "BackgroundLayer.h"
#include "LevelManager.h"
#include "AudioManager.h"
USING_NS_CC;
bool CBackgroundLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	char* strNameFile[7] = {"Background\\background_package_level_1.png", "Background\\background_package_level_2.png", "Background\\background_package_level_3.png",
							"Background\\background_package_level_4.png","background_package_level_5.png", "background_package_level_3.png",
							"background_package_level_6.png"
							};
	CCSprite* pSprite = CCSprite::create(strNameFile[CLevelManager::GetInstance()->GetLevelInformation()->m_iMapCurrent - 1]);
	pSprite->setPosition( ccp(size.width/2, size.height/2) );
	this->addChild(pSprite, 0);

	int arrIDbackgroundMusic[7] = {SOUND_BACKGROUND_HUMAN, SOUND_BACKGROUND_ELF, SOUND_BACKGROUND_ACADEMY, SOUND_BACKGROUND_DWARF,
									SOUND_BACKGROUND_DARKELF, SOUND_BACKGROUND_UNDEAD, SOUND_BACKGROUND_DEVIL
									};
	CAudioManager::instance()->stopAllEff();
	CAudioManager::instance()->stopBGMusic();
	CAudioManager::instance()->playBGMusic(arrIDbackgroundMusic[CLevelManager::GetInstance()->GetLevelInformation()->m_iMapCurrent - 1], true);
	return true;
}

void CBackgroundLayer::update(float dt)
{

}

void CBackgroundLayer::render()
{

}

void CBackgroundLayer::exit()
{

}