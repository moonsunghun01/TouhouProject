#include "stdafx.h"
#include "boss.h"


boss::boss()
{
}


boss::~boss()
{
}

HRESULT boss::init()
{
	return S_OK;
}

HRESULT boss::init(const char * imageName, float x, float y)
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
	//_moveCount = 0;

	_isCreateHp = true;
	_maxHp  = 3000;
	_currentHp = 0;
	_hpBar = new progressBar;

	_hpBar->init("images/progressBarFront.bmp", "images/progressBarBack.bmp", 100, 70, 600, 10);
	_hpBar->setGauge(_currentHp, _maxHp);

	return S_OK;
}

void boss::release()
{
	SAFE_DELETE(_hpBar);
}

void boss::update()
{
	if(_isCreateHp) createHpBar();
	_hpBar->setGauge(_currentHp, _maxHp);
	_hpBar->update();
	animation();
}

void boss::render()
{
	_hpBar->render();
	draw();
}

void boss::draw()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
}

void boss::animation()
{
	//if (_bossNum == 1)
	{
		// 가만히
		if (_bossStatus == 1)
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

		// 왼쪽
		else if (_bossStatus == 2)
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

		// 오른쪽
		else if (_bossStatus == 3)
		{
			_count++;
			_currentFrameY = 2;
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

		// 특수 공격 모션 ?
		else if (_bossStatus == 4)
		{
			_count++;
			_currentFrameY = 3;
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
}

void boss::createHpBar()
{
	_currentHp += 40;
	if (_currentHp >= _maxHp)
	{
		_currentHp = _maxHp;
		_isCreateHp = false;
	}
}
