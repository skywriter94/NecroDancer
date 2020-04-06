#pragma once
#include "gameNode.h"			// ���ӳ��
#include "alphaImageEffect.h"   // ����Ʈ ���
#include "playerLibrary.h"		// ���̺귯��
#include "animation.h"		    // �ִϸ��̼�
#include "jump.h"				// ����

class player : public gameNode
{
private:
	//�� Ÿ�� �Ǵ� MAP
	map<PLAYERDIRECTION, tagTile*>				_mPlayerTile;
	map<PLAYERDIRECTION, tagTile*>::iterator	_miPlayerTile;

	//�������� �Ǵ� MAP
	map<PLAYERDIRECTION, Enemy*>			_mPlayerEnemyTile;
	map<PLAYERDIRECTION, Enemy*>::iterator	_miPlayerEnemyTile;

	//�����̺� 
	map<PLAYERDIRECTION, slave*>            _mPlayerSlaveTile;
	map<PLAYERDIRECTION, slave*>::iterator _miPlayerSlaveTile;

	//������Ż
	map<PLAYERDIRECTION, deathMetal*>            _mPlayerdeathMetalTile;
	map<PLAYERDIRECTION, deathMetal*>::iterator   _miPlayerdeathMetalTile;

	//����Ʈ vector
	vector<alphaImageEffect*>		     _vEffect; 
	vector<alphaImageEffect*>::iterator _viEffect;

	//�κ��丮 
	vector<tagItem*>				_vInven;
	vector<tagItem*>::iterator  _viInven;
private:
	tagPlayer	_player;	// �÷��̾�
	jump*		_jump;		// ���� 
	NOWSTAGE _nowStage;     // ���� �������� 
	float _worldTimeCount;	// ���� Ÿ�� 
	float _distance;		// Ÿ�� ���� �Ÿ� 
	float _time;			// �ð� 
	float _angle;			// ���� 
	float _shadow;			// �׸���

	int _previousIdx;	    // ���� idx,idy
	int _previousIdy;

	bool _isMoving;			// BOOL ���������̵�
	bool _isKeyPress;		// KEY �Է� �� ��Ʈ �Ǵ� 
	bool _isKeyDown;		// KEY �Է� �Ǵ�
	bool _reversMove;		// ���Ⱑ ���� ��

	array<int,4> bodyRight; // ��� �ٲٱ� ���� �迭 
	array<int,4> bodyLeft;	// 

	tagItem* currentItem;   // ���� �������� ����Ʈ���� ���� temp�� 

	bool _combo;			// �޺��� 
	float _comboCountTime;	// �޺� �ð� �� 
	int playerAttackSoundID;// �÷��̾� �޺��� ���� ������ �����ϱ� ���� �� 
public:
	//��������������������������������� �޺� ���� ���������������������������������
	player();
	~player();

	HRESULT init(int idx, int idy, int tileSizeX, int tileSizeY);
	void release();
	void update();
	void render();
	void effectRender();

	// ���� �Լ� 
	void keyControl();	 // ���Ű
	void playerMove();	 // �̵� 
	void setJump() { _jump->setJumping(); }

	// ����Ʈ ���� �Լ� 
	void playerEffect_Miss();					
	void playerEffect_Shovel(tagTile* tile);
	void playerEffect_Attack(const char* imageName,tagTile* tile, int frameY);
	void playerEffect_Attack(const char* imageName, float x, float y, int frameY);
	void playerEffect_Attack(const char* imageName, int x, int y, int frameY);
	void playerEffect_Attack();

	bool getCombo() {return _combo;}
	void setCombo() { _combo = false; }
	
	void tileCheck();	 // Ÿ�� ���� 
	void wallCheck();	 // ���Ǵ�
	void enemyCheck();	 // ���� �Ǵ�
	void trapCheck();	 // ���� �Ǵ�
	void itempCheck();   // ������ �Ǵ�

	void makeItem(WEAPON weapon, ARMOR armor, STUFF stuff, int framex, int framey ,int sight,int damege, float guard, float hp);  //�κ��丮��  ������ ���� 
	void playerHit(int damage) { _player.hp = _player.hp - damage; }  // �ǰ� 
	void StateMove();		// �̵� �Ǵ�		

	//��������������������������������� ������ �����ڡ��������������������������������
	tagPlayer			getPlayer()			{ return _player; }			   //  ���� ��� 
	tagPlayer*		    PlayerAddress()	    { return &_player; }
	PLAYERDIRECTION		getDirection()		{ return _player.direction; }  //  ���� 
	bool   getPlayerKey()	{ return _isKeyPress;}	  // ��Ʈ�Ŵ��� ��� 
	float* getPlayerY()		{ return &_shadow; }	  // ��Ʈ���� ��� 

