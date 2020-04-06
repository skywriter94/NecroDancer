#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "tile.h"

class bossStageTestTile : public gameNode
{
private:

	tile*						_boss;				// ���� ��ġ Ÿ��(�׽�Ʈ��)
	int							_tileCnt;			// Ÿ�� ���͹���

	tagTile* _tiles[TILEX * TILEY];						// �ҷ��� ���� �����Ѵ�.
	vector<tagTile*>				_vTotalList;		// ��ü Ÿ�� ����	(�׽�Ʈ��)
	vector<tagTile*>::iterator		_viTotalList;		// ��ü Ÿ�� ����	(�׽�Ʈ��)


public:
	bossStageTestTile();
	~bossStageTestTile();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	// ����
	void setTile();	// Ÿ�� ����
	void setTotalTile(vector<tagTile*> total) { _vTotalList = total; }	// Ÿ�� ����
	
	// �� ��� ������ ����
	vector<tagTile*> getTotalTile() { return _vTotalList; } // Ÿ�� ����

	// �� �ҷ����� �Լ�
	void BossStageLoad();

};

