#pragma once
#include"gameNode.h"
#include"bullet.h"
#include"minion.h"
#include"middleBoss.h"
#include "boss.h"
#include "bossBackEffect.h"

class player;
class enemyManager :  public gameNode
{
private:

	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;
	player* _player;

	typedef vector<middleBoss*> vMBoss;
	typedef vector<middleBoss*>::iterator viMBoss;

	typedef vector<boss*> vBoss;
	typedef vector<boss*>::iterator viBoss;
private:

	vEnemy			_vMinion;
	viEnemy			_viMinion;
	bullet*			_bullet;
	bossMissile*    _bossMissile;

	vMBoss		_vMBoss;
	viMBoss		_viMBoss;

	vBoss		_vBoss;
	viBoss		_viBoss;

	bossBackEffect* _bossBackEffeck;

	RECT _tempRc;

	int _patternCount;
	int _timeCount;
	int _createCount;

	int _bulletCount;
	int _mBossSpeed;

	int _mBlueBossTimeCount;

	bool _isStartEnemyCreate;

public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void pattern();


	vEnemy		getVMinion() { return _vMinion; }
	viEnemy		getViMinion() { return _viMinion; }

	void createMinion(float x, float y, int movePattern);
	void moveMinion();
	void minionBulletFire();
	void removeMinion(int arrNum);

	void collision();

	void setRocketMemoryLink(player* rocket) { _player = rocket; }


	vMBoss		getVMBoss() { return _vMBoss; }
	viMBoss		getViMBoss() { return _viMBoss; }
	void createMBoss(int bossNum,float x, float y, int movePattern,int arrNum);
	void moveMBoss();
	void mBossBulletFire();
	void removeMBoss(int arrNum);


	vBoss		getVBoss() { return _vBoss; }
	viBoss		getViBoss() { return _viBoss; }
	void createBoss(float x, float y);
	void moveBoss();
	void bossBulletFire();
	void removeBoss(int arrNum);

	int getPatternCount() { return _patternCount; }
	void setPatternCount(int patternCount) { _patternCount = patternCount; }

	bool getIsStartEnemyCreate() { return _isStartEnemyCreate; }
	void setIsStartEnemyCreate(bool isStartEnemyCreate) { _isStartEnemyCreate = isStartEnemyCreate; }
};

