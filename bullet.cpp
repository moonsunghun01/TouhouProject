#include "stdafx.h"
#include "bullet.h"
#include "enemyManager.h"

bullet::bullet() {}
bullet::~bullet() {}

HRESULT bullet::init(char * imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;
	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	move();
}

void bullet::render()
{
	_viBullet = _vBullet.begin();

	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);

		//Rectangle(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->rc.right, _viBullet->rc.bottom);
	}
}

void bullet::fire(float x, float y, float angle, float speed)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.angle = angle;
	bullet.speed = speed;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.bulletImage->getWidth(), bullet.bulletImage->getHeight());

	_vBullet.push_back(bullet);
}

void bullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		if (_range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;

	}
}

void bullet::removeMissile(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

void bullet::removeAllMissile()
{
	_vBullet.clear();
}


//////////////////////////// 사용자  미사일
playerMissile::playerMissile()
{

}

playerMissile::~playerMissile()
{
}

HRESULT playerMissile::init(int bulletMax, float range)
{
	_vFireBullet.reserve(bulletMax);
	_vIdleBullet.reserve(bulletMax);

	_range = range;

	//총알 초기화
	for (int i = 0; i < bulletMax; i++)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		//bullet.bulletImage->init("images/playerMissile.bmp", 30, 64, true, RGB(255, 0, 255));
		bullet.speed = 10.0f;
		bullet.fire = false;
		_vIdleBullet.push_back(bullet);
	}

	return S_OK;
}

void playerMissile::release()
{

}

void playerMissile::update(enemyManager* _em)
{
	move(_em);
}

void playerMissile::render()
{
	for (int i = 0; i < _vFireBullet.size(); i++)
	{
		if (!_vFireBullet[i].fire) continue;
		_vFireBullet[i].bulletImage->render(getMemDC(), _vFireBullet[i].rc.left, _vFireBullet[i].rc.top);
		//Rectangle(getMemDC(), _vFireBullet[i].rc.left, _vFireBullet[i].rc.top, _vFireBullet[i].rc.right, _vFireBullet[i].rc.bottom);
	}
}

void playerMissile::fire(float x, float y, bool isAuto)
{
	//ZeroMemory(&_vIdleBullet.at(0), sizeof(tagBullet));
	//_vIdleBullet.at(0).bulletImage->init("images/playerMissile.bmp", 30, 64, true, RGB(255, 0, 255));
	_vIdleBullet.at(0).bulletImage = IMAGEMANAGER->findImage("playerMissile");

	_vIdleBullet.at(0).fire = true;

	_vIdleBullet.at(0).x = _vIdleBullet.at(0).fireX = x;
	_vIdleBullet.at(0).y = _vIdleBullet.at(0).fireY = y;
	_vIdleBullet.at(0).rc = RectMakeCenter(_vIdleBullet.at(0).x, _vIdleBullet.at(0).y, _vIdleBullet.at(0).bulletImage->getWidth(), _vIdleBullet.at(0).bulletImage->getHeight());

	_vFireBullet.push_back(_vIdleBullet.at(0));
	_vIdleBullet.erase(_vIdleBullet.begin());
}

void playerMissile::leftFire(float x, float y, bool isAuto)
{
	//_vIdleBullet.at(0).bulletImage->init("images/playerMiniMissile.bmp", 30, 64, true, RGB(255, 0, 255));
	//_vIdleBullet.at(0).bulletImage->init("images/playerMiniMissile.bmp", 15, 15, true, RGB(255, 0, 255));
	_vIdleBullet.at(0).bulletImage = IMAGEMANAGER->findImage("playerMiniMissile");

	_vIdleBullet.at(0).fire = true;
	_vIdleBullet.at(0).isAuto = isAuto;

	_vIdleBullet.at(0).speed = 20.0;
	_vIdleBullet.at(0).x = _vIdleBullet.at(0).fireX = x;
	_vIdleBullet.at(0).y = _vIdleBullet.at(0).fireY = y;
	_vIdleBullet.at(0).rc = RectMakeCenter(_vIdleBullet.at(0).x, _vIdleBullet.at(0).y, _vIdleBullet.at(0).bulletImage->getWidth(), _vIdleBullet.at(0).bulletImage->getHeight());

	_vFireBullet.push_back(_vIdleBullet.at(0));
	_vIdleBullet.erase(_vIdleBullet.begin());
}

void playerMissile::rightFire(float x, float y, bool isAuto)
{
	//_vIdleBullet.at(0).bulletImage->init("images/playerMiniMissile.bmp", 30, 64, true, RGB(255, 0, 255));
	//_vIdleBullet.at(0).bulletImage->init("images/playerMiniMissile.bmp", 15, 15, true, RGB(255, 0, 255));
	_vIdleBullet.at(0).bulletImage = IMAGEMANAGER->findImage("playerMiniMissile");

	_vIdleBullet.at(0).fire = true;
	_vIdleBullet.at(0).isAuto = isAuto;

	_vIdleBullet.at(0).speed = 20.0;
	_vIdleBullet.at(0).x = _vIdleBullet.at(0).fireX = x;
	_vIdleBullet.at(0).y = _vIdleBullet.at(0).fireY = y;
	_vIdleBullet.at(0).rc = RectMakeCenter(_vIdleBullet.at(0).x, _vIdleBullet.at(0).y, _vIdleBullet.at(0).bulletImage->getWidth(), _vIdleBullet.at(0).bulletImage->getHeight());

	_vFireBullet.push_back(_vIdleBullet.at(0));
	_vIdleBullet.erase(_vIdleBullet.begin());
}


