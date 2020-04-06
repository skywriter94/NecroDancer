#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include "UImanager.h"
#include "Collision.h"
#include "miniMap.h"
#include "zOrder.h"
#include "visionFloodFill.h"
#include"EnemyManager.h"
class bossStageScene;
class stageScene: public gameNode
{
private: // �� �浹  
	tagTile							_tiles[TILEX * TILEY];   // �������� ��
	vector<tagTile*>						  _vTotalList;	 // �������� �� ������ ����
	vector<tagTile*>::iterator			     _viTotalList;

	Collision _collision;			// �浹ó�� 
private: // Enemy ������ 
	map<CHARACTER, POINT>		   	_mEnemyPoint;
	map<CHARACTER, POINT>::iterator _miEnemyPoint;

private: // ���� ���� 	
	playerManager* _pm;					// �÷��̾� �Ŵ���
	EnemyManager* _em;					// �ֳʹ�
	UImanager* _ui;						// UI
	miniMap* _minimap;					// �̴ϸ�
	zOrder* _zOrder;					// Z-order
	bossStageScene* _bossStageScene;	// ������
	visionFloodFill* _floodFill;		// �ٴ� 

	int _playerIdx, _playerIdy;			// �÷��̾� id
	int _bossIdx, _bossIdy;				// ���� ��� ��ġ 
	int _stageIdx, _stageIdy;			// �������� ��� ��ġ 
	const char* fileName;				// �ε� ���� �̸� 


	int _tileFirstX, _tileSecondX; // Ÿ�� �����̴� ���� 
	int _tileFirstY, _tileSecondY; // Ÿ�� �����̴� ���� 

public:
	stageScene() { fileName = "Loby_SaveFile.map"; }
	~stageScene() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	player* getPlayerAddress()			{ return _pm->getPlayerInfo(); }		// Player
	vector<tagTile*> getStageTile()		{ return _vTotalList; }					// Ÿ�� �� 
	UImanager* getUiAddress()			{ return _ui; }							// UI
	playerManager* getPlayerManager()	{ return _pm; }							//Player Manager

	void stageMapLoad(const char* fileName);
	void stageCollision();														// �ٴ� �浹 
	void bossStageSceneAddressLink(bossStageScene* bossStageScene) { _bossStageScene = bossStageScene; }

	void nextPage();					// ���� ������ �Ѿ�� ���� �Լ� 
	void tileOnOff();					// �ٴ� ���� ��ȭ 
		
};