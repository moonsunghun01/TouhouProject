#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	_bullet = new bullet;
	_bullet->init("bullet", 20, 1500);

	_bossMissile = new bossMissile;
	_bossMissile->init(10000, 800);

	_mBossSpeed = 10;

	_bossBackEffeck = new bossBackEffect;
	_bossBackEffeck->init("bossBackEffect");

	return S_OK;
}

void enemyManager::release()
{
	SAFE_DELETE(_bullet);
}

void enemyManager::update()
{

	if (_isStartEnemyCreate) _timeCount++;

	// 미니언
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}
	moveMinion();
	_bullet->update();
	this->minionBulletFire();

	// 중간보스
	_viMBoss = _vMBoss.begin();
	for (_viMBoss; _viMBoss != _vMBoss.end(); ++_viMBoss)
	{
		(*_viMBoss)->update();
	}
	moveMBoss();
	_bossMissile->update();
	this->mBossBulletFire();

	// 보스
	_viBoss = _vBoss.begin();
	for (_viBoss; _viBoss != _vBoss.end(); ++_viBoss)
	{
		(*_viBoss)->update();
		//_bossBackEffeck->update((*_viBoss)->getImage().getX(), (*_viBoss)->getImage().getY());
	}
	moveBoss();
	_bossMissile->update();
	this->bossBulletFire();

	if (_player->getIsCreateBomb())
	{
		_bullet->removeAllMissile();
		_bossMissile->removeAllMissile();
		//_player->setIsCreateBomb(false);
	}
	
	// 전체 패턴
	pattern();

	collision();
}

void enemyManager::render()
{
	_viMinion = _vMinion.begin();

	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}

	_viMBoss = _vMBoss.begin();
	for (_viMBoss; _viMBoss != _vMBoss.end(); ++_viMBoss)
	{
		(*_viMBoss)->render();
	}

	_viBoss = _vBoss.begin();
	for (_viBoss; _viBoss != _vBoss.end(); ++_viBoss)
	{
		(*_viBoss)->render();
	}

	_bullet->render();
	_bossMissile->render();

	//_bossBackEffeck->render();
}


void enemyManager::pattern()
{
	if (_timeCount % 10 == 0)
	{
		/*if (_patternCount == 40)
		{
			createBoss(WINSIZEX / 2 - 100, 100);
		}*/

		// 세번쨰 패턴 연습
		/*if (_patternCount <4)
		{
			createMBoss(3, WINSIZEX / 2 - 350 + (_patternCount)*100, 100, 3, 0);
		}*/

		// 네번쨰 패턴 연습
		/*if (_patternCount ==1)
		{
			createMBoss(4, WINSIZEX / 2 - 100 , 100, 4, 0);
		}*/

		// 다섯번째 6번째 패턴 연습
		/*
		if (_patternCount == 1)
		{
			createMBoss(5, WINSIZEX / 2 - 100, 70, 5, 0);
		}

		if (_patternCount == 10)
		{
			createMBoss(6, WINSIZEX / 2 - 300, 70, 6, 0);
		}
		if (_patternCount == 10)
		{
			createMBoss(6, WINSIZEX / 2 + 100, 70, 6, 0);
		}*/

		// 7번쨰. 마지막 중간보스


		if (_isStartEnemyCreate)
		{
			//////////// 잡몹
			if (_patternCount < 10)
			{
				createMinion(120, 50, 1);
				//createMinion(120, 80, 1);
			}

			if (_patternCount > 10 && _patternCount < 20)
			{
				createMinion(700, 50, 2);
				//createMinion(700, 80, 2);
			}

			if (_patternCount > 25 && _patternCount < 30)
			{
				createMinion(120, 50, 3);
			}
			if (_patternCount > 25 && _patternCount < 30)
			{
				createMinion(170, 50, 3);
			}

			if (_patternCount > 29 && _patternCount < 34)
			{
				createMinion(700, 50, 4);
			}
			if (_patternCount > 29 && _patternCount < 34)
			{
				createMinion(650, 50, 4);
			}
			if (_patternCount > 36 && _patternCount < 40)
			{
				createMinion(100, 400, 5);
			}
			if (_patternCount > 38 && _patternCount < 42)
			{
				createMinion(700, 200, 6);
			}

			// 첫번째 중간 보스

			if (_patternCount >= 48 && _patternCount < 64)
			{
				if (_patternCount % 3 == 0) createMBoss(1, 120, 300, 1, _patternCount / 3 - 16);
			}

			///////// 두번째 중간 보스
			if (_patternCount == 70)
			{
				createMBoss(2, WINSIZEX / 2 - 250, 50, 2, 0);
			}
			if (_patternCount == 75)
			{
				createMBoss(2, WINSIZEX / 2, 50, 2, 0);
			}
			/*if (_patternCount == 80)
			{
				createMBoss(2, WINSIZEX / 2 - 150, 50, 2, 0);
			}*/

			if (_patternCount == 90)
			{
				createMBoss(2, WINSIZEX / 2 - 50, 50, 2, 0);
			}

			/////// 세번째 중간보스
			if (_patternCount > 95 && _patternCount < 100)
			{
				createMBoss(3, WINSIZEX / 2 - 500 + (_patternCount - 95) * 150, 100, 3, 0);
			}

			////// 네번째 중간보스
			if (_patternCount == 110)
			{
				createMBoss(4, WINSIZEX / 2 - 100, 100, 4, 0);
			}

			///// 다섯번째 여섯번째 중간
			if (_patternCount == 120)
			{
				createMBoss(5, WINSIZEX / 2 - 100, 70, 5, 0);
			}

			if (_patternCount == 130)
			{
				createMBoss(6, WINSIZEX / 2 - 300, 70, 6, 0);
			}
			if (_patternCount == 130)
			{
				createMBoss(6, WINSIZEX / 2 + 100, 70, 6, 0);
			}

			//// 일곱번쨰 마지막 중간보스
			if (_patternCount == 140)
			{
				createMBoss(7, WINSIZEX / 2 - 100, 70, 7, 0);
			}

			// 보스생성
			if (_patternCount == 220)
			{
				createBoss(WINSIZEX / 2 - 100, 100);
			}

			_patternCount++;
		}
	}
}