void playerMissile::move(enemyManager* _em)
{
	for (int i = 0; i < _vFireBullet.size(); i++)
	{

		if (!_vFireBullet[i].fire) continue;

		// 유도탄
		if (_vFireBullet[i].isAuto)
		{
			// 몬스터 없는경우
			if (_em->getVMinion().empty() && _em->getVMBoss().empty() && _em->getVBoss().empty())
			{
				_vFireBullet[i].y -= _vFireBullet[i].speed;
			}
			else if(!_em->getVMinion().empty())
			{
				if (_vFireBullet[i].rc.top + 100 > _em->getVMinion().at(0)->getRect().bottom)
				{
					{
						_vFireBullet[i].angle = getAngle(_vFireBullet[i].x, _vFireBullet[i].y,
							_em->getVMinion().at(0)->getRect().left + (_em->getVMinion().at(0)->getRect().right - _em->getVMinion().at(0)->getRect().left) / 2
							, _em->getVMinion().at(0)->getRect().bottom - (_em->getVMinion().at(0)->getRect().bottom - _em->getVMinion().at(0)->getRect().top) / 2);

						_vFireBullet[i].x += cosf(_vFireBullet[i].angle) * _vFireBullet[i].speed / 2;
						_vFireBullet[i].y += -sinf(_vFireBullet[i].angle) * _vFireBullet[i].speed;
						if (_vFireBullet[i].y < _em->getVMinion().at(0)->getRect().top - 45) _vFireBullet[i].isTop = true;
					}
				}
				else _vFireBullet[i].y -= _vFireBullet[i].speed;

				
			}

			// 중간 보스
			
			else if (!_em->getVMBoss().empty())
			{
				if (_vFireBullet[i].rc.top + 100 > _em->getVMBoss().at(0)->getRect().bottom)
				{
					{
						_vFireBullet[i].angle = getAngle(_vFireBullet[i].x, _vFireBullet[i].y,
							_em->getVMBoss().at(0)->getRect().left + (_em->getVMBoss().at(0)->getRect().right - _em->getVMBoss().at(0)->getRect().left) / 2
							, _em->getVMBoss().at(0)->getRect().bottom - (_em->getVMBoss().at(0)->getRect().bottom - _em->getVMBoss().at(0)->getRect().top) / 2);

						_vFireBullet[i].x += cosf(_vFireBullet[i].angle) * _vFireBullet[i].speed / 2;
						_vFireBullet[i].y += -sinf(_vFireBullet[i].angle) * _vFireBullet[i].speed;
						if (_vFireBullet[i].y < _em->getVMBoss().at(0)->getRect().top - 45) _vFireBullet[i].isTop = true;
					}
				}
				else _vFireBullet[i].y -= _vFireBullet[i].speed;
			}

			//보스
			else if (!_em->getVBoss().empty())
			{
				if (_vFireBullet[i].rc.top + 100 > _em->getVBoss().at(0)->getRect().bottom)
				{
					{
						_vFireBullet[i].angle = getAngle(_vFireBullet[i].x, _vFireBullet[i].y,
							_em->getVBoss().at(0)->getRect().left + (_em->getVBoss().at(0)->getRect().right - _em->getVBoss().at(0)->getRect().left) / 2
							, _em->getVBoss().at(0)->getRect().bottom - (_em->getVBoss().at(0)->getRect().bottom - _em->getVBoss().at(0)->getRect().top) / 2);

						_vFireBullet[i].x += cosf(_vFireBullet[i].angle) * _vFireBullet[i].speed / 2;
						_vFireBullet[i].y += -sinf(_vFireBullet[i].angle) * _vFireBullet[i].speed;
						if (_vFireBullet[i].y < _em->getVBoss().at(0)->getRect().top - 45) _vFireBullet[i].isTop = true;
					}
				}
				else _vFireBullet[i].y -= _vFireBullet[i].speed;
			}

			// 미사일 그리기
			_vFireBullet[i].rc = RectMakeCenter(_vFireBullet[i].x, _vFireBullet[i].y, _vFireBullet[i].bulletImage->getWidth(), _vFireBullet[i].bulletImage->getHeight());

		}
		else
		{
			_vFireBullet[i].y -= _vFireBullet[i].speed;
			_vFireBullet[i].rc = RectMakeCenter(_vFireBullet[i].x, _vFireBullet[i].y, _vFireBullet[i].bulletImage->getWidth(), _vFireBullet[i].bulletImage->getHeight());
			
		}

		// 미사일 사정거리 밖으로 나가면 삭제
		if (_range < getDistance(_vFireBullet[i].fireX, _vFireBullet[i].fireY, _vFireBullet[i].x, _vFireBullet[i].y))
		{
			_vFireBullet[i].fire = false;
			_vIdleBullet.push_back(_vFireBullet[i]);
			_vFireBullet.erase(_vFireBullet.begin() + i);
		}
	}
}
void playerMissile::playerMissileExplosion(int arrNum) {
	_vFireBullet[arrNum].bulletImage = IMAGEMANAGER->findImage("explosionBlack");
	_vFireBullet[arrNum].speed = 0;

}

void playerMissile::removePlayerMissile(int arrNum)
{
	//_vBullet.erase(_vBullet.begin() + arrNum);
	//_vFireBullet.erase(_vBullet.begin() + arrNum);
	_vIdleBullet.push_back(_vFireBullet[arrNum]);
	_vFireBullet.erase(_vFireBullet.begin() + arrNum);
}



playerBomb::playerBomb(){}
playerBomb::~playerBomb(){}
HRESULT playerBomb::init(int bulletMax, float range)
{
	_vFireBullet.reserve(bulletMax);
	_vIdleBullet.reserve(bulletMax);

	_range = range;

	//총알 초기화
	for (int i = 0; i < bulletMax; i++)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.speed = 10.0f;
		bullet.fire = false;
		_vIdleBullet.push_back(bullet);
	}
	return S_OK;
}

void playerBomb::release()
{
}

void playerBomb::update(enemyManager * _em)
{
	move(_em);
}

void playerBomb::render()
{
	for (int i = 0; i < _vFireBullet.size(); i++)
	{
		if (!_vFireBullet[i].fire) continue;
		_vFireBullet[i].bulletImage->render(getMemDC(), _vFireBullet[i].rc.left, _vFireBullet[i].rc.top);
	}
}

void playerBomb::fire(float x, float y)
{
	int rndNum = RND->getFromIntTo(1, 3);
	if(rndNum == 1) _vIdleBullet.at(0).bulletImage = IMAGEMANAGER->findImage("blueKnife");
	else if(rndNum == 2) _vIdleBullet.at(0).bulletImage = IMAGEMANAGER->findImage("grayKnife");
	else if(rndNum == 3) _vIdleBullet.at(0).bulletImage = IMAGEMANAGER->findImage("redKnife");
	_vIdleBullet.at(0).fire = true;
	_vIdleBullet.at(0).x = _vIdleBullet.at(0).fireX = x;
	_vIdleBullet.at(0).y = _vIdleBullet.at(0).fireY = y;
	_vIdleBullet.at(0).speed = RND->getFromIntTo(1, 10);
	_vIdleBullet.at(0).rc = RectMakeCenter(_vIdleBullet.at(0).x, _vIdleBullet.at(0).y, _vIdleBullet.at(0).bulletImage->getWidth(), _vIdleBullet.at(0).bulletImage->getHeight());

	_vFireBullet.push_back(_vIdleBullet.at(0));
	_vIdleBullet.erase(_vIdleBullet.begin());
}

