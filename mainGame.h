#pragma once
#include"gameNode.h"
#include"player.h"
#include"enemyManager.h"
#include"itemManager.h"
#include"scene1.h"
#include"mainGameScene.h"

class mainGame :  public gameNode
{
private:

	//rocket * _rocket;
	player * _player;
	enemyManager* _enemyManager;
	itemManager * _itemManager;

	int _loopX;
	int _loopY;

	float _defaultMapAlpha;
	float _blackMapAlpha;
	float _bossMapAlpha;

public:
	mainGame();
	~mainGame();

	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(/*HDC hdc*/);//그리는곳

	
};

