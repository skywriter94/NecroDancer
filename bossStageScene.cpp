#include "stdafx.h"
#include "bossStageScene.h"

#include "player.h"
#include "UImanager.h"

bossStageScene::bossStageScene()
{
}

bossStageScene::~bossStageScene()
{
}

HRESULT bossStageScene::init()
{
	_stageScene->release();
	_addBossImage->add_BossImage();
	_addBossImage->add_BossAnimation();

	_addSlaveImage->add_SlaveImage();
	_addSlaveImage->add_SlaveAnimation();

	_player = _stageScene->getPlayerAddress();								// �÷��̾� ��ũ
	_player->collisionSettingStage();
	_ui = _stageScene->getUiAddress();										// ui ��ũ
	
	bossStageMap_Load();													// ���Ͽ� �ִ� ���� �������� ���� �ҷ��ͼ� ���ͷ� �������ش�.

	playerPos_Setting();													// ���� ���������� ���� �� �÷��̾��� ��ġ�� ���� ��ġ�� ����ش�.

	distanceCheck = false;
	introSound = false;
	boss_Dead = false;

	_sm = new slaveManager;
	_sm->init();

	start_Slave_Create();													// �⺻���� �����濡 �ִ� �����̺� ����

	_zOrder = new zOrder;
	_zOrder->init();

	_floodFill = new visionFloodFill;
	_floodFill->init();

	// ���� ���� ���� ���� ���� �ʱ�ȭ
	bossSceneSetting();

	_player->setBossStage(); // ������������ ���� �߰� 
	BEATMANAGER->init();
	BEATMANAGER->AllStopMusic();
	return S_OK;
}

void bossStageScene::release()
{
}

void bossStageScene::update()
{

	if (!OPTION->getplayerDie())
	{
		// �÷��̾� �ε��� ���
		//cout << _player->getPlayer().idx << ", " << _player->getPlayer().idy << endl;
		endScene();
		// ���� ���� ���� ������ �÷��̰� �����ϴ�.
		bossSceneStart();


		if (_scene_Starter.isOpen)
		{
			_player->update();

			// �÷��̾� �ε��� ���
			//cout << _player->getPlayer().idx << ", " << _player->getPlayer().idy << endl;
			endScene();
			// ���� ���� ���� ������ �÷��̰� �����ϴ�.
			bossSceneStart();


			// �÷��̾ ���� �������� ����
			bossSceneDoorOpen();
			BEATMANAGER->SetMusicID(5);

			// �÷��̾ �����湮�� ���� ������ ������ �� ���� true�� �ٲ��.
			if (_scene_Starter.isDoorOpen)
			{
				
				if (!_deathMetal->getBoss_Dead()) _deathMetal->update();
				
				if (!_deathMetal->getBoss_Dead())  boss_PhaseMove();	// ���� ������ ����
				_ui->update();
				_sm->update();

				// �÷��̾ ���� ��ó�� �ִ��� �������� ã���ش�. (������ ����)
				if (!_deathMetal->getBoss_Dead())  closePlayer(_player, _deathMetal);

				// �÷��̾ �����̺� ��ó�� �ִ��� �������� ã���ش�.	(������ ����)
				searchSlave(_sm->get_SlaveList(), _player);

				// ���� ������ ����
				//if (KEYMANAGER->isToggleKey(VK_NUMPAD9))
				//{
					if (!_deathMetal->getBoss_Dead())  boss_Move_Player();
				//}

				// �����̺� ������ ����
				
				slave_Move_Player();
				


				// �����̺� �׽�Ʈ�� ��ȯ
				//if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD3))
				//{
				//	_sm->create_Slave(SLAVE_TYPE::SLAVE_SKELETON_YELLOW, 13, 13);
				//	//_sm->create_Slave(SLAVE_TYPE::SLAVE_BAT, _deathMetal->getBoss_Index().x + 1, _deathMetal->getBoss_Index().y - 1);
				//}

			}

			BEATMANAGER->update();


			// �÷��̾� �浹 
			_player->setDeathMetal(_collision.collision_player_Metal_tile(_deathMetal, _player));
			_player->setSlaveTile(_collision.collision_player_slave_tile(&_sm->get_SlaveList(), _player));

			tileOnOff();
			_zOrder->zOrderSetup(_player->getPlayer().idx, _player->getPlayer().idy, _tiles, _player, _sm, _deathMetal);
			_zOrder->update();
			_floodFill->setVision(_tiles, _player->getPlayer().idx, _player->getPlayer().idy, _player->getPlayer().sight);
			_player->setPlayerTile(_collision.collision_player_tile(&_vTotalList, _player));


			if (_deathMetal->getBoss_HP() <= 0)
			{
			
				if (!boss_Dead)
				{
					// ���� �״� ���带 ���ش�.
					SOUNDMANAGER->play("deathmetal_death");
					SOUNDMANAGER->play("vo_cad_yeah_02", 1.5f);
					boss_Dead = true;
				}
			
				bossClear();	// ���� ü���� 0�̶�� Ŭ������ ���̴�.
				_deathMetal->setBoss_Index(0, 0);
				_deathMetal->settingBossPos(0, 0, TILESIZE, TILESIZE);
			}
		}
	}

}

void bossStageScene::render()
{
	// ���� ������ش�.
	if (_vTotalList.size() > 0)
	{
		for (_viTotalList = _vTotalList.begin(); _viTotalList != _vTotalList.end(); _viTotalList++)
		{
			if ((*_viTotalList)->type == TYPE_NONE) continue;
			// Ÿ���� Ÿ���� TYPE_NONE�� �ƴ϶�� �׷��ش�.
			if ((*_viTotalList)->type != TYPE_NONE)
			{
				// Ÿ���� �Ӽ��� ���� �̹����� �Ѹ���.		

				findTileImage();
			}
		}

		for (_viTotalList = _vTotalList.begin(); _viTotalList != _vTotalList.end(); _viTotalList++)
		{
			if ((*_viTotalList)->type == TYPE_NONE) continue;
			if ((*_viTotalList)->alphaValue <= 0)
			{
				// ���� NONE�� �ƴ϶�� ���
				if ((*_viTotalList)->wall != W_NONE)
				{
					//	W_WALL, W_ITEM_WALL, W_WALL2, W_SHOP_WALL,
					//	W_END_WALL, W_BOSS_WALL,
					//	W_DOOR, W_TORCH, W_FIRE_WALL,
					//	W_NONE
					IMAGEMANAGER->frameRender("wallTiles", CAMERAMANAGER->getWorldDC(),
						(*_viTotalList)->rc.left, (*_viTotalList)->rc.top - 30,
						(*_viTotalList)->wallFrameX, (*_viTotalList)->wallFrameY);
					continue;
				}

				// ������ NONE�� �ƴ϶�� ���
				if ((*_viTotalList)->trap != TRAP_NONE)
				{
					//	TRAP_FAST_BEAT, TRAP_SLOW_BEAT, TRAP_MUTE,
					//	TRAP_LT_JUMP, TRAP_T_JUMP, TRAP_RT_JUMP,
					//	TRAP_L_JUMP, TRAP_R_JUMP,
					//	TRAP_LB_JUMP, TRAP_B_JUMP, TRAP_RB_JUMP,
					//	TRAP_CONFUSE,
					//	TRAP_BOMB,
					//	TRAP_NIDDLE,
					//	TRAP_SHADOW, TRAP_NIDDLE_SHADOW,
					//	TRAP_NONE
					IMAGEMANAGER->frameRender("trapTiles", CAMERAMANAGER->getWorldDC(),
						(*_viTotalList)->rc.left, (*_viTotalList)->rc.top,
						(*_viTotalList)->trapFrameX, (*_viTotalList)->trapFrameY);
					continue;
				}
			}
			else
			{
				// ���� NONE�� �ƴ϶�� ���
				if ((*_viTotalList)->wall != W_NONE)
				{
					//	W_WALL, W_ITEM_WALL, W_WALL2, W_SHOP_WALL,
					//	W_END_WALL, W_BOSS_WALL,
					//	W_DOOR, W_TORCH, W_FIRE_WALL,
					//	W_NONE
					IMAGEMANAGER->findImage("wallTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(),
						(*_viTotalList)->rc.left, (*_viTotalList)->rc.top - 30,
						(*_viTotalList)->wallFrameX, (*_viTotalList)->wallFrameY, (*_viTotalList)->alphaValue);
					continue;
				}

				// ������ NONE�� �ƴ϶�� ���
				if ((*_viTotalList)->trap != TRAP_NONE)
				{
					//	TRAP_FAST_BEAT, TRAP_SLOW_BEAT, TRAP_MUTE,
					//	TRAP_LT_JUMP, TRAP_T_JUMP, TRAP_RT_JUMP,
					//	TRAP_L_JUMP, TRAP_R_JUMP,
					//	TRAP_LB_JUMP, TRAP_B_JUMP, TRAP_RB_JUMP,
					//	TRAP_CONFUSE,
					//	TRAP_BOMB,
					//	TRAP_NIDDLE,
					//	TRAP_SHADOW, TRAP_NIDDLE_SHADOW,
					//	TRAP_NONE
					IMAGEMANAGER->findImage("trapTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(),
						(*_viTotalList)->rc.left, (*_viTotalList)->rc.top,
						(*_viTotalList)->trapFrameX, (*_viTotalList)->trapFrameY, (*_viTotalList)->alphaValue);
					continue;
				}
			}

		}
	}

	// ������ �÷��̾��� ���� ������ ã�´�.
	//z_Order_Player_Boss();

	_sm->render();

	_zOrder->render();				 // Z ���� 
	_player->effectRender();	 	// �÷��̾� ����Ʈ 

	// ������ ���� ������ ������ ����Ʈ�� �׷��ش�. (size�� 0 �̻��̶��)
	if (_vEffect.size() > 0 && !_deathMetal->getBoss_Dead())	boss_Base_Attack_Render();

	// �����̹����� �ѷ��ش�.
	CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);

	// UI ���
	_ui->render();

	// �׽�Ʈ ��Ʈ ��� ���

	if (_scene_Starter.isOpen)
	{
		BEATMANAGER->render();
	}

	bossSceneRender();
	OPTION->render(getMemDC()); // �÷��̾� ����� ���� ȭ�� ���� �߰� 
}

