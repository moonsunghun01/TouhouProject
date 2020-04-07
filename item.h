#pragma once
#include"gameNode.h"

struct tagItem
{
	image* itemImage;
	RECT rc;
	float x, y;
	float speed;
	int itemNum;
};

class item :public gameNode
{
private:
	image * _itemImage;
	RECT _itemRc;

	vector<tagItem> _vItem;
	vector<tagItem>::iterator _viItem;

	const char* _imageName;
	int _itemMax;

	//랜덤으로 아이템 발사할 변수들
	int _createCount;
	int _rndCreateCount;
public:
	item();
	~item();

	HRESULT init();
	HRESULT init(const char* imageName, int size);
	void release();
	void update();
	void render();

	void create(float x, float y, float speed , int itemNum);
	void move();

	vector<tagItem> getVItem() { return _vItem; }
	vector<tagItem>::iterator getVIItem() { return _viItem; }

	void removeItem(int arrNum);

};