void enemyManager::createMinion(float x, float y, int movePattern)
{
	enemy* ufo;
	ufo = new minion;
	ufo->init("enemy1", x, y);
	ufo->setIsCreate(true);
	ufo->setMovePattern(movePattern);
	_vMinion.push_back(ufo);
}

void enemyManager::moveMinion()
{
	for (int i = 0; i < _vMinion.size(); i++)
	{
		if (!_vMinion.at(i)->getIsCreate()) continue;

		// 첫번째 패턴
		if (_vMinion.at(i)->getMovePattern() == 1)
		{
			_vMinion.at(i)->setMoveCount(_vMinion.at(i)->getMoveCount() + 0.2);

			_vMinion.at(i)->setRect(RectMakeCenter
			(_vMinion.at(i)->getRect().left + (_vMinion.at(i)->getRect().right - _vMinion.at(i)->getRect().left) / 2 + _vMinion.at(i)->getMoveCount()
				, _vMinion.at(i)->getRect().top + (_vMinion.at(i)->getRect().bottom - _vMinion.at(i)->getRect().top) / 2 + 3
				, _vMinion.at(i)->getImage().getFrameWidth(), _vMinion.at(i)->getImage().getFrameHeight()));
		}

		// 두번째 패턴
		if (_vMinion.at(i)->getMovePattern() == 2)
		{
			_vMinion.at(i)->setMoveCount(_vMinion.at(i)->getMoveCount() - 0.2);

			_vMinion.at(i)->setRect(RectMakeCenter
			(_vMinion.at(i)->getRect().left + (_vMinion.at(i)->getRect().right - _vMinion.at(i)->getRect().left) / 2 + _vMinion.at(i)->getMoveCount()
				, _vMinion.at(i)->getRect().top + (_vMinion.at(i)->getRect().bottom - _vMinion.at(i)->getRect().top) / 2 + 3
				, _vMinion.at(i)->getImage().getFrameWidth(), _vMinion.at(i)->getImage().getFrameHeight()));

		}

		// 세번째 패턴
		if (_vMinion.at(i)->getMovePattern() == 3)
		{
			if (_vMinion.at(i)->getRect().bottom > WINSIZEY / 2)
			{
				_vMinion.at(i)->setRect(RectMakeCenter
				(_vMinion.at(i)->getRect().left + (_vMinion.at(i)->getRect().right - _vMinion.at(i)->getRect().left) / 2 + 5
					, _vMinion.at(i)->getRect().top + (_vMinion.at(i)->getRect().bottom - _vMinion.at(i)->getRect().top) / 2
					, _vMinion.at(i)->getImage().getFrameWidth(), _vMinion.at(i)->getImage().getFrameHeight()));
			}

			else
			{
				_vMinion.at(i)->setRect(RectMakeCenter
				(_vMinion.at(i)->getRect().left + (_vMinion.at(i)->getRect().right - _vMinion.at(i)->getRect().left) / 2
					, _vMinion.at(i)->getRect().top + (_vMinion.at(i)->getRect().bottom - _vMinion.at(i)->getRect().top) / 2 + 5
					, _vMinion.at(i)->getImage().getFrameWidth(), _vMinion.at(i)->getImage().getFrameHeight()));
			}
		}

		// 네번쨰 패턴
		if (_vMinion.at(i)->getMovePattern() == 4)
		{
			if (_vMinion.at(i)->getRect().bottom > WINSIZEY / 2 - 200)
			{
				_vMinion.at(i)->setRect(RectMakeCenter
				(_vMinion.at(i)->getRect().left + (_vMinion.at(i)->getRect().right - _vMinion.at(i)->getRect().left) / 2 - 7
					, _vMinion.at(i)->getRect().top + (_vMinion.at(i)->getRect().bottom - _vMinion.at(i)->getRect().top) / 2
					, _vMinion.at(i)->getImage().getFrameWidth(), _vMinion.at(i)->getImage().getFrameHeight()));
			}
			else
			{
				_vMinion.at(i)->setRect(RectMakeCenter
				(_vMinion.at(i)->getRect().left + (_vMinion.at(i)->getRect().right - _vMinion.at(i)->getRect().left) / 2
					, _vMinion.at(i)->getRect().top + (_vMinion.at(i)->getRect().bottom - _vMinion.at(i)->getRect().top) / 2 + 10
					, _vMinion.at(i)->getImage().getFrameWidth(), _vMinion.at(i)->getImage().getFrameHeight()));
			}
		}

		// 다섯번째 패턴
		if (_vMinion.at(i)->getMovePattern() == 5)
		{
			if (_vMinion.at(i)->getRect().right < WINSIZEX / 2 - 100)
			{
				_vMinion.at(i)->setRect(RectMakeCenter
				(_vMinion.at(i)->getRect().left + (_vMinion.at(i)->getRect().right - _vMinion.at(i)->getRect().left) / 2 + 3
					, _vMinion.at(i)->getRect().top + (_vMinion.at(i)->getRect().bottom - _vMinion.at(i)->getRect().top) / 2
					, _vMinion.at(i)->getImage().getFrameWidth(), _vMinion.at(i)->getImage().getFrameHeight()));
			}
			else
			{
				_vMinion.at(i)->setRect(RectMakeCenter
				(_vMinion.at(i)->getRect().left + (_vMinion.at(i)->getRect().right - _vMinion.at(i)->getRect().left) / 2 + 7
					, _vMinion.at(i)->getRect().top + (_vMinion.at(i)->getRect().bottom - _vMinion.at(i)->getRect().top) / 2 - 3
					, _vMinion.at(i)->getImage().getFrameWidth(), _vMinion.at(i)->getImage().getFrameHeight()));
			}
		}

		// 여섯번째 패턴
		if (_vMinion.at(i)->getMovePattern() == 6)
		{
			if (_vMinion.at(i)->getRect().left > WINSIZEX / 2)
			{
				_vMinion.at(i)->setRect(RectMakeCenter
				(_vMinion.at(i)->getRect().left + (_vMinion.at(i)->getRect().right - _vMinion.at(i)->getRect().left) / 2 - 3
					, _vMinion.at(i)->getRect().top + (_vMinion.at(i)->getRect().bottom - _vMinion.at(i)->getRect().top) / 2
					, _vMinion.at(i)->getImage().getFrameWidth(), _vMinion.at(i)->getImage().getFrameHeight()));
			}
			else
			{
				_vMinion.at(i)->setRect(RectMakeCenter
				(_vMinion.at(i)->getRect().left + (_vMinion.at(i)->getRect().right - _vMinion.at(i)->getRect().left) / 2 - 7
					, _vMinion.at(i)->getRect().top + (_vMinion.at(i)->getRect().bottom - _vMinion.at(i)->getRect().top) / 2 - 3
					, _vMinion.at(i)->getImage().getFrameWidth(), _vMinion.at(i)->getImage().getFrameHeight()));
			}
		}


		if (_vMinion.at(i)->getRect().right > 720 || _vMinion.at(i)->getRect().left < 70 || _vMinion.at(i)->getRect().top < 30)
		{
			_vMinion.erase(_vMinion.begin() + i);
		}
	}

}

