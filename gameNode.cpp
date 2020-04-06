#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == CV_EVENT_MOUSEMOVE)
	{
		//cout << "���콺 ��ǥ" << "x:" << x << "y :" << y << endl;
		_ptMouse.x = x;
		_ptMouse.y = y;
	}
}

HRESULT gameNode::init()
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;
	
	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TXTDATA->init();
		TIMEMANAGER->init();
		EFFECTMANAGER->init();
		SOUNDMANAGER->init();
		SCENEMANAGER->init();
		KEYANIMANAGER->init();
		INIDATAMANAGER->init();
		CAMERAMANAGER->init();
		BEATMANAGER->init();
		OPTION->init();
	}

	return S_OK;
}

void gameNode::release()
{
	if (_managerInit)
	{
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		TXTDATA->release();
		TXTDATA->releaseSingleton();
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		KEYANIMANAGER->release();
		KEYANIMANAGER->releaseSingleton();
		INIDATAMANAGER->release();
		INIDATAMANAGER->releaseSingleton();
		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();
		BEATMANAGER->release();
		BEATMANAGER->releaseSingleton();
		OPTION->release();
		OPTION->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()
{
	cvSetMouseCallback(WINNAME, CallBackFunc, NULL); // ��ġ ��ǥ�� �ֱ� ���� �� 
	SOUNDMANAGER->update();
	KEYANIMANAGER->update();
	EFFECTMANAGER->update();
	OPTION->update();
}

void gameNode::render()
{
}


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;
	HDC			hdc;

	switch (iMessage)
	{
		case WM_CREATE:
		
		break;

		//���� ���ļ� ��� �ּ����� ���� ���������ض�
		//���� �̷��� �ϴ� ������ �������� �������� ��ȹ�� ��ȹ�ڵ��� �ϴٺ���
		//MFC ������ ������ ������ ���� ��ȹ��Ʈ�� �Ѱ��ִ� ���� �ٹݻ翴��
		//�׷��� �ɹ��������� ���� ������ ��ɸ� ž���ؼ� �Ѱ����.
		//���� ������ �޽����� ������� �ʰ� �츮 ��ҿ� �ϴ���� �ϸ� 
		//�̷� ������ ���ĵ� �˴ϴ�
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>(LOWORD(lParam));
			_ptMouse.y = static_cast<float>(HIWORD(lParam));
			//cout << "���콺 ��ǥ" << "x:" << _ptMouse.x << "y :" << _ptMouse.y << endl;
			
		break;
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_ESCAPE:
					OPTION->SetOptionOpen();
					//PostQuitMessage(0);
				break;
			}
		}
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
			//OPTION->SetOptionOpen();
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}



