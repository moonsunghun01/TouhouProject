#include "stdafx.h"
#include "gameNode.h"



gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	
	
	_hdc = GetDC(m_hWnd);
	_managerInit = false;
	return S_OK;
}
HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(m_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		SetTimer(m_hWnd, 1, 10, NULL);
		//�Ŵ��� �ʱ�ȭ
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
	}
	
	return S_OK;
}
//void gameNode::setBackBuffer()
//{
//	_backBuffer = new image;
//	_backBuffer->init(WINSIZEX, WINSIZEY);
//}

void gameNode::release()
{	//Ÿ�̸� ����

	if (_managerInit)
	{
		//������ ���ϸ� ���Ḧ �ص� �޸𸮰� ������~

		KillTimer(m_hWnd, 1);
		//�Ŵ��� ����
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->releaseSingleton();
		IMAGEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		RND->releaseSingleton();

	}
	ReleaseDC(m_hWnd, _hdc);

	//SAFE_DELETE(_backBuffer);

}

void gameNode::update()
{
	//�������� ���� ������� �ʴ´� true->false
	InvalidateRect(m_hWnd, NULL, false);
}
void gameNode::render(/*HDC hdc*/)
{
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
	/*case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->render(hdc);
		EndPaint(hWnd, &ps);
		break;*/
	case WM_MOUSEMOVE:
		m_ptMouse.x = LOWORD(lParam);
		m_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}//end of switch

	return (DefWindowProc(hWnd,iMessage,wParam,lParam));
}