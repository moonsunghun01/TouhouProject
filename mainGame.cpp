#include "stdafx.h"
#include "mainGame.h"
mainGame::mainGame()
{
}
mainGame::~mainGame()
{
}
HRESULT mainGame::init()
{
	gameNode::init(true);

	
	//_defaultMapAlpha = 255;
	//_blackMapAlpha = 0;
	//_bossMapAlpha = 0;
	//IMAGEMANAGER->addImage("인터페이스", "images/interface_02.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("배경화면", "images/backGround_04.bmp",0,0,635,726, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("bossMap", "images/bossMap.bmp",0,0,635,726, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("black", "images/black.bmp",0,0,635,726, true, RGB(255, 0, 255));

	//// 인터페이스
	//IMAGEMANAGER->addImage("UIScore", "images/UIscore.bmp",0,0,75,25, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("UIplayer", "images/UIplayer.bmp",0,0,75,25, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("UIplayerLife", "images/UIplayerLife.bmp",0,0, 25, 25, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("UIbomb", "images/UIbomb.bmp",0,0,75,25, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("UIplayerBomb", "images/UIplayerBomb.bmp",0,0, 25, 25, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("UIPower", "images/UIPower.bmp",0,0,75,25, true, RGB(255, 0, 255));

	//// 적 이미지
	//IMAGEMANAGER->addImage("bullet", "images/bullet.bmp", 21, 21, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("enemy1", "images/enemy1.bmp", 396, 60, 12, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("m_boss", "images/m_boss.bmp", 248, 151, 4, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("m_boss_02", "images/m_boss_02.bmp", 350, 51, 5, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("m_boss_03", "images/m_boss_03.bmp", 230, 187, 4, 3, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("m_boss_green", "images/m_boss_green.bmp", 166, 31, 5, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("boss", "images/boss.bmp", 240, 260, 4, 4, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("bossBackEffect", "images/bossBackEffect.bmp", 1800, 100, 18, 1, true, RGB(255, 0, 255));


	//// 플레이어 미사일
	//IMAGEMANAGER->addImage("playerMissile", "images/playerMissile.bmp", 30, 64, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("playerMiniMissile", "images/playerMiniMissile.bmp", 16, 16, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("redKnife", "images/redKnife.bmp",18,26, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("blueKnife", "images/blueKnife.bmp",18, 26, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("grayKnife", "images/grayKnife.bmp", 18, 26, true, RGB(255, 0, 255));

	//// 중간보스 미사일
	//IMAGEMANAGER->addImage("mBossMissile", "images/mBossMissile.bmp", 16, 16, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("mBossMissile_02", "images/mBossMissile_02.bmp", 16, 16, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("mBossMissile_03", "images/mBossMissile_03.bmp", 16, 16, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("mBossMissile_04", "images/mBossMissile_04.bmp", 16, 16, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("purpleCircleMissile", "images/purpleCircleMissile.bmp", 16, 16, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("yellowCircleMissile", "images/yellowCircleMissile.bmp", 16, 16, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("redCircleMissile", "images/redCircleMissile.bmp", 16, 16, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("greenCircleMissile", "images/greenCircleMissile.bmp", 16, 16, true, RGB(255, 0, 255));

	//// 진짜 보스
	//IMAGEMANAGER->addImage("bossMissile_01", "images/mBossMissile_03.bmp", 25, 25, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("starMissile", "images/starMissile.bmp", 16, 16, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("starBigMissile", "images/starMissile.bmp", 25, 25, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("greenStarMissile", "images/greenStarMissile.bmp", 16, 16, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("yellowMissile", "images/yellowMissile.bmp", 16, 16, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("purpleMissile", "images/purpleMissile.bmp", 16, 16, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("purpleBigMissile", "images/purpleMissile.bmp", 25, 25, true, RGB(255, 0, 255));

	//IMAGEMANAGER->addImage("yellowLaser", "images/yellowLaser.bmp", 25, 25, true, RGB(255, 0, 255));

	//// 보스 hp
	//IMAGEMANAGER->addImage("progressBarFront", "images/progressBarFront.bmp", 50, 10, true, RGB(255, 0, 255));

	//// 아이템
	//IMAGEMANAGER->addImage("powerItem", "images/powerItem.bmp", 16, 16, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("bombItem", "images/bombItem.bmp", 16, 16, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("lifeItem", "images/lifeItem.bmp", 16, 16, true, RGB(255, 0, 255));

	//// 폭발
	//IMAGEMANAGER->addFrameImage("explosion", "images/explosion.bmp", 2280, 151, 15, 1, true, RGB(255, 0, 255));

	//_player = new player;
	//_player->init();

	//_enemyManager = new enemyManager;
	//_enemyManager->init();

	//_itemManager = new itemManager;
	//_itemManager->init();

	//_player->setEnemyMemoryLink(_enemyManager);
	//_enemyManager->setRocketMemoryLink(_player);

	//_itemManager->setPlayerMemoryLink(_player);


	SCENEMANAGER->addScene("scene1", new scene1);
	SCENEMANAGER->addScene("mainGameScene", new mainGameScene);

	SCENEMANAGER->changeScene("scene1");

	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
	/*SAFE_DELETE(_player);
	SAFE_DELETE(_enemyManager);
	SAFE_DELETE(_itemManager);*/

}

