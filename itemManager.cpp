#include "stdafx.h"
#include "itemManager.h"
#include "player.h"

itemManager::itemManager(){}
itemManager::~itemManager(){}

HRESULT itemManager::init()
{
	_item = new item;
	_item->init("powerItem", 500);
	return S_OK;
}

void itemManager::release()
{
}

void itemManager::update()
{
	_item->update();
	this->createItem();
	collision();
}

void itemManager::render()
{
	_viItem = _vItem.begin();
	for (_viItem; _viItem != _vItem.end(); ++_viItem)
	{
		(*_viItem)->render();
	}

	_item->render();
}

// 아이템 그리기
void itemManager::createItem()
{
	_count++;
	if (_count % 20 == 0)
	{
		if (_count % 500 == 0) _item->create(RND->getFromIntTo(100, 600), 50, 3, 2);
		else if (_count % 600 == 0) _item->create(RND->getFromIntTo(100, 600), 50, 3, 3);
		_item->create(RND->getFromIntTo(100,600), 50, 3,1);
	}
}

void itemManager::collision()
{
	for (int i = 0; i < _item->getVItem().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_item->getVItem()[i].rc, &_player->getPlayerRc()))
		{
			
			if (_item->getVItem()[i].itemNum == 1)
			{
				_player->setCurrentPower(_player->getCurrentPower() + 10);
				if (_player->getCurrentPower() >= 100) _player->setCurrentPower(100);
			}
			else if (_item->getVItem()[i].itemNum == 2)
			{
				_player->setBombCount(_player->getBombCount() + 1);
				if (_player->getBombCount() > 3) _player->setBombCount(3);
			}
			else if (_item->getVItem()[i].itemNum == 3)
			{
				_player->setLifeCount(_player->getLifeCount() + 1);
				if (_player->getLifeCount() > 5) _player->setLifeCount(5);
			}
			_item->removeItem(i);
		}
	}
}
