#include "stdafx.h"
#include "Enemy_Slime_Blue.h"


void Enemy_Slime_Blue::Action()
{
	/*_enemyInfo->left = false;
	_enemyInfo->right = false;
	_enemyInfo->up = false;
	_enemyInfo->down = false;*/
	switch (_enemyInfo->state)
	{
	case enemyState::STATE_IDLE:
		break;
	case enemyState::STATE_MOVE:
		if (_enemyInfo->beatCount >= 2)
		{
			Move();
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
	}
	//
	
}

void Enemy_Slime_Blue::Move()
{
	if (!_enemyInfo->Move)_enemyInfo->worldTimeCount = TIMEMANAGER->getWorldTime();
	_enemyInfo->Attack = false;
	//�� ���ڸ��� �����̸� �� �Ʒ� 2���� Ÿ�ϸ��� �պ��ϸ� �����δ�. �̵� ��ο� ���� �ִٸ� ���ڸ� ������ �Ѵ�.
	switch (_enemyInfo->direction)
	{
	case Direction::UP:
		if (_enemyInfo->idy - 1 == _playerInfo->idy && _enemyInfo->idx == _playerInfo->idx)
		{
			_enemyInfo->state = enemyState::STATE_ATTACK;
			_enemyInfo->AttackDirection = Direction::UP;
			break;
		}
		//���� �̵�
		_enemyInfo->idy -= 1;
		
		enemyAngle();
		_enemyInfo->direction = Direction::DOWN;
		break;
	case Direction::DOWN:
		if (_enemyInfo->idy + 1 == _playerInfo->idy && _enemyInfo->idx == _playerInfo->idx)
		{
			_enemyInfo->state = enemyState::STATE_ATTACK;
			_enemyInfo->AttackDirection = Direction::DOWN;
			break;
		}
		//�Ʒ��� �̵�
		_enemyInfo->idy += 1;
		enemyAngle();
		_enemyInfo->direction = Direction::UP;

		break;
	}
	_enemyInfo->Move = true;
}


//void Enemy_Slime_Blue::Attack()
//{
//	switch (_enemyInfo->direction)
//	{
//	case Direction::UP:
//		_enemyInfo->attackImage = IMAGEMANAGER->findImage("Enemy_Attack_Up");
//		_enemyInfo->attackAnimation = KEYANIMANAGER->findAnimation("Enemy_Attack_UP_Ani");
//		_enemyInfo->Attack = true;
//		break;
//	case Direction::DOWN:
//		_enemyInfo->attackImage = IMAGEMANAGER->findImage("Enemy_Attack_Down");
//		_enemyInfo->attackAnimation = KEYANIMANAGER->findAnimation("Enemy_Attack_DOWN_Ani");
//		_enemyInfo->Attack = true;
//		break;
//	}
//	if (_enemyInfo->Attack)
//	{
//		_enemyInfo->attackAnimation->start();
//	}
//	_enemyInfo->state = enemyState::STATE_MOVE;
//}

void Enemy_Slime_Blue::AniChange()
{
	if (_enemyInfo->Light) _enemyInfo->Animation = KEYANIMANAGER->findAnimation("Enemy_slime_blue_IDLE_Ani");
	else _enemyInfo->Animation = KEYANIMANAGER->findAnimation("Enemy_slime_blue_Shadow_IDLE_Ani");
	_enemyInfo->aniChange = true;
}