void enemyManager::minionBulletFire()
{
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		_bulletCount++;
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2,
				getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2,
					_player->getPlayerImage()->getX() + _player->getPlayerImage()->getWidth() / 2, _player->getPlayerImage()->getY())
				, 5.0f);

		}
	}
	for (int i = 0; i < _bullet->getVBullet().size(); i++)
	{
		if (_bullet->getVBullet()[i].rc.right > 700 || _bullet->getVBullet()[i].rc.left < 70)
		{
			_bullet->removeMissile(i);
		}
	}
}


void enemyManager::removeMinion(int arrNum)
{
	_vMinion.erase(_vMinion.begin() + arrNum);

}

// 중간 보스
void enemyManager::createMBoss(int bossNum, float x, float y, int movePattern, int arrNum)
{
	middleBoss* m_boss;
	m_boss = new middleBoss;
	if (bossNum == 1) m_boss->init("m_boss", x, y);
	else if (bossNum == 2)
	{
		m_boss->init("m_boss_02", x, y);
		m_boss->setAngle(PI);
		m_boss->setCenterX(x);
		m_boss->setCenterY(y);
	}

	else if (bossNum == 3)
	{
		m_boss->init("m_boss_03", x, y);
	}

	else if (bossNum == 4)
	{
		m_boss->init("m_boss_green", x, y);
	}

	else if (bossNum == 5)
	{
		m_boss->init("m_boss_02", x, y);
		m_boss->setAngle(PI);
		m_boss->setCenterX(x);
		m_boss->setCenterY(y);
	}
	else if (bossNum == 6)
	{
		m_boss->init("m_boss_02", x, y);
	}

	else if (bossNum == 7)
	{
		m_boss->init("enemy1", x, y);
	}

	m_boss->setHp(20);
	m_boss->setBossNum(bossNum);
	m_boss->setIsCreate(true);
	m_boss->setMovePattern(movePattern);
	m_boss->setMBossStatus(1);
	m_boss->setArrNum(arrNum);
	_vMBoss.push_back(m_boss);
}

