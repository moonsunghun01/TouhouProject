#pragma once
#include"gameNode.h"

class player;
class miniObject : public gameNode
{
private :

	image*		_leftMiniObject;
	RECT		_leftOjectRc;
	image*		_rightMiniObject;
	RECT		_rightOjectRc;

	player*		_player;
public:
	miniObject();
	~miniObject();

	HRESULT init();
	void release();
	void update(RECT playerRc);
	void render();
};