void bossStageScene::bossStageMap_Load()
{
	// ���� �������� ���� �ҷ��ͼ� 
	// _tiles�� ��´�.
	HANDLE file;
	DWORD read;

	file = CreateFile("Boss_SaveFile.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);

	int i = 0;

	while (i < TILEX * TILEY)
	{
		// Ÿ���� Ÿ���� NONE�� �ƴ϶�� ���Ϳ� ��´�.
		if (_tiles[i].type != TYPE_NONE)
		{
			if (_tiles[i].type == TYPE_TERRAIN)
			{
				_tiles[i].wall == W_NONE;
			}
			_tiles[i].alphaValue = 255;

			if (_tiles[i].character == CHAR_BOSS)
			{
				_deathMetal = new deathMetal;
				_deathMetal->init("������Ż", _tiles[i].idX, _tiles[i].idY, TESTTILESIZE, TESTTILESIZE);		// �ӽ÷� ������Ż�� �ش� ��ġ�� ��ġ�ߴ�.
			}

			if (_tiles[i].character == CHAR_PLAYER)
			{
				_player->PlayerAddress()->idx = _tiles[i].idX;
				_player->PlayerAddress()->idy = _tiles[i].idY;
			}

			if (_tiles[i].terrain == TR_STAIR)
			{
				_endX = _tiles[i].idX;
				_endY = _tiles[i].idY;
			}
			_vTotalList.push_back(&_tiles[i]);
		}

		i++;
	}


}

void bossStageScene::findTileImage()
{
	RECT temp;
	if (IntersectRect(&temp, &CAMERAMANAGER->getCamera_Rect(), &(*_viTotalList)->rc))
	{
		// ������ NONE�� �ƴ϶�� ���
		if ((*_viTotalList)->terrain != TR_NONE)
		{
			//	TR_BASIC_STAGE_TILE, TR_BASIC_COMBO_TILE,
			//	TR_BOSS_STAGE_TILE, TR_BOSS_COMBO_TILE,
			//	TR_STAIR, TR_SHOP,
			//	TR_NONE,
			//	TR_END,
			//	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER
			if ((*_viTotalList)->alphaValue <= 0)
			{
				IMAGEMANAGER->frameRender("terrainTiles", CAMERAMANAGER->getWorldDC(),
					(*_viTotalList)->rc.left, (*_viTotalList)->rc.top,
					(*_viTotalList)->terrainFrameX, (*_viTotalList)->terrainFrameY);
			}
			else
			{
				IMAGEMANAGER->findImage("terrainTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(),
					(*_viTotalList)->rc.left, (*_viTotalList)->rc.top,
					(*_viTotalList)->terrainFrameX, (*_viTotalList)->terrainFrameY, (*_viTotalList)->alphaValue);
			}
		}
	}
}

void bossStageScene::z_Order_Player_Boss()
{
	// ������ �ε���y�� �÷��̾��� �ε���y���� ũ�ٸ� �÷��̾ ���� �׷��ش�.
	// �׷��� �ʴٸ� ������ ���� �׷��ش�.
	if (_deathMetal->getBoss_Index().y > _player->getPlayer().idy)	// ������ �÷��̾�� �տ� �ִ�.
	{
		//_player->render();
		//if (_deathMetal->getBoss_HP() > 0)	_deathMetal->render();

	}
	else	// ������ �÷��̾�� �ڿ� �ִ�.
	{
		//if (_deathMetal->getBoss_HP() > 0)	_deathMetal->render();
		//_player->render();

	}

}

void bossStageScene::playerPos_Setting()
{
	_player->PlayerAddress()->x = _player->PlayerAddress()->idx * TESTTILESIZE + (TESTTILESIZE / 2);
	_player->PlayerAddress()->y = _player->PlayerAddress()->idy * TESTTILESIZE + (TESTTILESIZE / 3);
	_player->PlayerAddress()->rc = RectMakeCenter(_player->PlayerAddress()->x, _player->PlayerAddress()->y,
		_player->PlayerAddress()->bodyImage->getFrameWidth(), _player->PlayerAddress()->headImage->getFrameHeight());
	CAMERAMANAGER->set_CameraXY(_player->PlayerAddress()->idx * TESTTILESIZE + (TESTTILESIZE / 2),
		_player->PlayerAddress()->idy * TESTTILESIZE + (TESTTILESIZE / 3));

}

void bossStageScene::closePlayer(player* player, deathMetal* deathMetal)
{
	// �÷��̾�� ������ ��Ʈ ������ ��´�.
	POINTFLOAT playerCenter;
	POINTFLOAT bossCenter;
	playerCenter.x = 0;
	playerCenter.y = 0;
	bossCenter.x = 0;
	bossCenter.y = 0;

	// ���ϴ� ���� ��� ã�Ҵٸ� �ݺ����� ���ö� ���
	bool find_P, find_B;
	find_P = find_B = false;



	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		// �÷��̾� �ε����� ���� Ÿ���� ã�Ƽ� ��Ʈ�� ������ ���Ѵ�.
		if (_vTotalList[i]->idX == player->getPlayer().idx && _vTotalList[i]->idY == player->getPlayer().idy)
		{
			playerCenter.x = (_vTotalList[i]->rc.left + _vTotalList[i]->rc.right) / 2;
			playerCenter.y = (_vTotalList[i]->rc.top + _vTotalList[i]->rc.bottom) / 2;

			// ã�Ҵٸ� true
			find_P = true;
		}

		// ���� �ε����� ���� Ÿ���� ã�Ƽ� ��Ʈ�� ������ ���Ѵ�.
		if (_vTotalList[i]->idX == deathMetal->getBoss_Index().x && _vTotalList[i]->idY == deathMetal->getBoss_Index().y)
		{
			bossCenter.x = (_vTotalList[i]->rc.left + _vTotalList[i]->rc.right) / 2;
			bossCenter.y = (_vTotalList[i]->rc.top + _vTotalList[i]->rc.bottom) / 2;
			// ã�Ҵٸ� true
			find_B = true;
		}

		// �� �� ã�Ҵٸ� �ݺ����� ���´�.
		if (find_P && find_B) break;
	}

	// �÷��̾�� ������ �Ÿ��� �����Ѵ�.
	float distance = getDistance(bossCenter.x, bossCenter.y,
		playerCenter.x, playerCenter.y);



	// ���� Ÿ���� �������� 52�� ���������� 0�� ���´ٸ� 52(�翷���Ʒ�)�� �Ÿ��� ��� �Ѵ�.
	if ((int)distance % TILESIZE == 0)
	{
		// �Ÿ��� �޶������� ���� �ٲ�� ������ �ѹ��� ������ �ȴ�.
		if (!distanceCheck)
		{
			// �÷��̾ �ν� ���� �ȿ� �ִٸ� �����츦 ���´�.
			if (distance < TILESIZE * BOSS_RECOGNITION_RANGE)
			{
				distanceCheck = true;
				deathMetal->setBoss_ClosePlayer(true);
				//deathMetal->ChangeAni();
			}
		}

		if (distanceCheck)
		{
			// �÷��̾ �ν� ���� �ȿ� ���ٸ� �����츦 �Դ´�.
			if (distance >= TILESIZE * BOSS_RECOGNITION_RANGE)
			{
				distanceCheck = false;
				deathMetal->setBoss_ClosePlayer(false);
				//deathMetal->ChangeAni();
			}
		}
	}


	//cout << "distance :" << distance << endl;
	//cout << "range : " << TILESIZE * BOSS_RECOGNITION_RANGE << endl;
	//cout << distanceCheck << endl;

	// ���� Ÿ�� �������� 52�� ���������� 0�� ������ �ʴ´ٸ� �밢���̶�� ��
	else
	{
		// �Ÿ��� �޶������� ���� �ٲ�� ������ �ѹ��� ������ �ȴ�.
		if (!distanceCheck)
		{
			// �÷��̾ �ν� ���� �ȿ� �ִٸ� �����츦 ���´�. �νĹ��� ����ó���� ���ش�.
			if (distance < (TILESIZE) * (BOSS_RECOGNITION_RANGE - 1) && distance < 165)
			{
				distanceCheck = true;
				deathMetal->setBoss_ClosePlayer(true);
				//deathMetal->ChangeAni();
			}
		}

		if (distanceCheck)
		{
			// �÷��̾ �ν� ���� �ȿ� ���ٸ� �����츦 �Դ´�. �νĹ��� ����ó���� ���ش�.
			if (distance >= (TILESIZE) * (BOSS_RECOGNITION_RANGE - 1) || distance > 165)
			{
				distanceCheck = false;
				deathMetal->setBoss_ClosePlayer(false);
				//deathMetal->ChangeAni();
			}
		}
	}
}

void bossStageScene::searchSlave(vector<slave*> vSlaveList, player* player)
{
	for (int i = 0; i < vSlaveList.size(); ++i)
	{
		closePlayer_Slave(player, vSlaveList[i]->get_Slave());
	}
}

void bossStageScene::closePlayer_Slave(player* player, SLAVE_INFO* slave)
{
	// �÷��̾�� �����̺��� ��Ʈ ������ ��´�.
	POINTFLOAT playerCenter;
	POINTFLOAT slaveCenter;



	// ���ϴ� ���� ��� ã�Ҵٸ� �ݺ����� ���ö� ���
	bool find_P, find_S;
	find_P = find_S = false;



	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		// �÷��̾� �ε����� ���� Ÿ���� ã�Ƽ� ��Ʈ�� ������ ���Ѵ�.
		if (_vTotalList[i]->idX == player->getPlayer().idx && _vTotalList[i]->idY == player->getPlayer().idy)
		{
			playerCenter.x = (_vTotalList[i]->rc.left + _vTotalList[i]->rc.right) / 2;
			playerCenter.y = (_vTotalList[i]->rc.top + _vTotalList[i]->rc.bottom) / 2;

			// ã�Ҵٸ� true
			find_P = true;
		}

		// �����̺� �ε����� ���� Ÿ���� ã�Ƽ� ��Ʈ�� ������ ���Ѵ�.
		if (_vTotalList[i]->idX == slave->pos.index.x && _vTotalList[i]->idY == slave->pos.index.y)
		{
			slaveCenter.x = (_vTotalList[i]->rc.left + _vTotalList[i]->rc.right) / 2;
			slaveCenter.y = (_vTotalList[i]->rc.top + _vTotalList[i]->rc.bottom) / 2;

			// ã�Ҵٸ� true
			find_S = true;
		}

		// �� �� ã�Ҵٸ� �ݺ����� ���´�.
		if (find_P && find_S) break;
	}



	// �÷��̾�� �����̺��� �Ÿ��� �����Ѵ�.
	float distance = getDistance(slaveCenter.x, slaveCenter.y,
		playerCenter.x, playerCenter.y);


	// ���� Ÿ���� �������� 52�� ���������� 0�� ���´ٸ� 52(�翷���Ʒ�)�� �Ÿ��� ��� �Ѵ�.
	if ((int)distance % TILESIZE == 0)
	{
		// �Ÿ��� �޶������� ���� �ٲ�� ������ �ѹ��� ������ �ȴ�.
		if (!slave->b_Value.distanceCheck)
		{
			// �÷��̾ �ν� ���� �ȿ� �ִٸ� �����츦 ���´�.
			if (distance < TILESIZE * BOSS_RECOGNITION_RANGE)
			{
				slave->b_Value.distanceCheck = true;
				slave->b_Value.isClosePlayer = true;
			}
		}

		if (slave->b_Value.distanceCheck)
		{
			// �÷��̾ �ν� ���� �ȿ� ���ٸ� �����츦 �Դ´�.
			if (distance >= TILESIZE * BOSS_RECOGNITION_RANGE)
			{
				slave->b_Value.distanceCheck = false;
				slave->b_Value.isClosePlayer = false;
			}
		}
	}

	// ���� Ÿ�� �������� 52�� ���������� 0�� ������ �ʴ´ٸ� �밢���̶�� ��
	else
	{
		// �Ÿ��� �޶������� ���� �ٲ�� ������ �ѹ��� ������ �ȴ�.
		if (!slave->b_Value.distanceCheck)
		{
			// �÷��̾ �ν� ���� �ȿ� �ִٸ� �����츦 ���´�. �νĹ��� ����ó���� ���ش�.
			if (distance < (TILESIZE) * (BOSS_RECOGNITION_RANGE - 1) && distance < 165)
			{
				slave->b_Value.distanceCheck = true;
				slave->b_Value.isClosePlayer = true;
			}
		}

		if (slave->b_Value.distanceCheck)
		{
			// �÷��̾ �ν� ���� �ȿ� ���ٸ� �����츦 �Դ´�. �νĹ��� ����ó���� ���ش�.
			if (distance >= (TILESIZE) * (BOSS_RECOGNITION_RANGE - 1) || distance > 165)
			{
				slave->b_Value.distanceCheck = false;
				slave->b_Value.isClosePlayer = false;
			}
		}
	}

}

