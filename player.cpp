#include "stdafx.h"
#include "player.h"
#include"enemyManager.h"
//cpp에 인클루드 해야 진정한 상호참조...
player::player()
{
}

player::~player()
{
}

HRESULT player::init()
{

	//_player = IMAGEMANAGER->addImage("rocket", "images/rocket.bmp", WINSIZEX / 2, WINSIZEY - 200, 52, 64, true, RGB(255, 0, 255));
	_player = IMAGEMANAGER->addFrameImage("player", "images/player.bmp",WINSIZEX/2-100,WINSIZEY - 100, 240, 140, 8, 3, true, RGB(255, 0, 255));

		   _score1 = IMAGEMANAGER->addFrameImage("UIScoreNum1", "images/UIScoreNum.bmp", 935, 100, 180, 25, 10, 1, true, RGB(255, 0, 255));
		  _score10 = IMAGEMANAGER->addFrameImage("UIScoreNum10", "images/UIScoreNum.bmp", 920, 100, 180, 25, 10, 1, true, RGB(255, 0, 255));
	     _score100 = IMAGEMANAGER->addFrameImage("UIScoreNum100", "images/UIScoreNum.bmp", 905, 100, 180, 25,10,1, true, RGB(255, 0, 255));
	    _score1000 = IMAGEMANAGER->addFrameImage("UIScoreNum1000", "images/UIScoreNum.bmp", 890, 100, 180, 25,10,1, true, RGB(255, 0, 255));
	   _score10000 = IMAGEMANAGER->addFrameImage("UIScoreNum10000", "images/UIScoreNum.bmp", 875, 100, 180, 25,10,1, true, RGB(255, 0, 255));
	  _score100000 = IMAGEMANAGER->addFrameImage("UIScoreNum100000", "images/UIScoreNum.bmp", 860, 100, 180, 25,10,1, true, RGB(255, 0, 255));
	 _score1000000 = IMAGEMANAGER->addFrameImage("UIScoreNum1000000", "images/UIScoreNum.bmp", 845, 100, 180, 25,10,1, true, RGB(255, 0, 255));
	_score10000000 = IMAGEMANAGER->addFrameImage("UIScoreNum10000000", "images/UIScoreNum.bmp", 830, 100, 180, 25,10,1, true, RGB(255, 0, 255));

	_lifeCount = 5;
	_bombCount = 3;

	_maxPower = 100;
	_currentPower = 0;

	_powerBar = new progressBar;
	_powerBar->init("images/powerGauge.bmp", "images/powerGaugeBack.bmp", 850, 400, 150, 25);
	_powerBar->setGauge(_currentPower, _maxPower);

	_playerMissile = new playerMissile;
	_playerMissile->init(2000, 700);

	_miniObject = new miniObject;
	_miniObject->init();

	_playerBomb = new playerBomb;
	_playerBomb->init(300, 800);

	_bullet = new bullet;
	isIdle = true;
	
	_isHit = false;
	_playerAlpha = 255;
	return S_OK;
}

void player::release()
{
	SAFE_DELETE(_playerMissile);
	SAFE_DELETE(_miniObject);
	SAFE_DELETE(_playerBomb);
	SAFE_DELETE(_bullet);
	SAFE_DELETE(_powerBar);
}

void player::update()
{

	_playerRc = RectMakeCenter(_player->getX() + _player->getFrameWidth() / 2, _player->getY() + _player->getFrameHeight() / 2, _player->getFrameWidth(), _player->getFrameHeight());
	_playerMissile->update(_em);
	_playerBomb->update(_em);
	
	_powerBar->setGauge(_currentPower, _maxPower);
	_powerBar->update();
	if (_currentPower >= 100) _isAuto = true;
	else _isAuto = false;

	_miniObject->update(_playerRc);

	keyManager();
	playerMotion();

	updateScore();
	collision();

	if (_isFireBomb) fireBomb();
}