void enemyManager::moveMBoss()
{
	for (int i = 0; i < _vMBoss.size(); i++)
	{
		// 첫번째 패턴			-- 순서대로 가로 배열
		if (_vMBoss.at(i)->getMovePattern() == 1)
		{
			if (_vMBoss.at(i)->getRect().right < 700 - (_vMBoss.at(i)->getArrNum() * 100))
			{
				_vMBoss.at(i)->setRect(RectMakeCenter
				(_vMBoss.at(i)->getRect().left + (_vMBoss.at(i)->getRect().right - _vMBoss.at(i)->getRect().left) / 2 + (_mBossSpeed - i)
					, _vMBoss.at(i)->getRect().top + (_vMBoss.at(i)->getRect().bottom - _vMBoss.at(i)->getRect().top) / 2
					, _vMBoss.at(i)->getImage().getFrameWidth(), _vMBoss.at(i)->getImage().getFrameHeight()));
			}
			else if (_vMBoss.at(i)->getRect().right >= 700 - (_vMBoss.at(i)->getArrNum() * 100))
			{
				_vMBoss.at(i)->setMBossStatus(2);
				_vMBoss.at(i)->setIsFire(true);
			}

			//if (_timeCount - (i*5)  > 200)
			if (_timeCount - (i * 5) > 650)
			{
				_vMBoss.at(i)->setRect(RectMakeCenter
				(_vMBoss.at(i)->getRect().left + (_vMBoss.at(i)->getRect().right - _vMBoss.at(i)->getRect().left) / 2
					, _vMBoss.at(i)->getRect().top + (_vMBoss.at(i)->getRect().bottom - _vMBoss.at(i)->getRect().top) / 2 - 5
					, _vMBoss.at(i)->getImage().getFrameWidth(), _vMBoss.at(i)->getImage().getFrameHeight()));
			}
		}

		// 두번째 패턴			-- 타원으로 돔 
		if (_vMBoss.at(i)->getMovePattern() == 2)
		{
			if (!_vMBoss.at(i)->getIsCircle())
			{
				_vMBoss.at(i)->setRect(RectMakeCenter
				(_vMBoss.at(i)->getRect().left + (_vMBoss.at(i)->getRect().right - _vMBoss.at(i)->getRect().left) / 2
					, _vMBoss.at(i)->getRect().top + (_vMBoss.at(i)->getRect().bottom - _vMBoss.at(i)->getRect().top) / 2 + 5
					, _vMBoss.at(i)->getImage().getFrameWidth(), _vMBoss.at(i)->getImage().getFrameHeight()));

				if (_vMBoss.at(i)->getRect().bottom > 300) _vMBoss.at(i)->setIsCircle(true);
			}
			else if (_vMBoss.at(i)->getIsCircle())
			{
				if (_vMBoss.at(i)->getRect().bottom <= 299)
				{
					_vMBoss.at(i)->setRect(RectMakeCenter
					(_vMBoss.at(i)->getRect().left + (_vMBoss.at(i)->getRect().right - _vMBoss.at(i)->getRect().left) / 2
						, _vMBoss.at(i)->getRect().top + (_vMBoss.at(i)->getRect().bottom - _vMBoss.at(i)->getRect().top) / 2 - 5
						, _vMBoss.at(i)->getImage().getFrameWidth(), _vMBoss.at(i)->getImage().getFrameHeight()));
				}
				else if (_vMBoss.at(i)->getRect().bottom > 300)
				{
					_vMBoss.at(i)->setAngle(_vMBoss.at(i)->getAngle() + 0.05);
					_vMBoss.at(i)->setRect(RectMakeCenter
					(_vMBoss.at(i)->getRect().left + (_vMBoss.at(i)->getRect().right - _vMBoss.at(i)->getRect().left) / 2 + cosf(_vMBoss.at(i)->getAngle()) * 5
						, _vMBoss.at(i)->getRect().top + (_vMBoss.at(i)->getRect().bottom - _vMBoss.at(i)->getRect().top) / 2 + (-sinf(_vMBoss.at(i)->getAngle()) * 5)
						, _vMBoss.at(i)->getImage().getFrameWidth(), _vMBoss.at(i)->getImage().getFrameHeight()));
				}
				_vMBoss.at(i)->setIsFire(true);
			}
		}

		// 세번째 패턴		-- 내려왔다 올라감
		if (_vMBoss.at(i)->getMovePattern() == 3)
		{
			//if (_timeCount - (i * 5) > 200)
			if (_timeCount - (i * 5) > 1200)
			{
				_vMBoss.at(i)->setRect(RectMakeCenter
				(_vMBoss.at(i)->getRect().left + (_vMBoss.at(i)->getRect().right - _vMBoss.at(i)->getRect().left) / 2
					, _vMBoss.at(i)->getRect().top + (_vMBoss.at(i)->getRect().bottom - _vMBoss.at(i)->getRect().top) / 2 - 5
					, _vMBoss.at(i)->getImage().getFrameWidth(), _vMBoss.at(i)->getImage().getFrameHeight()));
			}
			else if (_vMBoss.at(i)->getRect().bottom < 300)
				_vMBoss.at(i)->setRect(RectMakeCenter
				(_vMBoss.at(i)->getRect().left + (_vMBoss.at(i)->getRect().right - _vMBoss.at(i)->getRect().left) / 2
					, _vMBoss.at(i)->getRect().top + (_vMBoss.at(i)->getRect().bottom - _vMBoss.at(i)->getRect().top) / 2 + 5
					, _vMBoss.at(i)->getImage().getFrameWidth(), _vMBoss.at(i)->getImage().getFrameHeight()));
			else
			{
				_vMBoss.at(i)->setMBossStatus(3);
				_vMBoss.at(i)->setIsFire(true);
			}
		}

		// 네번째 패턴		-- 내려왔다 올라감
		if (_vMBoss.at(i)->getMovePattern() == 4)
		{
			//if (_timeCount > 100)
			if (_timeCount > 1250)
			{
				_vMBoss.at(i)->setRect(RectMakeCenter
				(_vMBoss.at(i)->getRect().left + (_vMBoss.at(i)->getRect().right - _vMBoss.at(i)->getRect().left) / 2
					, _vMBoss.at(i)->getRect().top + (_vMBoss.at(i)->getRect().bottom - _vMBoss.at(i)->getRect().top) / 2 - 5
					, _vMBoss.at(i)->getImage().getFrameWidth(), _vMBoss.at(i)->getImage().getFrameHeight()));
			}
			else if (_vMBoss.at(i)->getRect().bottom < 300)
				_vMBoss.at(i)->setRect(RectMakeCenter
				(_vMBoss.at(i)->getRect().left + (_vMBoss.at(i)->getRect().right - _vMBoss.at(i)->getRect().left) / 2
					, _vMBoss.at(i)->getRect().top + (_vMBoss.at(i)->getRect().bottom - _vMBoss.at(i)->getRect().top) / 2 + 5
					, _vMBoss.at(i)->getImage().getFrameWidth(), _vMBoss.at(i)->getImage().getFrameHeight()));
			else if (_vMBoss.at(i)->getRect().bottom >= 300)
			{
				_vMBoss.at(i)->setIsFire(true);
			}
		}

		// 다섯번쨰 패턴   -- 내려갔다 반원그리고 멈췄다가 다시 반원
		if (_vMBoss.at(i)->getMovePattern() == 5)
		{
			if (!_vMBoss.at(i)->getIsCircle())
			{
				_vMBoss.at(i)->setRect(RectMakeCenter
				(_vMBoss.at(i)->getRect().left + (_vMBoss.at(i)->getRect().right - _vMBoss.at(i)->getRect().left) / 2
					, _vMBoss.at(i)->getRect().top + (_vMBoss.at(i)->getRect().bottom - _vMBoss.at(i)->getRect().top) / 2 + 5
					, _vMBoss.at(i)->getImage().getFrameWidth(), _vMBoss.at(i)->getImage().getFrameHeight()));

				if (_vMBoss.at(i)->getRect().bottom > 150) _vMBoss.at(i)->setIsCircle(true);
			}
			else if (_vMBoss.at(i)->getIsCircle())
			{
				if (_vMBoss.at(i)->getRect().bottom <= 120)
				{
					_vMBoss.at(i)->setRect(RectMakeCenter
					(_vMBoss.at(i)->getRect().left + (_vMBoss.at(i)->getRect().right - _vMBoss.at(i)->getRect().left) / 2
						, _vMBoss.at(i)->getRect().top + (_vMBoss.at(i)->getRect().bottom - _vMBoss.at(i)->getRect().top) / 2 - 5
						, _vMBoss.at(i)->getImage().getFrameWidth(), _vMBoss.at(i)->getImage().getFrameHeight()));
				}
				else if (_vMBoss.at(i)->getRect().bottom > 120)
				{
					// 반원그리고 하단에서 멈춤 
					//if (_timeCount < 100 || _timeCount > 200)
					if (_timeCount < 1300 || _timeCount > 1400)
					{
						_vMBoss.at(i)->setAngle(_vMBoss.at(i)->getAngle() + 0.05);
						_vMBoss.at(i)->setRect(RectMakeCenter
						(_vMBoss.at(i)->getRect().left + (_vMBoss.at(i)->getRect().right - _vMBoss.at(i)->getRect().left) / 2 + cosf(_vMBoss.at(i)->getAngle()) * 5
							, _vMBoss.at(i)->getRect().top + (_vMBoss.at(i)->getRect().bottom - _vMBoss.at(i)->getRect().top) / 2 + (-sinf(_vMBoss.at(i)->getAngle()) * 5)
							, _vMBoss.at(i)->getImage().getFrameWidth(), _vMBoss.at(i)->getImage().getFrameHeight()));
					}
					else _vMBoss.at(i)->setIsFire(true);
				}
			}
		}

		// 여섯번째 패턴		-- 내려왔다 올라감
		if (_vMBoss.at(i)->getMovePattern() == 6)
		{
			//if (_timeCount > 250)
			if (_timeCount > 1450)
			{
				_vMBoss.at(i)->setRect(RectMakeCenter
				(_vMBoss.at(i)->getRect().left + (_vMBoss.at(i)->getRect().right - _vMBoss.at(i)->getRect().left) / 2
					, _vMBoss.at(i)->getRect().top + (_vMBoss.at(i)->getRect().bottom - _vMBoss.at(i)->getRect().top) / 2 - 5
					, _vMBoss.at(i)->getImage().getFrameWidth(), _vMBoss.at(i)->getImage().getFrameHeight()));
			}
			else if (_vMBoss.at(i)->getRect().bottom < 150)
				_vMBoss.at(i)->setRect(RectMakeCenter
				(_vMBoss.at(i)->getRect().left + (_vMBoss.at(i)->getRect().right - _vMBoss.at(i)->getRect().left) / 2
					, _vMBoss.at(i)->getRect().top + (_vMBoss.at(i)->getRect().bottom - _vMBoss.at(i)->getRect().top) / 2 + 5
					, _vMBoss.at(i)->getImage().getFrameWidth(), _vMBoss.at(i)->getImage().getFrameHeight()));
			else if (_vMBoss.at(i)->getRect().bottom >= 150)
			{
				_vMBoss.at(i)->setIsFire(true);
			}
		}

		// 일곱번째 패턴		-- 내려왔다 올라감
		if (_vMBoss.at(i)->getMovePattern() == 7)
		{
			//if (_timeCount > 350)
			if (_timeCount > 1800)
			{
				_vMBoss.at(i)->setRect(RectMakeCenter
				(_vMBoss.at(i)->getRect().left + (_vMBoss.at(i)->getRect().right - _vMBoss.at(i)->getRect().left) / 2
					, _vMBoss.at(i)->getRect().top + (_vMBoss.at(i)->getRect().bottom - _vMBoss.at(i)->getRect().top) / 2 - 5
					, _vMBoss.at(i)->getImage().getFrameWidth(), _vMBoss.at(i)->getImage().getFrameHeight()));
			}
			else
				if (_vMBoss.at(i)->getRect().bottom < 150)
					_vMBoss.at(i)->setRect(RectMakeCenter
					(_vMBoss.at(i)->getRect().left + (_vMBoss.at(i)->getRect().right - _vMBoss.at(i)->getRect().left) / 2
						, _vMBoss.at(i)->getRect().top + (_vMBoss.at(i)->getRect().bottom - _vMBoss.at(i)->getRect().top) / 2 + 5
						, _vMBoss.at(i)->getImage().getFrameWidth(), _vMBoss.at(i)->getImage().getFrameHeight()));
				else if (_vMBoss.at(i)->getRect().bottom >= 150)
				{
					_vMBoss.at(i)->setIsFire(true);
				}
		}

		// 맵 밖으로 나가면 삭제
		if (_vMBoss.at(i)->getRect().right > 720 || _vMBoss.at(i)->getRect().left < 70 || _vMBoss.at(i)->getRect().top < 30)
		{
			//SAFE_DELETE(_vMBoss.at(i));
			_vMBoss.erase(_vMBoss.begin() + i);
		}
	}
}

