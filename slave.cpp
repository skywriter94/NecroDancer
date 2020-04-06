#include "stdafx.h"
#include "slave.h"

slave::slave()
{
}

slave::~slave()
{
}

HRESULT slave::init(SLAVE_TYPE type, int idx, int idy)
{
	_library.slave_Reset(&_slave);				// �����̺��� ������ Null ������ �ʱ�ȭ ���ش�.
	_library.slave_Setting(&_slave, type);		// �����̺��� Ÿ�Կ� �°� �������ͽ��� ������ش�.
	_library.pos_Setting(&_slave, idx, idy);	// �����̺��� ��ǥ �������� ���� ���ش�.
	_slave.image.animation->start();
	return S_OK;
}

void slave::release()
{
}

void slave::update()
{
}

void slave::render()
{
	if (!_slave.b_Value.ghostMoveStop)
	{
		_slave.image.img->aniRender(CAMERAMANAGER->getWorldDC(), _slave.pos.center.x, _slave.pos.center.y -
			(_slave.image.img->getFrameHeight() / 4), _slave.image.animation);
	}

	if (_slave.b_Value.ghostMoveStop)
	{
		if (!_slave.b_Value.ghostImgDirection)
		{
			if (_slave.b_Value.isClosePlayer)
			{
				// ���� ������ ���� ���
				_slave.image.img->alphaFrameRender(CAMERAMANAGER->getWorldDC(),
					_slave.pos.rc.left, _slave.pos.rc.top - (_slave.image.img->getFrameHeight() / 4), 0, 0, 200);
			}

			else
			{
				// ���� ������ ���
				_slave.image.img->frameRender(CAMERAMANAGER->getWorldDC(),
					_slave.pos.rc.left, _slave.pos.rc.top - (_slave.image.img->getFrameHeight() / 4), 2, 0);
			}
		}

		if (_slave.b_Value.ghostImgDirection)
		{
			if (_slave.b_Value.isClosePlayer)
			{
				// ������ ������ ���� ���
				_slave.image.img->alphaFrameRender(CAMERAMANAGER->getWorldDC(),
					_slave.pos.rc.left, _slave.pos.rc.top - (_slave.image.img->getFrameHeight() / 4), 2, 1, 200);
			}

			else
			{
				// ������ ������ ���
				_slave.image.img->frameRender(CAMERAMANAGER->getWorldDC(),
					_slave.pos.rc.left, _slave.pos.rc.top - (_slave.image.img->getFrameHeight() / 4), 0, 1);
			}
		}
	}
}

void slave::move()
{
}

void slave::slave_Pos_Setting()
{
	if (!_slave.b_Value.isMove)
	{
		// �����̺��� ��Ʈ�� ������ش�.
		_slave.pos.rc = RectMake(_slave.pos.index.x * _slave.operation.tile_SizeX, _slave.pos.index.y * _slave.operation.tile_SizeY,
			_slave.operation.tile_SizeX, _slave.operation.tile_SizeY);

		_slave.pos.center.x = (_slave.pos.rc.left + _slave.pos.rc.right) / 2;
		_slave.pos.center.y = (_slave.pos.rc.top + _slave.pos.rc.bottom) / 2;
	}
}


