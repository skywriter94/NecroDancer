#pragma once
#include "stdafx.h"

// �����̺� ����
enum class SLAVE_TYPE
{
	SLAVE_BAT,
	SLAVE_GHOST,
	SLAVE_SKELETON,
	SLAVE_SKELETON_YELLOW,
	SLAVE_NONE
};

// �����̺� ����
enum class SLAVE_DIRECTION
{
	SD_LEFT,
	SD_UP,
	SD_RIGHT,
	SD_DOWN,
	SD_NONE
};

// �����̺��� ����
enum class SLAVE_STATE
{
	SS_NONE,										// ������ ���°� ����
	SS_STAY,										// �����̺�� ��� ����	(�÷��̾ ��Ʈ�� �ٶ� ������ ��Ʈ�� ��� ����, ������ ������ �ʴ´�)
	SS_PLAYER_ATTACK,								// �����̺갡 �÷��̾ �߰�
	SS_RUN											// �������� ����			(�ذ��� �Ӹ��� ��������� �ذ��� �÷��̾� �ݴ� �������� ���� ����)
};

// �����̺��� �ɷ�ġ
struct SLAVE_STATUS
{
	SLAVE_TYPE			type;						// �����̺��� Ÿ���� ��´�.
	SLAVE_DIRECTION		direction;					// �����̺갡 �ٶ󺸴� ������ ��´�.
	SLAVE_DIRECTION		save_Direction;				// �����̺� ���� ���̺� ����

	int					hp;							// �����̺��� ü���� ��´�.
	float				attack;						// �����̺��� ���ݷ��� ��´�.
};

// �����̺��� ��ǥ
struct SLAVE_POS
{
	RECT				rc;							// �����̺� ��Ʈ
	POINTFLOAT			center;						// �����̺� �߽� ��ǥ
	POINT				index;						// �����̺� Ÿ�� �ε��� 
};

// �����̺��� �̹���
struct SLAVE_IMAGE
{
	animation*			animation;					// �����̺��� �ִϸ��̼��� ��´�.
	image*				img;						// �����̺��� �̹����� ��´�.
};

// ���� ����
struct SLAVE_BOOL
{
	bool				isClosePlayer;				// �����̺� ��ó�� �÷��̾ �ִ��� ������ ����.
	bool				save_ClosePlayer;			// �����̺갡 ��ó�� �ִ��� ���̺긦 �Ѵ�.
	bool				isChangeAni;				// �������ٸ� �ִϸ��̼��� �ٲ�����Ѵ�.
	bool				change_Ani;					// �ִϸ��̼��� ü������ �������� ����
	bool				distanceCheck;				// �÷��̾�� �Ÿ� üũ 
	
	bool				ghostMoveStop;				// ��Ʈ ������ ����
	bool				ghostImgDirection;			// ��Ʈ �̹��� ����
	bool				ghostJonYha;				// ��Ʈ�� �����϶� �����̴�.

	bool				isMove;						// ���� ����

	bool				beat;						// ��Ʈ�� �޾Ҵٸ� ture

	bool				isAttack;					// ���� �����Ҷ� true

	bool				skelY_NoHead;				// ���ο� ���̷����� �Ӹ��� ������
	bool				noHead_NoMove;				// �Ӹ��� ������ �̵� �Ұ��� �������� ������
};

// �����̺��� ���� ����
struct SLAVE_OPERATION
{
	// Ÿ�� ������
	int					tile_SizeX, tile_SizeY;		// Ÿ���� ����� ��Ƶд�.

	// �̵�
	float				angle;						// �̵��� ���� ����
	int					move_Count;					// �̵� ī��Ʈ (�� ���ڸ��� �����̴���)
	int					save_Move_Count;			// �̵� ī��Ʈ�� ���� �� �д�.
	float				move_Time;					// ���� Ÿ�ϱ��� �̵��� �ɸ��� �ð�
	float				move_Speed;					// ���� Ÿ�ϱ��� �̵��ϴ� �ӵ�
	float				move_Distance;				// ���� Ÿ�ϱ����� �Ÿ�
	float				worldTime;					// ���� Ÿ��

