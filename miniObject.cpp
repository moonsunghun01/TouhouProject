#include "stdafx.h"
#include "miniObject.h"
#include "player.h"

miniObject::miniObject()
{
}


miniObject::~miniObject()
{
}

HRESULT miniObject::init()
{
	_leftMiniObject = IMAGEMANAGER->addImage("leftObject", "images/miniObject.bmp", 25, 25, true, RGB(255, 0, 255));
	_rightMiniObject = IMAGEMANAGER->addImage("leftObject", "images/miniObject.bmp", 14, 14, true, RGB(255, 0, 255));
	return S_OK;
}

void miniObject::release()
{
}

void miniObject::update(RECT playerRc)
{
	
	_leftOjectRc = RectMakeCenter(playerRc.left-25, playerRc.top+25,25,25);

	_rightOjectRc = RectMakeCenter(playerRc.left+50, playerRc.top+25,25,25);
}

void miniObject::render()
{
	_leftMiniObject->alphaRender(getMemDC(), _leftOjectRc.left, _leftOjectRc.top,125);
	_rightMiniObject->alphaRender(getMemDC(), _rightOjectRc.left, _rightOjectRc.top,125);
}
