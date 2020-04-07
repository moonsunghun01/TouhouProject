#pragma once
#include"gameNode.h"
//에너미 클래스를 상속받아서 보스나 부하들을 만들어된다.
class enemy : public gameNode
{
private :

	image * _image;
	RECT _rc;

	int _currentFrameX;
	int _currentFrameY;
	int _count;

	//랜덤으로 총알 발사할 변수들
	int _fireCount;
	int _rndFireCount;

	bool isEnemyMaxFrame;

	float _moveCount;
	int   _movePattern;
	bool _isCreate;
	
public:
	enemy();
	~enemy();

	HRESULT init();
	HRESULT init(const char* imageName,float x,float y);
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update();
	void render();

	virtual void draw();
	virtual void animation();

	bool bulletCountFire();

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
};

