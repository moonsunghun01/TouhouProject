#pragma once
#include"gameNode.h"

class bossBackEffect : public gameNode
{
private:
	image * _image;
	RECT _rc;

	int _currentFrameX;
	int _currentFrameY;
	int _count;


public:
	bossBackEffect();
	~bossBackEffect();

	HRESULT init();
	HRESULT init(const char* imageName);
	void release();
	void update(float x, float y);
	void render();

	virtual void draw();
	virtual void animation();

	image getImage() { return *_image; }
	void setImage(image* image) { _image = image; }

	RECT getRect() { return _rc; }
	void setRect(RECT rc) { _rc = rc; }

};

