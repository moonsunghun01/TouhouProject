#pragma once
#include"gameNode.h"
#include"bullet.h"
#include"progressBar.h"
#include "miniObject.h"
#include "explosion.h"
#define PLAYERSPEED 5


//���� :  ��������� ���� ������ ������ �ӵ��� ���ϵȴ�.
/*
	class A�� a.h�ְ� class B�� b.h�� �ִµ�
	B�� A�� ����ϰ� A�� B�� ����� ��� :���谡 �߸��Ǿ��ٰ� ���� �ִ�.
	����ڷ� �ϸ� �����ϱ⵵ ����� ������ �����.

	���̴� ���� �����͸� �˱����ؼ� ���� ������ �˾ƾ��ϰ� �� �� ����� ��Ŭ��� �ؾ��Ѵ�.
	������ �񿡼� �̹� ���̶�� ����� ��Ŭ��带 �ϰ� �ֱ⿡ ���̿��� ���� ����� ��Ŭ��� �ϸ� ��ȣ ���� ������ �ȴ�.
	������ �ٲ��� ������ ��Ŭ��� �Ҽ� ����.
	���̿��� �� ��Ŭ��� �Ѵٰ� �Ҷ� ���� �� ����� �����Ǹ� ��Ŭ��� �κе� 
	�̿����� �ޱ� ������ ������ ���������� ������ �ӵ��� ���ϵȴ�.
	�̰��� �ذ��ϱ� ���� ����� ���漱���̴�.
	(���� :  �����Ϸ��� ������Ͽ� ������ ���ܵ� �����ϴ� ������Ͽ����� ���������� �̷�� ���� �ʴ´�.)
	�� ���� �ؾ� ���� :  ���漱���� ��� �� Ŭ���� ���� ��ü�� ������������ �����ؾ� �Ѵ�.
	���� ���������� �ƴ� ��ü�� ������ ��� ���漱���� Ư¡�� �� ��ü�� ũ�⸦ ��Ȯ�� �ľ��Ͽ� �Ҵ��� �����ֱ�
	�����̴�.(�ش� Ŭ������ �ִٴ� ������ ����� �𸥴�.)
*/

//��ȣ������ �� �Ŵ��� Ŭ���� ���漱��
class enemyManager;
class player :public gameNode
{
private:

	image * _player;
	RECT _playerRc;

	int _score;
	image * _score1;
	image * _score10;
	image * _score100;
	image * _score1000;
	image * _score10000;
	image * _score100000;
	image * _score1000000;
	image * _score10000000;

	int _lifeCount;

	int _bombCount;

	playerMissile* _playerMissile;
	playerBomb*    _playerBomb;
	bullet* _bullet;
	explosion* _explosion;

	miniObject* _miniObject;

	enemyManager* _em;		//�� �Ŵ��� Ŭ���� ����

	progressBar* _powerBar;
	float _currentPower;
	float _maxPower;

	int _count;
	int _index;

	int _missileCount;
	bool isIdle;
	bool isLeft;
	bool isRight;
	bool idleMaxFrame;

	bool isDebug;

	// �ǰ�
	bool _isHit;
	float _playerAlpha;
	float _hitTime;
	bool _alphaCheck;

	// ��ź
	bool _isCreateBomb;
	int _createBomcCount;
	bool _isFireBomb;

	// �ڵ� �̻���
	bool _isAuto;

	// ����
	bool _isPlayerDeath;
public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();

	//�̽� ����
	void removeMissile(int arrNum);
	//�浹�Լ�
	void collision();
	//�Ǳ�� �Լ�
	void hitDamage(float damage);

	//��Ŭ���� ��������
	playerMissile* getMissile() { return _playerMissile; }

	//���� �̹��� ��������
	image* getPlayerImage() { return _player; }
	RECT getPlayerRc() { return _playerRc; }

	void setEnemyMemoryLink(enemyManager* em) { _em = em; }

	void keyManager();
	void playerMotion();
	void updateScore();

	int getSocre() { return _score; }
	void setScore(int score) { _score = score; }

	bool getIsCreateBomb() { return _isCreateBomb; }
	void setIsCreateBomb(bool isCreateBomb) { _isCreateBomb = isCreateBomb; }

	void createBomb();
	void fireBomb();

	int getCurrentPower() { return _currentPower; }
	void setCurrentPower(int currentPower) { _currentPower = currentPower; }

	int getLifeCount() { return _lifeCount; }
	void setLifeCount(int lifeCount) { _lifeCount = lifeCount; }

	int getBombCount() { return _bombCount; }
	void setBombCount(int bombCount) { _bombCount = bombCount; }

	bool getIsPlayerDeath() { return _isPlayerDeath; }
	void setIsPlayerDeath(bool isPlayerDeath) { _isPlayerDeath = isPlayerDeath; }
};

