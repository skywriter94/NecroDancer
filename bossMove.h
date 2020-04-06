#pragma once
#include "bossLibrary.h"



class bossMove
{
private:
	int			   move_Count;	// �̵� ������ ���� ī��Ʈ�� ����Ѵ�.(1���� �� �̵�, 2���� �� �̵�.. ���)
	
public:
	bossMove();
	~bossMove();

	float getMoveSpeed(float time, float distance);		// ���ϴ� �Ÿ��� ���ϴ� �ð��� �����Ϸ��� � ���ǵ�� �����ϴ��� ���� �� �ִ�.

	// ���ϴ� �Ÿ��� ���ϴ� �ð��� �����Ϸ��� � ���ǵ�� �����ϴ��� ���� �� �ִ�.
	// ������ �ӵ��� �̿��Ͽ� �÷��̾ ���ϴ� ������ �̵� ��Ų��.
	// ��ǥ �ð��� �����Ѵٸ� bool���� �ٲ㼭 �������ش�.
	void startMove(float* time, float* distance, float* angle, float* speed,
		float* worldTime, POINTFLOAT* _center, POINT* index, BOSS_DIRECTION direction, bool* Move);

	// ������ ������ �̿��Ͽ� ��� �������� �̵��� �ϴ����� ���� �� �ִ�.
	// ������ ���� x, y�� �̿��Ͽ� ��ġ ����� �Ѵ�.
	// ������ ���� �����ϴ��߿� �ʿ��� ������ �̿��Ѵ�. (�ӵ�, �߷� ��)
	void jumping(BOSS_DIRECTION* direction, POINTFLOAT* center, tagBossJump* jump);

	void			set_BossMoveCount(int value) { move_Count = value; }	// ���� ī���� ����
	int				get_BossMoveCount()  { return move_Count; }				// ���� ī���� ����
};

