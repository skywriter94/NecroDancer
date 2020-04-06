#include "stdafx.h"
#include "boss_Skeleton_Yellow.h"

boss_Skeleton_Yellow::boss_Skeleton_Yellow()
{
}

boss_Skeleton_Yellow::~boss_Skeleton_Yellow()
{
}

HRESULT boss_Skeleton_Yellow::init()
{
	return S_OK;
}

void boss_Skeleton_Yellow::update()
{
	move();
	boss_Skeleton_Yellow_ChangeAnimation();
	slave_Pos_Setting();
}

void boss_Skeleton_Yellow::move()
{
	// ���ο� ���̷����� �Ѵ� ������ �Ӹ��� ���ư� �����̴�.
	if (slave::get_Slave()->status.hp < 2)
	{
		// �Ӹ��� ���� ���¸� ���ش�.
		slave::get_Slave()->b_Value.skelY_NoHead = true;
	}

	// �����̺��� ���갡 true�� ���ϸ�
	if (slave::_slave.b_Value.isMove)
	{
		switch (slave::_slave.status.direction)
		{
		case SLAVE_DIRECTION::SD_LEFT:
			if(!slave::get_Slave()->b_Value.skelY_NoHead) slave::_slave.pos.index.x--;
			if (slave::get_Slave()->b_Value.skelY_NoHead) slave::_slave.pos.index.x++;
			break;

		case SLAVE_DIRECTION::SD_UP:
			if (!slave::get_Slave()->b_Value.skelY_NoHead) slave::_slave.pos.index.y--;
			if (slave::get_Slave()->b_Value.skelY_NoHead) slave::_slave.pos.index.y++;
			break;

		case SLAVE_DIRECTION::SD_RIGHT:
			if (!slave::get_Slave()->b_Value.skelY_NoHead) slave::_slave.pos.index.x++;
			if (slave::get_Slave()->b_Value.skelY_NoHead) slave::_slave.pos.index.x--;
			break;

		case SLAVE_DIRECTION::SD_DOWN:
			if (!slave::get_Slave()->b_Value.skelY_NoHead) slave::_slave.pos.index.y++;
			if (slave::get_Slave()->b_Value.skelY_NoHead) slave::_slave.pos.index.y--;
			break;
		}

		slave::_slave.b_Value.isMove = false;
	}
}

