#include "stdafx.h"
#include "boss_Bat.h"

boss_Bat::boss_Bat()
{
}

boss_Bat::~boss_Bat()
{
}

HRESULT boss_Bat::init()
{


	return S_OK;
}

void boss_Bat::update()
{
	move();
	boss_Bat_ChangeAnimation();
	slave_Pos_Setting();
}

void boss_Bat::move()
{
	// �����̺��� ���갡 true�� ���ϸ�
	if (slave::_slave.b_Value.isMove)
	{
		switch (slave::get_Slave()->status.direction)
		{
		case SLAVE_DIRECTION::SD_LEFT:
			slave::_slave.pos.index.x--;
			break;

		case SLAVE_DIRECTION::SD_UP:
			slave::_slave.pos.index.y--;
			break;

		case SLAVE_DIRECTION::SD_RIGHT:
			slave::_slave.pos.index.x++;
			break;

		case SLAVE_DIRECTION::SD_DOWN:
			slave::_slave.pos.index.y++;
			break;
		}

		slave::_slave.b_Value.isMove = false;
	}
}

void boss_Bat::boss_Bat_ChangeAnimation()
{
	// ���⿡ ��ȭ�� ������ true�� ���� �־��ش�.
	if (slave::_slave.status.direction != slave::_slave.status.save_Direction)
	{
		// ���� ������ ��ȭ �Ҷ����� �̰��� ������ �ʴ´�.
		slave::_slave.status.save_Direction = slave::_slave.status.direction;
		slave::_slave.b_Value.isChangeAni = true;
		slave::_slave.b_Value.change_Ani = true;
	}

	// �÷��̾ ��ó�� �ְų� �ָ� ���ų� ���� ���� �Ǿ����� ���´�.
	if (slave::_slave.b_Value.isClosePlayer != slave::_slave.b_Value.save_ClosePlayer)
	{
		// ���� ��ȭ�� ���������� ������ �ʴ´�.
		slave::_slave.b_Value.save_ClosePlayer = slave::_slave.b_Value.isClosePlayer;
		slave::_slave.b_Value.isChangeAni = true;
		slave::_slave.b_Value.change_Ani = true;
	}

	// ���㰡 �ٶ󺸴� ���⿡ ���� �ִϸ��̼��� �ٲ��ش�.
	if (slave::_slave.b_Value.isChangeAni)	
	{
		switch (slave::_slave.status.direction)
		{
			case SLAVE_DIRECTION::SD_LEFT:

				// �÷��̾���� �Ÿ��� ����� ��� ���㰡 ���δ�.
				if (slave::_slave.b_Value.isClosePlayer)
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("bat_Left");
				}

				// �÷��̾���� �Ÿ��� �� ��� ������ ������ ���� �̹����̴�.
				else
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sBat_Left");
				}

				// ���㰡 �ش� ������ ���� ������ ������ �ʱ�ȭ���ش�.
				slave::_slave.operation.angle = PI;
				break;

			case SLAVE_DIRECTION::SD_RIGHT:

				// �÷��̾���� �Ÿ��� ����� ��� ���㰡 ���δ�.
				if (slave::_slave.b_Value.isClosePlayer)
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("bat_Right");
				}

				// �÷��̾���� �Ÿ��� �� ��� ������ ������ ���� �̹����̴�.
				else
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sBat_Right");
				}

				// ���㰡 �ش� ������ ���� ������ ������ �ʱ�ȭ���ش�.
				slave::_slave.operation.angle = 0;
				break;

			case SLAVE_DIRECTION::SD_UP: case SLAVE_DIRECTION::SD_DOWN:

				// ���㰡 ������ �ٶ󺸰� �ִٰ� �� �Ǵ� �Ʒ��� �ö� ���� ���
				if (slave::_slave.operation.angle == PI)
				{
					// �÷��̾���� �Ÿ��� ����� ��� ���㰡 ���δ�.
					if (slave::_slave.b_Value.isClosePlayer)
					{
						slave::_slave.image.animation = KEYANIMANAGER->findAnimation("bat_Left");
					}

					// �÷��̾���� �Ÿ��� �� ��� ������ ������ ���� �̹����̴�.
					else
					{
						slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sBat_Left");
					}
				}

				// ���㰡 �������� �ٶ󺸰� �ִٰ�  �� �Ǵ� �Ʒ��� �ö� ���� ���
				if (slave::_slave.operation.angle == 0)
				{
					// �÷��̾���� �Ÿ��� ����� ��� ���㰡 ���δ�.
					if (slave::_slave.b_Value.isClosePlayer)
					{
						slave::_slave.image.animation = KEYANIMANAGER->findAnimation("bat_Right"); 
					}

					// �÷��̾���� �Ÿ��� �� ��� ����� ������ ���� �̹����̴�.
					else
					{
						slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sBat_Right");
					}
				}

				break;
		}

		slave::_slave.b_Value.isChangeAni = false;		// ������ �����ӿ� ���� �ִϸ��̼��� �ٲ��־��ٸ�, ���� �����ӱ��� false�� �־ �ٽ� �ٲ��� �ʰ� �Ѵ�.
	}
	// ture�� ���϶� �ѹ��� ��ŸƮ ���ְ� �ٽ� false��
	if (slave::_slave.b_Value.change_Ani)
	{
		slave::_slave.b_Value.change_Ani = false;
		slave::_slave.image.animation->start();
	}
}




