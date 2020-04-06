#pragma once
#include "stdafx.h"

struct BOSS_STAGE_EFFECT_VECTOR
{
	image*		 img;			// �ѷ��� ����Ʈ �̹����� ��´�.
	RECT         rc;			// ��Ʈ ��ǥ
	POINTFLOAT	 center;		// ���� ��ǥ

	int			 Max_FrameX;	// �̹����� �ƽ� ������
};


enum class FIND_CHOICE_XY
{
	FC_XY,						// ����� ã��
	FC_X,						// x���� ã��
	FC_Y						// y���� ã��
};

enum class FIND_ANGLE
{
	FA_RT,						// 2��
	FA_TL,						// 10��
	FA_LB,						// 7��
	FA_BR						// 5��
};

enum class SHORT_XY
{
	SHORT_NONE,					// NULL
	SHORT_X,					// x�� ª��.
	SHORT_Y						// y�� ª��
};

struct BOSS_STAGE_OPEN
{
	bool	isOpen;				// ������ ������� ������ true�� �ٲ��.
	bool	isDoorOpen;			// �÷��̾ ���� ��������
	bool    startMoveImg;		// ���� �̹����� �����̱� �����Ѵ�.

	bool	main_OK;			// �̹����� �������� ���� �ߴٸ� ���� �ٲ��.
	bool	top_OK;				// �̹����� �������� ���� �ߴٸ� ���� �ٲ��.
	bool	bottom_OK;			// �̹����� �������� ���� �ߴٸ� ���� �ٲ��.

	int		image_Speed;		// �̹����� �����̴� �ӵ�

	image*	main_Img;			// ����� ����
	image*	top_Img;			// ����� ž 
	image*	bottom_Img;			// ����� ����
};