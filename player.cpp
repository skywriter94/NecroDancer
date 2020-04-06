#include "stdafx.h"
#include "player.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "deathMetal.h"
#include "slave.h"

player::player()
{
	_nowStage = NOWSTAGE_STAGE;
}

player::~player()
{
}

HRESULT player::init(int idx, int idy, int tileSizeX, int tileSizeY)
{
	imageSetting();			 // �̹��� 
	_jump = new jump;		 // ���� Ŭ����
	_jump->init();
	//�ִϸ��̼� �ʱ�ȭ 
	_player.headAni = KEYANIMANAGER->findAnimation("headRight");			// �ִϸ��̼� �̹���
	_player.bodyAni = KEYANIMANAGER->findAnimation("bodyRight");
	_player.headImage = IMAGEMANAGER->findImage("player1_heads");			// �̹���
	_player.bodyImage = IMAGEMANAGER->findImage("player1_armor_body_xmas");
	_player.headAni->start();
	_player.bodyAni->start();
	_player.direction = PLAYERDIRECTION_RIGHT;				// ���� ������	RIGHT
	_player.weapon = PLAYERWAEPON_NONE;						// ����			NONE
	_player.sight = 5;										// �þ� ��		4
	_player.damage = 1;										// ������        1
	_player.idx = idx;										// �ε��� X
	_player.idy = idy;										// �ε��� Y
	_player.score = 0;				// ����
	_player.coin = 0;				// ��
	_player.diamond = 0;			// ���̾Ƹ��
	_player.x = _player.idx * tileSizeX + (tileSizeX / 2);
	_player.y = _player.idy * tileSizeY + (tileSizeY / 3);
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.bodyImage->getFrameWidth(), _player.headImage->getFrameHeight());
	_shadow = _player.y;
	_player.isArmor = false;
	_player.isWeapon = false;
	_player.torch = false;
	_player.potion = false;
	_player.hp = 6;
	_player.maxHp = 6;

	_distance = tileSizeY;			//  Ÿ�� ���� �Ÿ�
	_time = 0.15;					//  MOVE �ð� 
	_reversMove = false;	 // ���� ���� �� �ǵ��� ���� ���� �� 
	_isMoving = false;		 // MOVE �Ǵ�
	_isKeyPress = false;     // ��Ʈ �Ǵ� 
	_isKeyDown = false;      // KEY �Է� �Ǵ�
	_comboCountTime = 0;

	// �ʱ� ���� ��� �� 
	_player.weapon = PLAYERWAEPON_DAGGER;							// 
	makeItem(WP_DAGGER_1, A_NONE, ST_NONE, 0, 0, 0, 1, 0, 0);		// ���� 
	makeItem(WP_NONE, A_SHOVEL, ST_NONE, 1, 0, 0, 0, 0, 0);			// �� 
	
	_combo = 0;							//�޺� 
	playerAttackSoundID = 0;			//���� ��ȣ 
	destroyAllWindows(); // �ӽ� ����
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	_jump->update();							  // JUMP
	if (!_jump->getJumping()) _shadow = _player.y; // �׸����� ��ġ(��Ʈ���� ���� �� ���ڷ� �Ѿ�� �ʰ� �ϱ� ���� ����)

	keyControl();					// KEY
	playerMove();					// MOVE

	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect) // ����Ʈ 
	{
		(*_viEffect)->update();
	}

	CAMERAMANAGER->set_CameraXY(_player.idx * _distance + (_distance / 2), _player.idy * _distance + (_distance / 3)); // ī�޶� ����

	playerDie(); // �÷��̾� ��� �Ǵ� 
}

void player::render()
{
	_player.bodyImage->aniRender(CAMERAMANAGER->getWorldDC(), _player.x, _player.y, _player.bodyAni);	// ��
	_player.headImage->aniRender(CAMERAMANAGER->getWorldDC(), _player.x, _player.y, _player.headAni);	// �� 
}

void player::effectRender()	// ����Ʈ ���� 
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->render(CAMERAMANAGER->getWorldDC());
	}
}