void mainGame::update()
{
	gameNode::update();
	SCENEMANAGER->update();


	//_player->update();
	//_enemyManager->update();
	//_itemManager->update();
	//
	//_loopY --;

	//// 보스 
	//if (_enemyManager->getPatternCount()>180 && _enemyManager->getPatternCount() < 200)
	//{
	//	if(_defaultMapAlpha > 0 ) _defaultMapAlpha -= 1;
	//	else if (_defaultMapAlpha <= 0) _defaultMapAlpha = 0;

	//	if(_blackMapAlpha <255) _blackMapAlpha += 1;
	//	else if (_blackMapAlpha >= 255) _blackMapAlpha = 255;
	//}
	//else if (_enemyManager->getPatternCount() > 210)
	//{
	//	if (_blackMapAlpha > 0) _blackMapAlpha -= 1;
	//	else if (_blackMapAlpha <= 0) _blackMapAlpha = 0;

	//	if (_bossMapAlpha < 255) _bossMapAlpha += 1;
	//	else if (_bossMapAlpha >= 255) _bossMapAlpha = 255;
	//}
}

void mainGame::render(/*HDC hdc*/)
{
	
	//흰색 비트맵
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//===================================================

	//IMAGEMANAGER->render("인터페이스", getMemDC());
	//IMAGEMANAGER->loopAlphaRender("배경화면", getMemDC(), &RectMake(85, 42, 635, 726 ), _loopX, _loopY,_defaultMapAlpha);
	//IMAGEMANAGER->loopAlphaRender("black", getMemDC(), &RectMake(85, 42, 635, 726 ), _loopX, _loopY,_blackMapAlpha);
	//IMAGEMANAGER->loopAlphaRender("bossMap", getMemDC(), &RectMake(85, 42, 635, 726 ), 0, 0,_bossMapAlpha);

	//IMAGEMANAGER->render("UIplayer", getMemDC(), 750, 250);
	//IMAGEMANAGER->render("UIbomb",   getMemDC(), 750, 300);
	//IMAGEMANAGER->render("UIPower", getMemDC(), 750, 400);
	//IMAGEMANAGER->render("UIScore", getMemDC(), 750, 100);

	//_player->render();
	//_enemyManager->render();
	//_itemManager->render();


	//TIMEMANAGER->render(getMemDC());


	SCENEMANAGER->render();
	//=================================================
	//백버퍼의 내용을 HDC에 그린다.(건드리지말것.)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

