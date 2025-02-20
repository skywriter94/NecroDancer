#include "stdafx.h"
#include "Enemy_Skeleton_Yellow.h"

void Enemy_Skeleton_Yellow::Action()
{
	if (_enemyInfo->HP <= 1)
	{
		AniChange();
	}
	switch (_enemyInfo->state)
	{
	case enemyState::STATE_IDLE:
		break;
	case enemyState::STATE_MOVE:
		if (_enemyInfo->beatCount >= 2)
		{
			if (_enemyInfo->HP > 1)
			{
				Move();
			}
			_enemyInfo->beatCount = 0;
		}
		break;
	case enemyState::STATE_ATTACK:
		if (_enemyInfo->beatCount >= 2)
		{
			_enemyInfo->attackEffect = true;
			_enemyInfo->beatCount = 0;
		}
		if (_enemyInfo->beatCount = 0)
		{
			_enemyInfo->attackEffect = false;
		}
			Attack();

		break;
	case enemyState::STATE_DIE:
		break;
	default:
		break;
	}
}
void Enemy_Skeleton_Yellow::AniChange()
{
	/*switch (_enemyInfo->direction)
	{
	case Direction::LEFT:
		if (_enemyInfo->Light)_enemyInfo->Animation = KEYANIMANAGER->findAnimation("skeleton_yellow_L_IDLE_Ani");
		else _enemyInfo->Animation = KEYANIMANAGER->findAnimation("skeleton_yellow_L_Shadow_IDLE_Ani");
		break;
	case Direction::RIGHT:
		if (_enemyInfo->Light)_enemyInfo->Animation = KEYANIMANAGER->findAnimation("skeleton_yellow_R_IDLE_Ani");
		else _enemyInfo->Animation = KEYANIMANAGER->findAnimation("skeleton_yellow_R_Shadow_IDLE_Ani");
		break;
	}*/
	if (_enemyInfo->HP <= 1)
	{
		_enemyInfo->Animation = KEYANIMANAGER->findAnimation("skeleton_yellow_RUNAWAY_Ani");
	}

	_enemyInfo->aniChange = true;
}
