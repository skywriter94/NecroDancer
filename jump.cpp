#include "stdafx.h"
#include "jump.h"


jump::jump()
{
}


jump::~jump()
{
}

HRESULT jump::init()
{
	_isJumping = _jumpPower = _gravity = 0;

	return S_OK;
}

void jump::release()
{
}

void jump::update()
{
	if (!_isJumping) return;


	// ���� UP Ű�� ������ 
	if (_isUpJumping) 
	{
		*_y -= _jumpPower;

		if (_startY > * _y)
		{
			_isJumping = false;
			_isUpJumping = false;
		}
	}
	else // �̿��� Ű�� ������ 
	{
		*_y -= _jumpPower;
		_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime() * 50;
		if (_startY < *_y)
		{
			_isJumping = false;
			*_y = _startY;
		}
	}

}

void jump::render()
{
}

void jump::jumping(float* x, float* y, float jumpPower, float gravity,bool upJump)
{
	//�������̸� ���� �̸��� �������̸� ������������
	if (_isJumping) return;
	_isUpJumping = upJump;
	_isJumping = true;

	_x = x;
	_y = y;

	_startX = *x;

	// UPŰ�� ������ 
	if (_isUpJumping)
	{
		_startY = *y-52; // �� Ÿ���� ���� y ��ǥ 
	}
	else // �̿��� Ű�� ������ 
	{
		_startY = *y;
	}

	//call by value
	//call by reference

	_gravity = gravity;
	_jumpPower = jumpPower;

}
