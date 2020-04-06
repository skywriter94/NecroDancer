#pragma once
#include "gameNode.h"
#include "bossKinds.h"
#include "slaveManager.h"
#include "boss_Stage_Library.h"
#include "addImage_Boss.h"
#include "Collision.h"
#include "stageScene.h"
#include "zOrder.h"
#include "visionFloodFill.h"

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinmainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

class stageScene;
class UImanager;
class player;

class bossStageScene : public gameNode
{
private:
	ADD_BOSS_IMAGE*								_addBossImage;					// ���� �̹��� ����
	ADD_SLAVE_IMAGE*							_addSlaveImage;					// ���� �����̺� �̹��� ����

	Collision									_collision;						// �浹 Ŭ����

	BOSS_STAGE_OPEN								_scene_Starter;					// ���� ����� ���� ����

	tagTile										_tiles[TILEX * TILEY];			// ���� �޾� �� Ÿ�� ����
	vector<tagTile*>							_vTotalList;					// ���� ���������� Ÿ�� ���� ���ͷ� �����ؼ� ����Ѵ�.
	vector<tagTile*>::iterator					_viTotalList;

	//vector<tagTile*>							_vTotalList;					// ���� ���������� Ÿ�� ���� ���ͷ� �����ؼ� ����Ѵ�.
	//vector<tagTile*>::iterator				_viTotalList;

	vector<BOSS_STAGE_EFFECT_VECTOR*>			_vEffect;						// ����Ʈ ����
	vector<BOSS_STAGE_EFFECT_VECTOR*>::iterator _viEffect;						// ����Ʈ ���Ϳ�����
	 
	stageScene*									_stageScene;					// �������� ��
	UImanager*									_ui;							// ui
	player*										_player;						// �÷��̾�	
	deathMetal*									_deathMetal;					// ������Ż
	slaveManager*								_sm;							// �����̺� �Ŵ���
	zOrder*										_zOrder;
	visionFloodFill*							_floodFill;
private:
	bool distanceCheck;															// �Ÿ��� üũ�Ѵ�. (������ �����ų� ������ ������ ���� �ٲ��.)
	bool introSound;
	bool boss_Dead;

	int _endX;   // ���������� ���� ���� ��ǥ �� 
	int _endY;


	int _tileFirstX, _tileSecondX; // Ÿ�� �����̴� ���� 
	int _tileFirstY, _tileSecondY; // Ÿ�� �����̴� ���� 
public:
	bossStageScene();
	~bossStageScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	// ���ְ� ���� ���� ������������ �ҷ� �� �� �ְ� �ε� ����� ������ �Ѵ�.
	// ���ְ� ���� ���� ������������ ���� ��� �����ϵ��� ���Ϳ� �����ؾ� �Ѵ�.
	// �� �Ӽ��� ���� �̹����� ����ϰ� �����?
	// Ÿ�� ��ü�� �̹����� �����ұ�? �� Ÿ�� ��ġ ���� ĳ������ ��Ʈ�� �̹����� �׸���?
	// �̵��� �� ������ �� Ÿ���� �Ӽ��� �ٲ�����Ѵ�.

	// ��
	void bossStageMap_Load();													// ���� �������� ���� ���� �������� �����Ѵ�.
	void findTileImage();														// Ÿ�� �̹����� ã���ش�.

	// ����
	void z_Order_Player_Boss();													// �÷��̾�� ������ z����

	// �÷��̾�
	void playerPos_Setting();													// �����濡 ó�� ������ �÷��̾��� ��ġ�� �ʱ�ȭ ���ش�.

	// ���� & �����̺�
	void closePlayer(player* player, deathMetal* deathMetal);					// �÷��̾ ��ó�� �ִٸ� ������ �̹����� ���´�.
	void searchSlave(vector<slave*> vSlaveList, player* player);				// �÷��̾ ��ó�� �ִٸ� ������ �̹����� ���´�.
	void closePlayer_Slave(player* player, SLAVE_INFO* slave);					// �÷��̾ ��ó�� �ִٸ� ������ �̹����� ���´�.
	void findPlayer(player* player, deathMetal* deathMetal, UImanager* ui);		// �÷��̾��� ��ġ�� ã�´�. (������Ż)
	SLAVE_DIRECTION findPlayer(player* player, SLAVE_INFO* slave);				// �÷��̾��� ��ġ�� ã�´�. (�����̺�)

	void boss_Move_Player();													// ������ �÷��̾�� �����̴� ����
	void slave_Move_Player();													// �����̺갡 �÷��̾�� �����̴� ����

	void boss_Base_Attack_Render();
	void boss_Base_Attack_Render(string skillName, player* player);				// ������ ���� ���� �ִϸ��̼��� �׷��ش�.

	void start_Slave_Create();				

	void boss_Phase_4_Move();													// ���� ������4 �̵�

	// �������� ������ ��ũ
	void stageSceneAddressLink(stageScene* stageScene) { _stageScene = stageScene; }

	void bossSceneSetting();													// ���� ����� ���� �ʱ�ȭ
	void bossSceneStart();														// ���� ����� ����
	void bossSceneRender();														// ���� ����� ���
	void bossSceneDoorOpen();													// ������ ���� ���� ����
	void bossClear();															// ���� Ŭ���� �� ���� �����°�


	void boss_PhaseMove();														// ���� ������ ����
	void setVolumeBossStage();

	void endScene();

	void tileOnOff();
};

