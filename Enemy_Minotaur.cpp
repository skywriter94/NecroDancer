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
//	//한 박자마다 움직이며 2단계 벽까지 부술 수 있다. 돌진 중에는 3단계 벽도 부술 수 있다.
//	//플레이어와 x,y좌표중 하나의 값이라도 같아지면 돌진을 한다.
//	//돌진 중에 다른 몬스터나 벽에 부딪히면 2박자간 기절 후 다음 박자에 일어나 그 다음 박자부터 움직인다.
//
//	//if(플레이어의 x = enemy의 x || 플레이어의 y = enemy의 y) _enemyInfo->state=Direction::State_ATTACK;
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
