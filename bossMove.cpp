#include "stdafx.h"
#include "bossMove.h"

bossMove::bossMove()
{
}

bossMove::~bossMove()
{
}

float bossMove::getMoveSpeed(float time, float distance)
{
	float elapsedTime = TIMEMANAGER->getElapsedTime();

	// distance�� �Ÿ��� time��ŭ�� �ð��� ���� �����ϱ� ���� �ӵ����� �����ش�.
	float moveSpeed = (elapsedTime / time) * distance;

	return moveSpeed;
}

void bossMove::startMove(float* time, float* distance, float* angle, float* speed, 
	float* worldTime, POINTFLOAT* _center, POINT* index, BOSS_DIRECTION direction, bool* Move)
{
	float elapsedTime = TIMEMANAGER->getElapsedTime();

	// ���ϴ� �Ÿ��� �ش� �ð��� �����Ϸ��� ���� �ӵ��� �̵� �ؾ��ϴ��� ����� ���ش�.
	*speed = (elapsedTime / *time) * *distance;

	// ������������ ������ �ӵ��� ���缭 ���ϴ� �ð��� �����ϰ� �Ѵ�.
	(*_center).x = (*_center).x + cosf(*angle) * *speed;
	(*_center).y = (*_center).y + (-sinf(*angle) * *speed);


	// ���� �ش� �ð��� �����ߴٸ�
	if (*time + *worldTime <= TIMEMANAGER->getWorldTime())
	{
		//*worldTime = TIMEMANAGER->getWorldTime(); // ? �̰� ��?
	
		// ���⿡ �°� index�� ���� �������ش�.
		switch (direction)
		{
		case BD_LEFT:
			(*index).x--;
			break;
	
		case BD_UP:
			(*index).y--;
			break;
	
		case BD_RIGHT:
			(*index).x++;
			break;
	
		case BD_DOWN:
			(*index).y++;
			break;
		}

		// ��ġ �����ϰ�, Move�� ���ش�.
		(*_center).x = (*index).x * *distance + (*distance / 2);
		(*_center).y = (*index).y * *distance + (*distance / 2);
	
		*Move = false;
	}
}

void bossMove::jumping(BOSS_DIRECTION* direction, POINTFLOAT* center, tagBossJump* jump)
{
	if (!(*jump).isJumping)
	{

	}
}

