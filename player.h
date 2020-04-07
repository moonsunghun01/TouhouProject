#pragma once
#include"gameNode.h"
#include"bullet.h"
#include"progressBar.h"
#include "miniObject.h"
#include "explosion.h"
#define PLAYERSPEED 5


//참고 :  헤더파일이 많아 질수록 컴파일 속도가 저하된다.
/*
	class A가 a.h있고 class B가 b.h에 있는데
	B가 A를 사용하고 A가 B를 사용할 경우 :설계가 잘못되었다고 볼수 있다.
	요로코롬 하면 이해하기도 힘들고 추적이 힘들다.

	에이는 비의 데이터를 알기위해서 비의 구조를 알아야하고 즉 비 헤더를 인클루드 해야한다.
	하지만 비에서 이미 에이라는 헤더를 인클루드를 하고 있기에 에이에서 비의 헤더를 인클루드 하면 상호 참조 에러가 된다.
	구조를 바꾸지 않으면 인클루드 할수 없다.
	에이에서 비를 인클루드 한다고 할때 만약 비 헤더가 수정되면 인클루드 부분도 
	이영향을 받기 때문에 수정이 많아질수록 컴파일 속도도 저하된다.
	이것을 해결하기 위한 방법은 전방선언이다.
	(장점 :  참조하려는 헤더파일에 변경이 생겨도 참조하는 헤더파일에서는 재컴파일이 이루어 지지 않는다.)
	단 주의 해야 할점 :  전방선언할 경우 그 클래스 관련 객체는 포인터형으로 선언해야 한다.
	만약 포인터형이 아닌 객체를 생성할 경우 전방선언의 특징상 그 객체의 크기를 정확히 파악하여 할당을 못해주기
	때문이다.(해당 클래스가 있다는 정보만 사이즈를 모른다.)
*/

//상호참조용 적 매니저 클래스 전방선언
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

	enemyManager* _em;		//적 매니저 클래스 선언

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

	// 피격
	bool _isHit;
	float _playerAlpha;
	float _hitTime;
	bool _alphaCheck;

	// 폭탄
	bool _isCreateBomb;
	int _createBomcCount;
	bool _isFireBomb;

	// 자동 미사일
	bool _isAuto;

	// 죽음
	bool _isPlayerDeath;
public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();

	//미슬 삭제
	void removeMissile(int arrNum);
	//충돌함수
	void collision();
	//피깎는 함수
	void hitDamage(float damage);

	//뉴클리어 가져오기
	playerMissile* getMissile() { return _playerMissile; }

	//로켓 이미지 가져오기
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

