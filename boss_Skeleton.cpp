#include "stdafx.h"
#include "boss_Skeleton.h"

boss_Skeleton::boss_Skeleton()
{
}

boss_Skeleton::~boss_Skeleton()
{
}

HRESULT boss_Skeleton::init()
{
	return S_OK;
}

void boss_Skeleton::update()
{
	move();
	boss_Skeleton_ChangeAnimation();
	slave_Pos_Setting();
}

void boss_Skeleton::move()
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

void boss_Skeleton::boss_Skeleton_ChangeAnimation()
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

				// �÷��̾���� �Ÿ��� ����� ��� ���̷����� ���δ�.
				if (slave::_slave.b_Value.isClosePlayer)
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("skel_Left");
				}

				// �÷��̾���� �Ÿ��� �� ��� ���̷����� ������ ���� �̹����̴�.
				else
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sSkel_Left");
				}

				// ���̷����� �ش� ������ ���� ������ ������ �ʱ�ȭ���ش�.
				slave::_slave.operation.angle = PI;
				break;

			case SLAVE_DIRECTION::SD_RIGHT:

				// �÷��̾���� �Ÿ��� ����� ��� ���̷����� ���δ�.
				if (slave::_slave.b_Value.isClosePlayer)
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("skel_Right");
				}

				// �÷��̾���� �Ÿ��� �� ��� ���̷����� ������ ���� �̹����̴�.
				else
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sSkel_Right");
				}

				// ���̷����� �ش� ������ ���� ������ ������ �ʱ�ȭ���ش�.
				slave::_slave.operation.angle = 0;
				break;

			case SLAVE_DIRECTION::SD_UP: case SLAVE_DIRECTION::SD_DOWN:

				// ���̷����� ������ �ٶ󺸰� �ִٰ� �� �Ǵ� �Ʒ��� �ö� ���� ���
				if (slave::_slave.operation.angle == PI)
				{
					// �÷��̾���� �Ÿ��� ����� ��� ���̷����� ���δ�.
					if (slave::_slave.b_Value.isClosePlayer)
					{
						slave::_slave.image.animation = KEYANIMANAGER->findAnimation("skel_Left");
					}

					// �÷��̾���� �Ÿ��� �� ��� ���̷����� ������ ���� �̹����̴�.
					else
					{
						slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sSkel_Left");
					}
				}

				// ���̷����� �������� �ٶ󺸰� �ִٰ�  �� �Ǵ� �Ʒ��� �ö� ���� ���
				if (slave::_slave.operation.angle == 0)
				{
					// �÷��̾���� �Ÿ��� ����� ��� ���̷����� ���δ�.
					if (slave::_slave.b_Value.isClosePlayer)
					{
						slave::_slave.image.animation = KEYANIMANAGER->findAnimation("skel_Right");
					}

					// �÷��̾���� �Ÿ��� �� ��� ���̷����� ������ ���� �̹����̴�.
					else
					{
						slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sSkel_Right");
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