void bossStageScene::findPlayer(player* player, deathMetal* deathMetal, UImanager* ui)
{

	// ������ �ε������� �÷��̾��� �ε����� ���� ���� ��Ƶд�. (�÷��̾��� ��ġ�� ã��, ��� ������ ������� �񱳿��� ����� ��)
	int x = deathMetal->getBoss_Index().x - player->getPlayer().idx;
	int y = deathMetal->getBoss_Index().y - player->getPlayer().idy;


	// x�� ª�ٸ� flase, y�� ª�ٸ� true�� ���� �����Ѵ�.
	bool x_OR_y = false;

	// ��ȣ�� ���ּ� ��� ������ �� ª������ ã���ش�. (ª�� ������� ���� ã�� �ȴ�.)
	if (abs(x) > abs(y))
	{
		// y�� �� ª�ٸ� true�� �־��ش�.
		x_OR_y = true;
	}
	else
	{
		// x�� �� ª�ٸ� false�� �־��ش�.
		x_OR_y = false;
	}

	// x, y �߿� x�� �� ª�ٸ� x���� ã���ش�.
	if (x_OR_y)
	{
		// x�� ������ �÷��̾�� ���ʿ� �ִ�.
		if (x > 0)
		{
			// ���� �ٷ� �տ� �÷��̾ ���� ��쿡�� �������� �����. ( �Ǵ� ���� ������ �Ѵ�.)
			if (deathMetal->getBoss_Index().x - 1 == player->getPlayer().idx
				&& deathMetal->getBoss_Index().y == player->getPlayer().idy)
			{
				if (_collision.collision_DeathMetal_Find_Player(_player, _deathMetal))
				{
					// �÷��̾ �տ� �ִٸ� ���� ������ ���ش�.
					//ui->set_HP();
					_player->playerHit(deathMetal->getBoss_Atk());
					CAMERAMANAGER->Camera_WorldDC_Shake();
				}

				// �÷��̾�� ���� ���� ����Ʈ�� �׷��ش�.
				boss_Base_Attack_Render("base_Attack", player);

				// ���⼭ ������ �����ְ�, ���� bool ���� ���ش�.
				deathMetal->setBoss_Direction(BD_LEFT);

				//// �÷��̾��� ���� ��ǥ�� �޾ƿ´�.
				//deathMetal->setBoss_BaseAttack_Pos(player->getPlayer().x, player->getPlayer().y);
				//
				//// ����Ʈ �̹����� �־��ش�.
				//deathMetal->setBoss_BaseSkill_Image("base_Attack");
				//
				//// � ����Ʈ�� �Ѹ��� �־��ش�.
				//deathMetal->setBoss_BaseSkill("Base_Attack");
				//
				//// ����Ʈ�� ���� ��Ų��.
				//deathMetal->start_AttackAni();

				// ���� �̵��� ���� ���� ī��Ʈ�� �ٽ� ä���ش�.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());
			}

			// �÷��̾ ���ٸ� �̵��� ���ش�.
			else
			{
				// ���⼭ ������ �����ְ�, ���� bool ���� ���ش�.
				deathMetal->setBoss_Direction(BD_LEFT);

				// ������������ ����� ���� �ð��� ���� ���ش�.
				deathMetal->setBoss_WorldTime(TIMEMANAGER->getWorldTime());

				// �̵� ���꿡 �ʿ��� bool ���� true�� �ٲ��ִ� �Լ�
				deathMetal->setBoss_Move_BoolValue_Ture();

				// ���� �̵��� ���� ���� ī��Ʈ�� �ٽ� ä���ش�.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());

				deathMetal->setBoss_Angle(PI);
			}
		}
		// x�� ������� �÷��̾�� �����ʿ� �ִ�.
		else
		{
			// ���� �ٷ� �տ� �÷��̾ ���� ��쿡�� �������� �����. ( �Ǵ� ���� ������ �Ѵ�.)
			if (deathMetal->getBoss_Index().x + 1 == player->getPlayer().idx
				&& deathMetal->getBoss_Index().y == player->getPlayer().idy)
			{
				if (_collision.collision_DeathMetal_Find_Player(_player, _deathMetal))
				{
					// �÷��̾ �տ� �ִٸ� ���� ������ ���ش�.
					//ui->set_HP();
					_player->playerHit(deathMetal->getBoss_Atk());
					CAMERAMANAGER->Camera_WorldDC_Shake();
				}

				// �÷��̾�� ���� ���� ����Ʈ�� �׷��ش�.
				boss_Base_Attack_Render("base_Attack", player);

				// ���⼭ ������ �����ְ�, ���� bool ���� ���ش�.
				deathMetal->setBoss_Direction(BD_RIGHT);

				//// �÷��̾��� ���� ��ǥ�� �޾ƿ´�.
				//deathMetal->setBoss_BaseAttack_Pos(player->getPlayer().x, player->getPlayer().y);
				//
				//// ����Ʈ �̹����� �־��ش�.
				//deathMetal->setBoss_BaseSkill_Image("base_Attack");
				//
				//// � ����Ʈ�� �Ѹ��� �־��ش�.
				//deathMetal->setBoss_BaseSkill("Base_Attack");
				//
				//// ����Ʈ�� ���� ��Ų��.
				//deathMetal->start_AttackAni();

				// ���� �̵��� ���� ���� ī��Ʈ�� �ٽ� ä���ش�.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());
			}

			// �÷��̾ ���ٸ� �̵��� ���ش�.
			else
			{
				// ���⼭ ������ �����ְ�, ���� bool ���� ���ش�.
				deathMetal->setBoss_Direction(BD_RIGHT);

				// ������������ ����� ���� �ð��� ���� ���ش�.
				deathMetal->setBoss_WorldTime(TIMEMANAGER->getWorldTime());

				// �̵� ���꿡 �ʿ��� bool ���� true�� �ٲ��ִ� �Լ�
				deathMetal->setBoss_Move_BoolValue_Ture();

				// ���� �̵��� ���� ���� ī��Ʈ�� �ٽ� ä���ش�.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());

				deathMetal->setBoss_Angle(0);
			}
		}
	}

	// x, y �߿� y�� �� ª�ٸ� y���� ã���ش�.
	if (!x_OR_y)
	{
		// y�� ������ �÷��̾�� ���ʿ� �ִ�.
		if (y > 0)
		{
			// ���� �ٷ� �տ� �÷��̾ ���� ��쿡�� �������� �����. ( �Ǵ� ���� ������ �Ѵ�.)
			if (deathMetal->getBoss_Index().x == player->getPlayer().idx
				&& deathMetal->getBoss_Index().y - 1 == player->getPlayer().idy)
			{
				if (_collision.collision_DeathMetal_Find_Player(_player, _deathMetal))
				{
					// �÷��̾ �տ� �ִٸ� ���� ������ ���ش�.
					//ui->set_HP();
					_player->playerHit(deathMetal->getBoss_Atk());
					CAMERAMANAGER->Camera_WorldDC_Shake();
				}

				// �÷��̾�� ���� ���� ����Ʈ�� �׷��ش�.
				boss_Base_Attack_Render("base_Attack", player);

				// ���⼭ ������ �����ְ�, ���� bool ���� ���ش�.
				deathMetal->setBoss_Direction(BD_UP);

				//// �÷��̾��� ���� ��ǥ�� �޾ƿ´�.
				//deathMetal->setBoss_BaseAttack_Pos(player->getPlayer().x, player->getPlayer().y);
				//
				//// ����Ʈ �̹����� �־��ش�.
				//deathMetal->setBoss_BaseSkill_Image("base_Attack");
				//
				//// � ����Ʈ�� �Ѹ��� �־��ش�.
				//deathMetal->setBoss_BaseSkill("Base_Attack");
				//
				//// ����Ʈ�� ���� ��Ų��.
				//deathMetal->start_AttackAni();

				// ���� �̵��� ���� ���� ī��Ʈ�� �ٽ� ä���ش�.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());
			}

			// �÷��̾ ���ٸ� �̵��� ���ش�.
			else
			{
				// ���⼭ ������ �����ְ�, ���� bool ���� ���ش�.
				deathMetal->setBoss_Direction(BD_UP);

				// ������������ ����� ���� �ð��� ���� ���ش�.
				deathMetal->setBoss_WorldTime(TIMEMANAGER->getWorldTime());

				// �̵� ���꿡 �ʿ��� bool ���� true�� �ٲ��ִ� �Լ�
				deathMetal->setBoss_Move_BoolValue_Ture();

				// ���� �̵��� ���� ���� ī��Ʈ�� �ٽ� ä���ش�.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());

				deathMetal->setBoss_Angle(PI / 2.f);
			}
		}
		// y�� ������� �÷��̾�� �Ʒ��ʿ� �ִ�.
		else
		{
			// ���� �ٷ� �տ� �÷��̾ ���� ��쿡�� �������� �����. ( �Ǵ� ���� ������ �Ѵ�.)
			if (deathMetal->getBoss_Index().x == player->getPlayer().idx
				&& deathMetal->getBoss_Index().y + 1 == player->getPlayer().idy)
			{
				if (_collision.collision_DeathMetal_Find_Player(_player, _deathMetal))
				{
					// �÷��̾ �տ� �ִٸ� ���� ������ ���ش�.
					//ui->set_HP();
					_player->playerHit(deathMetal->getBoss_Atk());
					CAMERAMANAGER->Camera_WorldDC_Shake();
				}

				// �÷��̾�� ���� ���� ����Ʈ�� �׷��ش�.
				boss_Base_Attack_Render("base_Attack", player);

				// ���⼭ ������ �����ְ�, ���� bool ���� ���ش�.
				deathMetal->setBoss_Direction(BD_DOWN);

				//// �÷��̾��� ���� ��ǥ�� �޾ƿ´�.
				//deathMetal->setBoss_BaseAttack_Pos(player->getPlayer().x, player->getPlayer().y);
				//
				//// ����Ʈ �̹����� �־��ش�.
				//deathMetal->setBoss_BaseSkill_Image("base_Attack");
				//
				//// � ����Ʈ�� �Ѹ��� �־��ش�.
				//deathMetal->setBoss_BaseSkill("Base_Attack");
				//
				//// ����Ʈ�� ���� ��Ų��.
				//deathMetal->start_AttackAni();

				// ���� �̵��� ���� ���� ī��Ʈ�� �ٽ� ä���ش�.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());
			}

			// �÷��̾ ���ٸ� �̵��� ���ش�.
			else
			{

				// ���⼭ ������ �����ְ�, ���� bool ���� ���ش�.
				deathMetal->setBoss_Direction(BD_DOWN);

				// ������������ ����� ���� �ð��� ���� ���ش�.
				deathMetal->setBoss_WorldTime(TIMEMANAGER->getWorldTime());

				// �̵� ���꿡 �ʿ��� bool ���� true�� �ٲ��ִ� �Լ�
				deathMetal->setBoss_Move_BoolValue_Ture();

				// ���� �̵��� ���� ���� ī��Ʈ�� �ٽ� ä���ش�.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());

				deathMetal->setBoss_Angle(PI + PI / 2);
			}
		}
	}

}

