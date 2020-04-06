#include "stdafx.h"
#include "Enemy_Slime_Orange.h"

void Enemy_Slime_Orange::Action()
{
	switch (_enemyInfo->state)
	{
	case enemyState::STATE_IDLE:
		break;
	case enemyState::STATE_MOVE:
		if (_enemyInfo->beatCount >= 1)
		{
			Move();
			_enemyInfo->beatCount = 0;
		}
		break;
	case enemyState::STATE_ATTACK:
		if (_enemyInfo->beatCount >= 1)
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
	//

}

void Enemy_Slime_Orange::Move()
{
	if (!_enemyInfo->Move)_enemyInfo->worldTimeCount = TIMEMANAGER->getWorldTime();
	_enemyInfo->Attack = false;
	//�� ���ڸ��� ������->�Ʒ�->����->�� ������ �ݺ��ϸ� �����δ�.
	switch (_enemyInfo->direction)
	{
	case Direction::RIGHT:
		//���������� �̵� (�̵� ��ο� �÷��̾ ������ ����)
		if (_enemyInfo->idx + 1 == _playerInfo->idx && _enemyInfo->idy == _playerInfo->idy)
		{
			//������ ����
			_enemyInfo->state = enemyState::STATE_ATTACK;
			_enemyInfo->AttackDirection = Direction::RIGHT;
			break;
		}
		//_enemyInfo->x += 52;
		_enemyInfo->idx += 1;

		
		enemyAngle();
		_enemyInfo->direction = Direction::DOWN;
		break;
	case Direction::DOWN:
		//�Ʒ��� �̵� (�̵� ��ο� �÷��̾ ������ ����)
		if (_enemyInfo->idx == _playerInfo->idx && _enemyInfo->idy + 1 == _playerInfo->idy)
		{
			//�Ʒ��� ����
			_enemyInfo->state = enemyState::STATE_ATTACK;
			_enemyInfo->AttackDirection = Direction::DOWN;
			break;
		}
		//_enemyInfo->y += 52;
		_enemyInfo->idy += 1;

		
		enemyAngle();
		_enemyInfo->direction = Direction::LEFT;
		break;
	case Direction::LEFT:
		//�������� �̵� (�̵� ��ο� �÷��̾ ������ ����)
		if (_enemyInfo->idx - 1 == _playerInfo->idx && _enemyInfo->idy == _playerInfo->idy)
		{
			//���� ����
			_enemyInfo->state = enemyState::STATE_ATTACK;
			_enemyInfo->AttackDirection = Direction::LEFT;
			break;
		}
		//_enemyInfo->x -= 52;
		_enemyInfo->idx -= 1;

		
		enemyAngle();
		_enemyInfo->direction = Direction::UP;
		break;
	case Direction::UP:
		//���� �̵� (�̵� ��ο� �÷��̾ ������ ����)
		if (_enemyInfo->idx == _playerInfo->idx && _enemyInfo->idy - 1 == _playerInfo->idy)
		{
			//���� ����
			_enemyInfo->state == enemyState::STATE_ATTACK;
			_enemyInfo->AttackDirection = Direction::UP;
			break;
		}
		//_enemyInfo->y -= 52;
		_enemyInfo->idy -= 1;
		enemyAngle();
		_enemyInfo->direction = Direction::RIGHT;
		break;
	}
	_enemyInfo->Move = true;
}

void Enemy_Slime_Orange::AniChange()
{
	if (_enemyInfo->Light)_enemyInfo->Animation = KEYANIMANAGER->findAnimation("Enemy_slime_orange_IDLE_Ani");
	else _enemyInfo->Animation = KEYANIMANAGER->findAnimation("Enemy_slime_orange_Shadow_IDLE_Ani");
	_enemyInfo->aniChange = true;
}
