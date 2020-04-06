#include "stdafx.h"
#include "UImanager.h"

HRESULT UImanager::init()
{
	//���� �κ��丮 �̹���
	_attackInven.image = IMAGEMANAGER->addImage("attack_Inven", "./image/UI/hud_slot_2.bmp", 60, 66, true, RGB(255, 0, 255));
	_shovelInven.image = IMAGEMANAGER->addImage("shovel_Inven", "./image/UI/hud_slot_1.bmp", 60, 66, true, RGB(255, 0, 255));
	_itemInven.image = IMAGEMANAGER->addImage("item_Inven", "./image/UI/hud_slot_action1.bmp", 60, 84, true, RGB(255, 0, 255));
	_bombInven.image = IMAGEMANAGER->addImage("bomb_Inven", "./image/UI/hud_slot_bomb.bmp", 60, 84, true, RGB(255, 0, 255));
	_throwInven.image = IMAGEMANAGER->addImage("throw_Inven", "./image/UI/hud_slot_throw.bmp", 60, 84, true, RGB(255, 0, 255));
	_bodyInven.image = IMAGEMANAGER->addImage("body_Inven", "./image/UI/hud_slot_3.bmp", 60, 66, true, RGB(255, 0, 255));
	_headInven.image = IMAGEMANAGER->addImage("head_Inven", "./image/UI/hud_slot_4.bmp", 60, 66, true, RGB(255, 0, 255));
	_feetInven.image = IMAGEMANAGER->addImage("feet_Inven", "./image/UI/hud_slot_5.bmp", 60, 66, true, RGB(255, 0, 255));
	_torchInven.image = IMAGEMANAGER->addImage("torch_Inven", "./image/UI/hud_slot_6.bmp", 60, 66, true, RGB(255, 0, 255));
	_ringInven.image = IMAGEMANAGER->addImage("ring_Inven", "./image/UI/hud_slot_7.bmp", 60, 66, true, RGB(255, 0, 255));

	//������ �κ��丮 �̹���
	_coinInven.image = IMAGEMANAGER->addImage("coin_Inven", "./image/UI/hud_coins.bmp", 48, 48, true, RGB(255, 0, 255));
	_daiaInven.image = IMAGEMANAGER->addImage("daia_Inven", "./image/UI/diamond.bmp", 50, 48, true, RGB(255, 0, 255));

	_scoreNum = IMAGEMANAGER->addFrameImage("number", "./image/UI/number.bmp", 80, 20, 10, 1, true, RGB(255, 0, 255));
	_scoreX = IMAGEMANAGER->addImage("numberX", "./image/UI/x.bmp", 8, 8, true, RGB(255, 0, 255));
	_daiaNum = IMAGEMANAGER->addFrameImage("number", "./image/UI/number.bmp", 80, 20, 10, 1, true, RGB(255, 0, 255));

	//�κ��丮 �ؽ�Ʈ �̹���
	_downLeft.image = IMAGEMANAGER->addImage("down_Left", "./image/UI/down_left_x2.bmp", 46, 48, true, RGB(255, 0, 255));
	_upDown.image = IMAGEMANAGER->addImage("up_Down", "./image/UI/up_down_x2.bmp", 46, 48, true, RGB(255, 0, 255));
	_upLeft.image = IMAGEMANAGER->addImage("up_Left", "./image/UI/up_left_x2.bmp", 46, 48, true, RGB(255, 0, 255));

	//��Ʈ �̹���
	IMAGEMANAGER->addFrameImage("heart_full", "./image/UI/heart_full.bmp", 109, 50, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("heart_half", "./image/UI/heart_half.bmp", 109, 50, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("heart_null", "./image/UI/heart_null.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255));

	for (int i = 0; i < 3; i++)
	{
		_heart[i].state = HEARTSTATE_FULL;								//��Ʈ���� �ʱ�ȭ
		_heart[i].image = IMAGEMANAGER->findImage("heart_full");		//��Ʈ���� �̹���
	}

	//�ִϸ��̼� ================================

	int heartFull[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("heart_full_ani", "heart_full", heartFull, 2, 10, true);
	int heartFull_move[] = { 0,1 };		//�ִϸ��̼ǸŴ����� �������̹��� ���� ���� �ʱ�ȭ								
	KEYANIMANAGER->addArrayFrameAnimation("heart_full_ani_move", "heart_full", heartFull_move, 2, 10, true);

	for (int i = 0; i < 3; i++)
	{
		_heart[i].anime = KEYANIMANAGER->findAnimation("heart_full_ani_move");				//�ִϸ��̼� Ű�� �ʱ�ȭ
		_heart[i].anime->start();															//���ϸ��̼� ��ŸƮ
	}
	//============================================

	_hp = _player->hp;										//HP �÷��̾� ����
	_coinvalue = _player->coin;								//���� �׽�Ʈ
	_diavalue = _player->diamond;							//���̾� �׽�Ʈ
	_heartBeatCnt = 0;										//��Ʈ��Ʈ ī��Ʈ

	_heartinterval = false;
	//�κ��丮 ����&���� �Ұ�=============================
	_attackInven.open = false;
	_shovelInven.open = false;
	_itemInven.open = false;
	_bombInven.open = false;
	_throwInven.open = false;
	_bodyInven.open = false;
	_headInven.open = false;
	_feetInven.open = false;
	_torchInven.open = false;
	_ringInven.open = false;

	//�κ��丮 ������ ��ġ
	_x1Slot = 20, _y1Slot = 5;
	_x2Slot = 90, _y2Slot = 81;
	_x3Slot = 160, _y3Slot = 195;
	_x4Slot = 230, _y4Slot = 299;
	_x5Slot = 300;
	_x6Slot = 370;
	_x7Slot = 440;

	//�κ��丮 �̹��� ��ǥ ����
	_itemInven.x = 20;
	_itemInven.image->setX(_itemInven.x);
	_itemInven.image->setY(_itemInven.y);

	_attackInven.y = 5;
	_attackInven.image->setX(_attackInven.x);
	_attackInven.image->setY(_attackInven.y);

	_throwInven.x = 20;
	_throwInven.image->setY(_throwInven.x);
	_throwInven.image->setY(_throwInven.y);

	_bodyInven.y = 5;
	_bodyInven.image->setX(_bodyInven.x);
	_bodyInven.image->setY(_bodyInven.y);

	_bombInven.x = 20;
	_bombInven.image->setX(_bombInven.x);
	_bombInven.image->setY(_bombInven.y);

	_headInven.y = 5;
	_headInven.image->setX(_headInven.x);
	_headInven.image->setY(_headInven.y);

	_feetInven.y = 5;
	_feetInven.image->setX(_feetInven.x);
	_feetInven.image->setY(_feetInven.y);

	_torchInven.y = 5;
	_torchInven.image->setX(_torchInven.x);
	_torchInven.image->setY(_torchInven.y);

	_ringInven.y = 5;
	_ringInven.image->setX(_ringInven.x);
	_ringInven.image->setY(_ringInven.y);

	_shovelInven.x = 20;
	_shovelInven.image->setX(_shovelInven.x);
	return S_OK;
}

void UImanager::release()
{

}

void UImanager::update()
{
	_coinvalue = _player->coin;										//�÷��̾� ���� �� �޾ƿ���
	_diavalue = _player->diamond;									//�÷��̾� ���̾Ƹ�� �� �޾ƿ���
	_hp = _player->hp;												//�÷��̾� HP �� �޾ƿ���

	//������ ��Ʈ�� �޾��� �� ��Ʈ�� �����̵���
	if (BEATMANAGER->getBeating() && _heartinterval)
	{
		_heartBeatCnt++;											//��Ʈ �ٴ� ī��Ʈ
		_heartinterval = false;										//��Ʈ ���͹�
		if (_heartBeatCnt > 2)										//����° ��Ʈ �ٰ� ����
		{
			_heartBeatCnt = 0;										//ù��° ��Ʈ�� ���ƿ�����
		}	
	}
	if (!BEATMANAGER->getBeating())  _heartinterval = true;			//���忡 ��Ʈ�� �� ������ �� ��Ʈ�� ���ߵ���

	//=======================================

	//HP�� ���� ��Ʈ�� ���� ����
	switch (_hp)
	{
	case 6:
		_heart[0].state = HEARTSTATE_FULL;							//ù��° ��Ʈ ���� ����
		_heart[1].state = HEARTSTATE_FULL;							//�ι�° ��Ʈ ���� ����
		_heart[2].state = HEARTSTATE_FULL;							//����° ��Ʈ ���� ����
		break;
	case 5:
		_heart[0].state = HEARTSTATE_FULL;							//ù��° ��Ʈ ���� ����
		_heart[1].state = HEARTSTATE_FULL;							//�ι�° ��Ʈ ���� ����
		_heart[2].state = HEARTSTATE_HALF;							//����° ��Ʈ ���丷 ����
		break;
	case 4:
		_heart[0].state = HEARTSTATE_FULL;							//ù��° ��Ʈ ���� ����
		_heart[1].state = HEARTSTATE_FULL;							//�ι�° ��Ʈ ���� ����
		_heart[2].state = HEARTSTATE_NULL;							//����° ��Ʈ �� ����
		break;
	case 3:
		_heart[0].state = HEARTSTATE_FULL;							//ù��° ��Ʈ ���� ����
		_heart[1].state = HEARTSTATE_HALF;							//�ι�° ��Ʈ ���丷 ����
		_heart[2].state = HEARTSTATE_NULL;							//����° ��Ʈ �� ����
		break;
	case 2:
		_heart[0].state = HEARTSTATE_FULL;							//ù��° ��Ʈ ���� ����
		_heart[1].state = HEARTSTATE_NULL;							//�ι�° ��Ʈ �� ����
		_heart[2].state = HEARTSTATE_NULL;							//����° ��Ʈ �� ����
		break;
	case 1:
		_heart[0].state = HEARTSTATE_HALF;							//ù��° ��Ʈ ���丷 ����
		_heart[1].state = HEARTSTATE_NULL;							//�ι�° ��Ʈ �� ����
		_heart[2].state = HEARTSTATE_NULL;							//����° ��Ʈ �� ����
		break;
	case 0:
		_heart[0].state = HEARTSTATE_NULL;							//ù��° ��Ʈ �� ����
		_heart[1].state = HEARTSTATE_NULL;							//�ι�° ��Ʈ �� ����
		_heart[2].state = HEARTSTATE_NULL;							//����° ��Ʈ �� ����
		break;
	}

	//��Ʈ ���¿� ���� �ش� �̹��� ã��
	for (int i = 0; i < 3; i++)
	{
		if (_heart[i].state == HEARTSTATE_FULL)						//��Ʈ ���� ����
		{
			_heart[i].image = IMAGEMANAGER->findImage("heart_full");//�̹���
		}
		if (_heart[i].state == HEARTSTATE_HALF)						//��Ʈ ���丷 ����	
		{
			_heart[i].image = IMAGEMANAGER->findImage("heart_half");//�̹���
		}
		if (_heart[i].state == HEARTSTATE_NULL)						//��Ʈ �� ����
		{
			_heart[i].image = IMAGEMANAGER->findImage("heart_null");//�̹���
		}
	}

	//��Ʈ��Ʈ�� �޾ƿ��� ������ ��=========================================
	//��Ʈ��Ʈ�� ������ ++���ٰ�
	//��Ʈ��Ʈ�� ���� ��Ʈ�� �ٴ� ��ġ�� �ٸ��� ���� ����
	switch (_heartBeatCnt)
	{
	case 0:
		_heart[0].turn = TURN_ON;				//TURN_ON  �ٰ� �ִ� ����
		_heart[1].turn = TURN_OFF;				//TURN_OFF ���� �ʴ� ����
		_heart[2].turn = TURN_OFF;
		break;
	case 1:
		_heart[0].turn = TURN_OFF;
		_heart[1].turn = TURN_ON;
		_heart[2].turn = TURN_OFF;
		if (_hp < 3)
		{
			_heartBeatCnt = 0;		//����ִ� ��Ʈ�� ù��° ��Ʈ���� �ִϸ��̼� �ǵ��� ����ó��
		}
		break;
	case 2:
		_heart[0].turn = TURN_OFF;
		_heart[1].turn = TURN_OFF;
		_heart[2].turn = TURN_ON;
		if (_hp < 5)
		{
			_heartBeatCnt = 0;
		}
		break;
	}

	for (int i = 0; i < 3; i++)															//�ٴ� ���¿�,�ƴ� ������ �ִϸ��̼� �ֱ�
	{
		if (_heart[i].turn == TURN_ON)													//TURN_ON  �ٰ� �ִ� ����
		{																				
			_heart[i].anime = KEYANIMANAGER->findAnimation("heart_full_ani_move");		//���� �ٴ� �������� �ִϸ��̼����� ó��
		}
		else if (_heart[i].turn == TURN_OFF)											//TURN_OFF ���� �ʴ� ����
		{
			_heart[i].anime = KEYANIMANAGER->findAnimation("heart_full_ani");
		}

	}

	//�κ��丮 �̵� ����ó��========================
//x�� ����

//�κ� ����&���� �Ұ��� ����
//Ư�� ���Կ� ��Ÿ������
	if (!_shovelInven.open)													
	{
		_attackInven.x = _x1Slot;											
		if (!_attackInven.open)												
		{
			_bodyInven.x = _x1Slot;
			if (!_bodyInven.open)
			{
				_headInven.x = _x1Slot;
				if (!_headInven.open)
				{
					_feetInven.x = _x1Slot;
					if (!_feetInven.open)
					{
						_torchInven.x = _x1Slot;
						if (!_torchInven.open)_ringInven.x = _x1Slot;
					}
				}
			}
		}
	}
//==================================
//�κ� ����&���� �Ұ��� ����
//Ư�� �������� �̵��ϵ��� (�� �κ��� ���� ���� ���� ����)
	if (_shovelInven.open)
	{
		_shovelInven.x = _x1Slot;
		if (_x2Slot >= _attackInven.x)_attackInven.x++;
		if (_x2Slot >= _bodyInven.x)_bodyInven.x++;
		if (_x2Slot >= _headInven.x)_headInven.x++;
		if (_x2Slot >= _feetInven.x)_feetInven.x++;
		if (_x2Slot >= _torchInven.x)_torchInven.x++;
		if (_x2Slot >= _ringInven.x)_ringInven.x++;
		if (_attackInven.open)
		{
			if (_x3Slot >= _bodyInven.x)_bodyInven.x++;
			if (_x3Slot >= _headInven.x)_headInven.x++;
			if (_x3Slot >= _feetInven.x)_feetInven.x++;
			if (_x3Slot >= _torchInven.x)_torchInven.x++;
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
			if (_bodyInven.open)
			{
				if (_x4Slot >= _headInven.x)_headInven.x++;
				if (_x4Slot >= _feetInven.x)_feetInven.x++;
				if (_x4Slot >= _torchInven.x)_torchInven.x++;
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
				if (_headInven.open)
				{
					if (_x5Slot >= _feetInven.x)_feetInven.x++;
					if (_x5Slot >= _torchInven.x)_torchInven.x++;
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
					if (_feetInven.open)
					{
						if (_x6Slot >= _torchInven.x)_torchInven.x++;
						if (_x6Slot >= _ringInven.x)_ringInven.x++;
						if (_torchInven.open)
						{
							if (_x7Slot >= _ringInven.x)_ringInven.x++;
						}
					}
					if (_torchInven.open)
					{
						if (_x6Slot >= _ringInven.x)_ringInven.x++;
					}
				}
				if (_feetInven.open)
				{
					if (_x5Slot >= _torchInven.x)_torchInven.x++;
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
					if (_torchInven.open)
					{
						if (_x6Slot >= _ringInven.x)_ringInven.x++;
					}
				}
				if (_torchInven.open)
				{
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
				}

			}
			if (_headInven.open)
			{
				if (_x4Slot >= _feetInven.x)_feetInven.x++;
				if (_x4Slot >= _torchInven.x)_torchInven.x++;
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
				if (_feetInven.open)
				{
					if (_x5Slot >= _torchInven.x)_torchInven.x++;
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
					if (_torchInven.open)
					{
						if (_x6Slot >= _ringInven.x)_ringInven.x++;
					}
				}
			}
			if (_feetInven.open)
			{
				if (_x4Slot >= _torchInven.x)_torchInven.x++;
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
				if (_torchInven.open)
				{
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
				}
			}
			if (_torchInven.open)
			{
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
			}
		}
		if (_bodyInven.open)
		{
			if (_x3Slot >= _headInven.x)_headInven.x++;
			if (_x3Slot >= _feetInven.x)_feetInven.x++;
			if (_x3Slot >= _torchInven.x)_torchInven.x++;
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
			if (_headInven.open)
			{
				if (_x4Slot >= _feetInven.x)_feetInven.x++;
				if (_x4Slot >= _torchInven.x)_torchInven.x++;
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
				if (_feetInven.open)
				{
					if (_x5Slot >= _torchInven.x)_torchInven.x++;
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
					if (_torchInven.open)
					{
						if (_x6Slot >= _ringInven.x)_ringInven.x++;
					}
				}
			}
		}
		if (_headInven.open)
		{
			if (_x3Slot >= _feetInven.x)_feetInven.x++;
			if (_x3Slot >= _torchInven.x)_torchInven.x++;
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
			if (_feetInven.open)
			{
				if (_x4Slot >= _torchInven.x)_torchInven.x++;
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
				if (_torchInven.open)
				{
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
				}
			}
		}
		if (_feetInven.open)
		{
			if (_x3Slot >= _torchInven.x)_torchInven.x++;
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
			if (_torchInven.open)
			{
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
			}
		}
		if (_torchInven.open)
		{
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
		}
	}

	//==============================================
	//Ư�� �������� �̵��ϵ��� (���� �κ��� ���� ���� ���� ����)

	if (_attackInven.open)
	{
		if (_x2Slot >= _bodyInven.x)_bodyInven.x++;
		if (_x2Slot >= _headInven.x)_headInven.x++;
		if (_x2Slot >= _feetInven.x)_feetInven.x++;
		if (_x2Slot >= _torchInven.x)_torchInven.x++;
		if (_x2Slot >= _ringInven.x)_ringInven.x++;
		if (_bodyInven.open)
		{
			if (_x3Slot >= _headInven.x)_headInven.x++; //���⼭ �ص尡 ������ 
			if (_x3Slot >= _feetInven.x)_feetInven.x++;	//�ؿ� ��׵��� x3�� �ӹ��±���
			if (_x3Slot >= _torchInven.x)_torchInven.x++;
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
			if (_headInven.open)
			{
				if (_x4Slot >= _feetInven.x)_feetInven.x++;
				if (_x4Slot >= _torchInven.x)_torchInven.x++;
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
				if (_feetInven.open)
				{
					if (_x5Slot >= _torchInven.x)_torchInven.x++;
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
					if (_torchInven.open)
					{
						if (_x6Slot >= _ringInven.x)_ringInven.x++;
					}

				}

			}

			if (_feetInven.open)
			{
				if (_x4Slot >= _torchInven.x)_torchInven.x++;
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
				if (_torchInven.open)
				{
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
				}
			}
			if (_torchInven.open)
			{
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
			}
		}
		if (_headInven.open)
		{
			if (_x3Slot >= _feetInven.x)_feetInven.x++;
			if (_x3Slot >= _torchInven.x)_torchInven.x++;
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
			if (_feetInven.open)
			{
				if (_x4Slot >= _torchInven.x)_torchInven.x++;
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
				if (_torchInven.open)
				{
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
				}

			}

		}
		if (_feetInven.open)
		{
			if (_x3Slot >= _torchInven.x)_torchInven.x++;
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
			if (_torchInven.open)
			{
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
			}

		}
		if (_torchInven.open)
		{
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
		}
	}


	//=================================================
	//Ư�� �������� �̵��ϵ��� (���� �κ��� ���� ���� ���� ����)

	if (_bodyInven.open)
	{
		if (_x2Slot >= _headInven.x)_headInven.x++;
		if (_x2Slot >= _feetInven.x)_feetInven.x++;
		if (_x2Slot >= _torchInven.x)_torchInven.x++;
		if (_x2Slot >= _ringInven.x)_ringInven.x++;
		if (_headInven.open)
		{
			if (_x3Slot >= _feetInven.x)_feetInven.x++;
			if (_x3Slot >= _torchInven.x)_torchInven.x++;
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
			if (_feetInven.open)
			{
				if (_x4Slot >= _torchInven.x)_torchInven.x++;
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
				if (_torchInven.open)
				{
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
				}
			}
			if (_torchInven.open)
			{
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
			}

		}
		if (_feetInven.open)
		{
			if (_x3Slot >= _torchInven.x)_torchInven.x++;
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
			if (_torchInven.open)
			{
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
			}
		}
		if (_torchInven.open)
		{
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
		}
	}

	//===================================
	//Ư�� �������� �̵��ϵ��� (��� �κ��� ���� ���� ���� ����)
	if (_headInven.open)
	{
		if (_x2Slot >= _feetInven.x)_feetInven.x++;
		if (_x2Slot >= _torchInven.x)_torchInven.x++;
		if (_x2Slot >= _ringInven.x)_ringInven.x++;
		if (_feetInven.open)
		{
			if (_x3Slot >= _torchInven.x)_torchInven.x++;
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
			if (_torchInven.open)
			{
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
			}
		}
		if (_torchInven.open)
		{
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
		}
	}
	//=============================
	//Ư�� �������� �̵��ϵ��� (�Ź� �κ��� ���� ���� ���� ����)

	if (_feetInven.open)
	{
		if (_x2Slot >= _torchInven.x)_torchInven.x++;
		if (_x2Slot >= _ringInven.x)_ringInven.x++;
		if (_torchInven.open)
		{
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
		}
	}

	//==========================
	//Ư�� �������� �̵��ϵ��� (ȶ�� �κ��� ���� ���� ���� ����)
	if (_torchInven.open)
	{
		if (_x2Slot >= _ringInven.x)_ringInven.x++;
	}

//y�� ����====================
//�κ� ����&���� �Ұ��� ����
//Ư�� ���Կ� ��Ÿ������
	_itemInven.y = _y2Slot;
	if (!_itemInven.open)
	{
		_throwInven.y = _y2Slot;
		if (!_throwInven.open)
		{
			_bombInven.y = _y2Slot;
		}
	}
	//Ư�� �������� �̵��ϵ��� (������ �κ��� ���� ���� ���� ����)
	else if (_itemInven.open)
	{
		if (_y3Slot >= _throwInven.y)_throwInven.y++;
		if (_y3Slot >= _bombInven.y)_bombInven.y++;
		if (_throwInven.open)
		{
			if (_y4Slot >= _bombInven.y)_bombInven.y++;
		}
		else if (!_throwInven.open)
		{
			_bombInven.y = _y3Slot;
		}
	}
	//Ư�� �������� �̵��ϵ��� (��ô ���� �κ��� ���� ���� ���� ����)
	if (_throwInven.open)
	{
		if (_y3Slot >= _bombInven.y)_bombInven.y++;
	}
//===================================

//������ ����� �ش� �������� �κ� ����&���� ���� ����
	//���� ������ �����
	for (int i = 0; i < _vInven.size(); i++)
	{
			switch (_vInven[i]->weapon)
			{
			case  WP_RAPIER:
				_attackInven.open = true;
				_throwInven.open = false;
				break;
			case  WP_LONG_SWORD:
				_attackInven.open = true;
				_throwInven.open = false;
				break;
			case  WP_BROAD_SWORD:
				_attackInven.open = true;
				_throwInven.open = false;
				break;
			case  WP_SPEAR:
				_attackInven.open = true;
				_throwInven.open = false;
				break;
			case  WP_DAGGER_1:
				_attackInven.open = true;
				_throwInven.open = true;
				break;
			case  WP_DAGGER_2:
				_attackInven.open = true;
				_throwInven.open = true;
				break;
			}
	//���� ������ �����
			switch (_vInven[i]->armor)
			{
			case A_TORCH_1:
				_torchInven.open = true;
				break;
			case A_TORCH_2:
				_torchInven.open = true;
				break;
			case A_TORCH_3:
				_torchInven.open = true;
				break;
			case A_ARMOR_1:
				_bodyInven.open = true;
				break;
			case A_ARMOR_2:
				_bodyInven.open = true;
				break;
			case A_ARMOR_3:
				_bodyInven.open = true;
				break;
			case A_ARMOR_4:
				_bodyInven.open = true;
				break;
			case A_SHOVEL:
				_shovelInven.open = true;
				break;
			}
	}
	
	for (int i = 0; i < _vInven.size(); i++)	//������ ���� ��� 
	{											//�κ��丮 ����&���� �������谡 ��߳��� �ʴ´�
	//�Һ� ������ �����
		switch (_vInven[i]->stuff)
		{
		case ST_APPLE:
			_itemInven.open = true;
			break;
		case ST_MEAT:
			_itemInven.open = true;
			break;
		case ST_CHEESE:
			_itemInven.open = true;
			break;

		}
	//�Һ� �������� �κ��丮�� ���� ��
		if (_vInven[i]->stuff == ST_MEAT ||			
			_vInven[i]->stuff == ST_CHEESE ||
			_vInven[i]->stuff == ST_APPLE)
		{
			break;									//�Һ� �������� ���� ���� �κ��丮 �����ϵ��� ����

		}
		else                           
		{
			_itemInven.open = false;                //�Һ� ������ �κ��丮�� �Һ� �������� ������ 
		}
	}
}

void UImanager::render()
{
	////���� �κ��丮 ����
	if(_shovelInven.open)_shovelInven.image->render(getMemDC(), _x1Slot, 5);
	if(_attackInven.open)_attackInven.image->render(getMemDC(), _attackInven.x, 5);
	if(_itemInven.open)_itemInven.image->render(getMemDC(), 20, _itemInven.y),_upLeft.image->render(getMemDC(), 30, _itemInven.y+60);
	if(_bombInven.open)_bombInven.image->render(getMemDC(), 20, _bombInven.y),_downLeft.image->render(getMemDC(), 30, _bombInven.y+60);
	if(_bodyInven.open)_bodyInven.image->render(getMemDC(), _bodyInven.x, _bodyInven.y);
	if(_headInven.open)_headInven.image->render(getMemDC(), _headInven.x, _headInven.y);
	if(_feetInven.open)_feetInven.image->render(getMemDC(), _feetInven.x, 5);
	if(_torchInven.open)_torchInven.image->render(getMemDC(), _torchInven.x, 5);
	if(_ringInven.open)_ringInven.image->render(getMemDC(), _ringInven.x, 5);
	if(_throwInven.open)_throwInven.image->render(getMemDC(), 20, _throwInven.y), _upDown.image->render(getMemDC(), 30, _throwInven.y + 60);
	//������ �κ��丮 ����
	_coinInven.image->render(getMemDC(), WINSIZEX - 125, 5);
	_daiaInven.image->render(getMemDC(), WINSIZEX - 125, 65);
	_scoreX->render(getMemDC(), WINSIZEX - 72, 30);
	_scoreX->render(getMemDC(), WINSIZEX - 72, 90);

	//��Ʈ �̹��� & �ִϸ��̼� ����
	for (int i = 0; i < 3; i++)
	{
		_heart[i].image->frameRender(getMemDC(), 573 + i * 60, 12, 0, 0);
		_heart[i].image->aniRender(getMemDC(), 600 + i * 60, 35, _heart[i].anime);
	}

	//���� ���ھ� ������ ����&����
	if (_coinvalue >= 1000)						//������ 1000�̻��� ���
	{
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 60, 20, _coinvalue / 1000 % 10, 0);	//ex)õ�� �ڸ� ���ڸ� õ���� ������
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 50, 20, _coinvalue / 100 % 10, 0);	//�� ���ڰ� 10 ���� ��� ��� �ǵ���
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 40, 20, _coinvalue / 10 % 10, 0);
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 30, 20, _coinvalue % 10, 0);
	}
	if (_coinvalue >= 100 && _coinvalue < 1000)
	{
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 60, 20, _coinvalue / 100 % 10, 0);
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 50, 20, _coinvalue / 10 % 10, 0);
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 40, 20, _coinvalue % 10, 0);
	}
	if (_coinvalue >= 10 && _coinvalue < 100)
	{
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 60, 20, _coinvalue / 10 % 10, 0);
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 50, 20, _coinvalue % 10, 0);
	}
	if (_coinvalue < 10)
	{
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 60, 20, _coinvalue % 10, 0);
	}
	
	//���̾� ���ھ� ������ ����&����
	if (_diavalue >= 1000)
	{
		_daiaNum->frameRender(getMemDC(), WINSIZEX - 60, 80, _diavalue / 1000 % 10, 0);
		_daiaNum->frameRender(getMemDC(), WINSIZEX - 50, 80, _diavalue / 100 % 10, 0);
		_daiaNum->frameRender(getMemDC(), WINSIZEX - 40, 80, _diavalue / 10 % 10, 0);
		_daiaNum->frameRender(getMemDC(), WINSIZEX - 30, 80, _diavalue % 10, 0);
	}
	if (_diavalue >= 100 && _diavalue < 1000)
	{
		_daiaNum->frameRender(getMemDC(), WINSIZEX - 60, 80, _diavalue / 100 % 10, 0);
		_daiaNum->frameRender(getMemDC(), WINSIZEX - 50, 80, _diavalue / 10 % 10, 0);
		_daiaNum->frameRender(getMemDC(), WINSIZEX - 40, 80, _diavalue % 10, 0);
	}
	if (_diavalue >= 10 && _diavalue < 100)
	{
		_daiaNum->frameRender(getMemDC(), WINSIZEX - 60, 80, _diavalue / 10 % 10, 0);
		_daiaNum->frameRender(getMemDC(), WINSIZEX - 50, 80, _diavalue % 10, 0);
	}
	if (_diavalue < 10)
	{
		_daiaNum->frameRender(getMemDC(), WINSIZEX - 60, 80, _diavalue % 10, 0);
	}

	//���� ������ ������ ���� ����
		for (int i = 0; i < _vInven.size(); i++)
		{
			switch (_vInven[i]->stuff)				//�Һ� ������ Ÿ��
			{
			case ST_APPLE:
				IMAGEMANAGER->findImage("stuffTiles")->frameRender(getMemDC(), _itemInven.x * i / i + 5, _itemInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
				break;
			case ST_MEAT:
				IMAGEMANAGER->findImage("stuffTiles")->frameRender(getMemDC(), _itemInven.x * i / i + 5, _itemInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
				break;
			case ST_CHEESE:
				IMAGEMANAGER->findImage("stuffTiles")->frameRender(getMemDC(), _itemInven.x * i / i + 5, _itemInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
				break;
			case ST_NONE:
				break;
			}

			switch (_vInven[i]->weapon)				//���� ������ Ÿ��
			{
			case  WP_RAPIER:
				IMAGEMANAGER->findImage("weaponTiles")->frameRender(getMemDC(), _attackInven.x + 5, _attackInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
			case  WP_LONG_SWORD:
				IMAGEMANAGER->findImage("weaponTiles")->frameRender(getMemDC(), _attackInven.x + 5, _attackInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
				break;
			case  WP_BROAD_SWORD:
				IMAGEMANAGER->findImage("weaponTiles")->frameRender(getMemDC(), _attackInven.x + 5, _attackInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
				break;
			case  WP_SPEAR:
				IMAGEMANAGER->findImage("weaponTiles")->frameRender(getMemDC(), _attackInven.x + 5, _attackInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
				break;
			case  WP_DAGGER_1:
				IMAGEMANAGER->findImage("weaponTiles")->frameRender(getMemDC(), _attackInven.x + 5, _attackInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
				IMAGEMANAGER->findImage("weaponTiles")->frameRender(getMemDC(), _throwInven.x + 5, _throwInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
				break;
			case  WP_DAGGER_2:
				IMAGEMANAGER->findImage("weaponTiles")->frameRender(getMemDC(), _attackInven.x + 5, _attackInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
				IMAGEMANAGER->findImage("weaponTiles")->frameRender(getMemDC(), _throwInven.x + 5, _throwInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
				break;
			}

			switch (_vInven[i]->armor)				//���� ������ Ÿ��
			{
			case A_TORCH_1:
				IMAGEMANAGER->findImage("armorTiles")->frameRender(getMemDC(), _torchInven.x * i / i + 5, _torchInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
				break;
			case A_TORCH_2:
				IMAGEMANAGER->findImage("armorTiles")->frameRender(getMemDC(), _torchInven.x * i / i + 5, _torchInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
				break;
			case A_TORCH_3:
				IMAGEMANAGER->findImage("armorTiles")->frameRender(getMemDC(), _torchInven.x * i / i + 5, _torchInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
				break;
			case A_ARMOR_1:
				IMAGEMANAGER->findImage("armorTiles")->frameRender(getMemDC(), _bodyInven.x * i / i + 5, _bodyInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
				break;
			case A_ARMOR_2:
				IMAGEMANAGER->findImage("armorTiles")->frameRender(getMemDC(), _bodyInven.x * i / i + 5, _bodyInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
				break;
			case A_ARMOR_3:
				IMAGEMANAGER->findImage("armorTiles")->frameRender(getMemDC(), _bodyInven.x * i / i + 5, _bodyInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
				break;
			case A_ARMOR_4:
				IMAGEMANAGER->findImage("armorTiles")->frameRender(getMemDC(), _bodyInven.x * i / i + 5, _bodyInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
				break;
			case A_SHOVEL:
				IMAGEMANAGER->findImage("armorTiles")->frameRender(getMemDC(), 20 + i * 5, 5 + 10, _vInven[i]->frameX, _vInven[i]->frameY);
				break;
			}

		}
	

}