SLAVE_DIRECTION bossStageScene::findPlayer(player* player, SLAVE_INFO* slave)
{
	// �÷��̾��� ������ ��Ƽ� ������ ���ϰ����� �����ش�.

	// �÷��̾��� ������ ã�´�.

	// x, y �� ª������ �����Ѵ�.

	// �̵� �� �̵� �Ұ��� ������Ʈ�� ã�´�.

	// ������ �ٸ� ��������

	// x, y �� ���� ���ο� �����Ѵٸ� ���� �������θ� �̵��� �Ѵ�.

	// �����̺�� �÷��̾��� Ÿ�� ������ ���Ѵ�.
	POINTFLOAT playerCenter;
	POINTFLOAT slaveCenter;
	playerCenter.x = 0;
	playerCenter.y = 0;
	slaveCenter.x = 0;
	slaveCenter.y = 0;

	// �� �� ���ϴ� ���� ã������ �ݺ������� �������´�.
	bool findPlayer, findSlave;
	findPlayer = findSlave = false;

	// �����ʿ��� �ش� �ε����� ã�� ���� �ݺ�.
	for (_viTotalList = _vTotalList.begin(); _viTotalList != _vTotalList.end(); ++_viTotalList)
	{
		// �÷��̾��� �ε����� ���� Ÿ���� ã�´�.
		if ((*_viTotalList)->idX == player->getPlayer().idx && (*_viTotalList)->idY == player->getPlayer().idy)
		{
			// Ÿ���� ��Ʈ�� �̿��Ͽ� ������ �����Ѵ�.
			playerCenter.x = ((*_viTotalList)->rc.left + (*_viTotalList)->rc.right) / 2;
			playerCenter.y = ((*_viTotalList)->rc.top + (*_viTotalList)->rc.bottom) / 2;

			findPlayer = true;
		}

		// �����̺��� �ε����� ���� Ÿ���� ã�´�.
		if ((*_viTotalList)->idX == slave->pos.index.x && (*_viTotalList)->idY == slave->pos.index.y)
		{
			// Ÿ���� ��Ʈ�� �̿��Ͽ� ������ �����Ѵ�.
			slaveCenter.x = ((*_viTotalList)->rc.left + (*_viTotalList)->rc.right) / 2;
			slaveCenter.y = ((*_viTotalList)->rc.top + (*_viTotalList)->rc.bottom) / 2;

			findSlave = true;
		}

		// ���� ��� ã�Ҵٸ� �ݺ������� ���´�.
		if (findPlayer && findSlave) break;
	}

	// �����̺�� �÷��̾���� x, y�� ���� ��´�. (�����̺� �������� ���ش�.)
	POINTFLOAT range;
	range.x = abs(slaveCenter.x - playerCenter.x);
	range.y = abs(slaveCenter.y - playerCenter.y);

	// x, y �� ª������ ���Ѵ�.
	SHORT_XY short_XY = SHORT_XY::SHORT_NONE;

	// x�� ª��.
	if (range.x < range.y)
		short_XY = SHORT_XY::SHORT_X;

	// y�� ª��.
	if (range.x > range.y)
		short_XY = SHORT_XY::SHORT_Y;


	// �����̺�� �÷��̾��� �ε��� �� ������ �ִٸ� �� ������ ���� �ϰ� ã�´�.
	FIND_CHOICE_XY find_Choice = FIND_CHOICE_XY::FC_XY;	// 0 = ����� ���, 1 = x ���⸸ ã�´�. 2 = y ���⸸ ã�´�.

	// �÷��̾��� x�� �����̺��� x�� ���ٸ� x ������ �����Ѱ� y������ ã���� �Ѵ�.
	if (player->getPlayer().idx == slave->pos.index.x)	find_Choice = FIND_CHOICE_XY::FC_Y;
	if (player->getPlayer().idy == slave->pos.index.y)	find_Choice = FIND_CHOICE_XY::FC_X;

	// �÷��̾��� ������ ã�´�. (�÷��̾ �ִ� ������ ���Ѵ�.)
	float player_Pos_Angle = 0;
	player_Pos_Angle = getAngle(slaveCenter.x, slaveCenter.y, playerCenter.x, playerCenter.y);

	// ���� ������ 0 ���Ϸ� ���´ٸ� (�������ش�. -������ +��)
	if (player_Pos_Angle < 0)
	{
		float tempAngle = 0;
		tempAngle = PI + player_Pos_Angle;
		player_Pos_Angle = PI + tempAngle;
	}

	// �÷��̾��� ������ �����Ѵ�.
	FIND_ANGLE find_Angle = FIND_ANGLE::FA_RT;		// 0 = 2��, 1 = 10��, 2 = 7��, 3 = 5��

	if (player_Pos_Angle > 0 && player_Pos_Angle < 1.57)	find_Angle = FIND_ANGLE::FA_RT;
	if (player_Pos_Angle > 1.57 && player_Pos_Angle < 3.14) find_Angle = FIND_ANGLE::FA_TL;
	if (player_Pos_Angle > 3.14 && player_Pos_Angle < 4.71) find_Angle = FIND_ANGLE::FA_LB;
	if (player_Pos_Angle > 4.71 && player_Pos_Angle < (PI * 2)) find_Angle = FIND_ANGLE::FA_BR;

	// �÷��̾��� �������� �̵��� �����Ѵ�.
	if (find_Choice == FIND_CHOICE_XY::FC_XY)
	{
		// x, y �� ª�� �������� ã�´�.
		switch (short_XY)
		{
		case SHORT_XY::SHORT_X:
			// �÷��̾� ���⿡ ���� �����̳� ���������� �̵��Ѵ�.
			if (find_Angle == FIND_ANGLE::FA_TL || find_Angle == FIND_ANGLE::FA_LB)		return SLAVE_DIRECTION::SD_LEFT;
			if (find_Angle == FIND_ANGLE::FA_RT || find_Angle == FIND_ANGLE::FA_BR)		return SLAVE_DIRECTION::SD_RIGHT;
			break;

		case SHORT_XY::SHORT_Y:
			// �÷��̾� ���⿡ ���� ���� �Ʒ��� �̵� �Ѵ�.
			if (find_Angle == FIND_ANGLE::FA_RT || find_Angle == FIND_ANGLE::FA_TL) 	return SLAVE_DIRECTION::SD_UP;
			if (find_Angle == FIND_ANGLE::FA_LB || find_Angle == FIND_ANGLE::FA_BR)     return SLAVE_DIRECTION::SD_DOWN;
			break;
		}
	}

	// y ���⸸ ã���� �ȴ�.
	if (find_Choice == FIND_CHOICE_XY::FC_Y)
	{
		// �÷��̾� ���⿡ ���� ���� �Ʒ��� �̵� �Ѵ�.
		if (find_Angle == FIND_ANGLE::FA_RT || find_Angle == FIND_ANGLE::FA_TL) 	return SLAVE_DIRECTION::SD_UP;
		if (find_Angle == FIND_ANGLE::FA_LB || find_Angle == FIND_ANGLE::FA_BR)     return SLAVE_DIRECTION::SD_DOWN;
	}

	// x ���⸸ ã���� �ȴ�.
	if (find_Choice == FIND_CHOICE_XY::FC_X)
	{
		// �÷��̾� ���⿡ ���� �����̳� ���������� �̵��Ѵ�.
		if (find_Angle == FIND_ANGLE::FA_TL || find_Angle == FIND_ANGLE::FA_LB)		return SLAVE_DIRECTION::SD_LEFT;
		if (find_Angle == FIND_ANGLE::FA_RT || find_Angle == FIND_ANGLE::FA_BR)		return SLAVE_DIRECTION::SD_RIGHT;
	}
}

void bossStageScene::boss_Move_Player()
{
	// ������Ż�� ���� ī��Ʈ�� 1 ���� �����ش�. (������Ż�� ��Ʈ�� ���� �ʾҴٸ� �̰��� ����.)
	if (BEATMANAGER->getBeating() && !_deathMetal->getBoss_Beat())
	{
		_deathMetal->setBoss_Beat(true);		// ��Ʈ�� �޾Ҵٸ� true�� �ٲ��ش�. (������ �����°��� ����)
		_deathMetal->setBoss_Move_Count();		// ���� ī��Ʈ�� 1 �����Ѵ�.

		// ���� ��ȯ ĳ���� ���̶��
		if (_deathMetal->boss_SummonSkill()->isCasting)
		{
			_deathMetal->boss_SummonSkill()->cTime--;
		}
	}

	// ��Ʈ�� ���� 0�� ������ false�� ������ �ٲ��ش�.
	if (!BEATMANAGER->getBeating()) _deathMetal->setBoss_Beat(false);

	// ������Ż�� ���� ī��Ʈ�� 0 ���ϰ� �ȴٸ� �̵��� ���� �Ѵ�.
	if (_deathMetal->getBoss_Move_Count() < 0)
	{
		// ������Ż�� �̵� ���ϴ°��� ã���ش�.
		if (!_collision.collision_Charactor_Object(&_vTotalList, _deathMetal) &&
			!_collision.collision_DeathMetal_Find_Slave(_deathMetal, _sm->get_SlaveList()))
		{
			// �÷��̾�� ������Ż�� ������ �̿��Ͽ� �̵� �� ������ ���Ѵ�. (4������ ���� �ٸ� ����������)
			//if (_deathMetal->getBoss_Phase() != BP_PHASE_4)  findPlayer(_player, _deathMetal, _ui);
			findPlayer(_player, _deathMetal, _ui);
		}

		//if (_deathMetal->getBoss_Phase() == BP_PHASE_4); boss_Phase_4_Move();
	}


}

