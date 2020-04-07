#pragma once
#include"gameNode.h"
class scene1 : public gameNode
{
private:
	image * _introText;

	float _introTextAlpha;
	bool _isIntroTextAlphaMax;
public:
	scene1();
	~scene1();

	HRESULT init();
	void release();
	void update();
	void render();
};