void playerBomb::move(enemyManager * _em)
{
	for (int i = 0; i < _vFireBullet.size(); i++)
	{
		if (!_vFireBullet[i].fire) continue;
		
		_vFireBullet[i].y -= _vFireBullet[i].speed;
		_vFireBullet[i].x += _vFireBullet[i].speed;
		
		_vFireBullet[i].rc = RectMakeCenter(_vFireBullet[i].x, _vFireBullet[i].y, _vFireBullet[i].bulletImage->getWidth(), _vFireBullet[i].bulletImage->getHeight());

		if (_range < getDistance(_vFireBullet[i].fireX, _vFireBullet[i].fireY, _vFireBullet[i].x, _vFireBullet[i].y)
			|| _vFireBullet[i].rc.left < 70 || _vFireBullet[i].rc.right > 720 || _vFireBullet[i].rc.top < 30)
		{
			_vFireBullet[i].fire = false;
			_vIdleBullet.push_back(_vFireBullet[i]);
			_vFireBullet.erase(_vFireBullet.begin() + i);
		}
	}
	
}

void playerBomb::removePlayerBomb(int arrNum)
{
	_vIdleBullet.push_back(_vFireBullet[arrNum]);
	_vFireBullet.erase(_vFireBullet.begin() + arrNum);
}



bossMissile::bossMissile(){}
bossMissile::~bossMissile(){}
HRESULT bossMissile::init(int bulletMax, float range)
{
	_vFireBullet.reserve(bulletMax);
	_vIdleBullet.reserve(bulletMax);

	_range = range;

	//총알 초기화
	for (int i = 0; i < bulletMax; i++)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.speed = 5.0f;
		bullet.radius = 10.0f;
		bullet.fire = false;
		_vIdleBullet.push_back(bullet);
	}

	return S_OK;
}

void bossMissile::release()
{

}

void bossMissile::update()
{
	move();
}

void bossMissile::render()
{
	for (int i = 0; i < _vFireBullet.size(); i++)
	{
		if (!_vFireBullet[i].fire) continue;
		_vFireBullet[i].bulletImage->render(getMemDC(), _vFireBullet[i].rc.left, _vFireBullet[i].rc.top);
		//Rectangle(getMemDC(), _vFireBullet[i].rc.left, _vFireBullet[i].rc.top, _vFireBullet[i].rc.right, _vFireBullet[i].rc.bottom);
	}
}

void bossMissile::fire(float x, float y)
{
	//_vIdleBullet.at(0).bulletImage->init("images/mBossMissile.bmp", 16, 16, true, RGB(255, 0, 255));
	_vIdleBullet.at(0).bulletImage = IMAGEMANAGER->findImage("mBossMissile");
	_vIdleBullet.at(0).fire = true;

	_vIdleBullet.at(0).x = _vIdleBullet.at(0).fireX = x;
	_vIdleBullet.at(0).y = _vIdleBullet.at(0).fireY = y;
	_vIdleBullet.at(0).rc = RectMakeCenter(_vIdleBullet.at(0).x, _vIdleBullet.at(0).y, _vIdleBullet.at(0).bulletImage->getWidth(), _vIdleBullet.at(0).bulletImage->getHeight());

	_vIdleBullet.at(0).speed = 5.0f;

	_vFireBullet.push_back(_vIdleBullet.at(0));
	_vIdleBullet.erase(_vIdleBullet.begin());
}


