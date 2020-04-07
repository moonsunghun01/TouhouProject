#include "stdafx.h"
#include "scene1.h"


scene1::scene1()
{
}


scene1::~scene1()
{
}

HRESULT scene1::init()
{

	IMAGEMANAGER->addImage("startScene", "images/startScene.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_introText = IMAGEMANAGER->addImage("introtext", "images/introtext.bmp", 0, 0, 200, 25, true, RGB(255, 0, 255));

	return S_OK;
}

void scene1::release()
{
}

void scene1::update()
{
	if (!_isIntroTextAlphaMax)
	{
		_introTextAlpha += 5;
		if (_introTextAlpha >= 255) _isIntroTextAlphaMax = true;
	}
	else if (_isIntroTextAlphaMax)
	{
		_introTextAlpha -= 5;
		if (_introTextAlpha <= 125) _isIntroTextAlphaMax = false;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		//¾ÀÃ¼ÀÎÁö
		SCENEMANAGER->changeScene("mainGameScene");
	}
}

void scene1::render()
{
	IMAGEMANAGER->render("startScene", getMemDC());
	//IMAGEMANAGER->render("introtext", getMemDC() , WINSIZEX/2-100, WINSIZEY/2);
	_introText->alphaRender(getMemDC(), WINSIZEX / 2 - 100, WINSIZEY / 2, _introTextAlpha);
}
