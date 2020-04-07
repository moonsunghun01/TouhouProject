#pragma once
#include"gameNode.h"
#define PI 3.14
class middleBoss : public gameNode
{
private:
	image * _image;
	RECT _rc;

	int _currentFrameX;
	int _currentFrameY;
	int _count;

	bool isMiddleMaxFrame;

	float _moveCount;
	int   _movePattern;							// 이동패턴
	bool _isCreate;

	int _index;								
	int _mBossStatus;							// 모션
	bool _isFire;								// 미사일 발사

	int _arrNum;								// 몇번쨰 생성 보스인지. 기억 
	int _missileCount;

	int _bossNum;								// 보스 넘버

	POINT _center;								// 보스 중심
	float _angle;								// 돌아가는 각도

	bool _isCircle;								// 원패턴 시작

	int _hp;
	int _hitCount;
public:
	middleBoss();
	~middleBoss();

	HRESULT init();
	HRESULT init(const char* imageName, float x, float y);
	void release();
	void update();
	void render();

	virtual void draw();
	virtual void animation();

	image getImage() { return *_image; }
	void setImage(image* image) { _image = image; }

	RECT getRect() { return _rc; }
	void setRect(RECT rc) { _rc = rc; }

	float getMoveCount() { return _moveCount; }
	void setMoveCount(float moveCount) { _moveCount = moveCount; }

	bool getIsCreate() { return _isCreate; }
	void setIsCreate(bool isCreate) { _isCreate = isCreate; }

	int getMovePattern() { return _movePattern; }
	void setMovePattern(int movePattern) { _movePattern = movePattern; }

	int getMBossStatus() { return _mBossStatus; }
	void setMBossStatus(int num) { _mBossStatus = num; }

	bool getIsFire() { return _isFire; }
	void setIsFire(bool isFire) { _isFire = isFire; }

	int getMissileCount() { return _missileCount; }
	void setMissileCount(int missileCount) { _missileCount = missileCount; }

	int getArrNum() { return _arrNum; }
	void setArrNum(int arrNum) { _arrNum = arrNum; }

	int getBossNum() { return _bossNum; }
	void setBossNum(int bossNum) { _bossNum = bossNum; }

	POINT getCenter() { return _center; }
	void setCenter(POINT center) { _center = center; }

	float getCenterX() { return _center.x; }
	void  setCenterX(float x) { _center.x = x; }

	float getCenterY() { return _center.y; }
	void  setCenterY(float y) { _center.y = y; }

	float getAngle() { return _angle; }
	void setAngle(float angle) { _angle = angle; }

	bool getIsCircle() { return _isCircle; }
	void setIsCircle(bool isCircle) { _isCircle = isCircle; }

	int getHp() { return _hp; }
	void setHp(int hp) { _hp = hp; }

	int getHitCount() { return _hitCount; }
	void setHitCount(int hitCount) { _hitCount = hitCount; }
};