void enemyManager::mBossBulletFire()
{

	for (int i = 0; i < _vMBoss.size(); i++)
	{
		if (_vMBoss[i]->getIsFire())
		{
			if (_vMBoss[i]->getBossNum() == 1)
			{
				if (_vMBoss[i]->getMissileCount() < 25)
				{
					RECT rc = _vMBoss[i]->getRect();
					_bossMissile->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2, _vMBoss[i]->getMissileCount(), _vMBoss[i]->getBossNum());
					_vMBoss[i]->setMissileCount(_vMBoss[i]->getMissileCount() + 1);
				}
			}
			else if (_vMBoss[i]->getBossNum() == 2)
			{
				if (_vMBoss[i]->getMissileCount() < 500)
				{
					RECT rc = _vMBoss[i]->getRect();
					_bossMissile->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2, _vMBoss[i]->getMissileCount(), _vMBoss[i]->getBossNum());
					_vMBoss[i]->setMissileCount(_vMBoss[i]->getMissileCount() + 1);
				}
			}
			else if (_vMBoss[i]->getBossNum() == 3)
			{
				if (_vMBoss[i]->getMissileCount() < 150)
				{
					if (_timeCount % 2 == 0)
					{
						RECT rc = _vMBoss[i]->getRect();
						_bossMissile->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2, _vMBoss[i]->getMissileCount(), _vMBoss[i]->getBossNum());
						_vMBoss[i]->setMissileCount(_vMBoss[i]->getMissileCount() + 1);
					}

				}
			}

			else if (_vMBoss[i]->getBossNum() == 4)
			{
				if (_vMBoss[i]->getMissileCount() < 25)
				{
					RECT rc = _vMBoss[i]->getRect();
					_bossMissile->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2, _vMBoss[i]->getMissileCount(), _vMBoss[i]->getBossNum());
					_bossMissile->fire(rc.left + (rc.right - rc.left) / 2 - 200, rc.bottom + (rc.top - rc.bottom) / 2 + 200, _vMBoss[i]->getMissileCount(), _vMBoss[i]->getBossNum());
					_bossMissile->fire(rc.left + (rc.right - rc.left) / 2 + 200, rc.bottom + (rc.top - rc.bottom) / 2 + 200, _vMBoss[i]->getMissileCount(), _vMBoss[i]->getBossNum());
					_bossMissile->fire(rc.left + (rc.right - rc.left) / 2 - 200, rc.bottom + (rc.top - rc.bottom) / 2 - 150, _vMBoss[i]->getMissileCount(), _vMBoss[i]->getBossNum());
					_bossMissile->fire(rc.left + (rc.right - rc.left) / 2 + 200, rc.bottom + (rc.top - rc.bottom) / 2 - 150, _vMBoss[i]->getMissileCount(), _vMBoss[i]->getBossNum());
					_vMBoss[i]->setMissileCount(_vMBoss[i]->getMissileCount() + 1);
				}
			}
			else if (_vMBoss[i]->getBossNum() == 5)
			{
				if (_vMBoss[i]->getMissileCount() < 100)
				{
					if (_vMBoss[i]->getMissileCount() % 10 == 0)
					{
						RECT rc = _vMBoss[i]->getRect();
						_bossMissile->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2, 17, _vMBoss[i]->getBossNum());

					}
					_vMBoss[i]->setMissileCount(_vMBoss[i]->getMissileCount() + 1);
				}
			}
			else if (_vMBoss[i]->getBossNum() == 6)
			{
				if (_vMBoss[i]->getMissileCount() < 100)
				{
					if (_vMBoss[i]->getMissileCount() % 10 == 0)
					{
						RECT rc = _vMBoss[i]->getRect();
						_bossMissile->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2, 17, 5);
					}
					_vMBoss[i]->setMissileCount(_vMBoss[i]->getMissileCount() + 1);
				}
			}

			else if (_vMBoss[i]->getBossNum() == 7)
			{
				_vMBoss[i]->setMissileCount(_vMBoss[i]->getMissileCount() + 1);
				if (_vMBoss[i]->getMissileCount() < 40 || (_vMBoss[i]->getMissileCount() >= 160 && _vMBoss[i]->getMissileCount() < 200) || (_vMBoss[i]->getMissileCount() >= 320 && _vMBoss[i]->getMissileCount() < 360))
				{
					RECT rc = _vMBoss[i]->getRect();
					if (_vMBoss[i]->getMissileCount() % 5 == 0)
						_bossMissile->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2, 4, 9);
					if (_vMBoss[i]->getMissileCount() % 5 == 0)
					{
						_bossMissile->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2, 17, _vMBoss[i]->getBossNum());
					}
				}
				else if ((_vMBoss[i]->getMissileCount() >= 80 && _vMBoss[i]->getMissileCount() < 120) || (_vMBoss[i]->getMissileCount() >= 240 && _vMBoss[i]->getMissileCount() < 280))
				{
					RECT rc = _vMBoss[i]->getRect();
					if (_vMBoss[i]->getMissileCount() % 5 == 0)
						_bossMissile->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2, 4, 10);
					if (_vMBoss[i]->getMissileCount() % 5 == 0)
					{
						_bossMissile->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2, 17, 8);
					}
				}
			}
		}
	}
}
void enemyManager::removeMBoss(int arrNum)
{
	_vMBoss.erase(_vMBoss.begin() + arrNum);
}