void player::playerMove()
{
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.bodyImage->getFrameWidth(), _player.headImage->getFrameHeight());

	if (!_isMoving) return;

	float elapsedTime = TIMEMANAGER->getElapsedTime();

	//200������ �Ÿ��� 2�ʿ� ���ļ� �����ؾ��Ѵٸ� �ӵ����� ������
	float moveSpeed = (elapsedTime / _time) * _distance;


	if (_reversMove) // ���Ⱑ ���� �� ���͸� �����ϸ� 
	{
		if ((_time / 2) + _worldTimeCount <= TIMEMANAGER->getWorldTime())
		{
			_player.x = _player.x - cosf(_angle) * moveSpeed;
			_player.y = _player.y - (-sinf(_angle) * moveSpeed);
		}
		else
		{
			_player.x = _player.x + cosf(_angle) * moveSpeed;
			_player.y = _player.y + (-sinf(_angle) * moveSpeed);
		}

		if (_time + _worldTimeCount <= TIMEMANAGER->getWorldTime())
		{
			_worldTimeCount = TIMEMANAGER->getWorldTime();
			// ��ġ�� ������Ű�� MOVE BOOL���� false��
			_player.idx = _previousIdx;
			_player.idy = _previousIdy;

			_player.x = _player.idx * _distance + (_distance / 2);
			_player.y = _player.idy * _distance + (_distance / 3);

			_isMoving = false;	    // ���� ���� 
			_reversMove = false;	// �ʱ�ȭ 
			return;
		}

	}
	else // �⺻ �̵��̸� 
	{
		//�̹����� ������������ ������ �ӵ��� ���缭 ���ϴ� �ð��� ������ �Ѵ�
		_player.x = _player.x + cosf(_angle) * moveSpeed;
		_player.y = _player.y + (-sinf(_angle) * moveSpeed);

		// ���� ���� �ð��� �����ϸ� 
		if (_time + _worldTimeCount <= TIMEMANAGER->getWorldTime())
		{
			_worldTimeCount = TIMEMANAGER->getWorldTime();
			// ��ġ�� ������Ű�� MOVE BOOL���� false��
			_player.x = _player.idx * _distance + (_distance / 2);
			_player.y = _player.idy * _distance + (_distance / 3);

			_isMoving = false;	    // ���� ���� 
			return;
		}
	}
}

void player::playerEffect_Miss()
{
	alphaImageEffect* effect;
	effect = new alphaImageEffect;
	effect->init("player_effect_missed", CAMERAMANAGER->get_CameraX() + BEATMANAGER->getHeartMiddle() - 30, CAMERAMANAGER->get_CameraY() + (WINSIZEY - 200), 10, SLOW);
	_vEffect.push_back(effect);
	_combo = false;
}

void player::playerEffect_Shovel(tagTile* tile)
{
	alphaImageEffect* effect;
	effect = new alphaImageEffect;
	effect->init("shovel_basic", tile->rc.left, tile->rc.top - 30, 10, TIMESLOW);
	_vEffect.push_back(effect);
	if (tile->wall == W_SHOP_WALL || tile->wall == W_END_WALL || tile->wall == W_BOSS_WALL) return;
	CAMERAMANAGER->Camera_WorldDC_Shake(); // ������ ����ó�� ������ ī�޶� 0,0������ �۵� ���� 
}

// ��ǥ�� x,y�� ��ġ
void player::playerEffect_Attack(const char* imageName, float x, float y, int frameY)
{
	alphaImageEffect* effect;
	effect = new alphaImageEffect;
	effect->init(imageName, x, y, 0, frameY, FRAMEIMAGE);
	_vEffect.push_back(effect);
}

// ������ ����Ʈ ��ġ 
void player::playerEffect_Attack()
{
	float x;
	float y;
	int frame;
	alphaImageEffect* effect;
	effect = new alphaImageEffect;
	if (_player.direction == PLAYERDIRECTION_UP)
	{
		x = _player.x;
		y = _player.y - 30;
		frame = 0;
	}
	else if (_player.direction == PLAYERDIRECTION_DOWN)
	{
		x = _player.x;
		y = _player.y + 30;
		frame = 1;
	}
	else if (_player.direction == PLAYERDIRECTION_LEFT)
	{
		x = _player.x - 30;
		y = _player.y;
		frame = 2;
	}
	else if (_player.direction == PLAYERDIRECTION_RIGHT)
	{
		x = _player.x + 30;
		y = _player.y;
		frame = 3;
	}

	switch (_player.weapon)
	{
	case PLAYERWAEPON_DAGGER:
		effect->init("swipe_dagger", x, y, 0, frame, FRAMEIMAGE);
		break;
	case PLAYERWAEPON_BROADSWORD:
		if (_player.direction == PLAYERDIRECTION_UP || _player.direction == PLAYERDIRECTION_DOWN)
		{
			effect->init("swipe_broadsword����", x, y, 0, frame % 2, FRAMEIMAGE);
		}
		else
		{
			effect->init("swipe_broadsword�¿�", x, y, 0, frame % 2, FRAMEIMAGE);
		}
		break;
	case PLAYERWAEPON_RAPIER:
	case PLAYERWAEPON_SPEAR:
		if (_player.direction == PLAYERDIRECTION_UP || _player.direction == PLAYERDIRECTION_DOWN)
		{
			effect->init("swipe_rapier����", x, y, 0, frame % 2, FRAMEIMAGE);
		}
		else
		{
			effect->init("swipe_rapier�¿�", x, y, 0, frame % 2, FRAMEIMAGE);
		}
		break;
	case PLAYERWAEPON_LONGSWORD:
		if (_player.direction == PLAYERDIRECTION_UP || _player.direction == PLAYERDIRECTION_DOWN)
		{
			effect->init("swipe_longsword����", x, y, 0, frame % 2, FRAMEIMAGE);
		}
		else
		{
			effect->init("swipe_longsword�¿�", x, y, 0, frame % 2, FRAMEIMAGE);
		}
		break;

	default:
		return;
		break;
	}

	_vEffect.push_back(effect);
	CAMERAMANAGER->Camera_WorldDC_Shake();
}

