#pragma once
#include"gameNode.h"
#include"item.h"

class player;
class itemManager : public gameNode
{
private:
	typedef vector<item*> vItem;
	typedef vector<item*>::iterator viItem;

private:

	vItem _vItem;
	viItem _viItem;

	item * _item;
	player * _player;

	int _count;

public:
	itemManager();
	~itemManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void createItem();

	void setPlayerMemoryLink(player* player) { _player = player; }

	void collision();
};