	// ���̺��
	int					save_Hp;					// �����̺� ü�� �񱳿�

};



// ��������������������������������������� �����̺��� ���� ���������������������������������������������������
struct SLAVE_INFO
{
	SLAVE_STATUS		status;						// �����̺� �������ͽ�
	SLAVE_POS			pos;						// �����̺� ��ǥ
	SLAVE_IMAGE			image;						// �����̺� �̹���
	SLAVE_OPERATION		operation;					// �����̺� ����
	SLAVE_BOOL			b_Value;					// �����̺� bool�� 
				
};






// ��������������������������������������� �����̺��� �Լ� ���������������������������������������������������
class slaveLibrary
{

public:

	void slave_Reset(SLAVE_INFO* slave)												// �����̺��� ������ �⺻ ���·� �����.
	{
		// �������ͽ� �ʱ�ȭ
		slave->status.type = SLAVE_TYPE::SLAVE_NONE;
		slave->status.direction = SLAVE_DIRECTION::SD_NONE;
		slave->status.hp = 1;														// �⺻ ü���� 1 �̴�.
		slave->status.attack = 1.f;													// �⺻ ���ݷ��� 0.5f �̴�.

		// ��ǥ �ʱ�ȭ
		slave->pos.index.x = slave->pos.index.y = 0;								// �⺻ �ε����� 0�̴�.
		slave->pos.center.x = slave->pos.center.y = 0;								// �⺻ ������ 0�̴�.
		slave->pos.rc = RectMake(0, 0, 0, 0);										// �⺻ ��Ʈ�� 0�̴�.

		// ���� ���� �ʱ�ȭ
		slave->operation.angle = 0;													
		slave->operation.move_Count = 0;	
		slave->operation.save_Move_Count = 0;
		slave->operation.move_Distance = 0;											
		slave->operation.move_Speed = 0;											
		slave->operation.move_Time = 0.2f;											
		slave->operation.worldTime = 0;												
		slave->operation.tile_SizeX = TILESIZE;										
		slave->operation.tile_SizeY = TILESIZE;				

		// bool ���� �ʱ�ȭ
		slave->b_Value.change_Ani = false;
		slave->b_Value.isChangeAni = false;
		slave->b_Value.isClosePlayer = false;
		slave->b_Value.save_ClosePlayer = false;
		slave->b_Value.distanceCheck = false;
		slave->b_Value.isMove = false;
		slave->b_Value.isAttack = false;
		slave->b_Value.ghostMoveStop = false;
		slave->b_Value.ghostImgDirection = false;
		slave->b_Value.ghostJonYha = false;
		slave->b_Value.skelY_NoHead = false;

		// �̹���, �ִϸ��̼� �Ҵ�
		slave->image.img = new image;
		slave->image.animation = new animation;
	}




