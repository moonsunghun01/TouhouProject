#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{
}

HRESULT item::init()
{
	return S_OK;
}

HRESULT item::init(const char* imageName, int size)
{
	_imageName = imageName;
	_itemMax =size; 

	return S_OK;
}


void item::release()
{
}

void item::update()
{
	move();
}

void item::render()
{
	_viItem = _vItem.begin();
	for (_viItem; _viItem != _vItem.end(); ++_viItem)
	{
		_viItem->itemImage->render(getMemDC(), _viItem->rc.left, _viItem->rc.top);
		//Rectangle(getMemDC(),_viItem->rc.left, _viItem->rc.top, _viItem->rc.right, _viItem->rc.bottom);
	}
}

void item::create(float x, float y, float speed , int itemNum)
{
	tagItem item;
	ZeroMemory(&item, sizeof(tagItem));
	item.itemImage = new image;
	if (itemNum == 1) item.itemImage = IMAGEMANAGER->findImage("powerItem");
	else if (itemNum == 2) item.itemImage = IMAGEMANAGER->findImage("bombItem");
	else if (itemNum == 3) item.itemImage = IMAGEMANAGER->findImage("lifeItem");

	item.itemNum = itemNum;
	item.speed = speed;
	item.x =  x;
	item.y =  y;
	item.rc = RectMakeCenter(item.x, item.y, item.itemImage->getWidth(), item.itemImage->getHeight());
	_vItem.push_back(item);
}

void item::move()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end();)
	{
		_viItem->y += _viItem->speed;

		_viItem->rc = RectMakeCenter(_viItem->x, _viItem->y,
			_viItem->itemImage->getWidth(),
			_viItem->itemImage->getHeight());

		if (_viItem->rc.bottom > WINSIZEY  )
		{
			_viItem = _vItem.erase(_viItem);
		}
		else ++_viItem;
	}
}

void item::removeItem(int arrNum)
{
	_vItem.erase(_vItem.begin() + arrNum);
}

