#pragma once
#include "gameNode.h"
#include "EnemyManager.h"
#include "playerManager.h"


class miniMap : public gameNode
{
private:
	vector<tagTile*>					_vStageMap;									//Ÿ�� ���� ����
	vector<tagTile*>::iterator			_viStageMap;								//Ÿ�� ���� ���ͷ�����

	EnemyManager* _em;																//���ʹ�
	playerManager* _pm;																//�÷��̾�

	const char* _imageName;															//�̴ϸ� �̹��� ���� Ű�� ����
	float _playerX;
	float _playerY;

public:
	miniMap();
	~miniMap();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void getStageMap(vector<tagTile*> stageMap) { _vStageMap = stageMap; }			//Ÿ�� ����
	void getEnemyPoint(EnemyManager* em) { _em = em; }								//���ʹ� ��ġ ����
	void setPlayerXY(float x, float y)												//�÷��̾� ��ġ ��ǥ ����
	{
		_playerX = x; 
		_playerY = y;
	}
};

