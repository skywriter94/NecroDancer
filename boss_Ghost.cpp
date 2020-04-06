#include "stdafx.h"
#include "boss_Ghost.h"

boss_Ghost::boss_Ghost()
{
}

boss_Ghost::~boss_Ghost()
{
}

HRESULT boss_Ghost::init()
{
	return S_OK;
}

void boss_Ghost::update()
{
	move();
	boss_Ghost_ChangeAnimation();
	slave_Pos_Setting();
}

void boss_Ghost::move()
{
	// �����̺��� ���갡 true�� ���ϸ�
	if (slave::_slave.b_Value.isMove)
	{
		switch (slave::_slave.status.direction)
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

void boss_Ghost::boss_Ghost_ChangeAnimation()
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

	// ������Ż�� �ٶ󺸴� ���⿡ ���� �ִϸ��̼��� �ٲ��ش�.
	if (slave::_slave.b_Value.isChangeAni)	// ������ �������ٸ� �ִϸ��̼��� �ٲ��־���Ѵ�.
	{
		switch (slave::_slave.status.direction)
		{
			case SLAVE_DIRECTION::SD_LEFT:

				// �÷��̾���� �Ÿ��� ����� ��� ��Ʈ�� ���δ�.
				if (slave::_slave.b_Value.isClosePlayer)
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("ghost_Left");
				}

				// �÷��̾���� �Ÿ��� �� ��� ��Ʈ�� ������ ���� �̹����̴�.
				else
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sGhost_Left");
				}

				// ��Ʈ�� �ش� ������ ���� ������ ������ �ʱ�ȭ���ش�.
				slave::_slave.operation.angle = PI;

				// 0�̶�� ����
				slave::_slave.b_Value.ghostImgDirection = 0;

				break;

			case SLAVE_DIRECTION::SD_RIGHT:

				// �÷��̾���� �Ÿ��� ����� ��� ��Ʈ�� ���δ�.
				if (slave::_slave.b_Value.isClosePlayer)
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("ghost_Right");
				}

				// �÷��̾���� �Ÿ��� �� ��� ��Ʈ�� ������ ���� �̹����̴�.
				else
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sGhost_Right");
				}

				// ��Ʈ�� �ش� ������ ���� ������ ������ �ʱ�ȭ���ش�.
				slave::_slave.operation.angle = 0;

				// 1�̶�� ������
				slave::_slave.b_Value.ghostImgDirection = 1;
				break;

			case SLAVE_DIRECTION::SD_UP: case SLAVE_DIRECTION::SD_DOWN:

				// ��Ʈ�� ������ �ٶ󺸰� �ִٰ� �� �Ǵ� �Ʒ��� �ö� ���� ���
				if (slave::_slave.operation.angle == PI)
				{
					// �÷��̾���� �Ÿ��� ����� ��� ��Ʈ�� ���δ�.
					if (slave::_slave.b_Value.isClosePlayer)
					{
						slave::_slave.image.animation = KEYANIMANAGER->findAnimation("ghost_Left");
					}

					// �÷��̾���� �Ÿ��� �� ��� ��Ʈ�� ������ ���� �̹����̴�.
					else
					{
						slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sGhost_Left");
					}
				}

				// ��Ʈ�� �������� �ٶ󺸰� �ִٰ�  �� �Ǵ� �Ʒ��� �ö� ���� ���
				if (slave::_slave.operation.angle == 0)
				{
					// �÷��̾���� �Ÿ��� ����� ��� ��Ʈ�� ���δ�.
					if (slave::_slave.b_Value.isClosePlayer)
					{
						slave::_slave.image.animation = KEYANIMANAGER->findAnimation("ghost_Right");
					}

					// �÷��̾���� �Ÿ��� �� ��� ��Ʈ�� ������ ���� �̹����̴�.
					else
					{
						slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sGhost_Right");
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




