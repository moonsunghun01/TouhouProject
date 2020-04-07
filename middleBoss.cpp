#include "stdafx.h"
#include "middleBoss.h"


middleBoss::middleBoss()
{
}


middleBoss::~middleBoss()
{
}

HRESULT middleBoss::init()
{
	return S_OK;
}

HRESULT middleBoss::init(const char * imageName, float x, float y)
{
	//프레임 초기화
	_count = 0;
	_currentFrameX = 0;
	_currentFrameY = 0;
	//이미지, 렉트
	_image = IMAGEMANAGER->findImage(imageName);
	_image->setX(x);
	_image->setY(y);

	_rc = RectMakeCenter(_image->getX(), _image->getY(), _image->getFrameWidth(), _image->getFrameHeight());

	_isCreate = false;
	_moveCount = 0;

	return S_OK;
}

void middleBoss::release()
{
}

void middleBoss::update()
{
	animation();

}

void middleBoss::render()
{
	draw();
}

void middleBoss::draw()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
}

void middleBoss::animation()
{
	if (_bossNum == 1)
	{
		if (_mBossStatus == 1)
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

		else if (_mBossStatus == 2)
		{
			_count++;
			_currentFrameY = 1;
			if (_count % 10 == 0)
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
	}

	else if (_bossNum == 2)
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
	else if (_bossNum == 3)
	{
		if (_mBossStatus == 1)
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
		else if (_mBossStatus == 3)
		{
			_count++;
			_currentFrameY = 2;
			if (_count % 7 == 0)
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
	}

	else if (_bossNum == 4)
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


	else if (_bossNum == 5)
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

	else if (_bossNum == 6)
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
	else if (_bossNum == 7)
	{
	_count++;
	_currentFrameY = 0;
	if (_count % 5 == 0)
	{
		_count = 0;
		_currentFrameX++;
		if (_currentFrameX >= 5)
		{
			_currentFrameX = 0;
		}
		_image->setFrameX(_image->getFrameX() + 1);
	}
	}
}
