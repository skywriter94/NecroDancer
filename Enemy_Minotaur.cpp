#include "stdafx.h"
#include "Enemy_Minotaur.h"
//
//HRESULT Enemy_Minotaur::init()
//{
//	_enemyInfo->image = IMAGEMANAGER->findImage("Enemy_minotaurL");
//	_enemyInfo->animation = KEYANIMANAGER->findAnimation("Minotaur_L_Shadow_IDLE_Ani");
//	return S_OK;
//}
//
//void Enemy_Minotaur::Move()
//{
//	//�� ���ڸ��� �����̸� 2�ܰ� ������ �μ� �� �ִ�. ���� �߿��� 3�ܰ� ���� �μ� �� �ִ�.
//	//�÷��̾�� x,y��ǥ�� �ϳ��� ���̶� �������� ������ �Ѵ�.
//	//���� �߿� �ٸ� ���ͳ� ���� �ε����� 2���ڰ� ���� �� ���� ���ڿ� �Ͼ �� ���� ���ں��� �����δ�.
//
//	//if(�÷��̾��� x = enemy�� x || �÷��̾��� y = enemy�� y) _enemyInfo->state=Direction::State_ATTACK;
//
//}
//
//void Enemy_Minotaur::AniChange()
//{
//	switch (_enemyInfo->direction)
//	{
//	case Direction::LEFT:
//		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Minotaur_L_IDLE_Ani");
//		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Minotaur_L_Shadow_IDLE_Ani");
//		break;
//	case Direction::RIGHT:
//		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Minotaur_R_IDLE_Ani");
//		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Minotaur_R_Shadow_IDLE_Ani");
//		break;
//	}
//}
