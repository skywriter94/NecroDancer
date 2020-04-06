#include "stdafx.h"
#include "bossStageTestTile.h"

bossStageTestTile::bossStageTestTile()
{
}

bossStageTestTile::~bossStageTestTile()
{
}

HRESULT bossStageTestTile::init()
{
	//setTile();	// �⺻ Ÿ�� ����
	BossStageLoad();	// �������� �ҷ��ͼ� �����Ѵ�.

	return S_OK;
}

void bossStageTestTile::release()
{
}

void bossStageTestTile::update()
{
}

void bossStageTestTile::render()
{
	// ������ ���� �ʴ´�.
	//for (int i = 0; i < _vTotalList.size(); ++i)
	//{
	//	if ((_vTotalList[i]->getIdX() + _vTotalList[i]->getIdY()) % 2)
	//	{
	//		if ((int)TIMEMANAGER->getWorldTime() % 2)
	//			IMAGEMANAGER->findImage("Floor_Test")->frameRender(getMemDC(), _vTotalList[i]->getRect().left, _vTotalList[i]->getRect().top, 1, 1);
	//		else
	//			IMAGEMANAGER->findImage("Floor_Test")->frameRender(getMemDC(), _vTotalList[i]->getRect().left, _vTotalList[i]->getRect().top, 2, 1);
	//	}
	//	else
	//	{
	//		if((int)TIMEMANAGER->getWorldTime() % 2)
	//			IMAGEMANAGER->findImage("Floor_Test")->frameRender(getMemDC(), _vTotalList[i]->getRect().left, _vTotalList[i]->getRect().top, 2, 1);
	//		else
	//			IMAGEMANAGER->findImage("Floor_Test")->frameRender(getMemDC(), _vTotalList[i]->getRect().left, _vTotalList[i]->getRect().top, 1, 1);
	//	}
	//}


}

void bossStageTestTile::setTile()
{
	// ������ ���� �ʴ� �Լ�
	//
	//// �׽�Ʈ�� �̹���
	//IMAGEMANAGER->addFrameImage("Heart_Test", "./image/Enemy/boss/beat_heart_test.bmp", 164, 104, 2, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Floor_Test", "./image/Enemy/boss/floor_test.bmp", 156, 104, 3, 2, true, RGB(255, 0, 255));
	//
	//// ��ü Ÿ�� ����
	//for (int y = 0; y < TESTTILEY; ++y)
	//{
	//	for (int x = 0; x < TESTTILEX; ++x)
	//	{
	//		tile* node = new tile;
	//		node->init("floor", x, y, TESTTILESIZE, TESTTILESIZE);
	//		node->setAttribute("�⺻Ÿ��");
	//
	//		_vTotalList.push_back(node);
	//	}
	//}
}

void bossStageTestTile::BossStageLoad()
{
	// ���� �������� ���� �ҷ��ͼ� 
	// _tiles�� ��´�.
	HANDLE file;
	DWORD read;

	file = CreateFile("BossStageFile.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);

	int i = 0;

	while (_tiles[i] != NULL)
	{
		// Ÿ���� Ÿ���� NONE�� �ƴ϶�� ���Ϳ� ��´�.
		if (_tiles[i]->type != TYPE_NONE)  _vTotalList.push_back(_tiles[i]);
		i++;
	}

	cout << _vTotalList.size() << endl;
}
