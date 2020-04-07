#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(const char * imageName,float x, float y)
{
	//프레임 초기화
	_count = 0;
	_currentFrameX = 0;
	_currentFrameY = 0;
	//랜덤
	_fireCount = 0;
	_rndFireCount = RND->getFromIntTo(1, 100);
	//이미지, 렉트
	_image = IMAGEMANAGER->findImage(imageName);
	_image->setX(x);
	_image->setY(y);
	_rc = RectMakeCenter(_image->getX(), _image->getY() , _image->getFrameWidth(), _image->getFrameHeight());
	//_rc = RectMakeCenter(_image->getX(), _image->getY(), _image->getFrameWidth(), _image->getFrameHeight());
	_isCreate = false;
	_moveCount = 0;

	return S_OK;
}

HRESULT enemy::init(const char * imageName, POINT position)
{
	//프레임 초기화
	_count= 0;
	_currentFrameX = 0;
	_currentFrameY = 0;
	//랜덤
	_fireCount = 0;
	_rndFireCount = RND->getFromIntTo(1, 1000);
	//이미지, 렉트

	_image = IMAGEMANAGER->findImage(imageName);
	_rc =  RectMakeCenter(position.x, position.y, _image->getFrameWidth(), _image->getFrameHeight());

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	animation();

}

void enemy::render()
{
	draw();
}

void enemy::draw()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	
}

void enemy::animation()
{
	_count++;
	if (_count % 5 == 0)
	{
		if (!isEnemyMaxFrame)
		{
			_image->setFrameX(_image->getFrameX() + 1);
			_currentFrameX++;

			if (_currentFrameX >= _image->getMaxFrameX())
			{
				isEnemyMaxFrame = true;
			}
		}
		else if (isEnemyMaxFrame)
		{
			_image->setFrameX(_image->getFrameX() - 1);
			_currentFrameX--;

			if (_currentFrameX <= 0)
			{
				isEnemyMaxFrame = false;
			}
		}
	}
}

bool enemy::bulletCountFire()
{
	_fireCount = 5;
	_rndFireCount = RND->getFromIntTo(1, 100);
	if (_fireCount % _rndFireCount == 0)
	{
		_fireCount = 5;;
		return true;
	}

	return false;
}
