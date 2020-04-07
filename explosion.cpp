#include "stdafx.h"
#include "explosion.h"


explosion::explosion()
{
}


explosion::~explosion()
{
}

HRESULT explosion::init()
{
	_count = 0;
	_currentFrameX = 0;
	_currentFrameY = 0;
	_explosionImage = IMAGEMANAGER->findImage("explosionBlack");
	return S_OK;
}

HRESULT explosion::init()
{


	return S_OK;
}


void explosion::release()
{
}

void explosion::update()
{
	animation();
}

void explosion::render()
{
	_viExplosion = _vExplosion.begin();
	for (_viExplosion; _viExplosion != _vExplosion.end(); ++_viExplosion)
	{
		_viExplosion->exImage->render(getMemDC(), _viExplosion->rc.left, _viExplosion->rc.top);
	}
}

void explosion::create(float x, float y)
{
	tagExplosion explosion;
	ZeroMemory(&explosion, sizeof(tagExplosion));
	explosion.exImage = new image;
	explosion.exImage = IMAGEMANAGER->findImage("explosionBlack");

	explosion.x = x;
	explosion.y = y;
	explosion.rc = RectMakeCenter(explosion.x, explosion.y, explosion.exImage->getFrameWidth(), explosion.exImage->getFrameHeight());
	_vExplosion.push_back(explosion);
}

void explosion::animation()
{
	_count++;
	_currentFrameY = 0;
	if (_count % 5 == 0)
	{
		_count = 0;
		_currentFrameX++;
		if (_currentFrameX >= _explosionImage->getMaxFrameX())
		{
			_currentFrameX = 0;
		}
		_explosionImage->setFrameX(_explosionImage->getFrameX() + 1);
	}
}

void explosion::removeItem(int arrNum)
{
	//_vItem.erase(_vItem.begin() + arrNum);
}