void player::keyControl()
{
	if (!_isKeyDown)
	{

		if (KEYMANAGER->isOncekeytwoDown(VK_LEFT, VK_UP))
		{

			if (BEATMANAGER->getInterval())
			{
				_isKeyDown = true;
				SOUNDMANAGER->play("sfx_item_food", 1.5f);
				itemUse();
			}
			else
			{
				SOUNDMANAGER->play("sfx_missedbeat", 1.5f);
				playerEffect_Miss();
			}

		}
		else if (KEYMANAGER->isOncekeytwoDown(VK_LEFT, VK_DOWN))
		{
			if (BEATMANAGER->getInterval())
			{
				_isKeyDown = true;
			}
			else
			{
				SOUNDMANAGER->play("sfx_missedbeat", 1.5f);
				playerEffect_Miss();
			}
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_player.direction = PLAYERDIRECTION_UP;
			_isKeyDown = true;
			if (BEATMANAGER->getInterval())
			{
				tileCheck();
			}
			else
			{
				SOUNDMANAGER->play("sfx_missedbeat", 1.5f);
				playerEffect_Miss();
			}
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_player.direction = PLAYERDIRECTION_DOWN;
			_isKeyDown = true;
			if (BEATMANAGER->getInterval())
			{
				tileCheck();
			}
			else
			{
				SOUNDMANAGER->play("sfx_missedbeat", 1.5f);
				playerEffect_Miss();
			}
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_player.direction = PLAYERDIRECTION_LEFT;
			_isKeyDown = true;
			if (BEATMANAGER->getInterval())
			{
				tileCheck();
			}
			else
			{
				SOUNDMANAGER->play("sfx_missedbeat", 1.5f);
				playerEffect_Miss();
			}
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_player.direction = PLAYERDIRECTION_RIGHT;
			_isKeyDown = true;
			if (BEATMANAGER->getInterval())
			{
				tileCheck();
			}
			else
			{
				SOUNDMANAGER->play("sfx_missedbeat", 1.5f);
				playerEffect_Miss();
			}
		}
	}
}