void player::render()
{
		//_player->frameRender(getMemDC(), _player->getX(), _player->getY(), _player->getFrameX(), _player->getFrameY()); 
		_player->alphaFrameRender(getMemDC(), _player->getX(), _player->getY(), _player->getFrameX(), _player->getFrameY(),_playerAlpha); 
	
	       _score1->frameRender(getMemDC(), _score1->getX(), _score1->getY(), _score1->getFrameX(), _score1->getFrameY());
	      _score10->frameRender(getMemDC(), _score10->getX(), _score10->getY(), _score10->getFrameX(), _score10->getFrameY());
	     _score100->frameRender(getMemDC(), _score100->getX(), _score100->getY(), _score100->getFrameX(), _score100->getFrameY());
	    _score1000->frameRender(getMemDC(), _score1000->getX(), _score1000->getY(), _score1000->getFrameX(), _score1000->getFrameY());
	   _score10000->frameRender(getMemDC(), _score10000->getX(), _score10000->getY(), _score10000->getFrameX(), _score10000->getFrameY());
	  _score100000->frameRender(getMemDC(), _score100000->getX(), _score100000->getY(), _score100000->getFrameX(), _score100000->getFrameY());
	 _score1000000->frameRender(getMemDC(), _score1000000->getX(), _score1000000->getY(), _score1000000->getFrameX(), _score1000000->getFrameY());
	_score10000000->frameRender(getMemDC(), _score10000000->getX(), _score10000000->getY(), _score10000000->getFrameX(), _score10000000->getFrameY());

	for (int i = 0; i < _lifeCount; i++)
	{
		IMAGEMANAGER->render("UIplayerLife", getMemDC(), 850 + (i *30 ), 250);
	}

	for (int i = 0; i < _bombCount; i++)
	{
		IMAGEMANAGER->render("UIplayerBomb", getMemDC(), 850 + (i * 30), 300);
	}
	_powerBar->render();
	if(isDebug) Rectangle(getMemDC(), _playerRc.left, _playerRc.top, _playerRc.right, _playerRc.bottom);

	_playerMissile->render();
	_playerBomb->render();
	_miniObject->render();
}

void player::removeMissile(int arrNum)
{
	_playerMissile->removePlayerMissile(arrNum);
}

void player::collision()
{
	// 플레이어 미사일 충돌
	for (int i = 0; i < _playerMissile->getVFireBullet().size(); i++)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			RECT rc;

			if (IntersectRect(&rc, &_playerMissile->getVFireBullet()[i].rc, &_em->getVMinion()[j]->getRect()))
			{
				_score++;
				//_playerMissile->playerMissileExplosion(i);
				_playerMissile->removePlayerMissile(i);
				_em->removeMinion(j);
				break;
			}
		}
	}

	for (int i = 0; i < _playerMissile->getVFireBullet().size(); i++)
	{
		for (int j = 0; j < _em->getVMBoss().size(); j++)
		{
			RECT rc;

			if (IntersectRect(&rc, &_playerMissile->getVFireBullet()[i].rc, &_em->getVMBoss()[j]->getRect()))
			{
				_score += 10;
				_playerMissile->removePlayerMissile(i);
				_em->getVMBoss().at(j)->setHitCount(_em->getVMBoss().at(j)->getHitCount()+1 );

				if(_em->getVMBoss().at(j)->getHitCount() >= _em->getVMBoss().at(j)->getHp()) _em->removeMBoss(j);
				break;
			}
		}
	}

	for (int i = 0; i < _playerMissile->getVFireBullet().size(); i++)
	{
		for (int j = 0; j < _em->getVBoss().size(); j++)
		{
			RECT rc;

			if (IntersectRect(&rc, &_playerMissile->getVFireBullet()[i].rc, &_em->getVBoss()[j]->getRect()))
			{
				_score += 100;
				_playerMissile->removePlayerMissile(i);
				_em->getVBoss().at(j)->setCurrentHp(_em->getVBoss().at(j)->getCurrentHp() - 5 );

				break;
			}
		}
	}

	// 플레이어 폭탄 충돌
	for (int i = 0; i < _playerBomb->getVFireBullet().size(); i++)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			RECT rc;

			if (IntersectRect(&rc, &_playerBomb->getVFireBullet()[i].rc, &_em->getVMinion()[j]->getRect()))
			{
				_score++;
				_playerBomb->removePlayerBomb(i);
				_em->removeMinion(j);
				break;
			}
		}
	}

	for (int i = 0; i < _playerBomb->getVFireBullet().size(); i++)
	{
		for (int j = 0; j < _em->getVMBoss().size(); j++)
		{
			RECT rc;

			if (IntersectRect(&rc, &_playerBomb->getVFireBullet()[i].rc, &_em->getVMBoss()[j]->getRect()))
			{
				_score += 10;
				_playerBomb->removePlayerBomb(i);
				_em->getVMBoss().at(j)->setHitCount(_em->getVMBoss().at(j)->getHitCount() + 1);

				if (_em->getVMBoss().at(j)->getHitCount() >= _em->getVMBoss().at(j)->getHp()) _em->removeMBoss(j);
				break;
			}
		}
	}

	for (int i = 0; i < _playerBomb->getVFireBullet().size(); i++)
	{
		for (int j = 0; j < _em->getVBoss().size(); j++)
		{
			RECT rc;

			if (IntersectRect(&rc, &_playerBomb->getVFireBullet()[i].rc, &_em->getVBoss()[j]->getRect()))
			{
				_score += 100;
				_playerBomb->removePlayerBomb(i);
				_em->getVBoss().at(j)->setCurrentHp(_em->getVBoss().at(j)->getCurrentHp() - 1);

				break;
			}
		}
	}
}

