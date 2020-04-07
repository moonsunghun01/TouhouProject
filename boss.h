#pragma once
#include"gameNode.h"
#include "progressBar.h"
#define PI 3.14
class boss : public gameNode
{
private:
	image * _image;
	RECT _rc;

	// HP ��
	progressBar* _hpBar;
	float _maxHp;
	float _currentHp;
	bool _isCreateHp;

	int _currentFrameX;
	int _currentFrameY;
	int _count;

	bool isBossMaxFrame;

	float _bossMoveCount;
	int   _movePattern;							// �̵�����
	bool _isCreate;

	int _index;
	int _bossStatus;							// ���
	bool _isFire;								// �̻��� �߻�

	int _arrNum;								// ����� ���� ��������. ��� 
	int _missileCount;

	int _bossNum;								// ���� �ѹ�

	POINT _center;								// ���� �߽�
	float _angle;								// ���ư��� ����

	bool _isCircle;								// ������ ����

	// ��� �������� �̵��� ������
	int _bossDirection;							// ���� ����

	// �� �̻��� ī��Ʈ
	int _starMissileCount;
	bool _isStarMax;

	// �׸� ���� ī��Ʈ
	int _rectMissileCount;
	bool _isRectMax;

	// ������ ī��Ʈ
	int _circleMissileCount;
	bool _isCircleMax;

public:
	boss();
	~boss();

	HRESULT init();
	HRESULT init(const char* imageName, float x, float y);
	void release();
	void update();
	void render();

	virtual void draw();
	virtual void animation();

	void createHpBar();

	image getImage() { return *_image; }
	void setImage(image* image) { _image = image; }

	RECT getRect() { return _rc; }
	void setRect(RECT rc) { _rc = rc; }

	float getBossMoveCount() { return _bossMoveCount; }
	void setBossMoveCount(float bossMoveCount) { _bossMoveCount = bossMoveCount; }

	bool getIsCreate() { return _isCreate; }
	void setIsCreate(bool isCreate) { _isCreate = isCreate; }

	int getMovePattern() { return _movePattern; }
	void setMovePattern(int movePattern) { _movePattern = movePattern; }

	int getBossStatus() { return _bossStatus; }
	void setBossStatus(int num) { _bossStatus = num; }

	bool getIsFire() { return _isFire; }
	void setIsFire(bool isFire) { _isFire = isFire; }

	int getMissileCount() { return _missileCount; }
	void setMissileCount(int missileCount) { _missileCount = missileCount; }

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

	int getBossDirection() { return _bossDirection; }
	void setBossDirection(int bossDirection) { _bossDirection = bossDirection; }

	int getStarMissileCount() { return _starMissileCount; }
	void setStarMissileCount(int starMissileCount) { _starMissileCount = starMissileCount; }

	bool getIsStarMax() { return _isStarMax; }
	void setIsStarMax(bool isStarMax) { _isStarMax = isStarMax; }

	int getRectMissileCount() { return _rectMissileCount; }
	void setRectMissileCount(int rectMissileCount) { _rectMissileCount = rectMissileCount; }

	bool getIsRectMax() { return _isRectMax; }
	void setIsRectMax(bool isRectMax) { _isRectMax = isRectMax; }

	int getCircleMissileCount() { return _circleMissileCount; }
	void setCircleMissileCount(int circleMissileCount) { _circleMissileCount = circleMissileCount; }

	bool getIsCircleMax() { return _isCircleMax; }
	void setIsCircleMax(bool isCircleMax) { _isCircleMax = isCircleMax; }


	progressBar getHpBar() { return *_hpBar; }
	void setHpBar(progressBar * hpBar) { _hpBar = hpBar; }

	float getMaxHp() { return _maxHp; }
	void setMaxHp(float maxHp) { _maxHp = maxHp; }

	float getCurrentHp() { return _currentHp; }
	void setCurrentHp(float currentHp) { _currentHp = currentHp; }
};