void player::tileCheck()
{
	_isKeyPress = true;				// ���͹� ���̿� ���� 
	bool action = false;			// �׼��� ���ߴ��� ���ߴ��� �Ǵ��� ���� 

	// �����¿��� Ÿ������
	for (_miPlayerTile = _mPlayerTile.begin(); _miPlayerTile != _mPlayerTile.end(); ++_miPlayerTile)
	{
		//UPŸ��
		if (_miPlayerTile->first == _player.direction)
		{
			//Ÿ���� ������ �Ǵ�
			switch (_miPlayerTile->second->type)
			{
			case TYPE_WALL:
				wallCheck();
				action = true;
				break;
			case TYPE_TRAP:
				trapCheck();
				action = true;
				break;
			case TYPE_ITEM_ARMOR:
			case TYPE_ITEM_WEAPON:
			case TYPE_ITEM_STUFF:
				itempCheck();
				StateMove();
				action = true;
				break;
			default:
				break;
			}
			break;
		}
	}
	if (action) return;
	// ENEMY Ÿ�� ���� ( �ۼ� ���� )
	if (_nowStage == NOWSTAGE_STAGE)
	{
		for (_miPlayerEnemyTile = _mPlayerEnemyTile.begin(); _miPlayerEnemyTile != _mPlayerEnemyTile.end(); ++_miPlayerEnemyTile)
		{
			if (_miPlayerEnemyTile->first == _player.direction)
			{
				if (_player.weapon == PLAYERWAEPON_NONE) // ���Ⱑ ������ 
				{
					_reversMove = true;
					StateMove();
				}
				else // ���Ⱑ ������ 
				{
					_combo = true;
					playerEffect_Attack();
					_miPlayerEnemyTile->second->Hit(_player.damage);

					if (playerAttackSoundID == 0) SOUNDMANAGER->play("vo_cad_melee_1");
					else if (playerAttackSoundID == 1) SOUNDMANAGER->play("vo_cad_melee_2");
					else if (playerAttackSoundID == 2) SOUNDMANAGER->play("vo_cad_melee_3");
					else
					{
						SOUNDMANAGER->play("vo_cad_melee_4");
						playerAttackSoundID = 0;
					}
					playerAttackSoundID++;
				}
				action = true;
				break;
			}
		}
	}
	else // ������ ����ü�� �ΰ��� ���� �ΰ� �Ҽ��� ���� 
	{
		bool Metal = false;
		for (_miPlayerdeathMetalTile = _mPlayerdeathMetalTile.begin(); _miPlayerdeathMetalTile != _mPlayerdeathMetalTile.end(); ++_miPlayerdeathMetalTile)
		{
			if (_miPlayerdeathMetalTile->first == _player.direction)
			{
				if (_player.weapon == PLAYERWAEPON_NONE)
				{
					_reversMove = true;
					StateMove();
				}
				else
				{
					_combo = true;
					playerEffect_Attack();
					if ((int)_miPlayerdeathMetalTile->second->getBoss_Direction() ==    // ������ �������� �� �����ϸ� 
						(int)_player.direction && _miPlayerdeathMetalTile->second->getBoss_Phase() == BP_PHASE_1)
					{
						_miPlayerdeathMetalTile->second->setBoss_Shield_Hit_True();
						action = true;
						SOUNDMANAGER->play("deathmetal_shieldhit");
						break;
					}
					_miPlayerdeathMetalTile->second->setBoss_HP_Hit(_player.damage);
				}
				action = true;
				break;
			}
		}
		if (action) return;
		for (_miPlayerSlaveTile = _mPlayerSlaveTile.begin(); _miPlayerSlaveTile != _mPlayerSlaveTile.end(); ++_miPlayerSlaveTile)
		{
			if (0 > _mPlayerSlaveTile.size()) break;
			if (_miPlayerSlaveTile->first == _player.direction)
			{
				if (_player.weapon == PLAYERWAEPON_NONE)
				{
					_reversMove = true;
					StateMove();
				}
				else
				{
					_combo = true;
					playerEffect_Attack();
					_miPlayerSlaveTile->second->slave_Hit(_player.damage);

					if (playerAttackSoundID == 0) SOUNDMANAGER->play("vo_cad_melee_1");
					else if (playerAttackSoundID == 1) SOUNDMANAGER->play("vo_cad_melee_2");
					else if (playerAttackSoundID == 2) SOUNDMANAGER->play("vo_cad_melee_3");
					else
					{
						SOUNDMANAGER->play("vo_cad_melee_4");
						playerAttackSoundID = 0;
					}
					playerAttackSoundID++;
				}
				action = true;
				break;
			}
		}


	}
	if (!action) StateMove();
}

void player::wallCheck()
{
	// Ÿ�� �� �����ؾ��� 
	switch (_miPlayerTile->second->wall)
	{
	case W_WALL:
	case W_WALL2: 
		SOUNDMANAGER->play("vo_cad_dig_01");
		SOUNDMANAGER->play("mov_dig_dirt", 1.5f);
		playerEffect_Shovel(_miPlayerTile->second);
		_miPlayerTile->second->type = TYPE_TERRAIN;
		_miPlayerTile->second->wall = W_NONE;
		break;
	case W_ITEM_WALL: 
		SOUNDMANAGER->play("vo_cad_dig_01");
		SOUNDMANAGER->play("mov_dig_dirt", 1.5f);
		playerEffect_Shovel(_miPlayerTile->second);
		_miPlayerTile->second->type = TYPE_TERRAIN;
		_miPlayerTile->second->wall = W_NONE;
		if (RND->getInt(10) % 2 == 0)
		{
			_miPlayerTile->second->type = TYPE_ITEM_ARMOR;
			_miPlayerTile->second->armorFrameX = RND->getInt(4);
			_miPlayerTile->second->armorFrameY = 1;
		}
		else if (RND->getInt(10) % 2 == 1)
		{
			_miPlayerTile->second->type = TYPE_ITEM_WEAPON;
			_miPlayerTile->second->weaponFrameX = RND->getInt(4);
			_miPlayerTile->second->weaponFrameY = 0;
		}
		break;
	case  W_END_WALL:
	case  W_BOSS_WALL:
	case  W_SHOP_WALL: 
		SOUNDMANAGER->play("vo_cad_dig_01");
		SOUNDMANAGER->play("mov_dig_fail", 1.5f);
		playerEffect_Shovel(_miPlayerTile->second);
		break;
	case W_DOOR: // �� ����
		SOUNDMANAGER->play("obj_door_open", 1.5f);
		_miPlayerTile->second->type = TYPE_TERRAIN;
		_miPlayerTile->second->wall = W_NONE;
		break;
	default:
		_miPlayerTile->second->type = TYPE_TERRAIN;
		_miPlayerTile->second->wall = W_NONE;
		break;
	}
}

