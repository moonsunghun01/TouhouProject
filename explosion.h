#pragma once
#include"gameNode.h"

struct tagExplosion
{
	image* exImage;
	RECT rc;
	float x, y;
	float speed;
	int itemNum;
};

class explosion :public gameNode
{
private:
	image * _explosionImage;
	RECT _explosionRc;

	vector<tagExplosion> _vExplosion;
	vector<tagExplosion>::iterator _viExplosion;

	const char* _imageName;
	
	int _count;
	int _currentFrameX;
	int _currentFrameY;

	
public:
	explosion();
	~explosion();

	HRESULT init();
	HRESULT init(const char* imageName, int size);
	void release();
	void update();
	void render();

	void create(float x, float y);
	void animation();

	vector<tagExplosion> getVItem() { return _vExplosion; }
	vector<tagExplosion>::iterator getVIItem() { return _viExplosion; }

	void removeItem(int arrNum);

};