void player::hitDamage(float damage)
{
	if (!_isHit)
	{
		_lifeCount--;
		_isHit = true;
		_hitTime = TIMEMANAGER->getWorldTime();
		//_currentPower = 0; 피격시 초기화 
		if (_lifeCount < 0) _isPlayerDeath = true;
	}
}

void player::keyManager()
{
	//왼쪽
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player->getX() > 120)
	{
		_player->setX(_player->getX() - PLAYERSPEED);
		isLeft = true;
		isIdle = false;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		isLeft = false;
		isIdle = true;
	}

	//오른쪽
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _player->getX() < WINSIZEX/2 + 150)
	{
		_player->setX(_player->getX() + PLAYERSPEED);
		isRight = true;
		isIdle = false;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		isRight = false;
		isIdle = true;
	}

	//위
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _player->getY() > 50)
	{
		_player->setY(_player->getY() - PLAYERSPEED);
		isIdle = true;
	}

	//아래
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _player->getY() < WINSIZEY -50)
	{
		_player->setY(_player->getY() + PLAYERSPEED);
		isIdle = true;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		isIdle = true;
	}


	if (KEYMANAGER->isStayKeyDown('Z'))
	{
		_missileCount++;
		if (_missileCount %5 == 0)
		{
			_playerMissile->fire(_player->getX() + _player->getFrameWidth() / 2, _player->getY() - 50,_isAuto);

			if (_missileCount % 10 == 0)
			{
				_missileCount = 0;
				_playerMissile->leftFire(_player->getX() - _player->getFrameWidth(), _player->getY() - 50,_isAuto);
				_playerMissile->rightFire(_player->getX() + 60, _player->getY() - 50 , _isAuto);
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_createBomcCount = 0;
		if (_bombCount != 0)
		{
			_isCreateBomb = true;
			createBomb();
		}
		_bombCount--;
		if (_bombCount < 0)
		{
			_bombCount = 0;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		if(!isDebug)isDebug = true;
		else if(isDebug)isDebug = false;
	}
}

void player::playerMotion()
{
	if (_isHit)
	{
		_count++;
		if (_count % 5 == 0)
		{
			if (!_alphaCheck)
			{
				_playerAlpha = 0;
				_alphaCheck = true;

			}
			else if (_alphaCheck)
			{
				_playerAlpha = 120;
				_alphaCheck = false;
			}
		}
		if (_hitTime + 3 < TIMEMANAGER->getWorldTime())
		{
			_isHit = false;
			_playerAlpha = 255;
		}
	}
	
	if (isIdle)
	{
		_count++;
		_player->setFrameY(0);
		if (_count % 5 == 0)
		{
			_count = 0;
			if (!idleMaxFrame)
			{
				if (_index >= _player->getMaxFrameX())
				{
					idleMaxFrame = true;
				}
				_index++;
				_player->setFrameX(_index);
			}
			else if (idleMaxFrame)
			{
				_index--;
				_player->setFrameX(_index);
				if (_index < 1)
				{
					idleMaxFrame = false;
				}
			}
		}
	}

	if (isLeft)
	{
		_count++;
		_player->setFrameY(1);
		if (_count % 5 == 0)
		{
			_count = 0;
			_index++;
			_player->setFrameX(_index);
			if (_index >= _player->getMaxFrameX())
			{
				_index = 0;
			}
		}
	}

	if (isRight)
	{
		_count++;
		_player->setFrameY(2);
		if (_count % 5 == 0)
		{
			_count = 0;
			_index++;
			_player->setFrameX(_index);
			if (_index >= _player->getMaxFrameX())
			{
				_index = 0;
			}
		}
	}
}

void player::updateScore()
{
	        _score1->setFrameX(_score % 10);
	       _score10->setFrameX(_score % 100 / 10);
	      _score100->setFrameX(_score % 1000/ 100);
	     _score1000->setFrameX(_score % 10000/ 1000);
	    _score10000->setFrameX(_score % 100000/ 10000);
	   _score100000->setFrameX(_score % 1000000/ 100000);
	  _score1000000->setFrameX(_score % 10000000/ 1000000);
	 _score10000000->setFrameX(_score % 100000000/ 10000000);
}

void player::createBomb()
{
	_isFireBomb = true;
}

void player::fireBomb()
{
	_createBomcCount++;
	_playerBomb->fire(RND->getFromIntTo(100, 500), RND->getFromIntTo(100, 700));
	if (_createBomcCount > 200)
	{
		_isFireBomb = false;
		_isCreateBomb = false;
	}
}