void player::enemyCheck()
{
}

void player::trapCheck()
{
}

void player::itempCheck()
{
	if (_miPlayerTile->second->type == TYPE_ITEM_ARMOR)
	{
		switch (_miPlayerTile->second->armor)
		{
		case A_HELMET:
			break;
		case A_ARMOR_1:
			bodyLeft = { 15,14,13,12 };
			bodyRight = { 8,9,10,11 };
			KEYANIMANAGER->findAnimation("bodyLeft")->setPlayFrame(&bodyLeft, 4, true);
			KEYANIMANAGER->findAnimation("bodyRight")->setPlayFrame(&bodyRight, 4, true);
			makeItem(WP_NONE, A_ARMOR_1, ST_NONE, 0, 1, 0, 0, 1, 0);
			_player.guard = 1;
			SOUNDMANAGER->play("sfx_pickup_armor");
			break;
		case A_ARMOR_2:  
			bodyLeft = { 23,22,21,20 };
			bodyRight = { 16,17,18,19 };
			KEYANIMANAGER->findAnimation("bodyLeft")->setPlayFrame(&bodyLeft, 4, true);
			KEYANIMANAGER->findAnimation("bodyRight")->setPlayFrame(&bodyRight, 4, true);
			makeItem(WP_NONE, A_ARMOR_2, ST_NONE, 1, 1, 0, 0, 2, 0);
			_player.guard = 2;
			SOUNDMANAGER->play("sfx_pickup_armor");
			break;
		case A_ARMOR_3:
			bodyLeft = { 31,30,29,28 };
			bodyRight = { 24,25,26,27 };
			KEYANIMANAGER->findAnimation("bodyLeft")->setPlayFrame(&bodyLeft, 4, true);
			KEYANIMANAGER->findAnimation("bodyRight")->setPlayFrame(&bodyRight, 4, true);
			makeItem(WP_NONE, A_ARMOR_3, ST_NONE, 2, 1, 0, 0, 3, 0);
			_player.guard = 3;
			SOUNDMANAGER->play("sfx_pickup_armor");
			break;
		case A_ARMOR_4:
			bodyLeft = { 39,38,37,36 };
			bodyRight = { 32,33,34,35 };
			KEYANIMANAGER->findAnimation("bodyLeft")->setPlayFrame(&bodyLeft, 4, true);
			KEYANIMANAGER->findAnimation("bodyRight")->setPlayFrame(&bodyRight, 4, true);
			makeItem(WP_NONE, A_ARMOR_4, ST_NONE, 3, 1, 0, 0, 4, 0);
			_player.guard = 4;
			SOUNDMANAGER->play("sfx_pickup_armor");
			break;
		case A_BOOTS:
			break;
		case A_RING:
			break;
		case A_TORCH_1:
			makeItem(WP_NONE, A_TORCH_1, ST_NONE, 0, 4, 1, 0, 0, 0);
			_player.sight = 5;
			SOUNDMANAGER->play("sfx_pickup_general_ST");
			break;
		case A_TORCH_2:
			makeItem(WP_NONE, A_TORCH_2, ST_NONE, 1, 4, 2, 0, 0, 0);
			_player.sight = 6;
			SOUNDMANAGER->play("sfx_pickup_general_ST");
			break;
		case A_TORCH_3:
			makeItem(WP_NONE, A_TORCH_3, ST_NONE, 2, 4, 3, 0, 0, 0);
			_player.sight = 7;
			SOUNDMANAGER->play("sfx_pickup_general_ST");
			break;
		case A_NONE:
			return;
			break;
		}
		if (_player.isArmor && ((_miPlayerTile->second->armor == A_ARMOR_1)
			|| (_miPlayerTile->second->armor == A_ARMOR_2)
			|| (_miPlayerTile->second->armor == A_ARMOR_3)
			|| (_miPlayerTile->second->armor == A_ARMOR_4)))
		{
			_miPlayerTile->second->type = TYPE_ITEM_ARMOR;
			_miPlayerTile->second->armor = currentItem->armor;
			_miPlayerTile->second->weapon = currentItem->weapon;
			_miPlayerTile->second->stuff = currentItem->stuff;
			_miPlayerTile->second->armorFrameX = currentItem->frameX;	  // ���� �Ӽ��� 
			_miPlayerTile->second->armorFrameY = currentItem->frameY;
		}
		else if (_player.torch && (_miPlayerTile->second->armor == A_TORCH_1
			|| _miPlayerTile->second->armor == A_TORCH_2
			|| _miPlayerTile->second->armor == A_TORCH_3))
		{
			_miPlayerTile->second->type = TYPE_ITEM_ARMOR;
			_miPlayerTile->second->armor = currentItem->armor;
			_miPlayerTile->second->weapon = currentItem->weapon;
			_miPlayerTile->second->stuff = currentItem->stuff;
			_miPlayerTile->second->armorFrameX = currentItem->frameX;	  // ���� �Ӽ��� 
			_miPlayerTile->second->armorFrameY = currentItem->frameY;
		}
		else
		{
			_miPlayerTile->second->type = TYPE_TERRAIN;
			_miPlayerTile->second->armor = A_NONE;
			_miPlayerTile->second->weapon = WP_NONE;
			_miPlayerTile->second->stuff = ST_NONE;
		}
	}
	if (_miPlayerTile->second->type == TYPE_ITEM_WEAPON)
	{
		//makeItem(WEAPON weapon, ARMOR armor,int framex, int framey ,int sight,int damege, float guard, float hp);
		switch (_miPlayerTile->second->weapon)
		{
		case WP_DAGGER_1:
			makeItem(WP_DAGGER_1, A_NONE, ST_NONE, 0, 0, 0, 1, 0, 0);
			_player.weapon = PLAYERWAEPON_DAGGER;
			SOUNDMANAGER->play("sfx_pickup_weapon");
			break;
		case WP_DAGGER_2:
			makeItem(WP_DAGGER_2, A_NONE, ST_NONE, 1, 0, 0, 1, 0, 0);
			_player.weapon = PLAYERWAEPON_DAGGER;
			SOUNDMANAGER->play("sfx_pickup_weapon");
			break;
		case WP_RAPIER:
			makeItem(WP_RAPIER, A_NONE, ST_NONE, 2, 0, 0, 1, 0, 0);
			_player.weapon = PLAYERWAEPON_RAPIER;
			SOUNDMANAGER->play("sfx_pickup_weapon");
			break;
		case WP_BROAD_SWORD:
			makeItem(WP_BROAD_SWORD, A_NONE, ST_NONE, 2, 2, 0, 1, 0, 0);
			_player.weapon = PLAYERWAEPON_BROADSWORD;
			SOUNDMANAGER->play("sfx_pickup_weapon");
			break;
		case WP_LONG_SWORD:
			makeItem(WP_LONG_SWORD, A_NONE, ST_NONE, 3, 0, 0, 1, 0, 0);
			_player.weapon = PLAYERWAEPON_LONGSWORD;
			SOUNDMANAGER->play("sfx_pickup_weapon");
			break;
		case WP_BOMB: // �������� ���� 
			break;
		case WP_RIFLE:
			break;
		case WP_SHOTGUN:
			break;
		case WP_SPEAR:
			break;
		case WP_MACE:
			break;
		case WP_WHIP:
			break;
		case WP_NINETAILS_WHIP:
			break;
		case WP_BOW:
			break;
		case WP_CROSS_BOW:
			break;
		case WP_NONE:
			return;
			break;
		}
		if (_player.isWeapon)
		{
			_miPlayerTile->second->type = TYPE_ITEM_WEAPON;
			_miPlayerTile->second->armor = currentItem->armor;
			_miPlayerTile->second->weapon = currentItem->weapon;
			_miPlayerTile->second->stuff = currentItem->stuff;
			_miPlayerTile->second->weaponFrameX = currentItem->frameX;	  // ���� �Ӽ��� 
			_miPlayerTile->second->weaponFrameY = currentItem->frameY;
		}
		else
		{
			_miPlayerTile->second->type = TYPE_TERRAIN;
			_miPlayerTile->second->armor = A_NONE;
			_miPlayerTile->second->weapon = WP_NONE;
			_miPlayerTile->second->stuff = ST_NONE;
		}
	}
	if (_miPlayerTile->second->type == TYPE_ITEM_STUFF)
	{
		switch (_miPlayerTile->second->stuff)
		{
		case ST_DIAMOND:
			_player.diamond++;
			SOUNDMANAGER->play("sfx_pickup_diamond");
			break;
		case ST_ONE_COIN:
			// ���� 
			break;
		case ST_ONE_HALF_COIN:
			// ���� ������ 
			break;
		case ST_COINS:
			_player.coin += 5;
			SOUNDMANAGER->play("sfx_pickup_gold_02");
			break;
		case ST_MORE_COINS:
			_player.coin += 15;
			SOUNDMANAGER->play("sfx_pickup_gold_02");
			break;
		case ST_APPLE:
			makeItem(WP_NONE, A_NONE, ST_APPLE, 0, 3, 0, 0, 0, 1);
			SOUNDMANAGER->play("sfx_pickup_general_ST");
			break;
		case ST_CHEESE:
			makeItem(WP_NONE, A_NONE, ST_CHEESE, 1, 3, 0, 0, 0, 2);
			SOUNDMANAGER->play("sfx_pickup_general_ST");
			break;
		case ST_MEAT:
			makeItem(WP_NONE, A_NONE, ST_MEAT, 2, 3, 0, 0, 0, 3);
			SOUNDMANAGER->play("sfx_pickup_general_ST");
			break;
		case ST_NONE:
			return;
			break;
		}
		if (_player.potion && (_miPlayerTile->second->stuff == ST_APPLE
			|| _miPlayerTile->second->stuff == ST_CHEESE || _miPlayerTile->second->stuff == ST_MEAT))
		{
			_miPlayerTile->second->type = TYPE_ITEM_STUFF;
			_miPlayerTile->second->armor = currentItem->armor;
			_miPlayerTile->second->weapon = currentItem->weapon;
			_miPlayerTile->second->stuff = currentItem->stuff;
			_miPlayerTile->second->stuffFrameX = currentItem->frameX;	  // ���� �Ӽ��� 
			_miPlayerTile->second->stuffFrameY = currentItem->frameY;
		}
		else
		{
			_miPlayerTile->second->type = TYPE_TERRAIN;
			_miPlayerTile->second->armor = A_NONE;
			_miPlayerTile->second->weapon = WP_NONE;
			_miPlayerTile->second->stuff = ST_NONE;
		}
	}
}