void boss_Skeleton_Yellow::boss_Skeleton_Yellow_ChangeAnimation()
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

	// �����̺� ü�� ��ȭ�� ���� ���
	if (slave::_slave.status.hp != slave::_slave.operation.save_Hp)
	{
		slave::_slave.b_Value.change_Ani = true;

		switch (slave::get_Slave()->status.direction)
		{
		case SLAVE_DIRECTION::SD_LEFT:
			// �÷��̾���� �Ÿ��� ����� ��� ��Ʈ�� ���δ�.
			if (slave::_slave.b_Value.isClosePlayer)
			{
				slave::_slave.image.animation = KEYANIMANAGER->findAnimation("skelY_Left_No");
			}

			// �÷��̾���� �Ÿ��� �� ��� ��Ʈ�� ������ ���� �̹����̴�.
			else
			{
				slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sSkelY_Left_No");
			}

			// ��Ʈ�� �ش� ������ ���� ������ ������ �ʱ�ȭ���ش�.
			slave::_slave.operation.angle = PI;

			break;

		case SLAVE_DIRECTION::SD_RIGHT:
			// �÷��̾���� �Ÿ��� ����� ��� ��Ʈ�� ���δ�.
			if (slave::_slave.b_Value.isClosePlayer)
			{
				slave::_slave.image.animation = KEYANIMANAGER->findAnimation("skelY_Right_No");
			}

			// �÷��̾���� �Ÿ��� �� ��� ��Ʈ�� ������ ���� �̹����̴�.
			else
			{
				slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sSkelY_Right_No");
			}

			// ��Ʈ�� �ش� ������ ���� ������ ������ �ʱ�ȭ���ش�.
			slave::_slave.operation.angle = 0;

			break;

		case SLAVE_DIRECTION::SD_UP:	case SLAVE_DIRECTION::SD_DOWN:
			// ��Ʈ�� ������ �ٶ󺸰� �ִٰ� �� �Ǵ� �Ʒ��� �ö� ���� ���
			if (slave::_slave.operation.angle == PI)
			{
				// �÷��̾���� �Ÿ��� ����� ��� ��Ʈ�� ���δ�.
				if (slave::_slave.b_Value.isClosePlayer)
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("skelY_Left_No");
				}

				// �÷��̾���� �Ÿ��� �� ��� ��Ʈ�� ������ ���� �̹����̴�.
				else
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sSkelY_Left_No");
				}
			}

			// ��Ʈ�� �������� �ٶ󺸰� �ִٰ�  �� �Ǵ� �Ʒ��� �ö� ���� ���
			if (slave::_slave.operation.angle == 0)
			{
				// �÷��̾���� �Ÿ��� ����� ��� ��Ʈ�� ���δ�.
				if (slave::_slave.b_Value.isClosePlayer)
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("skelY_Right_No");
				}

				// �÷��̾���� �Ÿ��� �� ��� ��Ʈ�� ������ ���� �̹����̴�.
				else
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sSkelY_Right_No");
				}
			}

			break;
		}
	}

	// ������Ż�� �ٶ󺸴� ���⿡ ���� �ִϸ��̼��� �ٲ��ش�.
	if (slave::_slave.b_Value.isChangeAni && !slave::_slave.b_Value.skelY_NoHead)	// ������ �������ٸ� �ִϸ��̼��� �ٲ��־���Ѵ�.
	{
		switch (slave::_slave.status.direction)
		{
			case SLAVE_DIRECTION::SD_LEFT:

				// �÷��̾���� �Ÿ��� ����� ��� ��Ʈ�� ���δ�.
				if (slave::_slave.b_Value.isClosePlayer)
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("skelY_Left");
				}

				// �÷��̾���� �Ÿ��� �� ��� ��Ʈ�� ������ ���� �̹����̴�.
				else
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sSkelY_Left");
				}

				// ��Ʈ�� �ش� ������ ���� ������ ������ �ʱ�ȭ���ش�.
				slave::_slave.operation.angle = PI;
				break;

			case SLAVE_DIRECTION::SD_RIGHT:

				// �÷��̾���� �Ÿ��� ����� ��� ��Ʈ�� ���δ�.
				if (slave::_slave.b_Value.isClosePlayer)
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("skelY_Right");
				}

				// �÷��̾���� �Ÿ��� �� ��� ��Ʈ�� ������ ���� �̹����̴�.
				else
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sSkelY_Right");
				}

				// ��Ʈ�� �ش� ������ ���� ������ ������ �ʱ�ȭ���ش�.
				slave::_slave.operation.angle = 0;
				break;

			case SLAVE_DIRECTION::SD_UP: case SLAVE_DIRECTION::SD_DOWN:

				// ��Ʈ�� ������ �ٶ󺸰� �ִٰ� �� �Ǵ� �Ʒ��� �ö� ���� ���
				if (slave::_slave.operation.angle == PI)
				{
					// �÷��̾���� �Ÿ��� ����� ��� ��Ʈ�� ���δ�.
					if (slave::_slave.b_Value.isClosePlayer)
					{
						slave::_slave.image.animation = KEYANIMANAGER->findAnimation("skelY_Left");
					}

					// �÷��̾���� �Ÿ��� �� ��� ��Ʈ�� ������ ���� �̹����̴�.
					else
					{
						slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sSkelY_Left");
					}
				}

				// ��Ʈ�� �������� �ٶ󺸰� �ִٰ�  �� �Ǵ� �Ʒ��� �ö� ���� ���
				if (slave::_slave.operation.angle == 0)
				{
					// �÷��̾���� �Ÿ��� ����� ��� ��Ʈ�� ���δ�.
					if (slave::_slave.b_Value.isClosePlayer)
					{
						slave::_slave.image.animation = KEYANIMANAGER->findAnimation("skel_Right");
					}

					// �÷��̾���� �Ÿ��� �� ��� ��Ʈ�� ������ ���� �̹����̴�.
					else
					{
						slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sSkelY_Right");
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

