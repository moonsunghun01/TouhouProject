#include "stdafx.h"
#include "bossBackEffect.h"


bossBackEffect::bossBackEffect()
{
}


bossBackEffect::~bossBackEffect()
{
}

HRESULT bossBackEffect::init()
{
	return S_OK;
}

HRESULT bossBackEffect::init(const char * imageName)
{
	//프레임 초기화
	_count = 0;
	_currentFrameX = 0;
	_currentFrameY = 0;
	//이미지, 렉트
	_image = IMAGEMANAGER->findImage("bossBackEffect");
	

	return S_OK;
}


void bossBackEffect::release()
{
}

void bossBackEffect::update(float x, float y)
{
	
	_image->setX(x);
	_image->setY(y);
	_rc = RectMakeCenter(_image->getX(), _image->getY(), _image->getFrameWidth(), _image->getFrameHeight());
	animation();
}

void bossBackEffect::render()
{
	draw();
}

void bossBackEffect::draw()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

void bossBackEffect::animation()
{
	_count++;
	_currentFrameY = 0;
	if (_count % 5 == 0)
	{
		_count = 0;
		_currentFrameX++;
		if (_currentFrameX >= _image->getMaxFrameX())
		{
			_currentFrameX = 0;
		}
		_image->setFrameX(_image->getFrameX() + 1);
	}
}