void player::makeItem(WEAPON weapon, ARMOR armor, STUFF stuff, int framex, int framey, int sight, int damege, float guard, float hp)
{
	if (armor == A_ARMOR_1
		|| armor == A_ARMOR_2
		|| armor == A_ARMOR_3
		|| armor == A_ARMOR_4)
	{
		for (int i = 0; i < _vInven.size(); ++i)
		{
			if (_vInven[i]->armor == A_ARMOR_1
				|| _vInven[i]->armor == A_ARMOR_2
				|| _vInven[i]->armor == A_ARMOR_3
				|| _vInven[i]->armor == A_ARMOR_4)
			{
				currentItem = _vInven[i];
				_player.isArmor = true;
				this->itemRemove(i);
				break;
			}
		}
	}
	else if (weapon != W_NONE && stuff == ST_NONE && armor == A_NONE)
	{
		for (int i = 0; i < _vInven.size(); ++i)
		{
			if (_vInven[i]->weapon == WP_DAGGER_1
				|| _vInven[i]->weapon == WP_DAGGER_2
				|| _vInven[i]->weapon == WP_RAPIER
				|| _vInven[i]->weapon == WP_BROAD_SWORD
				|| _vInven[i]->weapon == WP_LONG_SWORD)
			{
				currentItem = _vInven[i];
				_player.isWeapon = true;
				this->itemRemove(i);
				break;
			}
		}
	}
	else if (armor == A_TORCH_1
		|| armor == A_TORCH_2
		|| armor == A_TORCH_3)
	{
		for (int i = 0; i < _vInven.size(); ++i)
		{
			if (_vInven[i]->armor == A_TORCH_1
				|| _vInven[i]->armor == A_TORCH_2
				|| _vInven[i]->armor == A_TORCH_3)
			{
				currentItem = _vInven[i];
				_player.torch = true;
				this->itemRemove(i);
				break;
			}
		}
	}
	else if (stuff == ST_APPLE || stuff == ST_CHEESE || stuff == ST_MEAT)
	{
		for (int i = 0; i < _vInven.size(); ++i)
		{
			if (_vInven[i]->stuff == ST_APPLE
				|| _vInven[i]->stuff == ST_CHEESE
				|| _vInven[i]->stuff == ST_MEAT)
			{
				currentItem = _vInven[i];
				_player.potion = true;
				this->itemRemove(i);
				break;
			}
		}
	}


	tagItem* item;
	item = new tagItem;
	//ZeroMemory(item, sizeof(item));
	item->weapon = weapon;
	item->armor = armor;
	item->stuff = stuff;
	item->frameX = framex;
	item->frameY = framey;
	item->sight = sight;
	item->damege = damege;
	item->guard = guard;
	item->hp = hp;
	_vInven.push_back(item);
}

