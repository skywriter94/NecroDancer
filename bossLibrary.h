#pragma once
#include "stdafx.h"


// ���� ����
enum BOSSTYPE
{
	EMPTY,
	DEATH_METAL
};

// ���� ������ ����
enum BOSS_PHASESTATE	// ������ ������ ����
{
	BP_NORMAL,
	BP_PHASE_1,
	BP_PHASE_2,
	BP_PHASE_3,
	BP_PHASE_4
};

// ���� ���� ����
enum BOSS_DIRECTION		// ������ ����
{
	BD_LEFT,
	BD_UP,
	BD_RIGHT,
	BD_DOWN
};

// ������Ż �ǵ� ��ǥ�� ���� ������ ��°�
typedef struct tagThrowShield
{
	RECT			rc;					// ��Ʈ
	POINTFLOAT		center;				// ����
	image*			image;				// �ǵ� �̹����� ��´�.
	float			angle;				// ���ư��� ����
	float			speed;				// ���ư��� �ӵ�
	bool			isShieldUpdate;		// �ǵ� ��ġ ���� ����
	bool			isOut;				// �� ���� true��� ����
	BOSS_DIRECTION	direction;			// ������ �ٶ󺸴� ������ �����Ѵ�. (���⿡ ���� ���и� ������ ������ �ٸ���.)
}ThrowShield;

// ������ ���� �Լ�
struct tagBossJump
{
	float			 jumpPow;							// ���� ����
	float			 gravity;							// �߷� ����
	POINTFLOAT		 start;								// ���� ��ġ
	bool			 isJumping;							// �������̶�� true
};


struct BOSS_PHASE_SETTING_BOOL
{
	bool PHASE_1_Set;	// 1������ ������ �ߴٸ� true�� �ٲ۴�. (1���� �����ϱ� ���ؼ�)
	bool PHASE_2_Set;	// 2������ ������ �ߴٸ� true�� �ٲ۴�. (1���� �����ϱ� ���ؼ�)
	bool PHASE_3_Set;	// 3������ ������ �ߴٸ� true�� �ٲ۴�. (1���� �����ϱ� ���ؼ�)
	bool PHASE_4_Set;	// 4������ ������ �ߴٸ� true�� �ٲ۴�. (1���� �����ϱ� ���ؼ�)
};

// �������� ����ϴ� BOOL ���� ��Ƶ� ����ü
struct BOSS_BOOL
{
	BOSS_PHASE_SETTING_BOOL		PHASE_BOOL;

	bool						get_Beat;			// ���ڸ� �޾����� true�� ���Ѵ�.
	bool						boss_Die;			// ������ �׾��ٸ� true�� ���� ������.

	bool                        phase4_MoveX_Direction;			// ������� x�� �����̴���
	bool						phase4_MoveX_Direction_Find;	// ������ ã�Ҵ�.
	bool						phase4_MoveX_End;				// ������4���� x ��ǥ �̵��� ������.
	bool						phase4_MagicRangeSave;			// ���� ���� ���� �Ϸ�
};

struct BOSS_SUMMONS_SKILL
{
	bool						isCasting;		// ��ų ĳ����
	int							cTime;			// ��Ÿ��
	int							cTime_M;		// �ܽ�Ʈ ��Ÿ��

	int							rnd;			// ���� ��
};

struct BOSS_Magic_SKILL
{
	bool						isCasting;		// ��ų ĳ����
	int							cTime;			// ��Ÿ��
	int							cTime_M;		// �ܽ�Ʈ ��Ÿ��
};