void bossMissile::fire(float x, float y, int count, int pattern)
{
	_patternNum = pattern;
	_vIdleBullet.at(0).patternNum = pattern;
	_vIdleBullet.at(0).fire = true;

	_vIdleBullet.at(0).x = _vIdleBullet.at(0).fireX = x;
	_vIdleBullet.at(0).y = _vIdleBullet.at(0).fireY = y;

	_vIdleBullet.at(0).ySpeed = 5.0f;
	if (pattern == 1)
	{
		_vIdleBullet.at(0).speed = 5.0f;
		//_vIdleBullet.at(0).bulletImage->init("images/mBossMissile.bmp", 16, 16, true, RGB(255, 0, 255));
		_vIdleBullet.at(0).bulletImage = IMAGEMANAGER->findImage("mBossMissile");
		if (count % 5 == 0) _vIdleBullet.at(0).xSpeed = -5.0f;
		else if (count % 5 == 1) _vIdleBullet.at(0).xSpeed = -2.5f;
		else if (count % 5 == 2) _vIdleBullet.at(0).xSpeed = 0.0f;
		else if (count % 5 == 3) _vIdleBullet.at(0).xSpeed = 2.5f;
		else if (count % 5 == 4) _vIdleBullet.at(0).xSpeed = 5.0f;
		_vIdleBullet.at(0).ySpeed = 2.5f;
	}
	else if (pattern == 2)
	{
		_vIdleBullet.at(0).speed = 5.0f;
		//_vIdleBullet.at(0).bulletImage->init("images/mBossMissile.bmp", 16, 16, true, RGB(255, 0, 255));
		_vIdleBullet.at(0).bulletImage = IMAGEMANAGER->findImage("purpleCircleMissile");
		if (count % 5 == 0) _vIdleBullet.at(0).xSpeed = -5.0f, _vIdleBullet.at(0).ySpeed = 5.0f;
		else if (count % 5 == 1) _vIdleBullet.at(0).xSpeed = -2.5f, _vIdleBullet.at(0).ySpeed = 5.0f;
		else if (count % 5 == 2) _vIdleBullet.at(0).xSpeed = 0.0f, _vIdleBullet.at(0).ySpeed = 5.0f;
		else if (count % 5 == 3) _vIdleBullet.at(0).xSpeed = 2.5f, _vIdleBullet.at(0).ySpeed = 5.0f;
		else if (count % 5 == 4) _vIdleBullet.at(0).xSpeed = 5.0f, _vIdleBullet.at(0).ySpeed = 5.0f;
		_vIdleBullet.at(0).ySpeed = 2.5f;
	}
	else if (pattern == 3)
	{
		//_vIdleBullet.at(0).bulletImage->init("images/mBossMissile_02.bmp", 16, 16, true, RGB(255, 0, 255));
		_vIdleBullet.at(0).bulletImage = IMAGEMANAGER->findImage("yellowCircleMissile");
		_vIdleBullet.at(0).speed = 2.5f;
		if (count % 4 == 0)
		{
			_vIdleBullet.at(0).angle = PI / 2 + count / 4 * 0.1; // 90 
		}
		else if (count % 4 == 1)
		{
			_vIdleBullet.at(0).angle = PI + count / 4 * 0.1; // 180
		}
		else if (count % 4 == 2)
		{
			_vIdleBullet.at(0).angle = PI * 1.5 + count / 4 * 0.1; // 270
		}
		else if (count % 4 == 3)
		{
			_vIdleBullet.at(0).angle = PI * 2 + count / 4 * 0.1; // 360
		}
		_vIdleBullet.at(0).x += cosf(_vIdleBullet.at(0).angle)*(25);
		_vIdleBullet.at(0).y += -sinf(_vIdleBullet.at(0).angle)*(25);
	}

	else if (pattern == 4)
	{
		_vIdleBullet.at(0).speed = 10.0f;
		//_vIdleBullet.at(0).bulletImage->init("images/mBossMissile_03.bmp", 16, 16, true, RGB(255, 0, 255));
		_vIdleBullet.at(0).bulletImage = IMAGEMANAGER->findImage("mBossMissile_02");
		if (count % 4 == 0)
		{
			_vIdleBullet.at(0).angle = PI / 2 + count / 4 * 0.3; // 90 
		}
		else if (count % 4 == 1)
		{
			_vIdleBullet.at(0).angle = PI + count / 4 * 0.3; // 180
		}
		else if (count % 4 == 2)
		{
			_vIdleBullet.at(0).angle = PI * 1.5 + count / 4 * 0.3; // 270
		}
		else if (count % 4 == 3)
		{
			_vIdleBullet.at(0).angle = PI * 2 + count / 4 * 0.3; // 360
		}

		_vIdleBullet.at(0).x += cosf(_vIdleBullet.at(0).angle)*(50);
		_vIdleBullet.at(0).y += -sinf(_vIdleBullet.at(0).angle)*(50);

	}

	else if (pattern == 5)
	{
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.at(i).speed = 5.0f;
			_vIdleBullet.at(i).patternNum = pattern;
			//_vIdleBullet.at(i).bulletImage->init("images/mBossMissile_03.bmp", 16, 16, true, RGB(255, 0, 255));
			_vIdleBullet.at(i).bulletImage = IMAGEMANAGER->findImage("redCircleMissile");

			if (i % 17 == 0) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 90  
			else if (i % 17 == 1) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180 
			else if (i % 17 == 2) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180 
			else if (i % 17 == 3) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180 
			else if (i % 17 == 4) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180 
			else if (i % 17 == 5) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 6) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 7) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 8) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 9) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 10) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 11) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 12) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 13) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 14) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 15) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 16) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180

			_vIdleBullet.at(i).fire = true;

			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX = x;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY = y;
			_vIdleBullet.at(i).x += cosf(_vIdleBullet.at(i).angle)*(50);
			_vIdleBullet.at(i).y += -sinf(_vIdleBullet.at(i).angle)*(50);
			_vIdleBullet.at(i).rc = RectMakeCenter(_vIdleBullet.at(i).x, _vIdleBullet.at(i).y, _vIdleBullet.at(i).bulletImage->getWidth(), _vIdleBullet.at(i).bulletImage->getHeight());
			_vFireBullet.push_back(_vIdleBullet.at(i));
		}
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.erase(_vIdleBullet.begin());
		}
	}

	else if (pattern == 7)
	{
		_patternSevenTimeCount++;
		for (int i = 0; i < count; i++)
		{
			if (i % 17 == 0)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _patternSevenTimeCount * 0.5; // 90  
			else if (i % 17 == 1)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _patternSevenTimeCount * 0.5;
			else if (i % 17 == 2)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _patternSevenTimeCount * 0.5;
			else if (i % 17 == 3)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _patternSevenTimeCount * 0.5;
			else if (i % 17 == 4)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _patternSevenTimeCount * 0.5;
			else if (i % 17 == 5)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _patternSevenTimeCount * 0.5;
			else if (i % 17 == 6)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _patternSevenTimeCount * 0.5;
			else if (i % 17 == 7)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _patternSevenTimeCount * 0.5;
			else if (i % 17 == 8)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _patternSevenTimeCount * 0.5;
			else if (i % 17 == 9)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _patternSevenTimeCount * 0.5;
			else if (i % 17 == 10) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _patternSevenTimeCount * 0.5;
			else if (i % 17 == 11) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _patternSevenTimeCount * 0.5;
			else if (i % 17 == 12) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _patternSevenTimeCount * 0.5;
			else if (i % 17 == 13) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _patternSevenTimeCount * 0.5;
			else if (i % 17 == 14) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _patternSevenTimeCount * 0.5;
			else if (i % 17 == 15) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _patternSevenTimeCount * 0.5;
			else if (i % 17 == 16) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _patternSevenTimeCount * 0.5;

			_vIdleBullet.at(i).fire = true;
			_vIdleBullet.at(i).speed = 5.0f;
			_vIdleBullet.at(i).patternNum = pattern;
			//_vIdleBullet.at(i).bulletImage->init("images/mBossMissile_03.bmp", 16, 16, true, RGB(255, 0, 255));
			_vIdleBullet.at(i).bulletImage = IMAGEMANAGER->findImage("greenCircleMissile");
			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX = x;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY = y;
			_vIdleBullet.at(i).x += cosf(_vIdleBullet.at(i).angle)*(50);
			_vIdleBullet.at(i).y += -sinf(_vIdleBullet.at(i).angle)*(50);
			_vIdleBullet.at(i).rc = RectMakeCenter(_vIdleBullet.at(i).x, _vIdleBullet.at(i).y, _vIdleBullet.at(i).bulletImage->getWidth(), _vIdleBullet.at(i).bulletImage->getHeight());
			_vFireBullet.push_back(_vIdleBullet.at(i));
		}
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.erase(_vIdleBullet.begin());
		}
	}
	else if (pattern == 8)
	{
		_patternSevenTimeCount++;
		for (int i = 0; i < count; i++)
		{
			if (i % 17 == 0)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) - _patternSevenTimeCount * 0.5; // 90  
			else if (i % 17 == 1)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) - _patternSevenTimeCount * 0.5;
			else if (i % 17 == 2)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) - _patternSevenTimeCount * 0.5;
			else if (i % 17 == 3)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) - _patternSevenTimeCount * 0.5;
			else if (i % 17 == 4)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) - _patternSevenTimeCount * 0.5;
			else if (i % 17 == 5)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) - _patternSevenTimeCount * 0.5;
			else if (i % 17 == 6)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) - _patternSevenTimeCount * 0.5;
			else if (i % 17 == 7)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) - _patternSevenTimeCount * 0.5;
			else if (i % 17 == 8)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) - _patternSevenTimeCount * 0.5;
			else if (i % 17 == 9)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) - _patternSevenTimeCount * 0.5;
			else if (i % 17 == 10) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) - _patternSevenTimeCount * 0.5;
			else if (i % 17 == 11) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) - _patternSevenTimeCount * 0.5;
			else if (i % 17 == 12) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) - _patternSevenTimeCount * 0.5;
			else if (i % 17 == 13) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) - _patternSevenTimeCount * 0.5;
			else if (i % 17 == 14) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) - _patternSevenTimeCount * 0.5;
			else if (i % 17 == 15) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) - _patternSevenTimeCount * 0.5;
			else if (i % 17 == 16) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) - _patternSevenTimeCount * 0.5;

			_vIdleBullet.at(i).fire = true;
			_vIdleBullet.at(i).speed = 5.0f;
			_vIdleBullet.at(i).patternNum = 7;
			//_vIdleBullet.at(i).bulletImage->init("images/mBossMissile_03.bmp", 16, 16, true, RGB(255, 0, 255));
			_vIdleBullet.at(i).bulletImage = IMAGEMANAGER->findImage("greenCircleMissile");
			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX = x;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY = y;
			_vIdleBullet.at(i).x += cosf(_vIdleBullet.at(i).angle)*(50);
			_vIdleBullet.at(i).y += -sinf(_vIdleBullet.at(i).angle)*(50);
			_vIdleBullet.at(i).rc = RectMakeCenter(_vIdleBullet.at(i).x, _vIdleBullet.at(i).y, _vIdleBullet.at(i).bulletImage->getWidth(), _vIdleBullet.at(i).bulletImage->getHeight());
			_vFireBullet.push_back(_vIdleBullet.at(i));
		}
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.erase(_vIdleBullet.begin());
		}
	}
	else if (pattern == 9)
	{
		for (int i = 0; i < count; i++)
		{
			if (i % 4 == 0) _vIdleBullet.at(i).angle = PI * 0.75; // 90  
			else if (i % 4 == 1) _vIdleBullet.at(i).angle = PI * 1.25; // 180 
			else if (i % 4 == 2) _vIdleBullet.at(i).angle = PI * 1.75; // 270 
			else if (i % 4 == 3) _vIdleBullet.at(i).angle = PI * 2.25; // 360 
			_vIdleBullet.at(i).fire = true;
			_vIdleBullet.at(i).speed = 5.0f;
			_vIdleBullet.at(i).patternNum = 9;
			//_vIdleBullet.at(i).bulletImage->init("images/mBossMissile_03.bmp", 16, 16, true, RGB(255, 0, 255));
			_vIdleBullet.at(i).bulletImage = IMAGEMANAGER->findImage("mBossMissile_03");
			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX = x;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY = y;
			_vIdleBullet.at(i).x += cosf(_vIdleBullet.at(i).angle)*(50);
			_vIdleBullet.at(i).y += -sinf(_vIdleBullet.at(i).angle)*(50);
			_vIdleBullet.at(i).rc = RectMakeCenter(_vIdleBullet.at(i).x, _vIdleBullet.at(i).y, _vIdleBullet.at(i).bulletImage->getWidth(), _vIdleBullet.at(i).bulletImage->getHeight());
			_vFireBullet.push_back(_vIdleBullet.at(i));
		}
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.erase(_vIdleBullet.begin());
		}
	}
	else if (pattern == 10)
	{
		for (int i = 0; i < count; i++)
		{
			if (i % 4 == 0) _vIdleBullet.at(i).angle = PI / 2; // 90  
			else if (i % 4 == 1) _vIdleBullet.at(i).angle = PI; // 180 
			else if (i % 4 == 2) _vIdleBullet.at(i).angle = PI * 1.5; // 270 
			else if (i % 4 == 3) _vIdleBullet.at(i).angle = PI * 2; // 360 
			_vIdleBullet.at(i).fire = true;
			_vIdleBullet.at(i).speed = 5.0f;
			_vIdleBullet.at(i).patternNum = 9;
			//_vIdleBullet.at(i).bulletImage->init("images/mBossMissile_03.bmp", 16, 16, true, RGB(255, 0, 255));
			_vIdleBullet.at(i).bulletImage = IMAGEMANAGER->findImage("mBossMissile_03");
			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX = x;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY = y;
			_vIdleBullet.at(i).x += cosf(_vIdleBullet.at(i).angle)*(50);
			_vIdleBullet.at(i).y += -sinf(_vIdleBullet.at(i).angle)*(50);
			_vIdleBullet.at(i).rc = RectMakeCenter(_vIdleBullet.at(i).x, _vIdleBullet.at(i).y, _vIdleBullet.at(i).bulletImage->getWidth(), _vIdleBullet.at(i).bulletImage->getHeight());
			_vFireBullet.push_back(_vIdleBullet.at(i));
		}
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.erase(_vIdleBullet.begin());
		}
	}

	// 별그림
	else if (pattern == 101)
	{
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.at(i).fire = true;
			_vIdleBullet.at(i).speed = 5.0f;
			_vIdleBullet.at(i).bulletImage = IMAGEMANAGER->findImage("bossMissile_01");
			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX = x;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY = y;
			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX -= i * 8;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY += i * 25;
			_vIdleBullet.at(i).patternNum = 101;
			_vIdleBullet.at(i).rc = RectMakeCenter(_vIdleBullet.at(i).x, _vIdleBullet.at(i).y, _vIdleBullet.at(i).bulletImage->getWidth(), _vIdleBullet.at(i).bulletImage->getHeight());
			_vFireBullet.push_back(_vIdleBullet.at(i));
		}
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.erase(_vIdleBullet.begin());
		}
	}
	// 별그림
	else if (pattern == 102)
	{
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.at(i).fire = true;
			_vIdleBullet.at(i).speed = 5.0f;
			_vIdleBullet.at(i).bulletImage = IMAGEMANAGER->findImage("bossMissile_01");
			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX = x;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY = y;
			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX += i * 22;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY -= i * 18;
			_vIdleBullet.at(i).patternNum = 101;
			_vIdleBullet.at(i).rc = RectMakeCenter(_vIdleBullet.at(i).x, _vIdleBullet.at(i).y, _vIdleBullet.at(i).bulletImage->getWidth(), _vIdleBullet.at(i).bulletImage->getHeight());
			_vFireBullet.push_back(_vIdleBullet.at(i));
		}
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.erase(_vIdleBullet.begin());
		}
	}
	// 별그림
	else if (pattern == 103)
	{
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.at(i).fire = true;
			_vIdleBullet.at(i).speed = 5.0f;
			_vIdleBullet.at(i).bulletImage = IMAGEMANAGER->findImage("bossMissile_01");
			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX = x;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY = y;
			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX -= i * 25;
			_vIdleBullet.at(i).patternNum = 101;
			_vIdleBullet.at(i).rc = RectMakeCenter(_vIdleBullet.at(i).x, _vIdleBullet.at(i).y, _vIdleBullet.at(i).bulletImage->getWidth(), _vIdleBullet.at(i).bulletImage->getHeight());
			_vFireBullet.push_back(_vIdleBullet.at(i));
		}
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.erase(_vIdleBullet.begin());
		}
	}
	// 별그림
	else if (pattern == 104)
	{
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.at(i).fire = true;
			_vIdleBullet.at(i).speed = 5.0f;
			_vIdleBullet.at(i).bulletImage = IMAGEMANAGER->findImage("bossMissile_01");
			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX = x;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY = y;
			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX += i * 18;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY += i * 17;
			_vIdleBullet.at(i).patternNum = 101;
			_vIdleBullet.at(i).rc = RectMakeCenter(_vIdleBullet.at(i).x, _vIdleBullet.at(i).y, _vIdleBullet.at(i).bulletImage->getWidth(), _vIdleBullet.at(i).bulletImage->getHeight());
			_vFireBullet.push_back(_vIdleBullet.at(i));
		}
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.erase(_vIdleBullet.begin());
		}
	}
	// 별그림
	else if (pattern == 105)
	{
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.at(i).fire = true;
			_vIdleBullet.at(i).speed = 5.0f;
			_vIdleBullet.at(i).bulletImage = IMAGEMANAGER->findImage("bossMissile_01");
			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX = x;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY = y;
			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX -= i * 6;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY -= i * 25;
			_vIdleBullet.at(i).patternNum = 101;
			_vIdleBullet.at(i).rc = RectMakeCenter(_vIdleBullet.at(i).x, _vIdleBullet.at(i).y, _vIdleBullet.at(i).bulletImage->getWidth(), _vIdleBullet.at(i).bulletImage->getHeight());
			_vFireBullet.push_back(_vIdleBullet.at(i));
		}
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.erase(_vIdleBullet.begin());
		}
		_isStarPatternCountMax = false;
		_bossPatternOneTimeCount++;
		if (_bossPatternOneTimeCount % 10 == 0 ) _isStarPatternCountMax = true;
	}

	// 기본패턴
	else if (pattern == 106)
	{
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.at(i).speed = 1.0f; 
			_vIdleBullet.at(i).patternNum = pattern; 
			_vIdleBullet.at(i).bulletImage = IMAGEMANAGER->findImage("starBigMissile");

			if (i % 17 == 0) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 90  
			else if (i % 17 == 1) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180 
			else if (i % 17 == 2) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180 
			else if (i % 17 == 3) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180 
			else if (i % 17 == 4) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180 
			else if (i % 17 == 5) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 6) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 7) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 8) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 9) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 10) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 11) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 12) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 13) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 14) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 15) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180
			else if (i % 17 == 16) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)); // 180

			_vIdleBullet.at(i).fire = true;

			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX = x;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY = y;
			_vIdleBullet.at(i).x += cosf(_vIdleBullet.at(i).angle)*(50);
			_vIdleBullet.at(i).y += -sinf(_vIdleBullet.at(i).angle)*(50);
			_vIdleBullet.at(i).rc = RectMakeCenter(_vIdleBullet.at(i).x, _vIdleBullet.at(i).y, _vIdleBullet.at(i).bulletImage->getWidth(), _vIdleBullet.at(i).bulletImage->getHeight());
			_vFireBullet.push_back(_vIdleBullet.at(i));
		}


		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.erase(_vIdleBullet.begin());
		}
	}

	// 하늘에서 별떨어짐
	else if (pattern == 107)
	{
		_vIdleBullet.at(0).speed = 5.0f;
		_vIdleBullet.at(0).bulletImage = IMAGEMANAGER->findImage("greenStarMissile");
	}

	// 네모 그림
	else if (pattern == 108)
	{
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.at(i).fire = true;
			_vIdleBullet.at(i).speed = 5.0f;
			_vIdleBullet.at(i).bulletImage = IMAGEMANAGER->findImage("purpleMissile");
			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX = x;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY = y;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY += i * 10;
			_vIdleBullet.at(i).patternNum = 108;
			_vIdleBullet.at(i).rc = RectMakeCenter(_vIdleBullet.at(i).x, _vIdleBullet.at(i).y, _vIdleBullet.at(i).bulletImage->getWidth(), _vIdleBullet.at(i).bulletImage->getHeight());
			_vFireBullet.push_back(_vIdleBullet.at(i));
		}
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.erase(_vIdleBullet.begin());
		}
	}
	// 네모 그림
	else if (pattern == 109)
	{
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.at(i).fire = true;
			_vIdleBullet.at(i).speed = 5.0f;
			_vIdleBullet.at(i).bulletImage = IMAGEMANAGER->findImage("purpleMissile");
			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX = x;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY = y;
			_vIdleBullet.at(i).x  += i * 13;
			_vIdleBullet.at(i).patternNum = 108;
			_vIdleBullet.at(i).rc = RectMakeCenter(_vIdleBullet.at(i).x, _vIdleBullet.at(i).y, _vIdleBullet.at(i).bulletImage->getWidth(), _vIdleBullet.at(i).bulletImage->getHeight());
			_vFireBullet.push_back(_vIdleBullet.at(i));
		}
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.erase(_vIdleBullet.begin());
		}
	}
	// 네모 그림
	else if (pattern == 110)
	{
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.at(i).fire = true;
			_vIdleBullet.at(i).speed = 5.0f;
			_vIdleBullet.at(i).bulletImage = IMAGEMANAGER->findImage("purpleMissile");
			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX = x;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY = y;
			_vIdleBullet.at(i).y -= i * 12;
			_vIdleBullet.at(i).patternNum = 108;
			_vIdleBullet.at(i).rc = RectMakeCenter(_vIdleBullet.at(i).x, _vIdleBullet.at(i).y, _vIdleBullet.at(i).bulletImage->getWidth(), _vIdleBullet.at(i).bulletImage->getHeight());
			_vFireBullet.push_back(_vIdleBullet.at(i));
		}
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.erase(_vIdleBullet.begin());
		}
	}
	// 네모 그림
	else if (pattern == 111)
	{
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.at(i).fire = true;
			_vIdleBullet.at(i).speed = 10.0f;
			_vIdleBullet.at(i).bulletImage = IMAGEMANAGER->findImage("purpleMissile");
			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX = x;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY = y;
			_vIdleBullet.at(i).x -= i * 13;
			_vIdleBullet.at(i).patternNum = 108;
			_vIdleBullet.at(i).rc = RectMakeCenter(_vIdleBullet.at(i).x, _vIdleBullet.at(i).y, _vIdleBullet.at(i).bulletImage->getWidth(), _vIdleBullet.at(i).bulletImage->getHeight());
			_vFireBullet.push_back(_vIdleBullet.at(i));
		}
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.erase(_vIdleBullet.begin());
		}
		_bossPatternTwoTimeCount++;
		if (_bossPatternTwoTimeCount % 10 == 0)
		{
			_isRectPatternCountMax = true;
			_bossPatternTwoTimeCount = 0;
		}else _isRectPatternCountMax = false;
	}

	// 네모 떨어짐 아래로
	else if (pattern == 112)
	{
		_vIdleBullet.at(0).speed = 7.0f;
		_vIdleBullet.at(0).bulletImage = IMAGEMANAGER->findImage("purpleBigMissile");
	}

	// 네모 떨어짐 옆으로
	else if (pattern == 113)
	{
	_vIdleBullet.at(0).speed = 7.0f;
	_vIdleBullet.at(0).bulletImage = IMAGEMANAGER->findImage("purpleBigMissile");
	}


	// 원그림
	else if (pattern == 114)
	{
		_vIdleBullet.at(0).speed = 5.0f;
		_vIdleBullet.at(0).bulletImage = IMAGEMANAGER->findImage("yellowMissile");
		_vIdleBullet.at(0).angle = PI * 1.5 + count * 0.2; // 90 

		_vIdleBullet.at(0).x += cosf(_vIdleBullet.at(0).angle)*(75);
		_vIdleBullet.at(0).y += -sinf(_vIdleBullet.at(0).angle)*(75);

		_bossPatternTwoTimeCount++;
		if (_bossPatternTwoTimeCount % 40 == 0)
		{
			_isCirclePatternCountMax = true;
			_bossPatternTwoTimeCount = 0;
		}
		else  _isCirclePatternCountMax = false;
	}

	else if (pattern == 115)
	{
		_bossCirclePatternTimeCount++;
		for (int i = 0; i < count; i++)
		{
			     if (i % 17 == 0)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _bossCirclePatternTimeCount * 0.5; // 90  
			else if (i % 17 == 1)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _bossCirclePatternTimeCount * 0.5;
			else if (i % 17 == 2)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _bossCirclePatternTimeCount * 0.5;
			else if (i % 17 == 3)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _bossCirclePatternTimeCount * 0.5;
			else if (i % 17 == 4)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _bossCirclePatternTimeCount * 0.5;
			else if (i % 17 == 5)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _bossCirclePatternTimeCount * 0.5;
			else if (i % 17 == 6)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _bossCirclePatternTimeCount * 0.5;
			else if (i % 17 == 7)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _bossCirclePatternTimeCount * 0.5;
			else if (i % 17 == 8)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _bossCirclePatternTimeCount * 0.5;
			else if (i % 17 == 9)  _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _bossCirclePatternTimeCount * 0.5;
			else if (i % 17 == 10) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _bossCirclePatternTimeCount * 0.5;
			else if (i % 17 == 11) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _bossCirclePatternTimeCount * 0.5;
			else if (i % 17 == 12) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _bossCirclePatternTimeCount * 0.5;
			else if (i % 17 == 13) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _bossCirclePatternTimeCount * 0.5;
			else if (i % 17 == 14) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _bossCirclePatternTimeCount * 0.5;
			else if (i % 17 == 15) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _bossCirclePatternTimeCount * 0.5;
			else if (i % 17 == 16) _vIdleBullet.at(i).angle = PI * (0.5 + 0.125 * (i % 17)) + _bossCirclePatternTimeCount * 0.5;

			_vIdleBullet.at(i).fire = true;
			_vIdleBullet.at(i).speed = 2.0f;
			_vIdleBullet.at(i).patternNum = pattern;
			//_vIdleBullet.at(i).bulletImage->init("images/mBossMissile_03.bmp", 16, 16, true, RGB(255, 0, 255));
			_vIdleBullet.at(i).bulletImage = IMAGEMANAGER->findImage("mBossMissile_03");
			_vIdleBullet.at(i).x = _vIdleBullet.at(i).fireX = x;
			_vIdleBullet.at(i).y = _vIdleBullet.at(i).fireY = y;
			_vIdleBullet.at(i).x += cosf(_vIdleBullet.at(i).angle)*(50);
			_vIdleBullet.at(i).y += -sinf(_vIdleBullet.at(i).angle)*(50);
			_vIdleBullet.at(i).rc = RectMakeCenter(_vIdleBullet.at(i).x, _vIdleBullet.at(i).y, _vIdleBullet.at(i).bulletImage->getWidth(), _vIdleBullet.at(i).bulletImage->getHeight());
			_vFireBullet.push_back(_vIdleBullet.at(i));
		}
		for (int i = 0; i < count; i++)
		{
			_vIdleBullet.erase(_vIdleBullet.begin());
		}
	}


	if (pattern == 1 || pattern == 2 || pattern == 3 || pattern == 4   || pattern == 107  || pattern == 112 || pattern == 113 || pattern == 114)
	{
		_vIdleBullet.at(0).rc = RectMakeCenter(_vIdleBullet.at(0).x, _vIdleBullet.at(0).y, _vIdleBullet.at(0).bulletImage->getWidth(), _vIdleBullet.at(0).bulletImage->getHeight());
		_vFireBullet.push_back(_vIdleBullet.at(0));
		_vIdleBullet.erase(_vIdleBullet.begin());
	}


}

