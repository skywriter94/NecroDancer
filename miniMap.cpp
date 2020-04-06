#include "stdafx.h"
#include "miniMap.h"
miniMap::miniMap()
{
}

miniMap::~miniMap()
{
}

HRESULT miniMap::init()
{
	//�̴ϸ� �̹��� �߰�
	IMAGEMANAGER->addImage("min_door", "./image/UI/min_rect_door.bmp",6,6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_end", "./image/UI/min_rect_end.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_end_else", "./image/UI/min_rect_end_else.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_enemy", "./image/UI/min_rect_enemy.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_fallingdoor", "./image/UI/min_rect_fallingdoor.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_normal", "./image/UI/min_rect_normal.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_player", "./image/UI/min_rect_player.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_shop", "./image/UI/min_rect_shop.bmp", 6,6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_stair", "./image/UI/min_rect_stair.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_trap", "./image/UI/min_rect_trap.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_wall2", "./image/UI/min_rect_wall2.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_wall3", "./image/UI/min_rect_wall3.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_shoping_rc", "./image/UI/min_rect_shopingRect.bmp", 6, 6, true, RGB(255, 0, 255));
	
	//�÷��̾� ��ġ ���� �ʱ�ȭ
	_playerX = 0;
	_playerY = 0;
	return S_OK;
}

void miniMap::release()
{
}

void miniMap::update()
{
}

void miniMap::render()
{
	//�̴ϸ� Ÿ�� ������ ���� �̹��� Ű�� ����
	for (_viStageMap = _vStageMap.begin(); _viStageMap != _vStageMap.end(); ++_viStageMap)
	{
		if ((*_viStageMap)->type == TYPE_NONE) continue; //Ÿ���� ���� ��� �ѱ⵵��

		switch ((*_viStageMap)->type)
		{
		case TYPE_TERRAIN:								//���� Ÿ��
			if ((*_viStageMap)->terrain == TR_STAIR || (*_viStageMap)->terrain == TR_BOSS_STAIR)
			{
				_imageName = "min_stair";				//init���� �ʱ�ȭ�� �̹��� Ű���� ã�Ƽ� �־��ش�
			}
			else if ((*_viStageMap)->terrain == TR_SHOP )
			{
				_imageName = "min_shoping_rc";
			}
			else if ((*_viStageMap)->terrain == TR_END)
			{
				_imageName = "min_end";
			}
			else
			{
				_imageName = "min_normal";
			}
			break;
		case TYPE_WALL:									//�� Ÿ��
			if ((*_viStageMap)->wall == W_ITEM_WALL || (*_viStageMap)->wall == W_SHOP_WALL)
			{
				_imageName = "min_wall3";
			}
			else if ((*_viStageMap)->wall == W_WALL2 || (*_viStageMap)->wall == W_BOSS_WALL)
			{
				_imageName = "min_wall2";
			}
			else if ((*_viStageMap)->wall == W_DOOR)
			{
				_imageName = "min_door";
			}
			else if ((*_viStageMap)->wall == W_END_WALL)
			{
				_imageName = "min_end";
			}
			else
			{
				_imageName = "min_end_else";
			}
			break;
		case TYPE_TRAP:									//���� Ÿ��
			if ((*_viStageMap)->trap == TRAP_SHADOW || (*_viStageMap)->trap == TRAP_NIDDLE_SHADOW)
			{
			}
			else
			{
				_imageName = "min_trap";
			}
			break;
		case TYPE_ITEM_ARMOR:							//���� ������ Ÿ��
			if ((*_viStageMap)->armor == A_NONE)
			{
			}
			else
			{
				_imageName = "min_shop";
			}
			break;
		case TYPE_ITEM_WEAPON:
			if ((*_viStageMap)->weapon == WP_NONE)		//���� ������ Ÿ��
			{
			}
			else
			{
				_imageName = "min_shop";
			}
			break;
		case TYPE_ITEM_STUFF:
			if ((*_viStageMap)->stuff == ST_NONE)		//�Һ� ������ Ÿ��
			{
			}
			else
			{
				_imageName = "min_shop";
			}
			break;
		case TYPE_OBJECT:
			if ((*_viStageMap)->obj == OBJ_FALLING_DOOR)//�������� �� Ÿ��
			{
				_imageName = "min_fallingdoor";
			}
			break;
		case TYPE_NONE:
			break;
		default:
			break;
		}
		//�þ߿� ���� ���縸 ���̵���
		if ((*_viStageMap)->alphaValue <= 0)								//���ķ��������� 0�� Ÿ���� ���(�þ߿� ���� Ÿ��)
		{
			//Ÿ�� �̴ϸ� ���
			IMAGEMANAGER->findImage(_imageName)->render(getMemDC(),
				750 + (*_viStageMap)->rc.left / 10,
				450 + (*_viStageMap)->rc.top / 10);
			//�÷��̾� �̴ϸ� ���
			IMAGEMANAGER->findImage("min_player")->render(getMemDC(),
				747 + _playerX / 10,
				448 + _playerY / 10);
		}
	}
	//���� �̴ϸ� ���
	vector<Enemy*> vec = _em->getVEnemy();									//���ʹ� ���� 
	vector<Enemy*>::iterator ins = vec.begin();								//���ʹ� ���ͷ�����
	if ((*ins)->getEnemyInfo()->Light)										//���ʹ� ��ġ Ȯ�� �Ұ�
	{
		for (; ins != vec.end();)											//���ͷ����Ͱ� ������ ���� �ƴ� ���
		{
			IMAGEMANAGER->findImage("min_enemy")->render(getMemDC(),		//���ʹ� �̴ϸ� �̹��� ��� 
				750 + (*ins)->getEnemyInfo()->rc.left / 10,
				450 + (*ins)->getEnemyInfo()->rc.top / 10);
			ins++;															//���͸� ��� ��������
		}
	}
}