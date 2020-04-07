#pragma once
#include"gameNode.h"

struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float radius;
	float angle;
	float speed;
	float xSpeed;
	float ySpeed;
	bool fire;
	int count;
	bool isAuto;
	bool isTop;
	bool isFire;
	int patternNum;

	bool isSpeedDecrease;
};

class enemyManager;

class bullet  :public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;


	const char* _imageName;
	float _range;
	int _bulletMax;

public:
	bullet();
	~bullet();

	HRESULT init(char* imageName,int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed);
	void move();

	//총알삭제
	void removeMissile(int arrNum);
	void removeAllMissile();

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }
};

class playerMissile : public gameNode
{

private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	vector<tagBullet> _vFireBullet;
	vector<tagBullet>::iterator _viFireBullet;

	vector<tagBullet> _vIdleBullet;
	vector<tagBullet>::iterator _viIdleBullet;

	int _missileMax;
	float _range;
	int _count;

	int _tempNum;
public:

	playerMissile();
	~playerMissile();

	HRESULT init(int bulletMax, float range);
	void release();
	void update(enemyManager* _em);
	void render();

	void fire(float x, float y, bool isAuto);
	void move(enemyManager* _em);

	void leftFire(float x, float y , bool isAuto);
	void rightFire(float x, float y , bool isAuto);

	
	void removePlayerMissile(int arrNum);
	void playerMissileExplosion(int arrNum);

	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

	vector<tagBullet> getVFireBullet() { return _vFireBullet; }
	vector<tagBullet>::iterator getVIFireBullet() { return _viFireBullet; }
};

class playerBomb : public gameNode
{

private:
	vector<tagBullet> _vFireBullet;
	vector<tagBullet>::iterator _viFireBullet;

	vector<tagBullet> _vIdleBullet;
	vector<tagBullet>::iterator _viIdleBullet;

	int _missileMax;
	float _range;
	int _count;

	int _tempNum;
public:

	playerBomb();
	~playerBomb();

	HRESULT init(int bulletMax, float range);
	void release();
	void update(enemyManager* _em);
	void render();

	void fire(float x, float y);
	void move(enemyManager* _em);

	void removePlayerBomb(int arrNum);

	vector<tagBullet> getVFireBullet() { return _vFireBullet; }
	vector<tagBullet>::iterator getVIFireBullet() { return _viFireBullet; }
};


class bossMissile :public gameNode
{
private:

	vector<tagBullet> _vFireBullet;
	vector<tagBullet>::iterator _viFireBullet;

	vector<tagBullet> _vIdleBullet;
	vector<tagBullet>::iterator _viIdleBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;
	int _bulletCount;

	int _patternNum;

	int _bullectCreateCount;	// 네번쨰 패턴 원 다 생성했는지
	int _patternFourTimeCount;	// 네번쨰 원패턴 시간 카운트

	int _patternSevenTimeCount;	// 일곱번쨰 패턴 시간 카운트
	bool _isSpeedDecrease;
	//bool _isSpeedIncrease;

	int  _circleTimeCount;		// 원 카운트. 너무빨라서 원 이탈 
	bool _isCircleCreateCheck;	// 원 다 만들었는지 체크

	// 별
	int _bossPatternOneTimeCount;
	bool _isStarPatternCountMax;

	// 네모
	int _bossPatternTwoTimeCount;
	bool _isRectPatternCountMax;

	// 원
	int _bossPatternThreeTimeCount;
	bool _isCirclePatternCountMax;

	// 원패턴 시간 카운트
	int _bossCirclePatternTimeCount;

public:
	bossMissile();
	~bossMissile();

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y);
	void fire(float x, float y, int count, int pattern);
	void move();

	//총알삭제
	void removeBossMissile(int arrNum);
	void removeAllMissile();

	vector<tagBullet> getVFireBullet() { return _vFireBullet; }
	vector<tagBullet>::iterator getVIFireBullet() { return _viFireBullet; }
};