#include "stdafx.h"
#include "timer.h"

#pragma comment(lib, "winmm.lib")

timer::timer()
{
}


timer::~timer()
{
}

HRESULT timer::init()
{
	//CPU�� ����ð�(�����ð�) üũ�� �Ͽ� �޾Ƶд�
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		_timeScale = 1.0f / _periodFrequency;
	}

	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0;
	_worldTime = 0;
	_daehunWorldTime = 0;
	_countTime = 0;
	_countLoadingTime = 0;

	_countLoadingTimeSwitch = _countTimeResetSwitch = _countTimeSwitch = false;

	return S_OK;
}

void timer::tick(float lockFPS)
{
	//���� ���� �ֱ⸦ ��´�
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);

	//deltaTime�� �̴´�
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	//Frame Lock�� �ɾ deltaTime �ֱ⸦ ��� �����Ѵ�
	//Frame Skipping�� �Ѵ�
	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < 1.0f / lockFPS)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);

			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}


	_lastTime = _curTime;
	_FPSFrameCount++;
	_FPSTimeElapsed += _timeElapsed;
	_worldTime += _timeElapsed;
	_daehunWorldTime += _timeElapsed*1000;
	if (_daehunWorldTime >=1000)
	{
		_daehunWorldTime = 0;
	}

	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0.0f;
		_FPSTimeElapsed = 0.0f;
	}

	if (_countTimeSwitch)
	{
		_countTime += _timeElapsed;
	}
	if (_countTimeResetSwitch)
	{
		_countTimeResetSwitch = false;
		_countTime = 0;
	}

	if (_countLoadingTimeSwitch)
	{
		_countLoadingTime += _timeElapsed;
	}
}

unsigned long timer::getFrameRate(char * str) const
{
	if (str != NULL)
	{
		wsprintf(str, "FPS : %d", _frameRate);
	}

	return _frameRate;
}

bool timer::daehunCustom()
{
	return false;
}
