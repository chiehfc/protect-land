#ifndef __GAMEOBJECTLAYER_H__
#define __GAMEOBJECTLAYER_H__
#include <vector>
#include "cocos2d.h"
#include "PositionConfig.h"

#include "Utils.h"
#include "IncludeHelper.h"
#include "GamePlay.h"
#include "MySprite.h"
#include "Bullet.h"
#include "Monster.h"
#include "Tower.h"
#include "SkillLayer.h"
#include "ZOrderAddChildConfig.h"
USING_NS_CC;


#define MAX_ENEGY 10
#define TIME_DELAY_TO_PLAY_AMINATION 0.3f
#define TIME_DELAY_TO_DELETE_AMINATION 0.8f
class CThief;
class CBeet;
class CTeleport;
class CTarget;

class CGameObjectLayer: public cocos2d::CCLayer
{
private:

	CCSize	size; 
	//Sprite layer

	CCArray* 	m_pSpriteList;
	bool		m_bIscol;
	bool		m_bIsTouching;
	CCSprite*	m_pObject;
	CCSprite*	pMoveSprite;
	CCMenuItemImage *pMute;

	eAudioState eAstate;
	CCMenu* pMenu;
	
	//Area shoot bullet
	int m_typeBullet;
	CCSprite *m_pBaseTower;
	CMySprite *m_pTowerItem;
	int m_angleRotate;
	bool m_isClickChangeBullet;
	//Bullet
	float m_fSpeed;
	CCPoint m_pCurrentPoint;
	float m_fTimeRetireBullet;
    float m_TimeDelayBullet;
	int m_levelBullet;
	//Skill
	CCSprite *m_pSkill;
	CCSprite *m_pSkillBorder;
	float m_timeCounter;
	float m_timePlayAminationNext;
	float m_timeDeleteAmination;
	//vector<Bullet *> *m_vBullet;
	CCArray *m_arrBullet;	
	float length;
	//Physic

	
	//thong so truyen vao cua map:
	float timeDelay; //thoi gian delay giua cac dot ra quai
	int numOfTime; //so dot ra quai
	int typeMonster;  //so loai quai se ra.
	int *numOfMonsterPTime; //so luong quai moi dot
	int *typeOfAppear;  //cach xuat hien
	float *timeOfMonsterPerTime; //thoi gian cua moi dot quai
	float *m_totalTimeEachWay;
	int indexTime;   //index cua dot quai xuat hien
	float *timeForOneRow;
	void initMap();
	void appearInOneRow();
	void appearInTwoRows();
	void appearInThreeRows();
	void appearInMixture();
	int randomLevelMonster();
	int randomTypeMonster();
	int randomPosition(int firstPos, int secondPos);
	int *mixtureTime;
	float timeForMixtureTime;
	float timeDelayWin;

	//monster
	CCArray *m_arrMonster;
	CCArray *m_arrMonsterToDelete;
	float m_time;
	float m_timeMove;
	float currentTime;
	int currentHP;
	int turn;
	int m_index;
	CTower *m_tower;
	bool m_checkLose;
	CMonster * bossMonster;
	//Monster
	bool oneMonster;
	void processWhenMonsterDie(CMonster* pMonster);
	
	
	
	void addOneBullet(CCPoint &p,float angle);
	void addBullets(CCPoint &centerPoint);
	void loadTower(char * base, char * item);
	bool isClickSkill(CCPoint &p);
	CCPoint getDestination(float X,float Y);
	void updateBullet(int type, int level);
	float caculateAngle(CCPoint v,CCPoint v1);
	void removeStarSkill();
	void addStarSkill();  // them layer Skill
	void addSkillButton();
	void updateSkillButton();

	void spriteMoveDone( CCNode* sender );

	void playSound(CCNode* sender, void* data);	


	// boss:
	int MonsterPTime;
	int typeBossMonster;
	float nuMonsterPerTime;
	float timeBossOneRow;

public:	
	//Sprite	
	void loadMap();
	void creatMonster();
	void creatBoss();
	void createBossMonster();
	void attackTower();
	void actionKillMonster(CMonster* pMonster);
	void actionDestroyTower();
	void attackMonster();
	
	void menuSubMenuCallback(CCObject* pSender);
	void menuReplayMenuCallback(CCObject* pSender);
	void menuMuteMenuCallback(CCObject* pSender);

	void menuRestartCallback(CCObject* pSender);

	void delayWinScene(float dt);

	//add them cai de delete monster
	void addMonsterToDelete(CMonster * monster, int damage); //them vao danh sach xoa quai
	void addDeleteMonster(); //xoa quai sau mot thoi gian delay
	void hitMonster(CMonster * monster, int damage); //them vao luc quai bi attack
	void hurtMonster(CMonster *monster, int damage); //khi bi thuong
	bool check;

	virtual bool init();
	virtual void update(float dt);
	virtual void onExit();
	virtual void draw();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	CCRect getRectBulletFire(Bullet* pBullet);  // get Rect cua bullet nhap vao
	CCRect getRectMonsterFire(CMonster* pMonster); //get Rect cuar monster truyen vao


	//connect with skill layer
	bool m_bIsFullEmergy; // true if afford emergy to exe skill
	int m_iCurrentEnegy;  // enegy hien tai, moi lan kill quai cong len
	bool m_bToggle;
	bool m_bIsFinshChooseSkill; //check khi skill da chon xong ben Skill layer
	int m_iTypeSkillReturn;  // loai skill se hien len
	void addSkillAnimation(int typeSkill);  //ham thuc hien them animation skill vao GameObjectlayer
	int randomNumber(int firstPos, int secondPos);
	int getAvailabeMonter(int *arr,int numEle);
	bool monterIsFree(int *arr,int numEle, int pos);
	//check dieu kien lose khi tower het mau
	bool m_bIsLoose; // kiem tra xem da loose hay chua thong qua mau cua tower
	void checkLoose();

	//icon and label in game stage
	CCLabelBMFont* m_pLabelCoinCollect;  // so coin co duoc
	CCLabelBMFont* m_pLabelStageCurrent; // level hien tia cua stage
	void processLabelCoin(); //ham xu ly thay doi cho label coin trong ham update
	//phan tower
	CC_SYNTHESIZE(int, towerHp, TowerHP);
	CCSprite *m_activeHP, *m_inactiveHP;

	CC_SYNTHESIZE(bool, m_checkWin, CheckWin);//check xem win man nay chua

	CC_SYNTHESIZE(int, m_coinBonus, CoinBonus);

	CREATE_FUNC(CGameObjectLayer);

	void transToSkillUpgradeScene(CCNode* sender); //thuc hien chuyen scene sau khi nguoi choi gameover
	void transToWinScene(CCNode* sender); // thuc hien chuyen qua Win scence khi win
	void timeBossForOneRow();


	void changeTypeTower();
	void killMonster(int damage);

	void animationSkillDone(CCNode* pSender);

};


#endif