	void setPlayerKeyDown()				  { _isKeyDown = false; }  // ��Ʈ�Ŵ��� KEY�ʱ�ȭ
	void setPlayerKey(bool value = false) {	_isKeyPress = value;}  // ��Ʈ�Ŵ��� ���  

	//��������������������������������� �浹 ó���� ���� MAP�� ���������������������������������
	void setPlayerTile(map<PLAYERDIRECTION, tagTile*> tile)		 { _mPlayerTile = tile; }
	void setPlayerEnemyTile(map<PLAYERDIRECTION, Enemy*> tile)	 { _mPlayerEnemyTile = tile; }
	void setSlaveTile(map<PLAYERDIRECTION, slave*> tile) { _mPlayerSlaveTile = tile; }
	void setDeathMetal(map<PLAYERDIRECTION, deathMetal*> tile) { _mPlayerdeathMetalTile = tile; }
	
	//��������������������������������� �κ��丮 ��ȣ �ۿ�  ���������������������������������
	void itemUse();		 // ������ ���� 
	vector<tagItem*> getVInven() { return _vInven; }    // UI�� ������ ���� ������ 

	//�̹��� ����
	void imageSetting()
	{
		//�÷��̾� �̹���
		IMAGEMANAGER->addFrameImage("player1_heads", "./image/player/player1_heads.bmp", 384, 96, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("player1_armor_body_xmas", "./image/player/player1_armor_body_xmas.bmp", 384, 240, 8, 5, true, RGB(255, 0, 255));
		//����Ʈ
		IMAGEMANAGER->addImage("shovel_basic", "./image/player/shovel_basic.bmp", 48, 48, true, RGB(255, 0, 255), true); // �� 
		IMAGEMANAGER->addImage("player_effect_missed", "./image/player/TEMP_missed.bmp", 72, 26, true, RGB(255, 0, 255), true);  // ������ 
		IMAGEMANAGER->addFrameImage("swipe_dagger", "./image/player/swipe_dagger.bmp", 144, 192, 3, 4, true, RGB(255, 0, 255));
		// ���
		IMAGEMANAGER->addFrameImage("swipe_longsword����", "./image/player/swipe_longsword����.bmp", 192, 192, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("swipe_longsword�¿�", "./image/player/swipe_longsword�¿�.bmp", 384, 96, 4, 2, true, RGB(255, 0, 255));
		// ���� ��
		IMAGEMANAGER->addFrameImage("swipe_broadsword����", "./image/player/swipe_broadsword����.bmp", 432, 96, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("swipe_broadsword�¿�", "./image/player/swipe_broadsword�¿�.bmp", 144, 288, 3, 2, true, RGB(255, 0, 255));
		// �����Ǿ� 
		IMAGEMANAGER->addFrameImage("swipe_rapier����", "./image/player/swipe_rapier����.bmp", 192, 192, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("swipe_rapier�¿�", "./image/player/swipe_rapier�¿�.bmp", 384, 96, 4, 2, true, RGB(255, 0, 255));
	
		//������ �ִϸ��̼�
		int headRight[] = { 0,1,2,3,4,5,6,7 };
		KEYANIMANAGER->addArrayFrameAnimation("headRight", "player1_heads", headRight, 8, 10, true);

		int bodyRight[] = { 0,1,2,3 };
		KEYANIMANAGER->addArrayFrameAnimation("bodyRight", "player1_armor_body_xmas", bodyRight, 4, 10, true);

		// ���� �ִϸ��̼�
		int headLeft[] = { 15,14,13,12,11,10,9,8 };
		KEYANIMANAGER->addArrayFrameAnimation("headLeft", "player1_heads", headLeft, 8, 10, true);

		int	bodyLeft[] = { 7,6,5,4 };
		KEYANIMANAGER->addArrayFrameAnimation("bodyLeft", "player1_armor_body_xmas", bodyLeft, 4, 10, true);

	}
	void itemRemove(int num) { _vInven.erase(_vInven.begin() + num); }

	// �������� ���� Ÿ�� �ʱ�ȭ 
	void collisionSettingStage() 
	{
		if (!_mPlayerEnemyTile.empty()) _mPlayerEnemyTile.clear();
		if (!_mPlayerTile.empty())_mPlayerTile.clear();
	}
	// ������������ ���� Ÿ�� �ʱ�ȭ 
	void collisionSettingBoss()
	{
		if(!_mPlayerSlaveTile.empty())_mPlayerSlaveTile.clear();
		if(!_mPlayerdeathMetalTile.empty())_mPlayerdeathMetalTile.clear();
	}

	void setStage() { _nowStage = NOWSTAGE_STAGE; }			// �������� 
	void setBossStage() { _nowStage = NOWSTAGE_BOSS; }		// ���� 
	void playerDie();										// �÷��̾� ����� 
	void setPlayerHP(int hp) { _player.hp = hp; }			// ü�� ���� 
};	