void bossMissile::move()
{
	for (int i = 0; i < _vFireBullet.size(); i++)
	{
		if (!_vFireBullet[i].fire) continue;

		if (_vFireBullet[i].patternNum == 1)
		{
			_vFireBullet[i].y += _vFireBullet[i].ySpeed;
			_vFireBullet[i].x += _vFireBullet[i].xSpeed;
			_vFireBullet[i].rc = RectMakeCenter(_vFireBullet[i].x, _vFireBullet[i].y,
				_vFireBullet[i].bulletImage->getWidth(),
				_vFireBullet[i].bulletImage->getHeight());
		}
		else if (_vFireBullet[i].patternNum == 2)
		{
			_vFireBullet[i].y += _vFireBullet[i].ySpeed;
			_vFireBullet[i].x += _vFireBullet[i].xSpeed;
			_vFireBullet[i].rc = RectMakeCenter(_vFireBullet[i].x, _vFireBullet[i].y,
				_vFireBullet[i].bulletImage->getWidth(),
				_vFireBullet[i].bulletImage->getHeight());

		}
		else if (_vFireBullet[i].patternNum == 3)
		{
			//_vFireBullet[i].angle += 0.05;
			_vFireBullet[i].x += cosf(_vFireBullet[i].angle) * _vFireBullet[i].speed;
			_vFireBullet[i].y += -sinf(_vFireBullet[i].angle) *_vFireBullet[i].speed;

			_vFireBullet[i].rc = RectMakeCenter(_vFireBullet[i].x, _vFireBullet[i].y,
				_vFireBullet[i].bulletImage->getWidth(),
				_vFireBullet[i].bulletImage->getHeight());
		}
		else if (_vFireBullet[i].patternNum == 4)
		{
			if (_patternFourTimeCount <= 3000) _patternFourTimeCount++;
			if (_patternFourTimeCount > 3000)
			{
				_vFireBullet[i].y += _vFireBullet[i].speed;

				_vFireBullet[i].rc = RectMakeCenter(_vFireBullet[i].x, _vFireBullet[i].y,
					_vFireBullet[i].bulletImage->getWidth(),
					_vFireBullet[i].bulletImage->getHeight());
			}
		}

		else if (_vFireBullet[i].patternNum == 5)
		{
			_vFireBullet[i].x += cosf(_vFireBullet[i].angle) * _vFireBullet[i].speed;
			_vFireBullet[i].y += (-sinf(_vFireBullet[i].angle)) * _vFireBullet[i].speed;
			_vFireBullet[i].rc = RectMakeCenter(_vFireBullet[i].x, _vFireBullet[i].y,
				_vFireBullet[i].bulletImage->getWidth(),
				_vFireBullet[i].bulletImage->getHeight());
		}

		else if (_vFireBullet[i].patternNum == 7)
		{
			if (_vFireBullet[i].speed < 0) _vFireBullet[i].isSpeedDecrease = false;
			else if (_vFireBullet[i].speed > 5) _vFireBullet[i].isSpeedDecrease = true;

			if (_vFireBullet[i].isSpeedDecrease) _vFireBullet[i].speed -= 0.1;
			else if (!_vFireBullet[i].isSpeedDecrease) _vFireBullet[i].speed += 0.1;

			_vFireBullet[i].x += cosf(_vFireBullet[i].angle) * _vFireBullet[i].speed;
			_vFireBullet[i].y += (-sinf(_vFireBullet[i].angle)) * _vFireBullet[i].speed;
			_vFireBullet[i].rc = RectMakeCenter(_vFireBullet[i].x, _vFireBullet[i].y,
				_vFireBullet[i].bulletImage->getWidth(),
				_vFireBullet[i].bulletImage->getHeight());
		}

		else if (_vFireBullet[i].patternNum == 9)
		{
			_vFireBullet[i].x += cosf(_vFireBullet[i].angle) * _vFireBullet[i].speed;
			_vFireBullet[i].y += -sinf(_vFireBullet[i].angle) *_vFireBullet[i].speed;

			_vFireBullet[i].rc = RectMakeCenter(_vFireBullet[i].x, _vFireBullet[i].y,
				_vFireBullet[i].bulletImage->getWidth(),
				_vFireBullet[i].bulletImage->getHeight());
		}

		// 별 위로
		if (_vFireBullet[i].patternNum == 101)
		{
			if (_isStarPatternCountMax )
			{
				_vFireBullet[i].y -= 10;
				_vFireBullet[i].rc = RectMakeCenter(_vFireBullet[i].x, _vFireBullet[i].y,
					_vFireBullet[i].bulletImage->getWidth(),
					_vFireBullet[i].bulletImage->getHeight());
			}
		}

		// 보스 기본패턴
		if (_vFireBullet[i].patternNum == 106)
		{
			_vFireBullet[i].x += cosf(_vFireBullet[i].angle) * _vFireBullet[i].speed;
			_vFireBullet[i].y += (-sinf(_vFireBullet[i].angle)) * _vFireBullet[i].speed;

			_vFireBullet[i].rc = RectMakeCenter(_vFireBullet[i].x, _vFireBullet[i].y,
				_vFireBullet[i].bulletImage->getWidth(),
				_vFireBullet[i].bulletImage->getHeight());
		}

		// 별 아래로
		if (_vFireBullet[i].patternNum == 107)
		{

			_vFireBullet[i].y += _vFireBullet[i].speed;

			_vFireBullet[i].rc = RectMakeCenter(_vFireBullet[i].x, _vFireBullet[i].y,
				_vFireBullet[i].bulletImage->getWidth(),
				_vFireBullet[i].bulletImage->getHeight());
		}

		// 네모위로
		if (_vFireBullet[i].patternNum == 108)
		{
			if (_isRectPatternCountMax)
			{
				_vFireBullet[i].y -= 10;
				_vFireBullet[i].rc = RectMakeCenter(_vFireBullet[i].x, _vFireBullet[i].y,
					_vFireBullet[i].bulletImage->getWidth(),
					_vFireBullet[i].bulletImage->getHeight());
			}
		}

		// 네모 아래로
		if (_vFireBullet[i].patternNum == 112)
		{
			_vFireBullet[i].y += _vFireBullet[i].speed;

			_vFireBullet[i].rc = RectMakeCenter(_vFireBullet[i].x, _vFireBullet[i].y,
				_vFireBullet[i].bulletImage->getWidth(),
				_vFireBullet[i].bulletImage->getHeight());
		}
		
		// 네모 오른쪽
		if (_vFireBullet[i].patternNum == 113)
		{
			_vFireBullet[i].x += _vFireBullet[i].speed;

			_vFireBullet[i].rc = RectMakeCenter(_vFireBullet[i].x, _vFireBullet[i].y,
				_vFireBullet[i].bulletImage->getWidth(),
				_vFireBullet[i].bulletImage->getHeight());
		}

		// 원위로
		if (_vFireBullet[i].patternNum == 114)
		{
			if (_isCirclePatternCountMax)
			{
				_vFireBullet[i].y -= 5;
				_vFireBullet[i].rc = RectMakeCenter(_vFireBullet[i].x, _vFireBullet[i].y,
					_vFireBullet[i].bulletImage->getWidth(),
					_vFireBullet[i].bulletImage->getHeight());
			}
		}

		else if (_vFireBullet[i].patternNum == 115)
		{
			_vFireBullet[i].x += cosf(_vFireBullet[i].angle) * _vFireBullet[i].speed;
			_vFireBullet[i].y += (-sinf(_vFireBullet[i].angle)) * _vFireBullet[i].speed;
			_vFireBullet[i].rc = RectMakeCenter(_vFireBullet[i].x, _vFireBullet[i].y,
				_vFireBullet[i].bulletImage->getWidth(),
				_vFireBullet[i].bulletImage->getHeight());
		}

		// 미사일 삭제
		if (_range < getDistance(_vFireBullet[i].fireX, _vFireBullet[i].fireY, _vFireBullet[i].x, _vFireBullet[i].y)
			|| _vFireBullet[i].rc.left < 70 || _vFireBullet[i].rc.right > 720 || _vFireBullet[i].rc.top < 30)
		{
			_vFireBullet[i].fire = false;
			//SAFE_DELETE(_vFireBullet[i].bulletImage);
			_vIdleBullet.push_back(_vFireBullet[i]);
			_vFireBullet.erase(_vFireBullet.begin() + i);
		}
	}
}

void bossMissile::removeBossMissile(int arrNum)
{
	_vIdleBullet.push_back(_vFireBullet[arrNum]);
	_vFireBullet.erase(_vFireBullet.begin() + arrNum);
}

void bossMissile::removeAllMissile()
{
	for (int i = 0; i < _vFireBullet.size(); i++)
	{
		_vIdleBullet.push_back(_vFireBullet[i]);
	}
	_vFireBullet.clear();
}