void bossStageScene::slave_Move_Player()
{
	// �����̺갡 1���� �̻� ���� �Ǿ�߸� ����.  
	if (_sm->get_SlaveList().size() > 0)
	{
		for (int i = 0; i < _sm->get_SlaveList().size(); ++i)
		{
			// �����̺��� ���� ī��Ʈ�� 1 ���� �����ش�. (�����̺갡 ��Ʈ�� ���� �ʾҴٸ� �̰��� ����.)
			if (BEATMANAGER->getBeating() && !_sm->get_SlaveList()[i]->get_Slave()->b_Value.beat)
			{
				_sm->get_SlaveList()[i]->get_Slave()->b_Value.beat = true;		// ��Ʈ�� �޾Ҵٸ� true�� �ٲ��ش�.
				_sm->get_SlaveList()[i]->get_Slave()->operation.move_Count--;	// ���� ī��Ʈ�� 1 �����Ѵ�.
			}

			// ��Ʈ ���� 0�� �ɶ� false�� ������ �ٲ��ش�.
			if (!BEATMANAGER->getBeating()) _sm->get_SlaveList()[i]->get_Slave()->b_Value.beat = false;

			// �����̺��� ���� ī��Ʈ�� 0 ���ϰ� �ȴٸ� �̵��� �����Ѵ�.
			if (_sm->get_SlaveList()[i]->get_Slave()->operation.move_Count < 0)
			{
				// �����̺갡 �̵� �ؾ� �ϴ� ������ �޾ƿ´�.
				_sm->get_SlaveList()[i]->get_Slave()->operation.move_Count = _sm->get_SlaveList()[i]->get_Slave()->operation.save_Move_Count;

				// �÷��̾ �ִ� ������ ã�´�.
				// ��ó�� �÷��̾ �ִ��� ã�´�.
				// ������ ����
				// ������ �̵�
				SLAVE_DIRECTION temp_Direction;
				temp_Direction = _sm->get_SlaveList()[i]->get_Slave()->status.direction;
				_sm->get_SlaveList()[i]->get_Slave()->status.direction = findPlayer(_player, _sm->get_SlaveList()[i]->get_Slave());

				// �÷��̾ ��ó�� �ִ��� ã�´�. ���� �ִٸ� ����
				if (_collision.collision_Slave_Find_Player(_player, _sm->get_SlaveList()[i]->get_Slave()) &&
					!_sm->get_SlaveList()[i]->get_Slave()->b_Value.ghostJonYha)
				{

					if (!_sm->get_SlaveList()[i]->get_Slave()->b_Value.skelY_NoHead)
					{
						_player->playerHit(_sm->get_SlaveList()[i]->get_Slave()->status.attack);
						//_ui->set_HP();
						// �÷��̾�� ���� ���� ����Ʈ�� �׷��ش�.
						boss_Base_Attack_Render("base_Attack", _player);
						CAMERAMANAGER->Camera_WorldDC_Shake();
					}
				}

				// ������Ż�� ��ó�� �ִ��� ã�´�. ���� �ִٸ� �̵� ����
				if (_collision.collision_Slave_Find_DeathMetal(_deathMetal, _sm->get_SlaveList()[i]->get_Slave()) ||
					_collision.collision_Charactor_Object(&_vTotalList, _sm->get_SlaveList()[i]->get_Slave()) ||
					_collision.collision_Slave_Find_Slave(_sm->get_SlaveList()[i]->get_Slave(), _sm->get_SlaveList()))
				{
					// �̵� ����
				}

				if (!_collision.collision_Slave_Find_Player(_player, _sm->get_SlaveList()[i]->get_Slave()) &&
					!_collision.collision_Slave_Find_DeathMetal(_deathMetal, _sm->get_SlaveList()[i]->get_Slave()) &&
					!_collision.collision_Charactor_Object(&_vTotalList, _sm->get_SlaveList()[i]->get_Slave()) &&
					!_collision.collision_Slave_Find_Slave(_sm->get_SlaveList()[i]->get_Slave(), _sm->get_SlaveList()))
				{
					// �浹�ϴ°� ���ٸ� �̵��Ѵ�.
					// �÷��̾ ��Ʈ�� �ٶ� ������ �����̸� �ȵȴ�.
					if (_sm->get_SlaveList()[i]->get_Slave()->status.type == SLAVE_TYPE::SLAVE_GHOST)
					{
						if (_sm->get_SlaveList()[i]->get_Slave()->status.direction == SLAVE_DIRECTION::SD_LEFT &&
							_player->getPlayer().direction == PLAYERDIRECTION_RIGHT ||
							_sm->get_SlaveList()[i]->get_Slave()->status.direction == SLAVE_DIRECTION::SD_RIGHT &&
							_player->getPlayer().direction == PLAYERDIRECTION_LEFT ||
							_sm->get_SlaveList()[i]->get_Slave()->status.direction == SLAVE_DIRECTION::SD_UP &&
							_player->getPlayer().direction == PLAYERDIRECTION_DOWN ||
							_sm->get_SlaveList()[i]->get_Slave()->status.direction == SLAVE_DIRECTION::SD_DOWN &&
							_player->getPlayer().direction == PLAYERDIRECTION_UP)
						{
							// �����̸� �ȵ�
							// ��Ʈ�� �����������Ѵ�.
							// ��Ʈ�� �����Ҷ� ������ ������ �ʴ´�.
							_sm->get_SlaveList()[i]->get_Slave()->b_Value.ghostMoveStop = true;
							_sm->get_SlaveList()[i]->get_Slave()->b_Value.ghostJonYha = true;
						}
						else
						{
							// ��Ʈ�� �ٽ� ���� ���ƿ��� �̵��� �����ϴ�.
							// �ٽ� ���� ���� ���·� ���Ѵ�.
							_sm->get_SlaveList()[i]->get_Slave()->b_Value.ghostMoveStop = false;
							_sm->get_SlaveList()[i]->get_Slave()->b_Value.ghostJonYha = false;
							_sm->get_SlaveList()[i]->get_Slave()->b_Value.isMove = true;
						}
					}

					else
					{
						_sm->get_SlaveList()[i]->get_Slave()->b_Value.isMove = true;

						// ���� ���̷��� ���ο� Ÿ���̰�, �Ӹ��� ���� ���¶�� �÷��̾�� �������� ��Ȳ�̱� ������
						// ������ ���⿡ ���� �ִ��� üũ�� �ؾ��Ѵ�.
						if (_sm->get_SlaveList()[i]->get_Slave()->status.type == SLAVE_TYPE::SLAVE_SKELETON_YELLOW)
						{
							// �Ӹ��� ���� ��Ȳ�̶��
							if (_sm->get_SlaveList()[i]->get_Slave()->b_Value.skelY_NoHead)
							{
								// �������� �ϴ� ���⿡ ��� ��ֹ��� ���ٸ� true�� �־��ش�.
								if (!_collision.collision_Slave_Find_Player(_player, _sm->get_SlaveList()[i]->get_Slave(), true) &&
									!_collision.collision_Slave_Find_DeathMetal(_deathMetal, _sm->get_SlaveList()[i]->get_Slave(), true) &&
									!_collision.collision_Charactor_Object(&_vTotalList, _sm->get_SlaveList()[i]->get_Slave(), true) &&
									!_collision.collision_Slave_Find_Slave(_sm->get_SlaveList()[i]->get_Slave(), _sm->get_SlaveList(), true))
								{
									// �����̸� �ȵ�
									_sm->get_SlaveList()[i]->get_Slave()->b_Value.isMove = true;
								}

								else
								{
									_sm->get_SlaveList()[i]->get_Slave()->b_Value.isMove = false;
								}
							}
						}
					}
				}

				// ���� ������ ���� ������ ������ 
				if (_sm->get_SlaveList()[i]->get_Slave()->status.type == SLAVE_TYPE::SLAVE_BAT)
				{
					for (; ; )
					{
						// �������� ���� �ް�, �� ���⿡ ���ʹ�, ����, ���� ���ٸ� �� �������� �̵��Ϥ� �Ѵ�.
						int rndNum = RND->getInt(4);
						bool exit_For = false;

						switch (rndNum)
						{
							// ����
						case 0:
							_sm->get_SlaveList()[i]->get_Slave()->status.direction = SLAVE_DIRECTION::SD_LEFT;
							// �̵� ������ ������ ã���� ���� ���꿡 ������ �����ش�.
							if (!_collision.collision_Slave_Find_Player(_player, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Slave_Find_DeathMetal(_deathMetal, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Charactor_Object(&_vTotalList, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Slave_Find_Slave(_sm->get_SlaveList()[i]->get_Slave(), _sm->get_SlaveList()))
							{
								_sm->get_SlaveList()[i]->get_Slave()->b_Value.isMove = true;
								exit_For = true;
							}
							break;

							// ��
						case 1:
							_sm->get_SlaveList()[i]->get_Slave()->status.direction = SLAVE_DIRECTION::SD_UP;
							// �̵� ������ ������ ã���� ���� ���꿡 ������ �����ش�.
							if (!_collision.collision_Slave_Find_Player(_player, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Slave_Find_DeathMetal(_deathMetal, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Charactor_Object(&_vTotalList, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Slave_Find_Slave(_sm->get_SlaveList()[i]->get_Slave(), _sm->get_SlaveList()))
							{
								_sm->get_SlaveList()[i]->get_Slave()->b_Value.isMove = true;
								exit_For = true;
							}
							break;

							// ������
						case 2:
							_sm->get_SlaveList()[i]->get_Slave()->status.direction = SLAVE_DIRECTION::SD_RIGHT;
							// �̵� ������ ������ ã���� ���� ���꿡 ������ �����ش�.
							if (!_collision.collision_Slave_Find_Player(_player, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Slave_Find_DeathMetal(_deathMetal, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Charactor_Object(&_vTotalList, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Slave_Find_Slave(_sm->get_SlaveList()[i]->get_Slave(), _sm->get_SlaveList()))
							{
								_sm->get_SlaveList()[i]->get_Slave()->b_Value.isMove = true;
								exit_For = true;
							}
							break;

							// �Ʒ�
						case 3:
							_sm->get_SlaveList()[i]->get_Slave()->status.direction = SLAVE_DIRECTION::SD_DOWN;
							// �̵� ������ ������ ã���� ���� ���꿡 ������ �����ش�.
							if (!_collision.collision_Slave_Find_Player(_player, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Slave_Find_DeathMetal(_deathMetal, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Charactor_Object(&_vTotalList, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Slave_Find_Slave(_sm->get_SlaveList()[i]->get_Slave(), _sm->get_SlaveList()))
							{
								_sm->get_SlaveList()[i]->get_Slave()->b_Value.isMove = true;
								exit_For = true;
							}
							break;
						}

						// ������ ã�Ҵٸ� ������.
						if (exit_For) break;
					}
				}



			}
		}
	}
}

void bossStageScene::boss_Base_Attack_Render()
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->img->frameRender(CAMERAMANAGER->getWorldDC(), (*_viEffect)->rc.left, (*_viEffect)->rc.top,
			(*_viEffect)->img->getFrameX(), (*_viEffect)->img->getFrameY());

		// �̹����� �׷��ְ� ���� ���������� �Ѱ��ش�.
		(*_viEffect)->img->setFrameX((*_viEffect)->img->getFrameX() + 1);

		// ���� �ִ� ������ �̻��̶�� ���͸� �����ش�.
		if ((*_viEffect)->img->getFrameX() >= (*_viEffect)->Max_FrameX)
		{
			_vEffect.erase(_viEffect);

			break;
		}
	}
}

void bossStageScene::boss_Base_Attack_Render(string skillName, player* player)
{
	// ������ ������ ������ �� Ÿ�� ��ġ�� ����Ʈ�� �����ش�.
	// �ִϸ��̼� ���� �ʰ� ������ ������ �׸��ٰ� ������ �̹��� ��� ��
	// ���� ������ �ϴ°ɷ�?
	// ���ʹ� ��� ����?

	// �ѷ��� �̹����� �ѷ��� ��ǥ�� �ӽ÷� ���� �ϴ� ������ �����. + ���� �Ҵ�
	// �÷��̾��� ��Ʈ�� �̹����� �Ѹ���, �������� ��� �����ٸ� ���͸� ���� ���ش�.
	BOSS_STAGE_EFFECT_VECTOR* temp_Effect = new BOSS_STAGE_EFFECT_VECTOR;
	temp_Effect->img = IMAGEMANAGER->findImage(skillName);
	temp_Effect->img->setFrameX(0);
	temp_Effect->img->setFrameY(0);
	temp_Effect->Max_FrameX = temp_Effect->img->getMaxFrameX();
	temp_Effect->rc = RectMake(player->getPlayer().idx * TILESIZE, player->getPlayer().idy * TILESIZE,
		TILESIZE, TILESIZE);
	// ����Ʈ�� �ѷ��� ���� ��ǥ�� �ѷ��� ����Ʈ �̹����� ��� ����
	_vEffect.push_back(temp_Effect);
}

void bossStageScene::start_Slave_Create()
{
	// �⺻���� �����濡 �ִ� ��Ʈ 4����
	_sm->create_Slave(SLAVE_TYPE::SLAVE_GHOST, _deathMetal->getBoss_Index().x - 2, _deathMetal->getBoss_Index().y - 2);
	_sm->create_Slave(SLAVE_TYPE::SLAVE_GHOST, _deathMetal->getBoss_Index().x + 2, _deathMetal->getBoss_Index().y - 2);
	_sm->create_Slave(SLAVE_TYPE::SLAVE_GHOST, _deathMetal->getBoss_Index().x - 2, _deathMetal->getBoss_Index().y + 2);
	_sm->create_Slave(SLAVE_TYPE::SLAVE_GHOST, _deathMetal->getBoss_Index().x + 2, _deathMetal->getBoss_Index().y + 2);
}

void bossStageScene::boss_Phase_4_Move()
{
	// x ��ǥ�� ���� ���� ������� ������ ���� ��������� ���� �������� �̵��� ���� �Ѵ�.
	// ���� ������� �÷��̾ �ִ� y������ ���� �̵��� �Ѵ�.
	// �÷��̾ �߰��ߴٸ� ��ų�� ĳ�����ϰ� 3���� �ڿ� ���� ��ü ������ �����Ѵ�.

	// Ÿ�Ͽ��� ���� ã�´�. ���� ���������� x�� �������ش�.

	// ª������ ã�´�.
	// ���� ���� �� ����� ���
	if (_deathMetal->getBoss_Index().x - 8 < 18 - _deathMetal->getBoss_Index().x && !_deathMetal->getBoss_Bool()->phase4_MoveX_Direction_Find)
	{
		_deathMetal->getBoss_Bool()->phase4_MoveX_Direction = false;		// false�� x�� �� ª�ٴ� ��
		_deathMetal->getBoss_Bool()->phase4_MoveX_Direction_Find = true;	// ������ ã�Ҵ�.
	}

	// ������ ���� �� ����� ���
	if (_deathMetal->getBoss_Index().x - 8 > 18 - _deathMetal->getBoss_Index().x && !_deathMetal->getBoss_Bool()->phase4_MoveX_Direction_Find)
	{
		_deathMetal->getBoss_Bool()->phase4_MoveX_Direction = false;		// false�� y�� �� ª�ٴ� ��
		_deathMetal->getBoss_Bool()->phase4_MoveX_Direction_Find = true;	// ������ ã�Ҵ�.
	}

	// x �̵��� ������ �ʾҰ�, ������ ��������� �����Ѵ�.
	if (!_deathMetal->getBoss_Bool()->phase4_MoveX_End && _deathMetal->getBoss_Bool()->phase4_MoveX_Direction_Find)
	{
		for (int i = 0; i < _vTotalList.size(); ++i)
		{
			// ���� ���� �� ����� ���
			if (!_deathMetal->getBoss_Bool()->phase4_MoveX_Direction)
			{
				// ������ ������ ���� �ƴ� ��쿡�� �̵��� �Ѵ�.
				if (_deathMetal->getBoss_Index().x - 1 == _vTotalList[i]->idX &&
					_deathMetal->getBoss_Index().y == _vTotalList[i]->idY &&
					_vTotalList[i]->wall != W_WALL)
				{
					_deathMetal->setBoss_Index(_deathMetal->getBoss_Index().x - 1, _deathMetal->getBoss_Index().y);

					// ���⼭ ������ �����ְ�, ���� bool ���� ���ش�.
					_deathMetal->setBoss_Direction(BD_LEFT);
					
					// ������������ ����� ���� �ð��� ���� ���ش�.
					_deathMetal->setBoss_WorldTime(TIMEMANAGER->getWorldTime());
					//
					// �̵� ���꿡 �ʿ��� bool ���� true�� �ٲ��ִ� �Լ�
					_deathMetal->setBoss_Move_BoolValue_Ture();
					//
					// ���� �̵��� ���� ���� ī��Ʈ�� �ٽ� ä���ش�.
					_deathMetal->setBoss_Move_Count(_deathMetal->getBoss_Move_Count_Value());
					//
					_deathMetal->setBoss_Angle(PI);

					// �̵��� �����ٸ� �����ش�.
					break;
				}

				// ���� ���� ��� x���� �̵��� �����ٴ� ���� �ִ´�.
				else
				{
					_deathMetal->getBoss_Bool()->phase4_MoveX_End = true;
				}
			}

			// ������ ���� �� ����� ���
			if (_deathMetal->getBoss_Bool()->phase4_MoveX_Direction)
			{
				// ������ ������ ���� �ƴ� ��쿡�� �̵��� �Ѵ�.
				if (_deathMetal->getBoss_Index().x + 1 == _vTotalList[i]->idX &&
					_deathMetal->getBoss_Index().y == _vTotalList[i]->idY &&
					_vTotalList[i]->wall != W_WALL)
				{
					_deathMetal->setBoss_Index(_deathMetal->getBoss_Index().x + 1, _deathMetal->getBoss_Index().y);

					// ���⼭ ������ �����ְ�, ���� bool ���� ���ش�.
					_deathMetal->setBoss_Direction(BD_RIGHT);

					// ������������ ����� ���� �ð��� ���� ���ش�.
					_deathMetal->setBoss_WorldTime(TIMEMANAGER->getWorldTime());
					//
					// �̵� ���꿡 �ʿ��� bool ���� true�� �ٲ��ִ� �Լ�
					_deathMetal->setBoss_Move_BoolValue_Ture();
					//
					// ���� �̵��� ���� ���� ī��Ʈ�� �ٽ� ä���ش�.
					_deathMetal->setBoss_Move_Count(_deathMetal->getBoss_Move_Count_Value());
					//
					_deathMetal->setBoss_Angle(0);

					// �̵��� �����ٸ� �����ش�.
					break;
				}

				// ���� ���� ��� x���� �̵��� �����ٴ� ���� �ִ´�.
				else
				{
					_deathMetal->getBoss_Bool()->phase4_MoveX_End = true;
				}
			}
		}
	}

	// x���� �̵��� ��� �����ٸ� �÷��̾ �ִ� y���� ���󰣴�.
	if (_deathMetal->getBoss_Bool()->phase4_MoveX_End)
	{
		// ���� �÷��̾�� ������ y ��ǥ�� ���ٸ� ���� ĳ������ �����Ѵ�.
		if (_deathMetal->getBoss_Index().y == _player->getPlayer().idy && !_deathMetal->boss_FireBallSkill()->isCasting)
		{
			_deathMetal->boss_FireBallSkill()->isCasting = true;
		}

		// ���� 0���� �۴ٸ� �÷��̾�� �Ʒ��� �ִ�.
		if (_deathMetal->getBoss_Index().y - _player->getPlayer().idy < 0)
		{
			_deathMetal->setBoss_Index(_deathMetal->getBoss_Index().x, _deathMetal->getBoss_Index().y + 1);
		}

		// ���� 0���� ũ�ٸ� �÷��̾�� ���� �ִ�.
		if (_deathMetal->getBoss_Index().y - _player->getPlayer().idy > 0)
		{
			_deathMetal->setBoss_Index(_deathMetal->getBoss_Index().x, _deathMetal->getBoss_Index().y - 1);
		}
	}
}

void bossStageScene::bossSceneSetting()
{
	_scene_Starter.isOpen = false;
	_scene_Starter.startMoveImg = false;
	_scene_Starter.image_Speed = 10;
	_scene_Starter.main_OK = false;
	_scene_Starter.bottom_OK = false;
	_scene_Starter.top_OK = false;
	_scene_Starter.isDoorOpen = false;

	_scene_Starter.main_Img = IMAGEMANAGER->findImage("deathMetal_Main");
	_scene_Starter.top_Img = IMAGEMANAGER->findImage("deathMetal_TopBlade");
	_scene_Starter.bottom_Img = IMAGEMANAGER->findImage("deathMetal_BottomBlade");

	_scene_Starter.main_Img->setX(WINSIZEX);
	_scene_Starter.main_Img->setY(80);

	_scene_Starter.top_Img->setX(-WINSIZEX);
	_scene_Starter.top_Img->setY(100);

	_scene_Starter.bottom_Img->setX(WINSIZEX + 100);
	_scene_Starter.bottom_Img->setY(WINSIZEY - 150);
}

void bossStageScene::bossSceneStart()
{



	if (!_scene_Starter.isOpen)
	{
		// ������Ż ���尡 �鸰��.
		if (!introSound)
		{
			// ���⿡�� ���� �ѹ� ����
			SOUNDMANAGER->play("deathmetal_intro");
			introSound = true;
		}

		// ó�� ���� ���� ���� ���ƿ´�. ������ ��ġ���� �����ϸ�, ���͸� ������ �� ������ ��ġ�� ���ư���.
		// �׸��� ���͸� �ٽ� ������ ���� ���� �ٽ� �Դ���� �ǵ��ư��� �� ���ư����� ������ ���۵ȴ�.
		if (!_scene_Starter.startMoveImg)
		{
			// �̹����� ���� ���������� �� �̻� �̵��ϸ� �ȵȴ�.
			if (_scene_Starter.top_Img->getX() + _scene_Starter.image_Speed <= 0)
			{
				_scene_Starter.top_Img->setX(_scene_Starter.top_Img->getX() + _scene_Starter.image_Speed);
			}
			// �̹����� ���������� true
			else _scene_Starter.top_OK = true;

			if (_scene_Starter.main_Img->getX() - _scene_Starter.image_Speed >= 0)
			{
				_scene_Starter.main_Img->setX(_scene_Starter.main_Img->getX() - _scene_Starter.image_Speed);
			}
			// �̹����� ���������� true
			else _scene_Starter.main_OK = true;

			if (_scene_Starter.main_Img->getX() < WINSIZEX - 130)
			{
				if (_scene_Starter.bottom_Img->getX() - _scene_Starter.image_Speed > WINSIZEX - _scene_Starter.bottom_Img->getWidth())
				{
					_scene_Starter.bottom_Img->setX(_scene_Starter.bottom_Img->getX() - _scene_Starter.image_Speed);
				}
				// �̹����� ���������� true
				else _scene_Starter.bottom_OK = true;
			}

			// ��� �̹����� ���� ������ ���͸� ������ ������� ������ �����Ѵ�.
			if (_scene_Starter.main_OK && _scene_Starter.bottom_OK && _scene_Starter.top_OK)
			{
				if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
				{
					// �̹��� ���갡 ��� �������� true�� ���� �ִ´�.
					_scene_Starter.startMoveImg = true;
				}
			}
			else if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_scene_Starter.image_Speed = 16;
			}
		}

		if (_scene_Starter.startMoveImg)
		{
			// �̹����� ��� ����������� �ݺ��Ѵ�.
			if (_scene_Starter.top_Img->getX() + _scene_Starter.top_Img->getWidth() >= 0)
			{
				_scene_Starter.top_Img->setX(_scene_Starter.top_Img->getX() - _scene_Starter.image_Speed);
			}
			// �̹����� ��������� false
			else _scene_Starter.top_OK = false;

			if (_scene_Starter.main_Img->getX() <= WINSIZEX)
			{
				_scene_Starter.main_Img->setX(_scene_Starter.main_Img->getX() + _scene_Starter.image_Speed);
			}
			// �̹����� ��������� false
			else _scene_Starter.main_OK = false;


			if (_scene_Starter.bottom_Img->getX() <= WINSIZEX)
			{
				_scene_Starter.bottom_Img->setX(_scene_Starter.bottom_Img->getX() + _scene_Starter.image_Speed);
			}
			// �̹����� ��������� false
			else _scene_Starter.bottom_OK = false;


			// ��� �̹����� ������ٸ� ������ ���� �ȴ�.
			if (!_scene_Starter.main_OK && !_scene_Starter.bottom_OK && !_scene_Starter.top_OK)
			{
				_scene_Starter.isOpen = true;
			}
		}
	}
	// ���� �������� ���� ����, ���� ������ ���ο� ���� �Ҹ� ������
	setVolumeBossStage();
}

void bossStageScene::bossSceneRender()
{
	if (!_scene_Starter.isOpen)
	{
		_scene_Starter.top_Img->render(getMemDC(), _scene_Starter.top_Img->getX(), _scene_Starter.top_Img->getY());
		_scene_Starter.bottom_Img->render(getMemDC(), _scene_Starter.bottom_Img->getX(), _scene_Starter.bottom_Img->getY());
		_scene_Starter.main_Img->render(getMemDC(), _scene_Starter.main_Img->getX(), _scene_Starter.main_Img->getY());
	}
}

void bossStageScene::bossSceneDoorOpen()
{


	// �÷��̾ ���� �ִ� ��ġ�� �����ϸ� ���� �������.
	if (_player->getPlayer().idx == 12 && _player->getPlayer().idy == 21 ||
		_player->getPlayer().idx == 13 && _player->getPlayer().idy == 21 ||
		_player->getPlayer().idx == 14 && _player->getPlayer().idy == 21)
	{
		// ���̿��� ������ ������ �ٲ��.
		for (int i = 0; i < _vTotalList.size(); ++i)
		{
			// �ε����� ���� Ÿ���� ã�´�.
			if (_vTotalList[i]->idX == 12 && _vTotalList[i]->idY == 20 ||
				_vTotalList[i]->idX == 13 && _vTotalList[i]->idY == 20 ||
				_vTotalList[i]->idX == 14 && _vTotalList[i]->idY == 20)
			{
				//_vTotalList[i]->type = TYPE_NONE;
				_vTotalList[i]->wall = W_NONE;
			}
		}
	}

	// ���� �������� ������ ������ ��ģ��.
	// �÷��̾ ���� ���� ���� ���� �ִ� �ڸ��� ���� �����.
	if (_player->getPlayer().idx == 12 && _player->getPlayer().idy == 19 ||
		_player->getPlayer().idx == 13 && _player->getPlayer().idy == 19 ||
		_player->getPlayer().idx == 14 && _player->getPlayer().idy == 19)
	{
		// ������ �ѹ� ��ģ��.
		if (introSound)
		{
			// ���� ����
			SOUNDMANAGER->play("deathmetal_welcome");
			introSound = false;
		}

		// ���̿��� ������ ������ �ٲ��ش�.
		for (int i = 0; i < _vTotalList.size(); ++i)
		{
			// �ε����� ���� Ÿ�Ͽ� ���� �����ش�.
			if (_vTotalList[i]->idX == 12 && _vTotalList[i]->idY == 20 ||
				_vTotalList[i]->idX == 13 && _vTotalList[i]->idY == 20 ||
				_vTotalList[i]->idX == 14 && _vTotalList[i]->idY == 20)
			{
				_vTotalList[i]->type = TYPE_WALL;
				_vTotalList[i]->wall = W_BOSS_WALL;
				_vTotalList[i]->wallFrameX = 3;
				_vTotalList[i]->wallFrameY = 2;
			}
		}

		// �����濡 �ִ� ���̵��� �����̱� �����Ѵ�.
		_scene_Starter.isDoorOpen = true;
	}

}

void bossStageScene::bossClear()
{

	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		// ���� ������� �ϴ� �ε��� ��Ÿ���� ã�´�.
		if (_vTotalList[i]->idX == 11 && _vTotalList[i]->idY == 10 ||
			_vTotalList[i]->idX == 12 && _vTotalList[i]->idY == 10 ||
			_vTotalList[i]->idX == 13 && _vTotalList[i]->idY == 10 ||
			_vTotalList[i]->idX == 14 && _vTotalList[i]->idY == 10 ||
			_vTotalList[i]->idX == 15 && _vTotalList[i]->idY == 10)
		{
			_vTotalList[i]->wall = W_NONE;
		}
	}
}

void bossStageScene::boss_PhaseMove()
{
	// ����� �ൿ
	switch (_deathMetal->getBoss_Phase())
	{
	case BP_PHASE_1:
		// ���� ���Ⱑ �ƴ� ����� ���� ��Ż�� ������ �����ϸ� ƨ��⸸ �� (������x)
		// ���� 2���� ��ȯ

		// �ǵ尡 �ǰ��� ���ߴٸ� �ڷ� �з�����.
		if (_deathMetal->getBoss_isShield_Hit())
		{
			// �ش� ���⿡ �������� �з�����.
			switch (_deathMetal->getBoss_Direction())
			{
			case BD_LEFT:
				// ĳ���Ͱ� �ٶ󺸴� ���� ���ʿ� ������Ʈ�� ã���ش�. (�ڿ� �ƹ��͵� ���ٸ� false)
				if (!_collision.collision_Charactor_Object_Back(&_vTotalList, _deathMetal))
				{
					_deathMetal->setBoss_Index(_deathMetal->getBoss_Index().x + 1, _deathMetal->getBoss_Index().y);
				}

				break;

			case BD_UP:
				// ĳ���Ͱ� �ٶ󺸴� ���� ���ʿ� ������Ʈ�� ã���ش�. (�ڿ� �ƹ��͵� ���ٸ� false)
				if (!_collision.collision_Charactor_Object_Back(&_vTotalList, _deathMetal))
				{
					_deathMetal->setBoss_Index(_deathMetal->getBoss_Index().x, _deathMetal->getBoss_Index().y + 1);
				}

				break;

			case BD_RIGHT:
				// ĳ���Ͱ� �ٶ󺸴� ���� ���ʿ� ������Ʈ�� ã���ش�. (�ڿ� �ƹ��͵� ���ٸ� false)
				if (!_collision.collision_Charactor_Object_Back(&_vTotalList, _deathMetal))
				{
					_deathMetal->setBoss_Index(_deathMetal->getBoss_Index().x - 1, _deathMetal->getBoss_Index().y);
				}

				break;

			case BD_DOWN:
				// ĳ���Ͱ� �ٶ󺸴� ���� ���ʿ� ������Ʈ�� ã���ش�. (�ڿ� �ƹ��͵� ���ٸ� false)
				if (!_collision.collision_Charactor_Object_Back(&_vTotalList, _deathMetal))
				{
					_deathMetal->setBoss_Index(_deathMetal->getBoss_Index().x, _deathMetal->getBoss_Index().y - 1);
				}

				break;
			}

			// ���� �ֺ����� �������� ���� ��ȯ (2����)
			int tempX, tempY;
			tempX = tempY = 0;
			int rndX, rndY;
			rndX = rndY = 0;

			// 2������ ��ȯ�ؾ� �ϱ� ������ 2���� ����.
			for (int i = 0; i < 2; ++i)
			{
				rndX = RND->getInt(9) + 8;
				rndY = RND->getInt(7) + 11;

				// Ÿ�ϸʿ��� ������Ʈ�� �ƴ� �κ��� ã�´�.
				for (int j = 0; j < _vTotalList.size(); ++j)
				{
					// ������ ���������� ��ȯ�� �����ؾ� �Ѵ�.
					if (_vTotalList[j]->idX >= 8 && _vTotalList[j]->idX <= 18 &&
						_vTotalList[j]->idY >= 11 && _vTotalList[j]->idY <= 18)
					{
						// rndX,Y�� ���� Ÿ���� ã�´�.
						if (_vTotalList[j]->idX == rndX && _vTotalList[j]->idY == rndY)
						{
							if (_player->getPlayer().idx == rndX &&
								_player->getPlayer().idy == rndY ||
								_deathMetal->getBoss_Index().x == rndX &&
								_deathMetal->getBoss_Index().y == rndY)
							{
								// ������ �����̺갡 �ִ� ��ġ���� ������ �ȵ�
								for (int k = 0; k < _sm->get_SlaveList().size(); ++k)
								{
									if (_sm->get_SlaveList()[k]->get_Slave()->pos.index.x == rndX &&
										_sm->get_SlaveList()[k]->get_Slave()->pos.index.y == rndY)
									{
										rndX = RND->getInt(9) + 8;
										rndY = RND->getInt(7) + 11;
										j = -1;
										continue;
									}
								}
							}
							else
							{
								tempX = rndX;
								tempY = rndY;
							}
						}
					}
				}

				// ��ȯ ������ �ε����� ã�Ҵٸ� �װ��� ��ȯ�Ѵ�. 
				if (tempX && tempY)	_sm->create_Slave(SLAVE_TYPE::SLAVE_BAT, tempX, tempY);

			}


			// ������ ������ �ǰ��� false�� �����Ѵ�.
			_deathMetal->setBoss_isShield_Hit(false);
		}

		// ���� �¾������� ���� ü���� �޸� �ȵ�


		break;

	case BP_PHASE_2:
		// ���� ���ø��� 4 ���� ���� ������ ���� ������ �ذ� 1 ~ 3���� ��ȯ
		// ���� ������ �ݴ������� �����̵�
		// ���� ü���� �����صΰ� ü�� ��ȭ�� ��������
		// �����̵��� �ϰ� ī��Ʈ�� �ٽ� �÷��ش�. (�ִ� ī��Ʈ + 1�� ���༭ �� ���ڸ� ���� ���� ���� ��� ����)

		// Ȯ���� ���� ��� ��ų ����
		// ���� �� 4 ���� ���� ���� ���� ������ �ذ� ��ȯ

		if (!_deathMetal->boss_SummonSkill()->isCasting && _sm->get_SlaveList().size() < 8)
		{
			// �������� ���ڸ� �޴´�. 0 ~ 2
			_deathMetal->boss_SummonSkill()->rnd = RND->getInt(150);

			cout << _deathMetal->boss_SummonSkill()->rnd << endl;

			// ���ڰ� 9��� �ذ� ��ȯ ��ų�� �����Ѵ�.
			if (_deathMetal->getBoss_SummonSkill().rnd == 10) _deathMetal->boss_SummonSkill()->isCasting = true;

		}

		// 2�� ���Դٸ� ��ȯ
		if (_deathMetal->boss_SummonSkill()->isCasting)
		{
			// ���� ī��Ʈ�� ó���̶�� ������Ż�� ���� ���.
			if (_deathMetal->boss_SummonSkill()->cTime == _deathMetal->boss_SummonSkill()->cTime_M)
			{
				_deathMetal->setBoss_isCasting(true);
			}

			// ���� ī��Ʈ�� 0�̶�� �ذ� ��ȯ 1 ~ 3
			if (_deathMetal->boss_SummonSkill()->cTime < 0)
			{
				_deathMetal->setBoss_isCasting(false);

				// �ذ��� ��ȯ�Ѵ�.
				int rndSummons = RND->getInt(2) + 1;	// 1 ~ 2

				// ���� �ֺ����� �������� �ذ� ��ȯ (1 ~ 3����)
				int tempX, tempY;
				tempX = tempY = 0;
				int rndX, rndY;
				rndX = rndY = 0;

				for (int i = 0; i < rndSummons; ++i)
				{
					// ���� �� �ִ� ������ �����ش�.
					rndX = RND->getInt(9) + 8;
					rndY = RND->getInt(7) + 11;

					// Ÿ�ϸʿ��� ������Ʈ�� �ƴ� �κ��� ã�´�.
					for (int j = 0; j < _vTotalList.size(); ++j)
					{
						// ������ ���������� ��ȯ�� �����ؾ� �Ѵ�.
						if (_vTotalList[j]->idX >= 8 && _vTotalList[j]->idX <= 18 &&
							_vTotalList[j]->idY >= 11 && _vTotalList[j]->idY <= 18)
						{
							// rndX,Y�� ���� Ÿ���� ã�´�.
							if (_vTotalList[j]->idX == rndX && _vTotalList[j]->idY == rndY)
							{
								if (_player->getPlayer().idx == rndX &&
									_player->getPlayer().idy == rndY ||
									_deathMetal->getBoss_Index().x == rndX &&
									_deathMetal->getBoss_Index().y == rndY)
								{
									// ������ �����̺갡 �ִ� ��ġ���� ������ �ȵ�
									for (int k = 0; k < _sm->get_SlaveList().size(); ++k)
									{
										if (_sm->get_SlaveList()[k]->get_Slave()->pos.index.x == rndX &&
											_sm->get_SlaveList()[k]->get_Slave()->pos.index.y == rndY)
										{
											rndX = RND->getInt(9) + 8;
											rndY = RND->getInt(7) + 11;
											j = -1;
											continue;
										}
									}
								}
								else
								{
									tempX = rndX;
									tempY = rndY;
								}
							}
						}
					}

					// ��ȯ ������ �ε����� ã�Ҵٸ� �װ��� ��ȯ�Ѵ�. 
					if (tempX && tempY)	_sm->create_Slave(SLAVE_TYPE::SLAVE_SKELETON, tempX, tempY);
				}

				// ���� ������ ���� �ʱ�ȭ
				_deathMetal->boss_SummonSkill()->isCasting = false;
				_deathMetal->boss_SummonSkill()->cTime = _deathMetal->boss_SummonSkill()->cTime_M;
			}
		}
		break;

	case BP_PHASE_3:
		// �ذ��� ��� �ذ�� ��ü
		// ���� ���ø��� 4 ���� ���� ������ ���� ������ �ذ� 1 ~ 3���� ��ȯ
		// ���� ������ �ݴ������� �����̵�
		// ���� ü���� �����صΰ� ü�� ��ȭ�� ��������
		// �����̵��� �ϰ� ī��Ʈ�� �ٽ� �÷��ش�. (�ִ� ī��Ʈ + 1�� ���༭ �� ���ڸ� ���� ���� ���� ��� ����)

		// Ȯ���� ���� ��� ��ų ����
		// ���� �� 4 ���� ���� ���� ���� ������ �ذ� ��ȯ

		if (!_deathMetal->boss_SummonSkill()->isCasting && _sm->get_SlaveList().size() < 4)
		{
			// �������� ���ڸ� �޴´�. 0 ~ 2
			_deathMetal->boss_SummonSkill()->rnd = RND->getInt(150);

			cout << _deathMetal->boss_SummonSkill()->rnd << endl;

			// ���ڰ� 9��� �ذ� ��ȯ ��ų�� �����Ѵ�.
			if (_deathMetal->getBoss_SummonSkill().rnd == 10) _deathMetal->boss_SummonSkill()->isCasting = true;

		}

		// 2�� ���Դٸ� ��ȯ
		if (_deathMetal->boss_SummonSkill()->isCasting)
		{
			// ���� ī��Ʈ�� ó���̶�� ������Ż�� ���� ���.
			if (_deathMetal->boss_SummonSkill()->cTime == _deathMetal->boss_SummonSkill()->cTime_M)
			{
				_deathMetal->setBoss_isCasting(true);
			}

			// ���� ī��Ʈ�� 0�̶�� �ذ� ��ȯ 1 ~ 3
			if (_deathMetal->boss_SummonSkill()->cTime < 0)
			{
				_deathMetal->setBoss_isCasting(false);

				// �ذ��� ��ȯ�Ѵ�.
				int rndSummons = RND->getInt(2) + 1;	// 1 ~ 2

				// ���� �ֺ����� �������� �ذ� ��ȯ (1 ~ 3����)
				int tempX, tempY;
				tempX = tempY = 0;
				int rndX, rndY;
				rndX = rndY = 0;

				for (int i = 0; i < rndSummons; ++i)
				{
					// ���� �� �ִ� ������ �����ش�.
					rndX = RND->getInt(9) + 8;
					rndY = RND->getInt(7) + 11;

					// Ÿ�ϸʿ��� ������Ʈ�� �ƴ� �κ��� ã�´�.
					for (int j = 0; j < _vTotalList.size(); ++j)
					{
						// ������ ���������� ��ȯ�� �����ؾ� �Ѵ�.
						if (_vTotalList[j]->idX >= 8 && _vTotalList[j]->idX <= 18 &&
							_vTotalList[j]->idY >= 11 && _vTotalList[j]->idY <= 18)
						{
							// rndX,Y�� ���� Ÿ���� ã�´�.
							if (_vTotalList[j]->idX == rndX && _vTotalList[j]->idY == rndY)
							{
								if (_player->getPlayer().idx == rndX &&
									_player->getPlayer().idy == rndY ||
									_deathMetal->getBoss_Index().x == rndX &&
									_deathMetal->getBoss_Index().y == rndY)
								{
									// ������ �����̺갡 �ִ� ��ġ���� ������ �ȵ�
									for (int k = 0; k < _sm->get_SlaveList().size(); ++k)
									{
										if (_sm->get_SlaveList()[k]->get_Slave()->pos.index.x == rndX &&
											_sm->get_SlaveList()[k]->get_Slave()->pos.index.y == rndY)
										{
											rndX = RND->getInt(9) + 8;
											rndY = RND->getInt(7) + 11;
											j = -1;
											continue;
										}
									}
								}
								else
								{
									tempX = rndX;
									tempY = rndY;


								}
							}

							// �÷��̾� ��ġ���� ������ �ȵ�
							if (_player->getPlayer().idx != rndX &&
								_player->getPlayer().idy != rndY)
							{
								tempX = rndX;
								tempY = rndY;

							}

						}
					}

					// ��ȯ ������ �ε����� ã�Ҵٸ� �װ��� ��ȯ�Ѵ�. 
					if (tempX && tempY)	_sm->create_Slave(SLAVE_TYPE::SLAVE_SKELETON_YELLOW, tempX, tempY);
				}

				// ���� ������ ���� �ʱ�ȭ
				_deathMetal->boss_SummonSkill()->isCasting = false;
				_deathMetal->boss_SummonSkill()->cTime = _deathMetal->boss_SummonSkill()->cTime_M;
			}
		}

		break;

	case BP_PHASE_4:
		// �ѹ��ڷ� ���� ������ ���� �ٰ�, ���� �پ����� �� ���ڸ��� ���̾ �߻�

		break;
	}
}

void bossStageScene::setVolumeBossStage()
{
	if (_scene_Starter.isDoorOpen)
	{
		SOUNDMANAGER->setVolume("BGM_BOSS", 1.5f);
	}
	else
	{
		SOUNDMANAGER->setVolume("BGM_BOSS", 0.35f);
	}
}

void bossStageScene::endScene()
{
	if (_player->getPlayer().idx == _endX && _player->getPlayer().idy == _endY)
	{
		BEATMANAGER->AllStopMusic();
		SCENEMANAGER->changeScene("End");
	}
}

void bossStageScene::tileOnOff()
{
	// 01 11 Ÿ�� �׸���   42 52
	if (_player->getCombo())
	{
		if (BEATMANAGER->getTurnOnOff())
		{
			_tileFirstX = 4;
			_tileFirstY = 2;

			_tileSecondX = 5;
			_tileSecondY = 2;
		}
		else
		{
			_tileFirstX = 5;
			_tileFirstY = 2;

			_tileSecondX = 4;
			_tileSecondY = 2;

		}

	}
	else
	{
		if (BEATMANAGER->getTurnOnOff())
		{
			_tileFirstX = 0;
			_tileFirstY = 1;

			_tileSecondX = 1;
			_tileSecondY = 1;
		}
		else
		{
			_tileFirstX = 1;
			_tileFirstY = 1;

			_tileSecondX = 0;
			_tileSecondY = 1;
		}

	}

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0;j < TILEX; ++j)
		{
			if (_tiles[i * TILEX + j].type == TYPE_NONE) continue;
			if (_tiles[i * TILEX + j].terrain != TR_BASIC_STAGE_TILE &&
				_tiles[i * TILEX + j].terrain != TR_BASIC_COMBO_TILE) continue;

			if (j % 2 == 0)
			{
				if (i % 2 == 1)
				{
					_tiles[i * TILEX + j].terrainFrameX = _tileFirstX;
					_tiles[i * TILEX + j].terrainFrameY = _tileFirstY;
				}
				else
				{
					_tiles[i * TILEX + j].terrainFrameX = _tileSecondX;
					_tiles[i * TILEX + j].terrainFrameY = _tileSecondY;
				}
			}
			else
			{
				if (i % 2 == 1)
				{
					_tiles[i * TILEX + j].terrainFrameX = _tileSecondX;
					_tiles[i * TILEX + j].terrainFrameY = _tileSecondY;
				}
				else
				{
					_tiles[i * TILEX + j].terrainFrameX = _tileFirstX;
					_tiles[i * TILEX + j].terrainFrameY = _tileFirstY;
				}
			}



		}
	}
}
