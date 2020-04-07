#pragma once
#include"gameNode.h"
#include"player.h"
#include"enemyManager.h"
#include"itemManager.h"
#include"scene1.h"

class mainGameScene : public gameNode
{
private:
	//rocket * _rocket;
	player * _player;
	enemyManager* _enemyManager;
	itemManager * _itemManager;

	image* _stageOneText;

	int _loopX;
	int _loopY;

	float _defaultMapAlpha;
	float _blackMapAlpha;
	float _bossMapAlpha;

	float _endMapAlpha;
	float _gameOverTextAlpha;

	int _sceneCount;
public:
	mainGameScene();
	~mainGameScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