void enemyManager::createBoss(float x, float y)
{
	boss* _boss;
	_boss = new boss;
	_boss->init("boss", x, y);
	_boss->setBossNum(101);
	_boss->setIsCreate(true);
	_boss->setBossStatus(1);
	_boss->setBossDirection(3);
	_vBoss.push_back(_boss);

	_timeCount = 0;

}

void enemyManager::moveBoss()
{
	for (int i = 0; i < _vBoss.size(); i++)
	{
		_vBoss.at(i)->setBossMoveCount(_vBoss[i]->getBossMoveCount() + 1);

		if(_vBoss.at(i)->getBossDirection() == 3)
		{
			if (_vBoss.at(i)->getRect().bottom < 300 )
			{
				_vBoss[i]->setBossStatus(1);
				_vBoss.at(i)->setRect(RectMakeCenter
				(_vBoss.at(i)->getRect().left + (_vBoss.at(i)->getRect().right - _vBoss.at(i)->getRect().left) / 2
					, _vBoss.at(i)->getRect().top + (_vBoss.at(i)->getRect().bottom - _vBoss.at(i)->getRect().top) / 2 + 5
					, _vBoss.at(i)->getImage().getFrameWidth(), _vBoss.at(i)->getImage().getFrameHeight()));
			}
			if (_vBoss.at(i)->getRect().bottom >= 300 && _timeCount <300)
			{
				
				_vBoss.at(i)->setBossDirection(4);
				_vBoss.at(i)->setIsFire(true);
				_vBoss[i]->setBossStatus(4);
			}
		}
		
		else if (_vBoss.at(i)->getBossDirection() == 4 && _timeCount > 500)
		{
			if (_vBoss.at(i)->getRect().left > 200)
			{
				_vBoss[i]->setBossStatus(2);
				_vBoss.at(i)->setRect(RectMakeCenter
				(_vBoss.at(i)->getRect().left + (_vBoss.at(i)->getRect().right - _vBoss.at(i)->getRect().left) / 2 - 5
					, _vBoss.at(i)->getRect().top + (_vBoss.at(i)->getRect().bottom - _vBoss.at(i)->getRect().top) / 2 
					, _vBoss.at(i)->getImage().getFrameWidth(), _vBoss.at(i)->getImage().getFrameHeight()));
			}
			if (_vBoss.at(i)->getRect().left <= 200)
			{
				_vBoss[i]->setBossStatus(4);
				_vBoss.at(i)->setBossDirection(1);
			}
		}
		
		else if (_vBoss.at(i)->getBossDirection() == 1)
		{
			if (_vBoss.at(i)->getRect().top > 100 && _timeCount > 770)
			{
				_vBoss[i]->setBossStatus(1);
				_vBoss.at(i)->setRect(RectMakeCenter
				(_vBoss.at(i)->getRect().left + (_vBoss.at(i)->getRect().right - _vBoss.at(i)->getRect().left) / 2 
					, _vBoss.at(i)->getRect().top + (_vBoss.at(i)->getRect().bottom - _vBoss.at(i)->getRect().top) / 2 - 5
					, _vBoss.at(i)->getImage().getFrameWidth(), _vBoss.at(i)->getImage().getFrameHeight()));
			}
			if (_vBoss.at(i)->getRect().top <= 100)
			{
				_vBoss.at(i)->setBossDirection(2);
				_vBoss[i]->setBossStatus(1);
			}
		}

		
		else if (_vBoss.at(i)->getBossDirection() == 2)
		{
			if (_vBoss.at(i)->getRect().right < 650 )
			{
				_vBoss.at(i)->setBossStatus(3);
				_vBoss.at(i)->setRect(RectMakeCenter
				(_vBoss.at(i)->getRect().left + (_vBoss.at(i)->getRect().right - _vBoss.at(i)->getRect().left) / 2 + 5
					, _vBoss.at(i)->getRect().top + (_vBoss.at(i)->getRect().bottom - _vBoss.at(i)->getRect().top) / 2 
					, _vBoss.at(i)->getImage().getFrameWidth(), _vBoss.at(i)->getImage().getFrameHeight()));
			}
			if (_vBoss.at(i)->getRect().right >= 650 && _timeCount > 920)
			{
				_vBoss.at(i)->setBossDirection(3);
				_vBoss.at(i)->setBossStatus(1);
			}
		}

		if (_timeCount > 1100)
		{
			if (_vBoss.at(i)->getRect().left > 400)
			{
				_vBoss.at(i)->setRect(RectMakeCenter
				(_vBoss.at(i)->getRect().left + (_vBoss.at(i)->getRect().right - _vBoss.at(i)->getRect().left) / 2 - 5
					, _vBoss.at(i)->getRect().top + (_vBoss.at(i)->getRect().bottom - _vBoss.at(i)->getRect().top) / 2
					, _vBoss.at(i)->getImage().getFrameWidth(), _vBoss.at(i)->getImage().getFrameHeight()));
			}
		}

		if (_timeCount > 1300) _vBoss.at(i)->setIsCircleMax(false);
		
		if (_timeCount > 1500)
		{
			_timeCount = 0;
			_vBoss.at(i)->setMissileCount(0);

			_vBoss.at(i)->setStarMissileCount(0);
			_vBoss.at(i)->setIsStarMax(false);

			_vBoss.at(i)->setRectMissileCount(0);
			_vBoss.at(i)->setIsRectMax(false);

			_vBoss.at(i)->setCircleMissileCount(0);
			_vBoss.at(i)->setIsCircleMax(false);
		}
	}

}