void player::StateMove()
{
	_previousIdx = _player.idx;
	_previousIdy = _player.idy;

	switch (_player.direction)
	{
	case PLAYERDIRECTION_UP:
		_player.idy--;			// ��ǥY��--
		//��������
		_angle = getAngle(_player.x, _player.y, _player.x, _player.y - _distance);  // ���� 
		_worldTimeCount = TIMEMANAGER->getWorldTime();								// ���� �ð� 
		_isMoving = true;															// MOVE

		if (!_reversMove) _jump->jumping(&_player.x, &_player.y, 2, 1.5, true); //���� 
		break; 
	case PLAYERDIRECTION_DOWN:
		_player.idy++;	// ��ǥY��++
		//��������
		_angle = getAngle(_player.x, _player.y, _player.x, _player.y + _distance);  // ���� 
		_worldTimeCount = TIMEMANAGER->getWorldTime();								// ���� �ð� 
		_isMoving = true;															// MOVE

		if (!_reversMove) _jump->jumping(&_player.x, &_player.y, 8, 1.5);	//���� 
		break;
	case PLAYERDIRECTION_RIGHT:
		//�̹��� ����
		_player.headAni = KEYANIMANAGER->findAnimation("headRight");
		_player.bodyAni = KEYANIMANAGER->findAnimation("bodyRight");
		_player.headAni->start();
		_player.bodyAni->start();
		_player.idx++;	// ��ǥ X��++
		//��������
		_angle = getAngle(_player.x, _player.y, _player.x + _distance, _player.y);  // ���� 
		_worldTimeCount = TIMEMANAGER->getWorldTime();								// ���� �ð� 
		_isMoving = true;															// MOVE
		_jump->jumping(&_player.x, &_player.y, 7, 1.5);	// ����
		break;
	case PLAYERDIRECTION_LEFT:
		//�̹��� ����
		_player.headAni = KEYANIMANAGER->findAnimation("headLeft");
		_player.bodyAni = KEYANIMANAGER->findAnimation("bodyLeft");
		_player.headAni->start();
		_player.bodyAni->start();
		_player.idx--;	// ��ǥ X��--
		//��������
		_angle = getAngle(_player.x, _player.y, _player.x - _distance, _player.y);	// ���� 
		_worldTimeCount = TIMEMANAGER->getWorldTime();								// ���� �ð� 
		_isMoving = true;															// MOVE
		_jump->jumping(&_player.x, &_player.y, 7, 1.5);	//���� 
		break;
	}
}

void player::itemUse()
{
	for (int i = 0; i < _vInven.size(); ++i)
	{
		if (_vInven[i]->stuff == ST_APPLE
			|| _vInven[i]->stuff == ST_CHEESE
			|| _vInven[i]->stuff == ST_MEAT)
		{
			_player.hp = _player.hp + _vInven[i]->hp;
			if (_player.hp > _player.maxHp)
			{
				_player.hp = _player.maxHp;
			}
			_player.potion = false;

			this->itemRemove(i);
			break;
		}
	}

	for (int i = 0; i < _vInven.size(); ++i)
	{
		if (_vInven[i]->stuff == ST_APPLE
			|| _vInven[i]->stuff == ST_CHEESE
			|| _vInven[i]->stuff == ST_MEAT)
		{
			_player.potion = true;
			break;
		}
	}
}

void player::playerDie()
{
	if (_player.hp <= 0)
	{
		OPTION->setPlayerDie(true);
		BEATMANAGER->AllStopMusic();
	}
}