	void slave_Setting(SLAVE_INFO* slave, SLAVE_TYPE(type))							// �����̺��� Ÿ�Կ� �°� �������ͽ��� ������ش�.
	{

		switch (type)
		{
		case SLAVE_TYPE::SLAVE_BAT:
			slave->status.type = SLAVE_TYPE::SLAVE_BAT;								// �����̺��� Ÿ���� �����ش�.
			slave->status.direction = SLAVE_DIRECTION::SD_DOWN;						// �⺻ ������ �Ʒ��� ���Ѵ�.
			slave->status.hp = 1;													// �⺻ ü���� �����ش�.
			slave->image.img = IMAGEMANAGER->findImage("boss_Bat");					// �����̺��� �̹����� ã�Ƽ� �־��ش�.
			slave->image.animation = KEYANIMANAGER->findAnimation("sBat_Left");		// �����̺��� �ִϸ��̼��� ã�Ƽ� �־��ش�.
			slave->operation.move_Count = 3;										// �����̺��� �̵� ����
			slave->operation.save_Move_Count = 3;									// �����̺��� ���̺� ����
			
			break;

		case SLAVE_TYPE::SLAVE_GHOST:
			slave->status.type = SLAVE_TYPE::SLAVE_GHOST;							// �����̺��� Ÿ���� �����ش�.
			slave->status.direction = SLAVE_DIRECTION::SD_DOWN;						// �⺻ ������ �Ʒ��� ���Ѵ�.
			slave->status.hp = 1;													// �⺻ ü���� �����ش�.
			slave->image.img = IMAGEMANAGER->findImage("boss_Ghost");				// �����̺��� �̹����� ã�Ƽ� �־��ش�.
			slave->image.animation = KEYANIMANAGER->findAnimation("sGhost_Left");	// �����̺��� �ִϸ��̼��� ã�Ƽ� �־��ش�.
			slave->operation.move_Count = 1;										// �����̺��� �̵� ����
			slave->operation.save_Move_Count = 1;									// �����̺��� ���̺� ����

			break;

		case SLAVE_TYPE::SLAVE_SKELETON:
			slave->status.type = SLAVE_TYPE::SLAVE_SKELETON;						// �����̺��� Ÿ���� �����ش�.
			slave->status.direction = SLAVE_DIRECTION::SD_DOWN;						// �⺻ ������ �Ʒ��� ���Ѵ�.
			slave->status.hp = 1;													// �⺻ ü���� �����ش�.
			slave->image.img = IMAGEMANAGER->findImage("boss_Skeleton");			// �����̺��� �̹����� ã�Ƽ� �־��ش�.
			slave->image.animation = KEYANIMANAGER->findAnimation("sSkel_Left");		// �����̺��� �ִϸ��̼��� ã�Ƽ� �־��ش�.
			slave->operation.move_Count = 2;										// �����̺��� �̵� ����
			slave->operation.save_Move_Count = 2;									// �����̺��� ���̺� ����

			break;

		case SLAVE_TYPE::SLAVE_SKELETON_YELLOW:
			slave->status.type = SLAVE_TYPE::SLAVE_SKELETON_YELLOW;					// �����̺��� Ÿ���� �����ش�.
			slave->status.direction = SLAVE_DIRECTION::SD_DOWN;						// �⺻ ������ �Ʒ��� ���Ѵ�.
			slave->status.hp = 2;													// �⺻ ü���� �����ش�.
			slave->operation.save_Hp = 2;											// �ִ� ü��(�񱳿�)
			slave->image.img = IMAGEMANAGER->findImage("boss_Skeleton_Yellow");		// �����̺��� �̹����� ã�Ƽ� �־��ش�.
			slave->image.animation = KEYANIMANAGER->findAnimation("sSkelY_Left");	// �����̺��� �ִϸ��̼��� ã�Ƽ� �־��ش�.
			slave->operation.move_Count = 2;										// �����̺��� �̵� ����
			slave->operation.save_Move_Count = 2;									// �����̺��� ���̺� ����

			break;

		case SLAVE_TYPE::SLAVE_NONE:
			slave->status.type = SLAVE_TYPE::SLAVE_NONE;							// �����̺��� Ÿ���� �����ش�.
			slave->status.direction = SLAVE_DIRECTION::SD_DOWN;						// �⺻ ������ �Ʒ��� ���Ѵ�.
			slave->status.hp = 1;													// �⺻ ü���� �����ش�.
			slave->image.img = IMAGEMANAGER->findImage("boss_Bat");					// �����̺��� �̹����� ã�Ƽ� �־��ش�.
			slave->image.animation = KEYANIMANAGER->findAnimation("sBat_Left");		// �����̺��� �ִϸ��̼��� ã�Ƽ� �־��ش�.

			break;
		}

	}




	void pos_Setting(SLAVE_INFO* slave, int idx, int idy)					// �����̺��� ��ǥ �������� ������ش�.
	{
		// �ε��� �ʱ�ȭ
		slave->pos.index.x = idx;
		slave->pos.index.y = idy;

		// ��Ʈ �ʱ�ȭ
		slave->pos.rc = RectMake(idx * TILESIZE, idy * TILESIZE, TILESIZE, TILESIZE);

		// ���� �ʱ�ȭ
		slave->pos.center.x = (slave->pos.rc.left + slave->pos.rc.right) / 2;
		slave->pos.center.y = (slave->pos.rc.top + slave->pos.rc.bottom) / 2;
	}

};