void enemyManager::bossBulletFire()
{
	for (int i = 0; i < _vBoss.size(); i++)
	{
		_vBoss[i]->setMissileCount(_vBoss[i]->getMissileCount() + 1);
		if (_vBoss[i]->getIsFire())
		{
			if (_timeCount % 3 == 0)
			{
				// 보스 기본 패턴
				if (_vBoss[i]->getMissileCount() < 5000)
				{
					if (_vBoss[i]->getMissileCount() % 10 == 0)
					{
						RECT rc = _vBoss[i]->getRect();
						_bossMissile->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2, 17, _vBoss[i]->getBossNum() + 5);
					}
				}
			}

			// 별그리기
			if (_timeCount % 10 == 0)
			{
				if (_vBoss[i]->getStarMissileCount() < 10)
				{
					RECT rc = _vBoss[i]->getRect();

					//1-4
					_bossMissile->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) * 2, _vBoss[i]->getStarMissileCount(), _vBoss[i]->getBossNum());

					//4-2
					_bossMissile->fire(rc.left - (rc.right - rc.left) + 32, rc.bottom - (rc.top - rc.bottom) * 2 - 60, _vBoss[i]->getStarMissileCount(), _vBoss[i]->getBossNum() + 1);

					//2-5
					_bossMissile->fire(rc.left + (rc.right - rc.left) / 2 + 92, rc.bottom - (rc.bottom - rc.top) / 2 - 45, _vBoss[i]->getStarMissileCount(), _vBoss[i]->getBossNum() + 2);

					//5-3
					_bossMissile->fire(rc.left + (rc.right - rc.left) / 2 - 95, rc.bottom - (rc.bottom - rc.top) / 2 - 30, _vBoss[i]->getStarMissileCount(), _vBoss[i]->getBossNum() + 3);

					//3-1
					_bossMissile->fire(rc.left - (rc.right - rc.left) + 143, rc.bottom - (rc.top - rc.bottom) * 2 - 55, _vBoss[i]->getStarMissileCount(), _vBoss[i]->getBossNum() + 4);				

					if (_vBoss[i]->getStarMissileCount() % 10 == 0)
						_vBoss[i]->setIsStarMax(true);

					_vBoss[i]->setStarMissileCount(_vBoss[i]->getStarMissileCount() + 1);
				}
			}
			// 별 내리기
			if (_vBoss[i]->getIsStarMax())
			{
				if (_vBoss[i]->getMissileCount() > 250 && _vBoss[i]->getMissileCount() < 450)
				{
					_vBoss[i]->setBossStatus(1);
					if (_vBoss[i]->getMissileCount() % 5 == 0)
					{
						RECT rc = _vBoss[i]->getRect();
						_bossMissile->fire(RND->getFromIntTo(100, 700), 100, 17, _vBoss[i]->getBossNum() + 6);
					}
				}
			}

			// 네모 그리기
			if (_timeCount % 10 == 0)
			{
				if (_vBoss[i]->getRectMissileCount() < 10 && _timeCount > 520)
				{
					RECT rc = _vBoss[i]->getRect();
					_bossMissile->fire(rc.left - (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom), _vBoss[i]->getRectMissileCount(), _vBoss[i]->getBossNum() + 7);
					_bossMissile->fire(rc.left - (rc.right - rc.left) / 2, rc.bottom - (rc.top - rc.bottom) / 2, _vBoss[i]->getRectMissileCount(), _vBoss[i]->getBossNum() + 8);
					_bossMissile->fire(rc.left + (rc.right - rc.left) + 15, rc.bottom - (rc.top - rc.bottom) / 2, _vBoss[i]->getRectMissileCount(), _vBoss[i]->getBossNum() + 9);
					_bossMissile->fire(rc.left + (rc.right - rc.left) + 15, rc.bottom + (rc.top - rc.bottom) - 15, _vBoss[i]->getRectMissileCount(), _vBoss[i]->getBossNum() + 10);

					_vBoss[i]->setRectMissileCount(_vBoss[i]->getRectMissileCount() + 1);

					if (_vBoss[i]->getRectMissileCount() == 10) _vBoss[i]->setIsRectMax(true);
				}
			}

			// 네모 패턴	 가로 7개
			if (_vBoss[i]->getIsRectMax())
			{
				//if (_vBoss[i]->getMissileCount() > 720 && _vBoss[i]->getMissileCount() < 850)
				if (_timeCount > 770 && _timeCount  < 900)
				{
					{
						RECT rc = _vBoss[i]->getRect();
						_bossMissile->fire( ((_timeCount - 770) % 7 )* 100  , 100, 10, _vBoss[i]->getBossNum() + 11);
					}
				}
			}
			// 네모 패턴	 가로 7개
			if (_vBoss[i]->getIsRectMax())
			{
				//if (_vBoss[i]->getMissileCount() > 720 && _vBoss[i]->getMissileCount() < 850)
				if (_timeCount > 770 && _timeCount < 900)
				{
					{
						RECT rc = _vBoss[i]->getRect();
						_bossMissile->fire(100, ((_timeCount - 720) % 7) * 100, 10, _vBoss[i]->getBossNum() + 12);
					}
				}
			}

			// 원 그리기
			if (_vBoss[i]->getCircleMissileCount() < 40 && _timeCount > 970)
			{
				_vBoss[i]->setBossStatus(4);
				RECT rc = _vBoss[i]->getRect();
				_bossMissile->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2, _vBoss[i]->getMissileCount(), _vBoss[i]->getBossNum() + 13);

				_vBoss[i]->setCircleMissileCount(_vBoss[i]->getCircleMissileCount() + 1);

				if (_vBoss[i]->getCircleMissileCount() == 40) _vBoss[i]->setIsCircleMax(true);
			}
			
			// 원패턴 
			
			if (_vBoss[i]->getIsCircleMax() && _timeCount > 1050)
			{
				_vBoss[i]->setBossStatus(1);
				RECT rc = _vBoss[i]->getRect();
				if (_vBoss[i]->getMissileCount() % 20 == 0)
				{
					_bossMissile->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2, 17, _vBoss[i]->getBossNum() + 14);
				}
			}
			

			// 미사일 초기화
			/*if (_vBoss[i]->getMissileCount() > 750)
			{
				_vBoss[i]->setMissileCount(0);
				_vBoss[i]->setIsStarMax(false); 
			}*/
		}
	}
}

void enemyManager::removeBoss(int arrNum)
{
}

void enemyManager::collision()
{
	for (int i = 0; i < _bullet->getVBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_bullet->getVBullet()[i].rc, &_player->getPlayerRc()))
		{
			_bullet->removeMissile(i);
			_player->hitDamage(10);
		}
	}

	for (int i = 0; i < _bossMissile->getVFireBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_bossMissile->getVFireBullet()[i].rc, &_player->getPlayerRc()))
		{
			_bossMissile->removeBossMissile(i);
			_player->hitDamage(10);
		}
	}
}
